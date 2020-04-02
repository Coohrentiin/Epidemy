#ifndef STATES_H
#define STATES_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <iostream>

#include "disease.h"

enum State { Dead=Qt::black, Healthy=Qt::green, Carrier=Qt::yellow, Sick=Qt::red, Cared=Qt::blue};

class States{
    public:
        //Constructors
        States();
        States(State state);
        States(State state, Disease * disease);

        //Methods and functions
        void print();
        Qt::GlobalColor getColor();
        int getValue();
        State getState();
        int stateToInt(State state);
        int nextState(int value);
        void setState(State newState);

        //Operators
        bool operator>(State const& otherState) const;

    protected:
        int value;
        State state;
        Qt::GlobalColor color;
        Disease * theDisease;
        int aDiseaseParameter;
};

#endif // STATES_H
