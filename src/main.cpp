#include "include/hasher.hpp"
#include "include/parser.hpp"
#include "include/requester.hpp"

void usage [[noreturn]] (const std::string &prog_name)
{
    std::cout << "Usage: " << prog_name << " <file> <api-key>";
    std::cout << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char** argv)
{
    int exit_status = EXIT_SUCCESS;

    if(argc != 3)
        usage(argv[0]);

    try
    {
        Hasher::File f(argv[1]);
        std::cout << "[*] Hashing " << f.filename << ": " << f.size() << " bytes" << '\n';
        std::string url = Requester::set_url(std::string(argv[2]), Hasher::calculate_hash(f.read(), "sha256"));
        std::cout << "[*] Sending data." << '\n';

        Requester::get_data(url);
        auto write_buffer = Requester::get_write_buffer();
        Parser::load(write_buffer);
        Parser::results();

    }
    catch (Hasher::Exception &r_error)
    {
        std::cerr << "Error (" << r_error.code() << "): " << r_error.what() << std::endl;
        exit_status = r_error.code();
    }
    catch(Parser::JsonException &json_error)
    {
        std::cerr << "JsonException: " << json_error.what() << std::endl;
        exit_status = EXIT_FAILURE;
    }
    catch(std::runtime_error &r_error)
    {
        std::cerr << "Runtime exception: " << r_error.what() << std::endl;
        exit_status = EXIT_FAILURE;
    }
    catch(std::exception &ex)
    {
        std::cerr << "Unknown exception: " << ex.what() << std::endl;
        exit_status = EXIT_FAILURE;
    }

    return exit_status;
}
