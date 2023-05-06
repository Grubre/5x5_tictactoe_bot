#include "cmdline_args.hpp"
#include "connection.hpp"
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>
#include <iostream>

auto main(int argc, char *argv[]) -> int
{
    auto str_args = std::vector<std::string>(argv + 1, argv + argc);
    auto args = validate_arguments(str_args);

    if (!args) { return EXIT_FAILURE; }

    const auto &ip_number = args->ip;
    auto port_number = args->port;
    auto marker = args->marker;
    auto depth = args->depth;

    auto tcp_socket = connect_to_server(ip_number, port_number);

    auto server_message = receive_message(tcp_socket);
    std::cout << "Server message: " << server_message << std::endl;

    send_message(tcp_socket, marker);

    auto end_game = false;
    while (!end_game) {
        server_message = receive_message(tcp_socket);
        std::cout << "message: " << server_message << std::endl;

        auto msg = std::stoi(server_message);
        auto move = msg % 100;
        msg /= 100;

        if(move != 0) {

        }
    }
    return EXIT_SUCCESS;
}
