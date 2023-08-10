#ifndef __TEXT_QUERY_HPP__
#define __TEXT_QUERY_HPP__

#include <fstream>

class TextQuery {
private:
    std::vector<std::string> lines;

    void read_file(const std::string &path) {
        std::ifstream in(path);
        if (!in.is_open())
            throw std::runtime_error("Couldn't open file: " + path);
        
        if (!lines.empty())
            lines.clear();

        std::string line;
        while (std::getline(in, line))
            lines.push_back(line);
        
        in.close();
    }

public:
    explicit TextQuery(const std::string &path) {
        read_file(path);
    }

    const std::vector<std::string>& get_lines() const {
        return lines;
    }
};

#endif
