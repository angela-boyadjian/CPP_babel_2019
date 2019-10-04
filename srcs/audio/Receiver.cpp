/*
** EPITECH PROJECT, 2019
** babel
** File description:
** Receiver
*/

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
    Audio::AudioHeader header { };
    size_t received { 0 };
    int frameSize;

    nextPacketId = 0;
    do {
        received = sock.receive(&header, sizeof(Audio::AudioHeader), false);
        if (received > 0) {
            std::cout << nextPacketId << " <-> " << header.packetId << std::endl;
            Packet packet { 0 };
            received = sock.receive(packet.data(), header.size, true);
            frameSize = this->decoder.decode(packet, item, header.size, FrameSize);
            outStream.push(item);
            nextPacketId = header.packetId == 9 ? 0 : header.packetId + 1;
        }
    } while (received > 0);
}

}