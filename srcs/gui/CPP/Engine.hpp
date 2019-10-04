/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Engine
*/

#pragma once

#include <QGuiApplication>
#include <QQmlApplicationEngine>

class Engine {
public:
    static Engine *getInstance(QGuiApplication *app);
    QQmlApplicationEngine *getQmlEngine();
    ~Engine() = delete;

private:
    static Engine *_instance;
    QQmlApplicationEngine *_engine;
    Engine(QGuiApplication *app);
    // Engine(Engine const &) = delete;
    // Engine &operator=(Engine const &) = delete;
};