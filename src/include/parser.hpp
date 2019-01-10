#ifndef PARSER_HPP
#define PARSER_HPP
#include "hasher.hpp"
#include <exception>
#include <fstream>
#include <iostream>
#include <json/json.h>
#include <string>
#include <unistd.h>

namespace Parser {

    void load(std::unique_ptr<std::string> &);
    void results();
    void malware_results();
    float get_scan_rate();


    class JsonException : public std::exception
    {
        private:
            const std::string msg;

        public:
            JsonException(const std::string &m) : msg(m) {}
            const char* what() const noexcept
            {
                return msg.c_str();
            }
    };
}

#endif // PARSER_HPP
