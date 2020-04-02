#include "disease.h"
//#include "state.h"

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
}
