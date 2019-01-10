#ifndef HASHER_HPP
#define HASHER_HPP
#include <array>
#include <cstring>
#include <cerrno>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <memory>
#include <openssl/evp.h>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>


namespace Hasher {

    template<std::size_t SIZE>
    std::string hash_hex(const std::array<unsigned char, SIZE> &, const uint);

    std::string calculate_hash(const std::unique_ptr<std::string> &, const std::string &);

    class Exception : public std::exception{
        private:
            const std::string msg;
            const int error_code;

        public:
            Exception(const std::string &m, const int err) : msg(m), error_code(err) {}
            const char* what() const noexcept{
                return msg.c_str();
            }

            const int code() const noexcept{
                return error_code;
            }
    };

    class File {
        private:
            std::string pathname;
            std::ifstream ifile_stream;

        public:
            File(const std::string &);

             /**
             * Use the *nix stat function to check if the file exists.
             */
            inline bool exists(){
                struct stat st_buff;
                std::memset(&st_buff, 0, sizeof (struct stat));
                return (stat(pathname.c_str(), &st_buff) == 0);
            }

            inline off_t size(){
                struct stat f_stat;
                std::memset(&f_stat, 0, sizeof (struct stat));

                if(stat(pathname.c_str(), &f_stat) == -1){
                    int errsv = errno;
                    throw Hasher::Exception(std::strerror(errsv), errsv);
                }

                return f_stat.st_size;
            }

            /* Code taken from https://insanecoding.blogspot.com/2011/11/how-to-read-in-file-in-c.html */
            inline std::unique_ptr<std::string> read()
            {
                // Return a unique pointer to a string filled with the file data.
                return std::make_unique<std::string>(std::string(std::istreambuf_iterator<char>(ifile_stream), {}));
            }

            // Wanted to know how to make a lambda function...
            std::string filename = [this]()
            {
                // Get the last pathname separator ('/' on *nix).
                size_t inx = pathname.find_last_of('/');
                // Return the filename (not the pathname) if the index of the pathname isn't -1, if it does return pathname.
                return (inx != pathname.npos) ? pathname.substr(inx + 1) : pathname;
            }();

            ~File();
    };
}
#endif // HASHER_HPP
