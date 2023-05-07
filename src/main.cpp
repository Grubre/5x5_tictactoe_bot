#include "board.hpp"
#include "cmdline_args.hpp"
#include "connection.hpp"
#include "minimax.hpp"
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

    send_message(tcp_socket, std::to_string((int)marker));

    auto end_game = false;

    auto board = Board{};

    while (!end_game) {
        server_message = receive_message(tcp_socket);
        std::cout << "message: " << server_message << std::endl;

        auto msg = std::stoi(server_message);
        auto move = msg % 100;
        msg /= 100;

        if (move != 0) {
            board.set_cell(move / 10 - 1, move % 10 - 1, get_opponent(marker));
            board.print_board();
        }

        if ((msg == 0) || (msg == 6)) {
            move = find_best_move(board, marker, depth);
            board.set_cell(move / 10 - 1, move % 10 - 1, marker);
            board.print_board();

            send_message(tcp_socket, std::to_string(move));

            std::cout << "Client message: " << move << std::endl;
        } else {
            end_game = true;
            switch (msg) {
            case 1:
                std::cout << "You won." << std::endl;
                break;
            case 2:
                std::cout << "You lost." << std::endl;
                break;
            case 3:
                std::cout << "Draw." << std::endl;
                break;
            case 4:
                std::cout << "You won. Opponent error" << std::endl;
                break;
            case 5:
                std::cout << "You lost. Your error" << std::endl;
                break;
            default:
                break;
            }
        }
    }
    return EXIT_SUCCESS;
}
