#include "./Server.hpp"

int main()
{
    babel::Server server(8000);
    server.run();
    return 0;
}