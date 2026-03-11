#pragma once

#include <asio.hpp>
#include <thread>
#include <tuple>
#include <vector>

namespace madder {
template <class... Plugins> class Application {
public:
  Application() : m_io_context() {
    init_plugins(std::index_sequence_for<Plugins...>{});
  }

  auto run() {
    run_plugins(std::index_sequence_for<Plugins...>{});

    for (int i = 0; i < std::thread::hardware_concurrency(); ++i) {
      threads.emplace_back([this] { m_io_context.run(); });
    }
  }

private:
  template <std::size_t... I> void init_plugins(std::index_sequence<I...>) {
    (std::get<I>(m_plugins).init(m_io_context), ...);
  }

  template <std::size_t... I> void run_plugins(std::index_sequence<I...>) {
    (std::get<I>(m_plugins).run(), ...);
  }

  asio::io_context m_io_context{};

  std::tuple<Plugins...> m_plugins;
  std::vector<std::jthread> threads;
};
} // namespace madder
