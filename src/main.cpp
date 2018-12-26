#include "include/hasher.hpp"
#include "include/parser.hpp"
#include "include/requester.hpp"

void usage [[noreturn]] (const std::string &prog_name)
{
    std::cout << "Usage: " << prog_name << " <file>";
    std::cout << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char** argv)
{
    return 0;
}
