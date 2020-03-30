#ifndef Person_H
#define Person_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "states.h"

class Person : public QGraphicsItem
{
public:
    Person(int graphic_width, int graphic_heigth, States person_state, int radius);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setState(States state);
    void setListOfPerson(std::vector<Person *> list);
    bool collision();
//    virtual int type() override;
protected:
    void advance(int phase);
    void globalSetPosition(int angleToAdd, int noiseWidthAngle, qreal xAdditiveStep, qreal yAdditiveStep);
    QPointF centerCoordinate();
    std::vector<Person *> listOfPerson;

private:
    qreal angle;
    qreal speed;
    int radius;
    int graphic_width;
    int graphic_height;

    States person_state;
    void DoCollision();
};

#endif // Person_H
