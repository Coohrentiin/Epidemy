#include "states.h"
#include "disease.h"

States::States(){
    this->state=State::Healthy;
    this->color=static_cast<Qt::GlobalColor>(State::Healthy);
    this->value=stateToInt(state);
    this->theDisease=new Disease();
    theDisease->addState(stateToInt(state));
    this->aDiseaseParameter=-1;
}

States::States(State state){
    this->state=state;
    this->value=stateToInt(state);
    this->color=static_cast<Qt::GlobalColor>(state);
    this->theDisease=new Disease();
    theDisease->addState(stateToInt(state));
    if(state == State::Carrier){
        int randomNumber=rand()%999+1;
        float u=((float) randomNumber)/1000;
        int k=(int)(-log(1-u)*theDisease->getexpectedSickness());
        this->aDiseaseParameter=k;
    }
    else if(state== State::Sick){
        int randomNumber=rand()%100;
        if(randomNumber<100*theDisease->getMorbidityPb()){
            //he will die, let choose in how many days:
            randomNumber=rand()%999+1;
            float u=((float) randomNumber)/1000;
            int k=(int)(-log(1-u)*theDisease->getexpectedDeath());
            printf("Sick to dead in %d day \n",k);
            this->aDiseaseParameter=(-k-2); //from -k-2 to -2
        }
        else{
            //he will survive, let choose in how many days:
            randomNumber=rand()%100;
            float u=((float) randomNumber)/100;
            int k=(int)(-log(1-u)*theDisease->getexpectedCare());
            printf("Sick to cared in %d day \n",k);
            this->aDiseaseParameter=(k);
        }
    }
    else{
        this->aDiseaseParameter=-1;
    }
}

States::States(State state, Disease * disease){
    this->state=state;
    this->value=stateToInt(state);
    this->color=static_cast<Qt::GlobalColor>(state);
    this->theDisease=disease;
    theDisease->addState( stateToInt(state) );
    if(state == State::Carrier){
        int randomNumber=rand()%999+1;
        float u=((float) randomNumber)/1000;
        int k=(int)(-log(1-u)*theDisease->getexpectedSickness());
        this->aDiseaseParameter=k;
    }
    else if(state== State::Sick){
        int randomNumber=rand()%100;
        if(randomNumber<100*theDisease->getMorbidityPb()){
            //he will die, let choose in how many days:
            randomNumber=rand()%999+1;
            float u=((float) randomNumber)/1000;
            int k=100+(int)(-log(1-u)*theDisease->getexpectedDeath());
            printf("Sick to dead in %d day \n",k);
            this->aDiseaseParameter=(-k-2); //from -k-2 to -2
        }
        else{
            //he will survive, let choose in how many days:
            randomNumber=rand()%100;
            float u=((float) randomNumber)/100;
            int k=100+(int)(-log(1-u)*theDisease->getexpectedCare());
            printf("Sick to cared in %d day \n",k);
            this->aDiseaseParameter=(k);
        }
    }
    else{
        this->aDiseaseParameter=-1;
    }
}

void States::setState(State newState){
    this->state=newState;
    this->value=stateToInt(state);
    this->color=static_cast<Qt::GlobalColor>(state);
}
State States::getState(){
    return state;
}
void States::print(){
    printf("This person is ");
    switch (state) {
        case State::Dead:
            printf("Dead \n");
            break;
        case State::Healthy:
            printf("Healthy \n");
            break;
        case State::Sick:
            printf("Sick \n");
            break;
        case State::Carrier:
            printf("a Carrier \n");
            break;
        case State::Cared:
            printf("Cared \n");
            break;
        default:
            printf("Unknown \n");
            break;
    }
}

Qt::GlobalColor States::getColor(){
    return this->color;
}

int States::stateToInt(State state){
    switch (state) {
        case State::Dead:
            return(4);
            break;
        case State::Healthy:
            return(0);
            break;
        case State::Sick:
            return(2);
            break;
        case State::Carrier:
            return(1);
            break;
        case State::Cared:
            return(3);
            break;
        default:
            return(0);
            break;
    }
}

bool States::operator>(State const& otherState) const{
    return value>otherState;
}

int States::getValue(){
    return value;
}

void States::nextDay(){
   theDisease->nextDay();
   theDisease->print();
}

int States::nextState(int value){
    int randomNumber=0;
    switch (state) {
        case State::Healthy:
            randomNumber=rand()%100;
            if(randomNumber<100*theDisease->getContaminationPb()){
                setState(State::Carrier);
                theDisease->addState(1);
                theDisease->rmState(0);
                randomNumber=rand()%999+1;
                float u=((float) randomNumber)/1000;
                int k=15+(int)(-log(1-u)*theDisease->getexpectedSickness());
//                printf("Carrier to sick in %d day \n",k);
                return(k);
            }
            return(-1);
            break;
        case State::Carrier:
            if(this->aDiseaseParameter!=-1){
                int param=aDiseaseParameter;
                this->aDiseaseParameter=-1;
                return(param);
            }
            //exponential law
            if(value>0){
                return value-1;
            }
            else{
                setState(State::Sick);
                theDisease->addState(2);
                theDisease->rmState(1);
//                printf("    Carrier is now sick");
                //Choose if he will die or be cared
                randomNumber=rand()%100;
                //randomNumber<=(100*theDisease->getMorbidityPb())
                if(randomNumber<=(100*theDisease->getMorbidityPb())){
                    //he will die, let choose in how many days:
                    randomNumber=rand()%999+1;
                    float u=((float) randomNumber)/1000;
                    int k=(int)(-log(1-u)*theDisease->getexpectedDeath());
//                    printf("Sick to dead in %d day \n",-k-2);
                    return(-k-2); //from -k-2 to -2
                }
                else{
                    //he will survive, let choose in how many days:
                    randomNumber=rand()%999+1;
                    float u=((float) randomNumber)/1000;
                    int k=(int)(-log(1-u)*theDisease->getexpectedCare());
//                    printf("Sick to cared in %d day \n",k);
                    return(k);
                }
            }
            break;
        case State::Sick:
//            printf("sick: %d \n",value);
            if(this->aDiseaseParameter!=-1){
//                printf("adiseasparam %d \n",this->aDiseaseParameter);
                int param=aDiseaseParameter;
                if(this->aDiseaseParameter>0){
                    this->aDiseaseParameter=-1;
                }
                else{
                    this->aDiseaseParameter=+1;
                }
                return(param);
            }

            if(value==-2){
                //he is dead now
//                printf("DEAD");
                setState(State::Dead);
                theDisease->addState(4);
                theDisease->rmState(2);
                return -1;
            }
            else if(value==0){
                //he is cared now
                setState(State::Cared);
                theDisease->addState(3);
                theDisease->rmState(2);
                return(-1);
            }

            if(value>0){
//                printf("aie");
                return(value-1);
            }
            else{
//                printf("ouf");
                return(value+1);
            }
            break;
    }
}
