#include "person.h"
#include <cmath>
#include <iostream>

Person::Person(int width, int heigth, States state, int radius)
{
    //Set scene scale:
    graphic_width=width;
    graphic_height=heigth;

    //random start rotation
    angle = (qrand() % 360);
    setRotation(angle);

    //set the speed
    speed = 4;

    //Set State
    person_state = state;

    //Set Radius
    this->radius=radius;

    //random start position
    int StartX = 0;
    int StartY = 0;

    StartX = (( qrand() % (2* (width-20) ) ) - (width-20) )/2;
    StartY = (( qrand() % (2* (heigth-20) ) ) - (heigth-20) )/2;
    setPos(StartX,StartY);

//    disease=Disease();

}

//Person::Person(int graphic_width, int graphic_heigth, States person_state, int radius, Disease disease){
//    this->disease=disease;
//    Person(graphic_width, graphic_heigth, person_state, radius);
//}

QRectF Person::boundingRect() const
{
    return QRect(0,0,2*radius,2*radius);
}

void Person::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush Brush(Qt::gray);
    QPen pen;
    pen.setBrush(Qt::SolidPattern);
    painter->setPen(pen);
    painter->setBrush(person_state.getColor());
    painter->drawEllipse(rec);

}

void Person::setState(States state){
    person_state=state;
}

States Person::getState(){
    return person_state;
}

void Person::setListOfPerson(std::vector<Person *> list){
    for(int i=0; i<list.size(); i++){
        listOfPerson.push_back(list[i]);
    }
}

void Person::advance(int phase)
{
    if(!phase) return;
    const QList<QGraphicsItem *> collide = scene()->items(QPolygonF()<<mapToParent(0,0)<<mapToParent(10,0)<<mapToParent(0,10)<<mapToParent(10,10));
    collision();
    setPos(mapToParent(0,(speed)));
}


/**
 * @brief Person::collision
 * This function detect collision and proceed sphere direction changes
 * @return true if a collision happen
 */
bool Person::collision(){
    bool collide=false;

    //Position in the scene of the sphere center:
    QPointF center_point=this->centerCoordinate();
    qreal X=center_point.x();
    qreal Y=center_point.y();

    // Set angle betwwen 0 and 360 for tests
    if(rotation()<0){
        setRotation(rotation()+360);
    }
    qreal save_angle=rotation();
    qreal n=1;
    //TODO: this portion of code should be improve, some test can be combine
    //Checks with corners
    //Right to left, up to down
    if(save_angle<90){
        //Check collision with down:
        if( Y+n*radius> (qreal) graphic_height/2){
//            printf("<- u to d  collision down");
            globalSetPosition(90, 20, 0, 0);
            collide=true;
        }
        //Check collision with left:
        else if( X-n*radius < (qreal) -graphic_width/2){
//            printf("<- u to d collision left");
            globalSetPosition(180, 20, 0, 0);
            collide=true;
        }
    }
    //Right to left, down to up
    else if(save_angle<180 && save_angle>90){
        //Check collision with up:
        if( Y-n*radius< (qreal) -graphic_height/2){
//            printf("<- d to u collision up");
            globalSetPosition(-90, 20, 0, 0);
            collide=true;
        }
        //Check collision with left:
        else if( X-n*radius < (qreal) -graphic_width/2){
//            printf("<- d to u collision left");
            globalSetPosition(180, 20, 0, 0);
            collide=true;
        }
    }
    //Left to right, down to up
    else if(save_angle<270 && save_angle>180){
        //Check collision with up:
        if( Y-n*radius< (qreal) -graphic_height/2){
//            printf("-> d to u collision up");
            globalSetPosition(90, 20, 0, 0);
            collide=true;
        }
        //Check collision with right:
        else if( X+n*radius > (qreal) graphic_width/2){
//            printf("-> d to u collision right");
            globalSetPosition(180, 20, 0, 0);
            collide=true;
        }
    }
    //Left to right, up to down
    else if (save_angle>270){
        //Check collision with down:
        if( Y+n*radius> (qreal) graphic_height/2){
//            printf("-> u to d collision down");
            globalSetPosition(-90, 20, 0, 0);
            collide=true;
        }
        //Check collision with right:
        else if( X+n*radius > (qreal) graphic_width/2){
//            printf("-> d to u collision right");
            globalSetPosition(180, 20, 0, 0);
            collide=true;
        }
    }

    // Now is there is no collision with corners (which is the priority), we check is 2 two sphere enter in collision.
    if(!collide){
        /*
         * We will check the distance between the sphere and all others sphere.
         * If the distance is < than 2*radius there is a collision and sphere turn at 180 (plus noise)
        */
        for(Person * aPerson: listOfPerson){
            if(aPerson!=this){
                QPointF aPersonCenter = aPerson->centerCoordinate();
                qreal distance=sqrt( pow((X-aPersonCenter.x()),2) + pow((Y-aPersonCenter.y()),2));

                if(distance<2*radius){
//                    printf("distance=%f \n",distance);
                    //Collision with another sphere
                    globalSetPosition(180, 10, 0, 0);
                    aPerson->globalSetPosition(180, 10, 0, speed/2);
                    collide=true;
                    contamination(aPerson);
                }
            }
        }
    }
    return(collide);
}

