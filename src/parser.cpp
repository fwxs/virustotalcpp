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

    void results()
    {
        if(json_scan_results["response_code"].asInt() == 1)
        {
            malware_results();
        }
        else
        {
            std::cout << "[+] File hash: " << json_scan_results["resource"].asString() << '\n';
            std::cout << "[+] Message: " << json_scan_results["verbose_msg"].asString() << std::endl;
        }
    }

    void malware_results()
    {
        std::cout << "[+] Scan rate: " << get_scan_rate() << '\n';
        std::cout << "[+] First time the file was scanned: " << json_scan_results["scan_date"].asString() << '\n';
        std::cout << "[+] AVs used" << '\n';

        Json::Value scans = json_scan_results["scans"];

        for(Json::ValueConstIterator outer_iterator = scans.begin(); outer_iterator != scans.end(); outer_iterator++)
        {
            std::cout << "\t[+] " << outer_iterator.name() << '\n';
            for(Json::ValueConstIterator inner_iterator = (*outer_iterator).begin(); inner_iterator != (*outer_iterator).end(); inner_iterator++)
            {
                std::string key_value = (*inner_iterator).asString();

                if(key_value.empty())
                    continue;

                std::cout << "\t ---> " << inner_iterator.name() << ": " << key_value << '\n';
            }
            std::cout << '\n';
        }
    }

    float get_scan_rate()
    {
        return (json_scan_results["positives"].asFloat() * PERCENT) / json_scan_results["total"].asFloat();
    }
}
