#include "./Server.hpp"

int main()
{
    try {
        babel::Server server(8000, 8001);
        server.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}