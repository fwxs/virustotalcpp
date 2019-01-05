#include "include/parser.hpp"

namespace Parser {
    static Json::Value json_scan_results;
    const unsigned short PERCENT = 100;

    void load(std::unique_ptr<std::string> &json_response)
    {
        std::stringstream ss(*json_response);
        Json::CharReaderBuilder reader_builder;
        std::string error;

        if(!Json::parseFromStream(reader_builder, ss, &json_scan_results, &error))
            throw Parser::JsonException(error);
    }

    void print_results()
    {
        std::cout << "Scan rate: " << get_scan_results() << '\n';
        std::cout << "First time the file was scanned: " << json_scan_results["scan_date"].asString() << '\n';
        std::cout << "AVs used" << '\n';

        Json::Value scans = json_scan_results["scans"];

        for(Json::ValueConstIterator outer_iterator = scans.begin(); outer_iterator != scans.end(); outer_iterator++)
        {
            std::cout << "[*] " << outer_iterator.name() << '\n';
            for(Json::ValueConstIterator inner_iterator = (*outer_iterator).begin(); inner_iterator != (*outer_iterator).end(); inner_iterator++)
            {
                std::cout << " +---> " << inner_iterator.name() << ": " << (*inner_iterator).asString() << '\n';
            }
            std::cout << '\n';
        }
    }

    float get_scan_results()
    {
        return (json_scan_results["positives"].asFloat() * PERCENT) / json_scan_results["total"].asFloat();
    }
}
