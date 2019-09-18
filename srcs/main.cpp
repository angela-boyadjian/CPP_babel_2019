#include <iostream>
#include <portaudio.h>
#include <opus/opus.h>
#include "Audio.hpp"
#include "Recorded.hpp"
#include "./network/Socket.hpp"

int main(int argc, char** argv)
{
    Audio *in = new Audio(44100, 2, 0);

    std::cout << 1 << std::endl;
    Pa_Sleep(2000);
    std::cout << 1 << std::endl;
    in->close();
    std::cout << "Create" << std::endl;
    Audio *reader = new Audio(44100, 0, 2);
    std::cout << "Finished create" << std::endl;
    in->connectOutput(reader);
    std::cout << "Connected" << std::endl;
    Pa_Sleep(2000);
}
