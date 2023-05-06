#pragma once
#include <boost/asio.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/system/error_code.hpp>

auto connect_to_server(const std::string &ip, const int port) -> boost::asio::ip::tcp::socket;
auto receive_message(boost::asio::ip::tcp::socket &socket) -> std::string;
void send_message(boost::asio::ip::tcp::socket &socket, const std::string &message);
