#include "include/requester.hpp"

namespace Requester {

    static char error_buffer[CURL_ERROR_SIZE];
    static std::string wbuffer;

    static size_t writer(char *data, size_t size, size_t nmemb, std::string *writer_data)
    {
        if(writer_data == nullptr)
            return 0;

        writer_data->append(data, size * nmemb);
        return size * nmemb;
    }

    std::string set_url(const std::string &api_key, const std::string &hash)
    {
        return VIRUS_TOTAL_REPORT_URL + "apikey=" + api_key + "&resource=" + hash;
    }

    void get_data(const std::string url) noexcept(false)
    {
        CURLcode code;
        curl_global_init(CURL_GLOBAL_DEFAULT);
        curl_obj = std::make_unique<CURL *>(curl_easy_init());

        if(curl_obj == nullptr)
            throw std::runtime_error("Libcurl couldn't be initialized.");

        if((code = curl_easy_setopt(*curl_obj, CURLOPT_URL, url.c_str())) != CURLE_OK)
            throw std::runtime_error("Failed setting URL.");

        std::memset(error_buffer, 0, CURL_ERROR_SIZE);
        if((code = curl_easy_setopt(*curl_obj, CURLOPT_ERRORBUFFER, error_buffer)) != CURLE_OK)
            throw std::runtime_error("Failed setting URL.");

        if((code = curl_easy_setopt(*curl_obj, CURLOPT_WRITEFUNCTION, Requester::writer)) != CURLE_OK)
            throw std::runtime_error("Failed writing data to buffer");

        if((code = curl_easy_setopt(*curl_obj, CURLOPT_WRITEDATA, &wbuffer)) != CURLE_OK)
            throw std::runtime_error("Failed writing data to buffer");

         if((code = curl_easy_perform(*curl_obj)) != CURLE_OK)
             throw std::runtime_error("curl_easy_perform");

         curl_easy_cleanup(*curl_obj);
    }

    std::unique_ptr<std::string> get_write_buffer()
    {
        return std::make_unique<std::string>(wbuffer);
    }
}
