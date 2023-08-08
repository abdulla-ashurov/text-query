#ifndef __QUERY_HPP__
#define __QUERY_HPP__

#include <vector>
#include "text-query.hpp"

class BaseQuery {
public:
    virtual std::vector<size_t> run(const TextQuery &file) const = 0;
    virtual ~BaseQuery() {};
};

class WordQuery;
class NotWordQuery;
class OrWordQuery;
class AndWordQuery;

class Query {
private:
    std::shared_ptr<BaseQuery> base;
    std::string word;

    explicit Query(const std::shared_ptr<BaseQuery> &base) : base(base) {}
public:
    explicit Query(const std::string &word)
        : word(word), base(new WordQuery(word)) {}

    std::vector<size_t> run(const TextQuery &file) const {
        return base->run(file);
    }

    friend Query operator~(const Query &query);
    friend Query operator|(const Query &left_query, const Query &right_query);
    friend Query operator&(const Query &left_query, const Query &right_query);
};

inline Query operator~(const Query &query) {
    return Query(std::shared_ptr<BaseQuery>(new NotWordQuery(query)));
}

inline Query operator|(const Query &left_query, const Query &right_query) {
    return Query(std::shared_ptr<BaseQuery>(new OrWordQuery(left_query, right_query)));
}

inline Query operator&(const Query &left_query, const Query &right_query) {
    return Query(std::shared_ptr<BaseQuery>(new AndWordQuery(left_query, right_query)));
}

class WordQuery : public BaseQuery {
private:
    std::string query_word;

public:
    WordQuery(const std::string &query_word) : query_word(query_word) {}

    std::vector<size_t> run(const TextQuery &file) const {
        std::vector<std::string> lines = file.get_lines();
        
        std::vector<size_t> lines_number;
        for (size_t i = 0; i < lines.size(); i++) {
            if (lines[i].find(query_word) != std::string::npos) {
                lines_number.push_back(i);
            }
        }

        return lines_number;
    }
};

class NotWordQuery : public BaseQuery {
private:
    const Query query;
public:
    NotWordQuery(const Query &query) : query(query) {}

    std::vector<size_t> run(const TextQuery &file) const {
        std::vector<size_t> match_lines = query.run(file);

        std::vector<size_t> not_matched_lines;
        for (size_t line = 0; line < file.get_lines().size(); line++) {
            if (std::find(match_lines.begin(), match_lines.end(), line) == match_lines.end()) {
                not_matched_lines.push_back(line);
            }
        }

        return not_matched_lines;
    }
};

class BinaryQuery : public BaseQuery {
protected:
    const Query left_query;
    const Query right_query;
public:
    BinaryQuery(const Query &left_query, const Query &right_query)
        : left_query(left_query), right_query(right_query) {}
    std::vector<size_t> run(const TextQuery &file) const = 0;
};

class OrWordQuery : public BinaryQuery {
public:
    OrWordQuery(const Query &left_query, const Query &right_query)
        : BinaryQuery(left_query, right_query) {}
    
    std::vector<size_t> run(const TextQuery &file) const {
        std::vector<size_t> left_result = left_query.run(file);
        std::vector<size_t> right_result = right_query.run(file);

        left_result.insert(left_result.end(), right_result.begin(), right_result.end());

        return left_result;
    }
};

class AndWordQuery : public BinaryQuery {
public:
    AndWordQuery(const Query &left_query, const Query &right_query)
        : BinaryQuery(left_query, right_query) {}

    std::vector<size_t> run(const TextQuery &file) const {
        std::vector<size_t> left_result = left_query.run(file);
        std::vector<size_t> right_result = right_query.run(file);

        std::vector<size_t> result;
        for (size_t i = 0; i < left_result.size(); i++) {
            if (std::find(right_result.begin(), right_result.end(), left_result[i]) != right_result.end()) {
                result.push_back(left_result[i]);
            }
        }

        return result;
    }
};

#endif /* __QUERY_HPP__ */
