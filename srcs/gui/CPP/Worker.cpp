/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Worker
*/

#include "Worker.hpp"

Worker::Worker(QObject *parent) : QObject(parent)
{
    connect(&timer, SIGNAL (timeout()), this, SLOT (doWork()));
    timer.start(100);
}

Worker::~Worker()
{
}

void Worker::doWork()
{
    auto client = Network::getInstance()->getClient();
    client->updateServerInfos();
}