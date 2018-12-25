#include "include/hasher.hpp"

#define TEST_FILE "/home/greyder/Workspace/Python/Malware_analysis/Trojans/f83396f9c1451a9291d8c997711d318b62b367e1aae11dd58e8b538d258e0642.exe"

void usage [[noreturn]] (const std::string &prog_name)
{
    std::cout << "Usage: " << prog_name << " <file>";
    std::cout << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char** argv)
{
    if(argc != 2)
        usage(argv[0]);

    std::string file(argv[1]);
    auto f = std::make_unique<Hasher::File>(file);

    std::unique_ptr<std::string> contents = f->read();

    std::cout << "SHA 256 hash of " << f->filename << ": " << Hasher::calculate_sha256(contents) << '\n';
    std::cout << "SHA1 hash of " << f->filename << ": " << Hasher::calculate_sha1(contents) << '\n';
    std::cout << "MD5 hash of " << f->filename << ": " << Hasher::calculate_md5(contents) << '\n';

    return 0;
}
