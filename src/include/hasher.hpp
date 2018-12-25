#ifndef HASHER_HPP
#define HASHER_HPP
#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <memory>
#include <openssl/sha.h>
#include <openssl/md5.h>
#include <sstream>
#include <string>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>


namespace Hasher {
    std::string calculate_sha256(const std::unique_ptr<std::string> &);
    std::string calculate_sha1(const std::unique_ptr<std::string> &);
    std::string calculate_md5(const std::unique_ptr<std::string> &);

    template<std::size_t SIZE>
    std::string hash_hex(const std::vector<unsigned char> &);

    class File {
        private:
            std::string pathname;
            std::ifstream ifile_stream;

        public:
            File(const std::string &);

            /* Code taken from https://insanecoding.blogspot.com/2011/11/how-to-read-in-file-in-c.html */
            inline std::unique_ptr<std::string> read()
            {
                return std::make_unique<std::string>(std::string(std::istreambuf_iterator<char>(ifile_stream), {}));
            }

            std::string filename = [this]()
            {
                size_t inx = pathname.find_last_of('/');
                return (inx != pathname.npos) ? pathname.substr(inx + 1) : pathname;
            }();

            ~File();
    };
}
#endif // HASHER_HPP
