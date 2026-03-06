#include <asio.hpp>
#include <execution>
#include <coroutine>
#include <iostream>
#include <memory>
#include <thread>

struct async_task: std::suspend_always
{
    using promise_type = async_task;
    async_task get_return_object() { return {}; }
    void return_void() {}
    void unhandled_exception() { std::terminate(); }
};

async_task handle_client(asio::ip::tcp::socket socket)
{

}

async_task run_server(asio::io_context& io_context, unsigned short port)
{
    asio::ip::tcp::acceptor acceptor(
        io_context,
        {asio::ip::tcp::v4(), port}
    );

    std::cout << "Serwer nasłuchuje na porcie " << port << std::endl;
}

int main()
{
    asio::io_context io_context;

    auto server_task = run_server(io_context, 8080);

    std::vector<std::jthread> threads;
    for (int i = 0; i < std::thread::hardware_concurrency(); ++i) {
        threads.emplace_back([&io_context] { io_context.run(); });
    }

    return 0;
}
