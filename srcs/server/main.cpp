#include "./Server.hpp"
#include "../common/Args.hpp"

int main(int ac, char **av)
{
    try {
        auto args = Args(ac, av);
        babel::Server server(args.tcpport, args.udpport);
        server.run();
    } catch (ArgsHelp &e) {
        return 0;
    } catch (ArgsInvalidArgument &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}