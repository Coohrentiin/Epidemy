#include "person.h"
#include <cmath>
#include <iostream>

Person::Person(int width, int heigth, States state)
{
    //random start rotation
    angle = (qrand() % 360);
    setRotation(angle);

    //set the speed
    speed = 4;

    //Set State
    person_state = state;

    //random start position
    int StartX = 0;
    int StartY = 0;

    StartX = (( qrand() % (2* (width-20) ) ) - (width-20) )/2;
    StartY = (( qrand() % (2* (heigth-20) ) ) - (heigth-20) )/2;

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
//    painter->drawRect(rec);
    painter->drawEllipse(rec);

}

void Person::setState(States state){
    person_state=state;
}

void Person::advance(int phase)
{
    if(!phase) return;
//    QPointF location = this->pos();

//    const QList<QGraphicsItem *> collide = scene()->items(QPolygonF()<<mapToParent(6,6)<<mapToParent(6,-6)<<mapToParent(-6,-6)<<mapToParent(-6,6));
//    const QList<QGraphicsItem *> collide = scene()->items(QPolygonF()<<mapToParent(6,6)<<mapToParent(-6,-6)<<mapToParent(0,-6)<<mapToParent(6,0));
    const QList<QGraphicsItem *> collide = scene()->items(QPolygonF()<<mapToParent(0,0)<<mapToParent(10,0)<<mapToParent(0,10)<<mapToParent(10,10));
//    if(!scene()->collidingItems(this).isEmpty())
    if(collide.size()>1)
    {
        //Set the position
        QGraphicsItem *item=collide[0];
        DoCollision();
        int a = scene()->collidingItems(this).size();
        printf("colision detected with:%d \n",a);
    }
    else{
        setPos(mapToParent(0,(speed)));
    }
//    person_state.print();
}

void Person::DoCollision()
{
    //Find the colliding direction
    const QList<QGraphicsItem *> frontCollide = scene()->items(QPolygonF()<<mapToScene(5,0)<<mapToScene(10,0)<<mapToScene(10,10)<<mapToScene(10,5));
    const QList<QGraphicsItem *> backCollide = scene()->items(QPolygonF()<<mapToScene(0,0)<<mapToScene(5,0)<<mapToScene(10,5)<<mapToScene(10,0));

    int front = frontCollide.size();
    int back = backCollide.size();

    for (const QGraphicsItem *item : frontCollide) {
            if (item == this){
                front=front-1;
            }
    }
    for (const QGraphicsItem *item : backCollide) {
            if (item == this){
                back=back-1;
            }
    }
    printf("detection: front=%d,back=%d \n",front,back);

    qreal corner=-5;
    QPointF newpoint = mapToScene(10,-corner);
    if(front>0){
        newpoint = mapToScene(10,-corner);
        //Change the angle with a little randomness
        if(((qrand() %1)))
        {
            setRotation(rotation() + (180 + (qrand() % 20 )));
        }
        else
        {
            setRotation(rotation() + (180 + (qrand() % -20 )));
        }
    }
    else if(back>0){
        newpoint = mapToScene(0,speed+1);
        //Change the angle with a little randomness
        if(((qrand() %1)))
        {
            setRotation(rotation() + ((qrand() % 20 )));
        }
        else
        {
            setRotation(rotation() + ((qrand() % -20 )));
        }
    }
    else{
        newpoint = mapToScene(10,-corner);
        //Change the angle with a little randomness
        if(((qrand() %1)))
        {
            setRotation(rotation() + (180 + (qrand() % 20 )));
        }
        else
        {
            setRotation(rotation() + (180 + (qrand() % -20 )));
        }
    }
    setPos(newpoint);

//    setRotation(rotation() + 180);

    if(!scene()->sceneRect().contains((newpoint)))
    {
        //move it back in bounds
        newpoint = mapToParent(0,0);
    }

}
