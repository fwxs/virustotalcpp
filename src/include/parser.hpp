#ifndef PARSER_HPP
#define PARSER_HPP
#include <exception>
#include <string>

namespace Parser {

    void load(const std::string &);
    float get_scan_results();
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
