/*
** EPITECH PROJECT, 2019
** babel
** File description:
** Encoder class
*/

#include "Encoder.hpp"
#include <string>
#include <iostream>

Encoder::Encoder(int chans)
{
    InitEncoder(chans);
}

Encoder::~Encoder()
{
    opus_encoder_destroy(this->encoder);
}

void Encoder::InitEncoder(int chans)
{
    int err = OPUS_OK;

    if (this->encoder != nullptr) {
        return;
    }

    this->encoder = opus_encoder_create(
        48000,
        chans,
        OPUS_APPLICATION_VOIP,
        &err);
    if (err != OPUS_OK) {
         throw std::runtime_error("Could not initialize the encoder : " +
            std::string(opus_strerror(err)));
    }
    // opus_encoder_ctl(this->encoder, OPUS_SET_BITRATE(64000));
}

int Encoder::encode(SoundItem &input,
                Packet &output,
                int frameSize)
{
    int byteEncoded;

    byteEncoded = opus_encode_float(this->encoder,
                input.data(),
                frameSize,
                output.data(),
                sizeof(Packet));
    if (byteEncoded < 0) {
        throw std::runtime_error("Encode failed : " +
            std::string(opus_strerror(byteEncoded)));
    }
    return byteEncoded;
}