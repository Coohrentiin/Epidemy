#include "state.h"

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <iostream>

State::State()
{
    this->color=Qt::black;
}

Qt::GlobalColor State::getColor(){
    return this->color;
}
