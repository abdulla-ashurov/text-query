#ifndef __QUERY_HPP__
#define __QUERY_HPP__

#include "text-query.hpp"

class Query {
public:
    Query(const std::string &&word);

    const Query& operator~() const;
    std::vector<size_t> run(const TextQuery &file) const;
};

Query operator|(const Query &q1, const Query &q2);
Query operator&(const Query &q1, const Query &q2);

#endif /* __QUERY_HPP__ */
