/*
** EPITECH PROJECT, 2019
** babel
** File description:
** Sender
*/

#pragma once

#include "ADataTransfer.hpp"
#include "../network/Socket.hpp"
#include "Audio.hpp"
#include "Encoder.hpp"

namespace babel {

class Sender : public ADataTransfer {
	public:
		Sender();
		~Sender();

        void send(Socket &sock);

	protected:
	private:
		Encoder encoder;

};

}
