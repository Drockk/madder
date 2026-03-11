#include <asio.hpp>
#include <coroutine>
#include <iostream>
#include <madder.hpp>
#include <optional>
#include <print>
#include <stdexec/execution.hpp>
#include <string>
#include <functional>

auto handle_client(asio::ip::tcp::socket t_socket) -> asio::awaitable<void> {
  try {
    while (true) {
      std::array<char, 1024> buffer;
      auto bytes_read = co_await t_socket.async_read_some(asio::buffer(buffer),
                                                          asio::use_awaitable);

      if (bytes_read == 0) {
        break; // Connection closed
      }

      std::println("Received: {}", std::string(buffer.data(), bytes_read));

      co_await asio::async_write(t_socket, asio::buffer(buffer, bytes_read),
                                 asio::use_awaitable);
    }

  } catch (const std::exception &t_exception) {
    std::println(std::cerr, "Client error: {}", t_exception.what());
  }
  co_return;
}

auto run_server(asio::io_context &t_io_context,
                uint16_t t_port) -> asio::awaitable<void> {
  asio::ip::tcp::acceptor acceptor(t_io_context, {asio::ip::tcp::v4(), t_port});

  std::println("Server listening in port: {}", t_port);

  while (true) {
    auto socket = co_await acceptor.async_accept(asio::use_awaitable);

    asio::co_spawn(socket.get_executor(), handle_client(std::move(socket)),
                   asio::detached);
  }
  co_return;
}

struct HelloServer {};

template <class Controller> class TcpServerPlugin {
public:
  auto init(asio::io_context &t_io_context) -> void {
    m_io_context = t_io_context;
  }

  auto run() -> void {
    if (!m_io_context.has_value()) {
      throw std::logic_error("TcpServerPlugin not initialized");
    }

    auto &io_context = m_io_context->get();
    asio::co_spawn(io_context, run_server(io_context, 8080), asio::detached);
  }

private:
  std::optional<std::reference_wrapper<asio::io_context>> m_io_context;
};

int main() {
  madder::Application<TcpServerPlugin<HelloServer>> app;
  app.run();
  return 0;
}