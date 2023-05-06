#include "connection.hpp"
#include <array>
#include <boost/asio/deadline_timer.hpp>

void send_message(boost::asio::ip::tcp::socket &socket, const std::string &message)
{
    constexpr size_t buf_size = 16;
    std::array<char, buf_size> buf = { 0 };

    size_t message_size = message.size() < buf_size ? message.size() : buf_size - 1;
    std::copy_n(message.begin(), message_size, buf.begin());

    boost::asio::write(socket, boost::asio::buffer(buf));
}

auto receive_message(boost::asio::ip::tcp::socket &socket) -> std::string
{
    constexpr size_t buf_size = 16;
    std::array<char, 16> buf = { 0 };

    boost::system::error_code error;
    size_t n = socket.read_some(boost::asio::buffer(buf, buf_size - 1), error);

    if (error && error != boost::asio::error::eof) {
        std::cout << "Error while receiving server's message: " << error.message() << std::endl;
        return "";
    }

    return std::string{ std::begin(buf), std::end(buf) };
}

auto connect_with_timeout(boost::asio::io_service &io_service,
  boost::asio::ip::tcp::socket &socket,
  const boost::asio::ip::tcp::endpoint &endpoint,
  const boost::posix_time::time_duration &timeout) -> bool
{
    bool connected = false;
    boost::system::error_code connect_error = boost::asio::error::would_block;

    socket.async_connect(endpoint, [&](const boost::system::error_code &ec) {
        connect_error = ec;
        connected = !ec;
    });

    boost::asio::deadline_timer timer(io_service, timeout);
    timer.async_wait([&](const boost::system::error_code &ec) {
        if (ec != boost::asio::error::operation_aborted) { socket.cancel(); }
    });

    do {
        io_service.run_one();
    } while (connect_error == boost::asio::error::would_block);

    timer.cancel();

    return connected;
}

auto connect_to_server(const std::string &ip, const int port) -> boost::asio::ip::tcp::socket
{
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::socket socket(io_service);

    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::ip::tcp::resolver::query query(ip, std::to_string(port));
    boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

    boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
    boost::posix_time::time_duration timeout = boost::posix_time::seconds(5);

    if (!connect_with_timeout(io_service, socket, endpoint, timeout)) {
        std::cerr << "Failed to connect to the server: " << socket.remote_endpoint().address().to_string() << ":"
                  << socket.remote_endpoint().port() << std::endl;
        throw std::runtime_error("Failed to connect to the server");
    }

    std::cout << "Connected to the server." << std::endl;

    return socket;
}
