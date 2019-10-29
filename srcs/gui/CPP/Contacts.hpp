/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Contacts
*/

#pragma once

#include <QString>
#include <QStringList>
#include <QList>
#include <QQmlListProperty>
#include <iostream>
#include <QStringList>

class Contacts : public QObject {
    Q_OBJECT
    Q_PROPERTY(QStringList friendList READ friendList)
public:
	explicit Contacts(QObject *parent = nullptr);
	~Contacts() = default;

	void getFriends();
	QStringList friendList() const;
	
	Q_INVOKABLE QString addFriend(QString name);
	Q_INVOKABLE void removeFriend(QString name);
	Q_INVOKABLE void debug(QString s) const;
	
signals:
	void friendListChanged();

private:
	//void displayList() const;
	QStringList _friendsList;
};