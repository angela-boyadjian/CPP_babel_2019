/*
** EPITECH PROJECT, 2019
** babel
** File description:
** AudioModule
*/

#pragma once

#include <thread>
#include "../network/Socket.hpp"
#include "../audio/ADataTransfer.hpp"
#include "../audio/Audio.hpp"
#include "../audio/Receiver.hpp"
#include "../audio/Sender.hpp"

namespace babel {

class AudioModule : public ADataTransfer {
	public:
		AudioModule(Socket &sock);
		~AudioModule();

        void start();
        void end();
        void launchPoint();

	protected:
	private:
        std::atomic<bool> exitCondition { false };
        Socket &sock;
        std::thread *thread;
};

}
