#include <iostream>
#include "./network/Socket.hpp"

int main()
{
    babel::Socket client {};
    babel::Socket server {};
    try {
        server.listen(8000);
        client.connect("127.0.0.1", 8000);
        auto clientSock = server.accept(true);
        clientSock->send("Hello world");
        auto strReceived = client.receive(true);
        std::cout << strReceived << std::endl;
    } catch(std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}