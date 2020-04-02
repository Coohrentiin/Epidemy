#ifndef STATE_H
#define STATE_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <iostream>

class State
{
public:
    State();
    Qt::GlobalColor getColor();

private:
    Qt::GlobalColor color;
};

#endif // STATE_H
