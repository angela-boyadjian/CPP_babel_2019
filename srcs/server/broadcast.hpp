/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** broadcast
*/

#pragma once

enum BroadcastType {
    TO_ONE,
    TO_MANY,
    TO_ALL,
};

struct BroadcastToMany {
    int number;
    int targets[256];
};

union BroadcastTarget {
    int singleTarget;
    BroadcastToMany manyTargets;
};

struct RequestHandling {
    BroadcastType broadcastType;
    BroadcastTarget targetsinfos;
    Request response;
};