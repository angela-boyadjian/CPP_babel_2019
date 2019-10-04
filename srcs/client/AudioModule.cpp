/*
** EPITECH PROJECT, 2019
** babel
** File description:
** AudioModule
*/

#include "AudioModule.hpp"

namespace babel {

AudioModule::AudioModule(Socket &sock) : sock(sock)
{
}

AudioModule::~AudioModule()
{
    this->end();
}

void AudioModule::launchPoint()
{
    Audio sound(SampleRate, 2, 2);
    Receiver recv { };
    Sender sender { };

    recv.connectOutput(&sound);
    sound.connectOutput(&sender);

    while (exitCondition == false) {
        recv.receive(sock);
        sender.send(sock);
        Pa_Sleep(200);
    }
}

void AudioModule::start()
{
    if (thread != nullptr) {
        std::cerr << "Audio already started, please fix" << std::endl;
    }
    thread = new std::thread([this]() { launchPoint(); });
}

void AudioModule::end()
{
    if (thread != nullptr) {
        exitCondition = true;
    }
}

}