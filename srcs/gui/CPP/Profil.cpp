/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Profil cpp
*/

#include "Profil.hpp"

Profil::Profil(QObject *parent) : QObject(parent), isCo(false)
{
}

Q_INVOKABLE bool Profil::isConnected() const
{
    return isCo;
}

Q_INVOKABLE void Profil::setConnected(bool co)
{
    isCo = co;    
}

Q_INVOKABLE QString Profil::getBio() const
{
    return bio;
}

Q_INVOKABLE void Profil::setBio(QString b)
{
    bio = b;
}

Q_INVOKABLE QString Profil::getUserName() const
{
    return userName;
}

Q_INVOKABLE void Profil::setUserName(QString n)
{
    userName = n;
}