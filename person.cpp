#include "person.h"
#include <cmath>
#include <iostream>

Person::Person(int width, int heigth, States state)
{
    //random start rotation
    angle = (qrand() % 360);
    setRotation(angle);

    //set the speed
    speed = 5;

    //Set State
    person_state = state;

    //random start position
    int StartX = 0;
    int StartY = 0;

    StartX = (( qrand() % (2* (width-10) ) ) - (width-10) )/2;
    StartY = (( qrand() % (2* (heigth-10) ) ) - (heigth-10) )/2;

    setPos(StartX,StartY);
}

QRectF Person::boundingRect() const
{
    return QRect(0,0,10,10);
}

void Person::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush Brush(Qt::gray);
    //basic Collision detection
    QPen pen;
    pen.setBrush(Qt::SolidPattern);
    painter->setPen(pen);
    painter->setBrush(person_state.getColor());

    if(!scene()->collidingItems(this).isEmpty())
    {
        //Set the position
        DoCollision();
    }

    painter->drawEllipse(rec);

}

void Person::advance(int phase)
{
    if(!phase) return;
//    QPointF location = this->pos();
    setPos(mapToParent(0,-(speed)));
    person_state.print();
}

void Person::DoCollision()
{
    //Get a new position
    //Change the angle with a little randomness
    if(((qrand() %1)))
    {
        setRotation(rotation() + (180 + (qrand() % 10 )));
    }
    else
    {
        setRotation(rotation() + (180 + (qrand() % -10 )));
    }

    qreal corner=sqrt(2)*boundingRect().width();
    QPointF newpoint = mapToParent(-corner, -corner);
    if(!scene()->sceneRect().contains((newpoint)))
    {
        //move it back in bounds
        newpoint = mapToParent(0,0);
    }
    else
    {
        //set the new position
        setPos(newpoint);
    }
}
