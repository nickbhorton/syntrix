#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <format>
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

std::vector<std::tuple<syntrix::Symbol, int>>
get_clusters(const std::string &input)
{
    std::vector<std::tuple<syntrix::Symbol, int>> result;
    std::stringstream in{input};
    char c;
    while (in.get(c))
    {
        char start_char = c;
        int repeat_count = 1;
        while (in.peek() == start_char)
        {
            in.get(c);
            repeat_count++;
        }
        result.push_back(
            {syntrix::Symbol{static_cast<uint8_t>(start_char)}, repeat_count});
    }
    return result;
}

enum class ClusterType
{
    None,
    Identifier
};

std::vector<
    std::tuple<std::vector<std::tuple<syntrix::Symbol, int>>, ClusterType>>
combine_identifiers(std::vector<std::tuple<syntrix::Symbol, int>> input)
{
    std::vector<
        std::tuple<std::vector<std::tuple<syntrix::Symbol, int>>, ClusterType>>
        result;
    std::vector<std::tuple<syntrix::Symbol, int>> working;
    for (size_t i = 0; i < input.size(); i++)
    {
        auto current = input[i];
        if (is_name_symbol(std::get<0>(current).get_symbol_kind()))
        {
            working.push_back(current);
        }
        else
        {
            if (working.size() != 0)
            {
                result.push_back({working, ClusterType::Identifier});
                working.clear();
            }
            working.push_back(current);
            result.push_back({working, ClusterType::None});
            working.clear();
        }
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

    auto cluster_vector = get_clusters(input);
    auto identifyer_matrix = combine_identifiers(cluster_vector);
    for (size_t i = 0; i < identifyer_matrix.size(); i++)
    {
        auto [current_cluster_vector, cluster_type] = identifyer_matrix[i];
        switch (cluster_type)
        {
            case ClusterType::None:
            {
                for (size_t j = 0; j < current_cluster_vector.size(); j++)
                {
                    auto [s, repeated] = current_cluster_vector[j];
                    if (repeated > 1)
                    {
                        ss << std::format("{}{}{}{}*{}{}", misc_symbol_styling,
                                          s.to_string(), clear, raw_styling,
                                          repeated, clear);
                    }
                    else
                    {
                        ss << std::format("{}{}{}", misc_symbol_styling,
                                          s.to_string(), clear);
                    }
                }
                break;
            }
            case ClusterType::Identifier:
            {
                for (size_t j = 0; j < current_cluster_vector.size(); j++)
                {
                    auto [s, repeated] = current_cluster_vector[j];
                    for (int k = 0; k < repeated; k++)
                    {
                        ss << s.to_string();
                    }
                }
                break;
            }
        }
        ss << " ";
    }
    std::cout << ss.str().substr(0, ss.str().length() - 1);
}
