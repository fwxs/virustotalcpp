#include "include/hasher.hpp"

namespace Hasher {
    /* Code based on https://stackoverflow.com/questions/17156282/passing-a-stdarray-of-unknown-size-to-a-function (Ans by Andy Prowl)*/
    template<std::size_t SIZE>
    std::string hash_hex(const std::array<unsigned char, SIZE> &hash, const uint bytes_written)
    {
        // Create a stringstream to store the string version of the provided hash.
        std::stringstream ss;
        // Create a readable hash string, iterating through each byte of the array.
        for (unsigned int inx = 0; inx < bytes_written; ++inx)
        {
            ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<uint>(hash[inx]);
        }
        return ss.str();
    }

    /**
      Get the message hash:
      1 - Create an unsigned array of 32 (SHA 256), 20 (SHA1) or MD5(16) bytes
      2 - Initiate a [SHA256, SHA, MD5]_CTX structure to save the updated hash on it.
      3 - Calculate the hash.
      4 - Store the calculated hash on the u_char array.

      @param msg: A unique ptr tp the message to hash.
      @param digest_name: Name of the hash function.
    **/
    std::string calculate_hash(const std::unique_ptr<std::string> &msg, const std::string &digest_name)
    {
        // Use the Openssl API to convert the provided hash function name to an EVP_MD struct
        auto md = std::make_unique<const EVP_MD *>(EVP_get_digestbyname(digest_name.c_str()));

        // Check if the EVP_MD is valid.
        if(*md == nullptr){
            throw Hasher::Exception(digest_name + " doesn't exists.", EXIT_FAILURE);
        }

        // Init an array of 'HF_BLOCK_SIZE' bytes.
        std::array<unsigned char, EVP_MAX_MD_SIZE> hash;
        // Create an EVP_MD_CTX context, to store the hash on it.
        auto mdctx = std::make_unique<EVP_MD_CTX *>(EVP_MD_CTX_new());

        EVP_DigestInit_ex(*mdctx, *md, nullptr);
        EVP_DigestUpdate(*mdctx, msg->c_str(), msg->length());

        unsigned int bytes_written;

        EVP_DigestFinal_ex(*mdctx, hash.data(), &bytes_written);
        EVP_MD_CTX_free(*mdctx);

        return hash_hex<hash.size()>(hash, bytes_written);
    }

    File::File(const std::string &f) : pathname(f)
    {
        // Check if file exists.
        if(!File::exists())
        {
            int errsv = errno;
            throw Hasher::Exception( pathname + " " + std::strerror(errsv), errsv);
        }

        // Open the specified file with the binary flag.
        this->ifile_stream.open(pathname, std::ios::in | std::ios::binary);

        // Check for errors while opening the file.
        if(!this->ifile_stream.is_open())
        {
            throw Hasher::Exception(std::string("Can't open ") + filename, EXIT_FAILURE);
        }
    }

    File::~File()
    {
        // Close the existing stream.
        if(ifile_stream.is_open())
            ifile_stream.close();
    }
}
