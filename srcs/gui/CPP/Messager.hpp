/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Messager
*/

#pragma once

#include <QObject>
#include <QString>

#include "Engine.hpp"

class Messager : public QObject {
    Q_OBJECT
public:
    explicit Messager(QObject *parent = nullptr);
    ~Messager() = default;
    Q_INVOKABLE void sendMessage(QString const &, int);
    Q_INVOKABLE QString getMessage();

signals:
    void receivedMessage(int targetId, int senderId, QString msg);
    // void receivedMessage(int targetId, int senderName, QString msg);
private:
    QString _msg;
};