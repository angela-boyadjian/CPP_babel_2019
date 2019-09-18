/*
** EPITECH PROJECT, 2019
** babel
** File description:
** Audio
*/

#pragma once

#include "Babel.hpp"
#include <portaudio.h>
#include <fstream>
#include <memory.h>
#include <sstream>
#include "ADataTransfer.hpp"
#include <array>

using AudioStream = PaStream;
using Sample = float;

#include <vector>

class Audio : public ADataTransfer {
	public:
		Audio(int sampleRate, int inputs, int outputs);
		~Audio();

        void init();
		void printInfos();
		void close();
        void connect();

		void connectOutput(ADataTransfer *) override;

		// Can't put in to private because callback function calls it from outside
		int onData(const void *input,
			void *output,
			unsigned long frameCount,
			const PaStreamCallbackTimeInfo *timeInfo,
			PaStreamCallbackFlags statusFlags,
			void *userData
		);
	protected:
	private:
		static bool soundInitialized;

		int inputs;
		int outputs;

		int currentIndex { 0 };

		AudioStream *audioStream { nullptr };
		SoundItem currentSoundItem { };

		void flush();
		void _connectStream(PaStream **stream, int input, int output, PaStreamCallback callback);

		int sampleRate { 0 };
};
