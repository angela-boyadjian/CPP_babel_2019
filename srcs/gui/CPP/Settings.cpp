/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Settings
*/

#include "Settings.hpp"

#include <QDebug>
#include <iostream>


Settings::Settings(QObject *parent) :
    _volume(50), _theme("transparent")
{
}

Q_INVOKABLE void Settings::save(qint8 volume, QString theme)
{
    _volume = volume;
    changeTheme(theme);
}

void Settings::changeTheme(QString newTheme)
{
    std::string theme {newTheme.toUtf8().constData()};

    if (theme == "Default")
        _theme = "transparent";
    else if (theme == "Candies")
        _theme = "#E91E63";
    else
        _theme = "#3A2D68";
    // emit updateTheme(_theme);
}

Q_INVOKABLE void Settings::reset()
{
    _volume = 50;
    _theme = "transparent";
}