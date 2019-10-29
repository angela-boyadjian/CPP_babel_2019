/*
** EPITECH PROJECT, 2019
** babel
** File description:
** Receiver
*/

#include <memory>
#include "Audio.hpp"
#include "Receiver.hpp"

namespace babel
{

Receiver::Receiver() : decoder(Decoder(SampleRate, 2))
{
}

Receiver::~Receiver()
{
}

void Receiver::receive(Socket &sock)
{
    SoundItem item { };
    Audio::AudioPacket tcpPacket { };
    size_t received { 0 };
    int frameSize;
    void *tmp;

    do {
        received = sock.receive(&tcpPacket, sizeof(Audio::AudioPacket), false);
        if (received > 0) {
            //std::cout << "Packet size received = " << header.size << std::endl;
            Packet packet { 0 };
            memcpy(packet.data(), tcpPacket.data, tcpPacket.size);
            frameSize = this->decoder.decode(&packet, item, tcpPacket.size, FRAME_SIZE);
            outStream.push(item);
        }
    } while (received > 0);
}

}
