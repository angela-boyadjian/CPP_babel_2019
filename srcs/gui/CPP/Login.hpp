/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Login
*/

#pragma once

#include <QObject>
#include <QString>

#include <memory>

#include "../../client/Client.hpp"
#include "../../network/SocketException.hpp"


class Login : public QObject {
    Q_OBJECT

	public:
	    explicit Login(QObject *parent = nullptr);
		~Login() = default;

    	Q_INVOKABLE QString connect(QString const &, QString const &, QString const &);
		Q_INVOKABLE QString signUp(QString const &, QString const &, QString const &);
		Q_INVOKABLE bool logout();

	private:
		QString _address;
		// QString _username;
		// QString _password;
};
