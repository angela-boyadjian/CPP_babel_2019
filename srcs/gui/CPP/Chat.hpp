/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Chat
*/

#pragma once

#include <QObject>
#include <QString>

#include "Engine.hpp"

class Chat : public QObject {
    Q_OBJECT
public:
    explicit Chat(QObject *parent = nullptr);
    ~Chat() = default;
private:
};