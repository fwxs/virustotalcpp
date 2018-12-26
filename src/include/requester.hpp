#ifndef REQUESTER_HPP
#define REQUESTER_HPP
#include <cstring>
#include <curl/curl.h>
#include <iostream>
#include <memory>
#include <string>

namespace Requester {
     const std::string VIRUS_TOTAL_REPORT_URL = "https://www.virustotal.com/vtapi/v2/file/report?";
     namespace
     {
         static size_t writer(char *, size_t, size_t, std::string *);
     }
     static std::unique_ptr<CURL *> curl_obj;

     std::string set_url(const std::string&, const std::string &);
     void get_data(const std::string)  noexcept(false);
     std::unique_ptr<std::string> get_write_buffer();
}

#endif // REQUESTER_HPP
