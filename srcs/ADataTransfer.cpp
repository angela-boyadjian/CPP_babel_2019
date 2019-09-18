/*
** EPITECH PROJECT, 2019
** babel
** File description:
** ADataTransfer
*/

#include "ADataTransfer.hpp"

ADataTransfer::ADataTransfer()
{

}

ADataTransfer::~ADataTransfer()
{

}

void ADataTransfer::onNewInput(ADataTransfer *newTransfer)
{
    this->inputStream = &newTransfer->outStream;
}

void ADataTransfer::connectOutput(ADataTransfer *toNew)
{
    toNew->onNewInput(this);
}
