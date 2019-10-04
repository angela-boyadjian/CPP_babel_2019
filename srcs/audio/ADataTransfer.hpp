/*
** EPITECH PROJECT, 2019
** babel
** File description:
** ADataTransfer
*/

#pragma once

#include <queue>
#include <array>

using SoundItem = std::array<float, 960>;
using Stream = std::queue<SoundItem>;

class ADataTransfer {
	public:
		ADataTransfer();
		~ADataTransfer();

        Stream outStream;

        virtual void connectOutput(ADataTransfer *);
	protected:
		Stream *inputStream;
		virtual void onNewInput(ADataTransfer *);
	private:
};
