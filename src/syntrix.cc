#include <arpa/inet.h>
#include <format>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <netinet/in.h>
#include <sstream>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

#include "symbol.h"

std::string get_string_of_cin()
{
    std::string input{};
    constexpr size_t buffer_size = 65536;
    char buffer[buffer_size];
    while (true)
    {
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        timeval tv;
        tv.tv_sec = 2;
        tv.tv_usec = 0;
        int select_result = select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
        if (select_result > 0)
        {
            // There is something in stdin
            ssize_t bytes_from_stdin = read(STDIN_FILENO, buffer, buffer_size);
            if (bytes_from_stdin < 0)
            {
                std::cerr << "read() from stdin error: " << std::strerror(errno)
                          << "\n";
                exit(1);
            }
            else if (bytes_from_stdin == 0)
            {
                break;
            }
            else
            {
                input +=
                    std::string(buffer, static_cast<size_t>(bytes_from_stdin));
            }
        }
        else if (select_result == 0)
        {
            std::cerr << "timedout reading from STDIN\n";
            if (input.length() > 0)
            {
                break;
            }
            exit(2);
        }
        else
        {
            std::cerr << "select() error: " << std::strerror(errno) << "\n";
            exit(1);
        }
    }
    return input;
}

static bool is_name_symbol(syntrix::Symbol::Kind s)
{
    if (s == syntrix::Symbol::Kind::UpperCase ||
        s == syntrix::Symbol::Kind::LowerCase ||
        s == syntrix::Symbol::Kind::UnderScore)
    {
        return true;
    }
    return false;
}

std::vector<int> get_clusters(const std::string &input)
{
    std::vector<int> result;

    int cluster_count = 0;
    syntrix::Symbol previous_symbol{0};
    for (const auto &c : input)
    {
        syntrix::Symbol current_symbol{static_cast<uint8_t>(c)};
        if (is_name_symbol(current_symbol.get_symbol_kind()))
        {
            cluster_count++;
        }
        else
        {
            if (cluster_count > 0)
            {
                result.push_back(cluster_count);
                cluster_count = 0;
            }
            if (c == 0)
            {
                result.push_back(0);
            }
            else
            {
                result.push_back(1);
            }
        }
        previous_symbol = current_symbol;
    }
    return result;
}

std::string whitespace_styling = "\x1b[48;5;15m\x1b[38;5;16m";
std::string wrapper_styling = "\x1b[38;5;33m";
std::string raw_styling = "\x1b[38;5;196m";
std::string semicolon_styling = "\x1b[38;5;177m";
std::string misc_symbol_styling = "\x1b[38;5;51m";
std::string clear = "\x1b[0m";

int main()
{
    std::string input = get_string_of_cin();
    std::stringstream ss{};
    ss << clear;

    std::vector<int> cluster_vector = get_clusters(input);
    size_t input_index = 0;
    size_t cv_index = 0;
    while (cv_index < cluster_vector.size())
    {
        if (cluster_vector[cv_index] > 1)
        {
            for (int i = 0; i < cluster_vector[cv_index]; i++)
            {
                ss << syntrix::Symbol{static_cast<uint8_t>(input[input_index])}
                          .to_string();
                input_index++;
            }
            ss << " ";
            cv_index++;
        }
        else if (cluster_vector[cv_index] == 1)
        {
            ss << misc_symbol_styling;
            ss << syntrix::Symbol{static_cast<uint8_t>(input[input_index])}
                      .to_string();
            input_index++;
            ss << clear;
            ss << " ";
            cv_index++;
        }
        else
        {
            int zero_count = 1;
            input_index++;
            cv_index++;
            while (cluster_vector[cv_index] == 0 && cv_index < cluster_vector.size()){
                zero_count++;
                input_index++;
                cv_index++;
            }
            ss << raw_styling;
            if (zero_count == 1) {
                ss << syntrix::Symbol{0}.to_string();
            }
            else {
                ss << std::format("{}*{}", syntrix::Symbol{0}.to_string(), zero_count);
            }
            ss << clear;
            ss << " ";
        }
    }
    std::cout << ss.str().substr(0, ss.str().length() - 1);
}
