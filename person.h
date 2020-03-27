#ifndef Person_H
#define Person_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "states.h"

class Person : public QGraphicsItem
{
public:
    Person(int width, int heigth, States state);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void advance(int phase);

private:
    qreal angle;
    qreal speed;
    States person_state;
    void DoCollision();
};

#endif // Person_H
