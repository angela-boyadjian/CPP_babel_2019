/*
** EPITECH PROJECT, 2019
** babel
** File description:
** Decoder cpp
*/

#include "Decoder.hpp"
#include <string>
#include <iostream>

Decoder::Decoder(int SampleRate, int channels)
{
    initDecoder(SampleRate, channels);
}

Decoder::~Decoder()
{
    opus_decoder_destroy(this->decoder);
}

void Decoder::initDecoder(int sampleRate, int channels)
{
    int err = OPUS_OK;

    if (this->decoder != nullptr) {
        return;
    }
    std::cout << "decoder create -> " << sampleRate << " " << channels << std::endl;
    this->decoder = opus_decoder_create(sampleRate, channels, &err);
    std::cout << "decoder err = " << err << std::endl;
    if (err != OPUS_OK) {
        throw std::runtime_error("Could not initialize the decoder : " +
            std::string(opus_strerror(err)));
    }
}

int Decoder::decode(Packet &input,
                SoundItem &output,
                int inputSize,
                int frameSize)
{
    int decodedFrameSize;

    decodedFrameSize = opus_decode_float(this->decoder,
                input.data(),
                inputSize,
                output.data(),
                frameSize, 0);
    if (decodedFrameSize < 0) {
        throw std::runtime_error("Decode failed : " +
            std::string(opus_strerror(decodedFrameSize)));
    }
    return decodedFrameSize;
}