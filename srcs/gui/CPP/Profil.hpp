/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Login
*/

#pragma once

#include <QObject>
#include <QString>
#include <iostream>

class Profil : public QObject {
    Q_OBJECT

	public:
	    explicit Profil(QObject *parent = nullptr);
		~Profil() = default;

        Q_INVOKABLE bool isConnected() const;
        Q_INVOKABLE void setConnected(bool co);

        Q_INVOKABLE QString getBio() const;
        Q_INVOKABLE void setBio(QString b);

        Q_INVOKABLE QString getUserName() const;
        Q_INVOKABLE void setUserName(QString n);

        Q_INVOKABLE void debug(QString str) const { std::cout << str.toStdString() << std::endl; }

    private:
		bool isCo;
        QString bio;
        QString userName;
        QString firstName;
        QString email;
};