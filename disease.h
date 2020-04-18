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
    Disease(Ui::Dialog * ui, int total);
    Disease(double contaminationPb, double morbidityPb, double expectedSickness, double expectedCare, double expectedDeath);
    double getContaminationPb();
    double getMorbidityPb();
    double getexpectedSickness();
    double getexpectedCare();
    double getexpectedDeath();
    void addState(int state);
    void rmState(int state);
    void print();
    void PrintPlot(Ui::Dialog *ui);
    void PrintPlotInit(Ui::Dialog *ui);

    void nextDay();

    void SetData();

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

    int total_number;
    QVector<double> days;
    QVector<double> healthyList;
    QVector<double> sickList;
    QVector<double> carrierList;
    QVector<double> caredList;
    QVector<double> deadList;

    int day;
    int X_range;
    Ui::Dialog * gui_param;
};

#endif // DISEASE_H
