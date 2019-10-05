/*
** EPITECH PROJECT, 2019
** babel
** File description:
** Decoder
*/

#pragma once

#include <opus/opus.h>
#include "ADataTransfer.hpp"

using Packet = std::array<unsigned char, sizeof(SoundItem)>;

class Decoder {
	public:
		Decoder(int sampleRate, int channels);
		~Decoder();

        int decode(Packet *input, SoundItem &output, int inputSize, int frameSize);

    private:
        void initDecoder(int sampleRate, int channels);

	protected:
        OpusDecoder *decoder;

};
