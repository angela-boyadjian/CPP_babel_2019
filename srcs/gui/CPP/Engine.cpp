/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Engine
*/

#include <iostream>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QSettings>

#include "Engine.hpp"

Engine *Engine::_instance = nullptr;

Engine::Engine(QGuiApplication *app)
{
    _engine = new QQmlApplicationEngine(app);
}

Engine *Engine::getInstance(QGuiApplication *app)
{
    if (_instance == nullptr)
        _instance = new Engine(app);
    return _instance;
}

QQmlApplicationEngine *Engine::getQmlEngine()
{
    return _engine;
}