#include "states.h"

States::States(){
    this->state=State::Healthy;
    this->color=static_cast<Qt::GlobalColor>(State::Healthy);
    this->value=stateToInt(state);
}

States::States(State state){
    this->state=state;
    this->value=stateToInt(state);
    this->color=static_cast<Qt::GlobalColor>(state);
    this->value=stateToInt(state);
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
            return(2);
            break;
        case State::Healthy:
            return(1);
            break;
        case State::Sick:
            return(3);
            break;
        case State::Carrier:
            return(2);
            break;
        case State::Cared:
            return(4);
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

State States::IntToState(int value){
    switch (value) {
        case 1:
            return(State::Healthy);
            break;
        case 3:
            return(State::Sick);
            break;
        case 2:
            return(State::Carrier);
            break;
        case 4:
            return(State::Cared);
            break;
        default:
            return(State::Healthy);
            break;
    }
}

void States::nextState(){
    if(value<4){
        value=value+1;
        this->state=IntToState(value);
        this->color=static_cast<Qt::GlobalColor>(state);
    }
}
