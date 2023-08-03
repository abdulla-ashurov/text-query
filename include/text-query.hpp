/*
Tasks:
    1. It must allow the user to indicate the name of a file to process.
    The program will store the contents of the file so that we can 
    display the original line in which each word appears.
    2. The program must break each line into words and remember all the
    lines in which each word appears. When it prints the line numbers,
    they should be presented in ascending order and contain no duplicates.
    3. The result of querying for a particular word should be the line 
    numbers on which that word appeared.
    4. To print the text in which the word appeared, it must be possible to
    fetch the line from the input file corresponding to a given line number.
*/ 


#ifndef __TEXT_QUERY_HPP__
#define __TEXT_QUERY_HPP__

#include <iostream>
#include <fstream>
#include <vector>

class TextQuery {
private:
    std::vector<std::string> lines;
public:
    void read_file(const std::string &&path) {
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
    
    std::vector<size_t> query(const std::string &&word) const {
        std::vector<size_t> lines_number;
        for (size_t i = 0; i < lines.size(); i++)
            if (lines[i].find(word) != std::string::npos)
                lines_number.push_back(i);
        
        return lines_number;
    }

    void print(std::vector<size_t> &lines_number) const {
        std::cout << "line occurs: " << lines_number.size() << " times\n";
        for (size_t i = 0; i < lines_number.size(); i++) {
            std::cout << "\t(line " << lines_number[i] << ") "
                      << lines[lines_number[i]] << std::endl;
        }
    }
};

#endif
