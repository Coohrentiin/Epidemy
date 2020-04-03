#include "disease.h"
//#include "state.h"
#include "ui_dialog.h"
#include <QLabel>
#include <sstream>

Disease::Disease()
{
    contaminationPb=1;   //probability to contaminate by contact
    morbidityPb=0;       //probability to die when you are infacted
    expectedSickness=30;    //expected value of the number of day being a carrier
    expectedCare=60; //expected value of the number of day being sick before become cared
    expectedDeath=0; //expected value of the number of day being sick before die
    numberOfSick=0;
    numberOfHealthy=0;
    numberOfCarrier=0;
    numberOfCared=0;
    numberOfDead=0;
}

Disease::Disease(Ui::Dialog *ui){
    contaminationPb=1;   //probability to contaminate by contact
    morbidityPb=0;       //probability to die when you are infacted
    expectedSickness=30;    //expected value of the number of day being a carrier
    expectedCare=60; //expected value of the number of day being sick before become cared
    expectedDeath=0; //expected value of the number of day being sick before die
    numberOfSick=0;
    numberOfHealthy=0;
    numberOfCarrier=0;
    numberOfCared=0;
    numberOfDead=0;

    gui_param=ui;
    gui_param->information->setText("Coucou de disease");
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

void Disease::print(){
    printf("\n Diseas states:\n");
    printf("    number of healthy people: %d \n",numberOfHealthy);
    printf("    number of carrier people: %d \n",numberOfCarrier);
    printf("    number of sick people: %d \n",numberOfSick);
    printf("    number of cared people: %d \n",numberOfCared);
    printf("    number of dead people: %d \n",numberOfDead);
    printf("Total number of people: %d \n",numberOfHealthy+numberOfCarrier+numberOfSick+numberOfCared+numberOfDead);

    QString message;

    message="\n Diseas states:\n";
    message=message+"    number of healthy people: %1 \n";
    message=message+"    number of carrier people: %2 \n";
    message=message+"    number of sick people: %3 \n";
    message=message+"    number of cared people: %4 \n";
    message=message+"    number of dead people: %5 \n";
    message=message+"Total number of people: %6 \n";
    //-- On devrait voir apparaitre 22 à l'écran
    gui_param->information->setText(message.arg(this->numberOfHealthy).arg(numberOfCarrier).arg(numberOfSick).arg(numberOfCared).arg(numberOfDead).arg(numberOfHealthy+numberOfCarrier+numberOfSick+numberOfCared+numberOfDead));
}
