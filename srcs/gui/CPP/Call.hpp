/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Call
*/

#pragma once

#include <QObject>
#include <QString>

#include "Engine.hpp"

class Call : public QObject {
    Q_OBJECT
public:
    explicit Call(QObject *parent = nullptr);
    ~Call() = default;
    Call(Call const &);
    Call& operator=(Call const &);

    Q_INVOKABLE void requestCall(QString);
    Q_INVOKABLE void stopCall();
    Q_INVOKABLE bool isCalling();

public slots:
    void onClickedAccept();
    void onClickedDeny();

signals:
    void callingYou(int callerId);
    void acceptedYourCall();
    void deniedYourCall();

private:
    void reset();
    QString const getFriendsName(int);

private:
    int _targetId;
    // QQmlApplicationEngine *_engine;
    std::string _targetName;
    bool _calling;
    bool _callAccepted;
};