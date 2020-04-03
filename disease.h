#ifndef DISEASE_H
#define DISEASE_H

//#include "person.h"
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "ui_dialog.h"
//#include "state.h"

class Disease
{

public:
    Disease();
    Disease(Ui::Dialog * ui);
    Disease(double contaminationPb, double morbidityPb, double expectedSickness, double expectedCare, double expectedDeath);
    double getContaminationPb();
    double getMorbidityPb();
    double getexpectedSickness();
    double getexpectedCare();
    double getexpectedDeath();
    void addState(int state);
    void rmState(int state);
    void print();

private:
    double contaminationPb;
    double morbidityPb;
    double expectedSickness;
    double expectedCare;
    double expectedDeath;

    int numberOfSick;
    int numberOfHealthy;
    int numberOfCarrier;
    int numberOfCared;
    int numberOfDead;

    Ui::Dialog * gui_param;
};

#endif // DISEASE_H
