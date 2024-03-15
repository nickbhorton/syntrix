#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sstream>

#include "symbol.h"

std::string get_string_of_cin() {
    std::string input{};
    constexpr size_t buffer_size = 65536;
    char buffer[buffer_size];
    while (true) {
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        timeval tv;
        tv.tv_sec = 2;
        tv.tv_usec = 0;
        int select_result = select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
        if (select_result > 0) {
            // There is something in stdin
            ssize_t bytes_from_stdin = read(STDIN_FILENO, buffer, buffer_size);
            if (bytes_from_stdin < 0) {
                std::cerr << "read() from stdin error: " << std::strerror(errno)
                          << "\n";
                exit(1);
            } else if (bytes_from_stdin == 0) {
                break;
            } else {
                input += std::string(buffer, static_cast<size_t>(bytes_from_stdin));
            }
        } else if (select_result == 0) {
            std::cerr << "timedout reading from STDIN\n";
            if (input.length() > 0) {
                break;
            }
            exit(2);
        } else {
            std::cerr << "select() error: " << std::strerror(errno) << "\n";
            exit(1);
        }
    }
    return input;
}

int main()
{
    std::string input = get_string_of_cin();
    std::stringstream ss;
    for (const auto & c : input) {
        ss << syntrix::Symbol{static_cast<uint8_t>(c)}.to_string() << " ";
    }
    std::cout << ss.str().substr(0, ss.str().length() - 1);
}