/**
 * @brief Person::globalSetPosition
 * @param angle is the value of the rotate angle to apply at the Person current object
 * @param noiseWidthAngle value of additive noise amplitude. Angle will be modificate with a random number in [-noiseWidthAngle/2;noiseWidthAngle/2]
 * @param xAdditiveStep : a facultative value to add at the x relative coordinate before position setting
 * @param yAdditiveStep : a facultative value to add at the y relative coordinate before position setting
 */
void Person::globalSetPosition(int angleToAdd, int noiseWidthAngle, qreal xAdditiveStep, qreal yAdditiveStep){
    int noise=0;
    if(noiseWidthAngle!=0){
        noise= qrand()%(noiseWidthAngle*2)-noiseWidthAngle;
    }
    qreal oldAngle=rotation();
    setRotation( ( (int)rotation() +angleToAdd+noise) % 360 );
    qreal rad_angle= -(oldAngle-rotation())/180*3.1415;
    qreal step_x=(cos(rad_angle)+sin(rad_angle)-1)*radius;
    qreal step_y=(cos(rad_angle)-sin(rad_angle)-1)*radius;
    QPointF newpoint=mapToParent(step_x+xAdditiveStep,step_y+yAdditiveStep);
    setPos(newpoint);
}

/**
 * @brief Person::centerCoordinate
 * Calculate the coordinate of the centre of the Person shape
 * @return
 */
QPointF Person::centerCoordinate(){
    qreal rotation_rad=this->rotation()/180*3.1415;
    qreal a=(qreal) radius * (cos(rotation_rad)-sin(rotation_rad));
    qreal b=(qreal) radius * (cos(rotation_rad)+sin(rotation_rad));
    qreal X= this->pos().x()+a;
    qreal Y= this->pos().y()+b;
    QPointF point(X,Y);
    return point;
}

bool Person::contamination(Person * otherPerson){
    bool isContamination=false;
    if(this->person_state.getValue()>otherPerson->getState().getValue()){
        //"This" is contaminating otherPerson
        printf("contamination %d to %d\n",person_state.getValue(),otherPerson->getState().getValue());
        otherPerson->nextState();
        isContamination=true;
    }
    else if (this->person_state.getValue()<otherPerson->getState().getValue()){
        //OtherPerson is contaminating "This"
        printf("contamination %d to %d\n",otherPerson->getState().getValue(),person_state.getValue());
        this->nextState();
        isContamination=true;
    }
    if(isContamination){
        printf("        now: %d and %d\n",otherPerson->getState().getValue(),person_state.getValue());
    }
    return isContamination;
}

void Person::nextState(){
    person_state.nextState();
}
