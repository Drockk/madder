#include <asio.hpp>
#include <coroutine>
#include <iostream>
#include <print>
#include <stdexec/execution.hpp>
#include <string>
#include <thread>
#include <vector>

struct asio_context {
  asio::io_context &ctx;

  auto get_scheduler() const noexcept { return *this; }

  auto schedule() const noexcept {
    struct io_schedule_op {
      asio::io_context &ctx;
    };
    return io_schedule_op{ctx};
  }

  bool operator==(const asio_context &other) const noexcept {
    return &ctx == &other.ctx;
  }

  bool operator!=(const asio_context &other) const noexcept {
    return !(*this == other);
  }
};

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

int main() {
  asio::io_context io_context;

  asio::co_spawn(io_context, run_server(io_context, 8080), asio::detached);

  std::vector<std::jthread> threads;
  for (int i = 0; i < std::thread::hardware_concurrency(); ++i) {
    threads.emplace_back([&io_context] { io_context.run(); });
  }

  return 0;
}