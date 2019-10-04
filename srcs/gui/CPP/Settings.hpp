/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Settings
*/

#pragma once

#include <QObject>
#include <QString>

class Settings : public QObject {
    Q_OBJECT
    public:
        explicit Settings(QObject *parent = nullptr);
        ~Settings() = default;

        Q_INVOKABLE void save(qint8, QString);
        Q_INVOKABLE void reset();
        void changeTheme(QString);

        // NOTE Getters
        Q_INVOKABLE qint8 getVolume() const { return _volume; }
        Q_INVOKABLE QString getTheme() const { return _theme; }
    // signals:
            // void updateTheme(QString);
    private:
        // changeVolume(qint8); // TODO
        qint8 _volume;
        QString _theme;
};