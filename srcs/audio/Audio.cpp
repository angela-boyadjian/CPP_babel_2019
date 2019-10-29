/*
** EPITECH PROJECT, 2019
** babel
** File description:
** Audio
*/

#include "Audio.hpp"

bool Audio::soundInitialized = false;

static int onDataOutOfClass(const void *input,
			void *output,
			unsigned long frameCount,
			const PaStreamCallbackTimeInfo *timeInfo,
			PaStreamCallbackFlags statusFlags,
			void *userData
)
{
    Audio *thiss = (Audio *) userData;
    return thiss->onData(input, output, frameCount, timeInfo, statusFlags, nullptr);
}

Audio::Audio(int sampleRate, int inputs, int outputs) : sampleRate(sampleRate), inputs(inputs), outputs(outputs)
{
    this->init();

    this->_connectStream(&audioStream, this->inputs, this->outputs, onDataOutOfClass);
}

Audio::~Audio()
{
    this->close();
}

void Audio::close()
{
    PaError err = Pa_CloseStream(audioStream);
    // PaError err = Pa_Terminate();

    if (err != paNoError) {
        throw std::runtime_error("Could not initialize sound" + std::string(Pa_GetErrorText(err)));
    }
}

void Audio::init()
{
    if (!soundInitialized) {
        PaError err = Pa_Initialize();

        if (err != paNoError) {
            throw std::runtime_error("Could not initialize sound" + std::string(Pa_GetErrorText(err)));
        }
        soundInitialized = true;
    }
}

void Audio::printInfos()
{
    int numDevices = Pa_GetDeviceCount();

    if (numDevices < 0)
    {
        printf( "ERROR: Pa_CountDevices returned 0x%x\n", numDevices);
        std::cout << Pa_GetErrorText(numDevices) << std::endl;
    }
    for (int i = 0; i < numDevices; i++)
    {
        const PaDeviceInfo *deviceInfo = Pa_GetDeviceInfo(i);
        std::cout << deviceInfo->name << std::endl;
    }
}

void Audio::_connectStream(PaStream **givenStream, int input, int output, PaStreamCallback callback)
{
    PaError err = Pa_OpenDefaultStream(givenStream,
            input,          /* no input channels */
            output,          /* stereo output */
            paFloat32,  /* 32 bit floating point output */
            sampleRate,
            FRAME_SIZE,        /* frames per buffer, i.e. the number
                                of sample frames that PortAudio will
                                request from the callback. Many apps
                                may want to use
                                paFramesPerBufferUnspecified, which
                                tells PortAudio to pick the best,
                                possibly changing, buffer size.*/
            callback, /* this is your callback function */
            this); /*This is a pointer that will be passed to
                                your callback*/
    if (err != paNoError) {
        std::cout << "Error !!!" << Pa_GetErrorText(err) << std::endl;
    }
    Pa_StartStream(*givenStream);
    err = Pa_IsStreamActive(*givenStream);
    if (err == 1) {
        std::cout << "Running" << std::endl;
    } else if (err == 0) {
        std::cout << "Not running" << std::endl;
    } else {
        std::cout << "Error" << std::endl;
    }
}

void Audio::connectOutput(ADataTransfer *transfer)
{
    ADataTransfer::connectOutput(transfer);
}

void Audio::flush()
{
    outStream.push(currentSoundItem);
    currentSoundItem.fill(0);
}

int Audio::onData(const void *input,
			void *output,
			unsigned long frameCount,
			const PaStreamCallbackTimeInfo *timeInfo,
			PaStreamCallbackFlags statusFlags,
			void *userData
)
{
    if (input != nullptr) {
        currentIndex += FRAME_SIZE * 2;
        memcpy(currentSoundItem.data(), input, FRAME_SIZE * 2 * sizeof(Sample));
        if (currentIndex >= 1023) {
            flush();
        }
    }
    if (inputStream != nullptr && inputStream->size() > 0) {
        Sample inStreamData[512 * 2] { 0 };
        SoundItem &item = inputStream->front();
        memcpy(output, &item, FRAME_SIZE * 2 * sizeof(Sample));
        inputStream->pop();
    }
    return 0;
}


// freelance -> 404works