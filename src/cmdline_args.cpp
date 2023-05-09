#include "cmdline_args.hpp"
#include <array>
#include <boost/asio.hpp>
#include <iostream>

auto validate_arguments(const std::vector<std::string> &args) -> std::optional<cmdline_args>
{
    if (args.size() != 4) {
        std::cerr << "Invalid number of arguments.\n";
        std::cerr << "Usage: ./game_client <ip_number> <port_number> <player_marker> <minimax_depth>\n";
        return {};
    }

    const auto &ip_number = args[0];
    const auto &port_number = args[1];
    const auto &player_marker = args[2];
    const auto &depth_number = args[3];

    // Validate IP address
    boost::system::error_code ec;
    boost::asio::ip::address::from_string(ip_number, ec);
    if (ec) {
        std::cerr << "Invalid IP address format.\n";
        return std::nullopt;
    }

    // Validate port number
    const int port = std::stoi(port_number);
    if (port < 1 || port > 65535) {
        std::cerr << "Invalid port number. Must be in the range [1, 65535].\n";
        return std::nullopt;
    }

    // Validate player marker
    const int marker = std::stoi(player_marker);
    if (1 > marker || 2 < marker) {
        std::cerr << "Invalid player marker. Must be '1' for 'X' or '2' for 'O'.\n";
        return std::nullopt;
    }

    // Validate min max depth
    const int depth = std::stoi(depth_number);
    if (1 > depth || depth > 10) {
        std::cerr << "Depth must be a number between 1 and 10.\n";
        return std::nullopt;
    }

    return cmdline_args{ .ip = ip_number, .port = port, .marker = Marker{ marker }, .depth = depth };
}


auto validate_arguments_params(const std::vector<std::string> &args) -> std::optional<cmdline_args>
{
    if (args.size() != 8) {
        std::cerr << "Invalid number of arguments.\n";
        std::cerr << "Usage: ./game_client <ip_number> <port_number> <player_marker> <minimax_depth> <params...>\n";
        return {};
    }

    const auto &ip_number = args[0];
    const auto &port_number = args[1];
    const auto &player_marker = args[2];
    const auto &depth_number = args[3];

    // Validate IP address
    boost::system::error_code ec;
    boost::asio::ip::address::from_string(ip_number, ec);
    if (ec) {
        std::cerr << "Invalid IP address format.\n";
        return std::nullopt;
    }

    // Validate port number
    const int port = std::stoi(port_number);
    if (port < 1 || port > 65535) {
        std::cerr << "Invalid port number. Must be in the range [1, 65535].\n";
        return std::nullopt;
    }

    // Validate player marker
    const int marker = std::stoi(player_marker);
    if (1 > marker || 2 < marker) {
        std::cerr << "Invalid player marker. Must be '1' for 'X' or '2' for 'O'.\n";
        return std::nullopt;
    }

    // Validate min max depth
    const int depth = std::stoi(depth_number);
    if (1 > depth || depth > 10) {
        std::cerr << "Depth must be a number between 1 and 10.\n";
        return std::nullopt;
    }

    const std::array<int, 4> params = {
        std::stoi(args[4]), std::stoi(args[5]), std::stoi(args[6]), std::stoi(args[7])
    };

    return cmdline_args{ .ip = ip_number, .port = port, .marker = Marker{ marker }, .depth = depth, .params = params };
}
