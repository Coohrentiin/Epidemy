#include "states.h"

States::States(){
    this->state=State::Healthy;
    this->color=static_cast<Qt::GlobalColor>(State::Healthy);
}

States::States(State state){
    this->state=state;
    this->color=static_cast<Qt::GlobalColor>(state);
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
