#include <fstream>
#include <iostream>
#include <json/json.h>
#include <string>
#include "include/parser.hpp"

namespace Parser {
    static Json::Value json_scan_results;
    const unsigned short PERCENT = 100;

    void load(const std::string &filename)
    {
        std::ifstream json_file(filename, std::ifstream::binary);
        Json::CharReaderBuilder reader_builder;
        std::string error;
        if(!Json::parseFromStream(reader_builder, json_file, &json_scan_results, &error))
            throw Parser::JsonException(error);
    }

    float get_scan_results()
    {
        return (json_scan_results["positives"].asFloat() * PERCENT) / json_scan_results["total"].asFloat();
    }
}
