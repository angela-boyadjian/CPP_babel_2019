/*
** EPITECH PROJECT, 2019
** babel
** File description:
** Receiver
*/

#pragma once

#include "ADataTransfer.hpp"
#include "Audio.hpp"
#include "../network/Socket.hpp"
#include "Decoder.hpp"

namespace babel
{

class Receiver : public ADataTransfer {
	public:
		Receiver();
		~Receiver();

        void receive(Socket &sock);

	protected:
	private:
		Decoder decoder;
		int nextPacketId;
};

}
