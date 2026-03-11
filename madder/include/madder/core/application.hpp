#pragma once

#include <asio.hpp>

namespace madder {
template <class Plugins...> class Application {
public:
private:
  asio::io_context m_io_context;
};
} // namespace madder
