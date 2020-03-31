#ifndef STATES_H
#define STATES_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <iostream>

enum State { Dead=Qt::black, Healthy=Qt::green, Carrier=Qt::yellow, Sick=Qt::red, Cared=Qt::blue};

class States{
    public:
        States();
        States(State state);
        void print();
        Qt::GlobalColor getColor();
        int getValue();

        bool operator>(State const& otherState) const;
        int stateToInt(State state);
        State IntToState(int value);
        void nextState();

    protected:
        int value;
        State state;
        Qt::GlobalColor color;
};

#endif // STATES_H
