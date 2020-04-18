#include "disease.h"
//#include "state.h"
#include "ui_dialog.h"
#include <QLabel>
#include <sstream>

Disease::Disease()
{
    contaminationPb=1;   //probability to contaminate by contact
    morbidityPb=1;       //probability to die when you are infacted
    expectedSickness=180;    //expected value of the number of day being a carrier
    expectedCare=360; //expected value of the number of day being sick before become cared
    expectedDeath=400; //expected value of the number of day being sick before die
    numberOfSick=0;
    numberOfHealthy=0;
    numberOfCarrier=0;
    numberOfCared=0;
    numberOfDead=0;
    day=0;
}

Disease::Disease(Ui::Dialog *ui, int total){
    total_number=total;
    contaminationPb=1;   //probability to contaminate by contact
    morbidityPb=0.02;       //probability to die when you are infacted
    expectedSickness=300;    //expected value of the number of day being a carrier
    expectedCare=600; //expected value of the number of day being sick before become cared
    expectedDeath=600; //expected value of the number of day being sick before die
    numberOfSick=0;
    numberOfHealthy=0;
    numberOfCarrier=0;
    numberOfCared=0;
    numberOfDead=0;
    day=0;
    X_range=200;
    gui_param=ui;
    gui_param->information->setText("Please press \"start\" button to lanch");
    PrintPlotInit(ui);
}

Disease::Disease(double contaminationPb, double morbidityPb, double expectedSickness, double expectedCare, double expectedDeath){
    this->contaminationPb=contaminationPb;
    this->morbidityPb=morbidityPb;
    this->expectedSickness=expectedSickness;
    this->expectedCare=expectedCare;
    this->expectedDeath=expectedDeath;
    numberOfSick=0;
    numberOfHealthy=0;
    numberOfCarrier=0;
    numberOfCared=0;
    numberOfDead=0;
    day=0;
}

double Disease::getContaminationPb(){
    return(contaminationPb);
}
double Disease::getMorbidityPb(){
    return morbidityPb;
}
double Disease::getexpectedSickness(){
    return expectedSickness;
}
double Disease::getexpectedCare(){
    return expectedCare;
}
double Disease::getexpectedDeath(){
    return expectedDeath;
}

void Disease::addState(int state){
    switch (state) {
        case 0:
            this->numberOfHealthy+=1;
            break;
        case 1:
            this->numberOfCarrier+=1;
            break;
        case 2:
            this->numberOfSick+=1;
            break;
        case 3:
            this->numberOfCared+=1;
            break;
        case 4:
            this->numberOfDead+=1;
            break;
    }
}
void Disease::rmState(int state){
    switch (state) {
        case 0:
            this->numberOfHealthy-=1;
            break;
        case 1:
            this->numberOfCarrier-=1;
            break;
        case 2:
            this->numberOfSick-=1;
            break;
        case 3:
            this->numberOfCared-=1;
            break;
        case 4:
            this->numberOfDead-=1;
            break;
    }
}

void Disease::nextDay(){
    day++;
    if(day%total_number==0){
        SetData();
    }
}

void Disease::print(){
//    printf("\n Diseas states:\n");
//    printf("    number of healthy people: %d \n",numberOfHealthy);
//    printf("    number of carrier people: %d \n",numberOfCarrier);
//    printf("    number of sick people: %d \n",numberOfSick);
//    printf("    number of cared people: %d \n",numberOfCared);
//    printf("    number of dead people: %d \n",numberOfDead);
//    printf("Total number of people: %d \n",numberOfHealthy+numberOfCarrier+numberOfSick+numberOfCared+numberOfDead);
    int tot=numberOfHealthy+numberOfCarrier+numberOfSick+numberOfCared+numberOfDead;
    QString message;

    message="\n Disease state day %7:\n";
    message=message+"    healthy  : %1 \n";
    message=message+"    carrier  : %2 \n";
    message=message+"    sick     : %3 \n";
    message=message+"    cured    : %4 \n";
    message=message+"    dead     : %5 \n";
    message=message+"Total number of people: %6 \n";

    gui_param->information->setText(message.arg(this->numberOfHealthy).arg(numberOfCarrier).arg(numberOfSick).arg(numberOfCared).arg(numberOfDead).arg(numberOfHealthy+numberOfCarrier+numberOfSick+numberOfCared+numberOfDead).arg(day/tot));
    if(day%(tot*20) == 0){
            PrintPlot(gui_param);
    }
}
void Disease::PrintPlotInit(Ui::Dialog *ui){
    // create graph:
    ui->customPlot->addGraph();
    ui->customPlot->graph()->setLineStyle((QCPGraph::LineStyle)1);
    ui->customPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("step");
    ui->customPlot->yAxis->setLabel("number");
    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(0, X_range);
    ui->customPlot->yAxis->setRange(0, total_number);
    ui->customPlot->replot();
}

void Disease::SetData(){
    this->days.append(day/total_number);
    this->healthyList.append(numberOfHealthy);
    this->sickList.append(numberOfSick);
    this->carrierList.append(numberOfCarrier);
    this->caredList.append(numberOfCared);
    this->deadList.append(numberOfDead);
}

void Disease::PrintPlot(Ui::Dialog *ui){
    QPen pen;
    // generate some data:
    if(day/total_number+5>X_range){
        X_range=X_range+200;
        ui->customPlot->xAxis->setRange(0,X_range);
    }
    ui->customPlot->addGraph();
    pen.setColor( Qt::green );
    ui->customPlot->graph()->setPen( pen);
    ui->customPlot->graph()->setData( days, healthyList);

    ui->customPlot->addGraph();
    pen.setColor( Qt::red );
    ui->customPlot->graph()->setPen( pen);
    ui->customPlot->graph()->setData( days, sickList);

    ui->customPlot->addGraph();
    pen.setColor( Qt::cyan );
    ui->customPlot->graph()->setPen( pen);
    ui->customPlot->graph()->setData( days, carrierList);

    ui->customPlot->addGraph();
    pen.setColor( Qt::blue );
    ui->customPlot->graph()->setPen( pen);
    ui->customPlot->graph()->setData( days, caredList);

    ui->customPlot->addGraph();
    pen.setColor( Qt::black );
    ui->customPlot->graph()->setPen( pen);
    ui->customPlot->graph()->setData( days, deadList);

    ui->customPlot->replot();
//    ui->customPlot->update();
}

