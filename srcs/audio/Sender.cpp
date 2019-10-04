/*
** EPITECH PROJECT, 2019
** babel
** File description:
** Sender
*/

#include "Sender.hpp"
#include "Audio.hpp"

namespace babel
{

Sender::Sender() : encoder(Encoder(2))
{
}

Sender::~Sender()
{
}

void Sender::send(Socket &sock)
{
    int id = 0;

    if (inputStream->size() == 0) return;

    while (inputStream->size() > 0) {
        SoundItem next = inputStream->front();
        Packet output = { 0 };
        Audio::AudioHeader header { };
        header.size = encoder.encode(next, output, FrameSize);
        header.packetId = id;
        sock.send(&header, sizeof(Audio::AudioHeader));
        sock.send(output.data(), header.size);
        inputStream->pop();
        id++;
        if (id == 10)
            id = 0;
    };
}

}
