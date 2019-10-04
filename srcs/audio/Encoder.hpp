/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Encoder
*/

#pragma once

#include <opus/opus.h>
#include "ADataTransfer.hpp"

using Packet = std::array<unsigned char, sizeof(SoundItem)>;

class Encoder {
	public:
		Encoder(int channel);
		~Encoder();

        int encode(SoundItem &input, Packet &output, int frameSize);

	private:
		void InitEncoder(int chans);

	protected:
		OpusEncoder *encoder;
};
