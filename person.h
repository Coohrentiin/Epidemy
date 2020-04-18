#ifndef Person_H
#define Person_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "states.h"
//#include "disease.h"

class Person : public QGraphicsItem
{
public:
    //Constructors:
    Person(int graphic_width, int graphic_heigth, States person_state, int radius, int x, int y, bool mobility);
    Person(int graphic_width, int graphic_heigth, States person_state, int radius, bool mobility);
    Person(int graphic_width, int graphic_heigth, States person_state, int radius, Disease disease, int name);

    //Public methods for drawing
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    //Outside informations
    std::vector<Person *> listOfPerson;

    //Outside method:
    void setListOfPerson(std::vector<Person *> list);

    //Getter Setter
    void setState(States astate);
    States getState();
    bool getMobility();
    void nextState();
    int getSpeed();

protected:
    //Movement fonctions and methods
    void advance(int phase);
    void globalSetPosition(int angleToAdd, int noiseWidthAngle, qreal xAdditiveStep, qreal yAdditiveStep);
    bool collision();
    bool contamination(Person * otherPerson);
    QPointF centerCoordinate();

private:
    //Geometric attributes
    qreal angle;
    qreal speed;
    int radius;
    int timeDiseaseParameter;
    //Screen definition attributs
    int graphic_width;
    int graphic_height;
    int name;

    bool randomPosition;
    bool mobility;
    //Outside informations
    States person_state;
    Disease disease;
};

#endif // Person_H
