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
    if (inputStream->size() == 0) return;

    while (inputStream->size() > 0) {
        SoundItem next = inputStream->front();
        Packet output = { 0 };
        Audio::AudioPacket packet { };
        packet.size = encoder.encode(next, output, FRAME_SIZE);
        memcpy(packet.data, output.data(), packet.size);
        sock.send(&packet, sizeof(Audio::AudioPacket));
        inputStream->pop();
    };
}

}
