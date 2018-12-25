#include "include/hasher.hpp"

namespace Hasher {
    /* Code based on https://stackoverflow.com/questions/17156282/passing-a-stdarray-of-unknown-size-to-a-function (Ans by Andy Prowl)*/
    template<std::size_t SIZE>
    std::string hash_hex(const std::array<unsigned char, SIZE> &hash)
    {
        std::stringstream ss;
        for (unsigned int inx = 0; inx < SIZE; ++inx)
        {
            ss << std::hex << std::setw(2) << std::setfill('0') << (uint)hash[inx];
        }
        return ss.str();
    }

    /* Code based on https://stackoverflow.com/questions/2262386/generate-sha256-with-openssl-and-c (Edited by: Jonathan Drapeau) */
    std::string calculate_sha256(const std::unique_ptr<std::string> &msg)
    {
        std::array<unsigned char, SHA256_DIGEST_LENGTH> hash;
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, msg->c_str(), msg->length());
        SHA256_Final(hash.data(), &sha256);
        return hash_hex<SHA256_DIGEST_LENGTH>(hash);
    }

    std::string calculate_sha1(const std::unique_ptr<std::string> & msg)
    {
        std::array<unsigned char, SHA_DIGEST_LENGTH> hash;
        SHA_CTX sha;

        SHA1_Init(&sha);
        SHA1_Update(&sha, msg->c_str(), SHA_DIGEST_LENGTH);
        SHA1_Final(hash.data(), &sha);

        return hash_hex<SHA_DIGEST_LENGTH>(hash);
    }

    std::string calculate_md5(const std::unique_ptr<std::string> &msg){
        std::array<unsigned char, MD5_DIGEST_LENGTH> hash;
        MD5_CTX md5;
        MD5_Init(&md5);
        MD5_Update(&md5, msg->c_str(), msg->length());
        MD5_Final(hash.data(), &md5);
        return hash_hex<MD5_DIGEST_LENGTH>(hash);
    }

    File::File(const std::string &f) : pathname(f)
    {
        this->ifile_stream.open(pathname, std::ios::in | std::ios::binary);
        if(!this->ifile_stream.is_open())
            throw std::runtime_error("Can't open " + pathname);
    }

    File::~File()
    {
        if(ifile_stream.is_open())
            ifile_stream.close();
    }
}
