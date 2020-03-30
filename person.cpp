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
//    setRotation( rotation() -60 );
}

//virtual int Person::type() override{
//    int n=42;
//    return n;
//}

QRectF Person::boundingRect() const
{
    return QRect(0,0,2*radius,2*radius);
}

void Person::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush Brush(Qt::gray);
    //basic Collision detection
    QPen pen;
    pen.setBrush(Qt::SolidPattern);
    painter->setPen(pen);
    painter->setBrush(person_state.getColor());
//    painter->drawRect(rec);
    painter->drawEllipse(rec);

}

void Person::setState(States state){
    person_state=state;
}

void Person::setListOfPerson(std::vector<Person *> list){
    for(int i=0; i<list.size(); i++){
        listOfPerson.push_back(list[i]);
    }
}

void Person::advance(int phase)
{
    if(!phase) return;
//    QPointF location = this->pos();

//    const QList<QGraphicsItem *> collide = scene()->items(QPolygonF()<<mapToParent(6,6)<<mapToParent(6,-6)<<mapToParent(-6,-6)<<mapToParent(-6,6));
//    const QList<QGraphicsItem *> collide = scene()->items(QPolygonF()<<mapToParent(6,6)<<mapToParent(-6,-6)<<mapToParent(0,-6)<<mapToParent(6,0));
    const QList<QGraphicsItem *> collide = scene()->items(QPolygonF()<<mapToParent(0,0)<<mapToParent(10,0)<<mapToParent(0,10)<<mapToParent(10,10));
//    if(!scene()->collidingItems(this).isEmpty())
    collision();
    if(!collision()){
        setPos(mapToParent(0,(speed)));
    }
    else{
//        setPos(mapToParent(0,(-speed/2)));
    }
//    if(collide.size()>1)
//    {
//        //Set the position
////        DoCollision();
////        printf("colision detected with:%d \n",a);
//    }
//    else{
//        setPos(mapToParent(0,(speed)));
//    }
//    person_state.print();
}

void Person::DoCollision()
{
    //Find the colliding direction
    const QList<QGraphicsItem *> frontCollide = scene()->items(QPolygonF()<<mapToScene(5,0)<<mapToScene(10,0)<<mapToScene(10,10)<<mapToScene(10,5));
    const QList<QGraphicsItem *> backCollide = scene()->items(QPolygonF()<<mapToScene(0,0)<<mapToScene(5,0)<<mapToScene(10,5)<<mapToScene(10,0));

    int front = frontCollide.size();
    int back = backCollide.size();

    for (const QGraphicsItem *item : frontCollide) {
            if (item == this){
                front=front-1;
            }
    }
    for (const QGraphicsItem *item : backCollide) {
            if (item == this){
                back=back-1;
            }
    }
//    printf("detection: front=%d,back=%d \n",front,back);

    qreal corner=-5;
    QPointF newpoint = mapToScene(10,-corner);
    if(front>0){
        newpoint = mapToScene(10,-corner);
        //Change the angle with a little randomness
        if(((qrand() %1)))
        {
            setRotation(( (int) rotation() + (180 + (qrand() % 20 )))%360);
        }
        else
        {
            setRotation(( (int) rotation() + (180 + (qrand() % -20 )))%360);
        }
    }
    else if(back>0){
        newpoint = mapToScene(0,speed+1);
        //Change the angle with a little randomness
        if(((qrand() %1)))
        {
            setRotation(( (int)rotation() + ((qrand() % 20 )))%360);
        }
        else
        {
            setRotation(( (int)rotation() + ((qrand() % -20 )))%360);
        }
    }
    else{
        newpoint = mapToScene(10,-corner);
        //Change the angle with a little randomness
        if(((qrand() %1)))
        {
            setRotation(( (int) rotation() + (180 + (qrand() % 20 )))%360);
        }
        else
        {
            setRotation(( (int) rotation() + (180 + (qrand() % -20 )))%360);
        }
    }
    setPos(newpoint);

//    setRotation(rotation() + 180);

    if(!scene()->sceneRect().contains((newpoint)))
    {
        //move it back in bounds
        newpoint = mapToParent(0,0);
    }

}

bool Person::collision(){
    bool collide=false;
    QPointF point = this->pos();
    QPointF newpoint = mapToScene(0,0);


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
    //Checks with corners
    //Right to left, up to down
    if(save_angle<90){
        //Check collision with down:
        if( Y+n*radius> (qreal) graphic_height/2){
            printf("<- u to d  collision down");
            setRotation( ( (int)rotation() +90) % 360 );
            collide=true;
        }
        //Check collision with left:
        else if( X-n*radius < (qreal) -graphic_width/2){
            printf("<- u to d collision left");
            setRotation( ( -(int)rotation()) % 360 );
            collide=true;
        }
    }
    //Right to left, down to up
    else if(save_angle<180 && save_angle>90){
        //Check collision with up:
        if( Y-n*radius< (qreal) -graphic_height/2){
            printf("<- d to u collision up");
            setRotation( ( (int)rotation() -90) % 360 );
            collide=true;
        }
        //Check collision with left:
        else if( X-n*radius < (qreal) -graphic_width/2){
            printf("<- d to u collision left");
            setRotation( ( -(int)rotation() ) % 360 );
            collide=true;
        }
    }
    //Left to right, down to up
    else if(save_angle<270 && save_angle>180){
        //Check collision with up:
        if( Y-n*radius< (qreal) -graphic_height/2){
            printf("-> d to u collision up");
            setRotation( ( (int)rotation() +90) % 360 );
            collide=true;
        }
        //Check collision with right:
        else if( X+n*radius > (qreal) graphic_width/2){
            printf("-> d to u collision right");
            setRotation( ( -(int)rotation() ) % 360 );
            collide=true;
        }
    }
    //Left to right, up to down
    else if (save_angle>270){
        //Check collision with down:
        if( Y+n*radius> (qreal) graphic_height/2){
            printf("-> u to d collision down");
            setRotation( ( (int)rotation() -90) % 360 );
            collide=true;
        }
        //Check collision with right:
        else if( X+n*radius > (qreal) graphic_width/2){
            printf("-> d to u collision right");
            setRotation( ( -(int)rotation()) % 360 );
            collide=true;
        }
    }

    if(collide){
        int noise= qrand()%40-20;
        setRotation( ((int)rotation()+noise) % 360 );
        qreal rad_angle= -(save_angle-rotation())/180*3.1415;
        qreal step_x=(cos(rad_angle)+sin(rad_angle)-1)*radius;
        qreal step_y=(cos(rad_angle)-sin(rad_angle)-1)*radius;
        newpoint=mapToParent(step_x,step_y);
    }
    // Now is there is no collision with corners (which is the priority), we check is 2 two sphere enter in collision.
    else{
        /*
         * We will check the distance between the sphere and all others sphere.
         * If the distance is < than 2*radius there is a collision and sphere turn at 180 (plus noise)
        */
        for(Person * aPerson: listOfPerson){
            if(aPerson!=this){
                QPointF aPersonCenter = aPerson->centerCoordinate();
                qreal distance=sqrt( pow((X-aPersonCenter.x()),2) + pow((Y-aPersonCenter.y()),2));

                if(distance<2*radius){
                    printf("distance=%f \n",distance);
                    //Collision with another sphere
                    int noise= qrand()%40-20;
                    setRotation( ((int)rotation()+180) % 360 );
                    qreal rad_angle= -(save_angle-rotation())/180*3.1415;
                    qreal step_x=(cos(rad_angle)+sin(rad_angle)-1)*radius;
                    qreal step_y=(cos(rad_angle)-sin(rad_angle)-1)*radius;
                    newpoint=mapToParent(step_x,step_y);

                    qreal save_angle_aperson=aPerson->rotation();
                    aPerson->setRotation( ((int)aPerson->rotation()+180) % 360 );
                    qreal rad_angle_aperson= -(save_angle_aperson-aPerson->rotation())/180*3.1415;
                    qreal step_x_aperson=(cos(rad_angle_aperson)+sin(rad_angle_aperson)-1)*radius;
                    qreal step_y_aperson=(cos(rad_angle_aperson)-sin(rad_angle_aperson)-1)*radius;
                    QPointF newpoint_aperson=aPerson->mapToParent(step_x_aperson,step_y_aperson+speed);
                    aPerson->setPos(newpoint_aperson);

                    collide=true;
                }
            }
        }
    }
    setPos(newpoint);
    return(collide);
}

QPointF Person::centerCoordinate(Person aPerson){
    qreal rotation_rad=aPerson.rotation()/180*3.1415;
    qreal a=(qreal) radius * (cos(rotation_rad)-sin(rotation_rad));
    qreal b=(qreal) radius * (cos(rotation_rad)+sin(rotation_rad));
    qreal X= aPerson.pos().x()+a;
    qreal Y= aPerson.pos().y()+b;
    QPointF point(X,Y);
    return point;
}

QPointF Person::centerCoordinate(){
    qreal rotation_rad=this->rotation()/180*3.1415;
    qreal a=(qreal) radius * (cos(rotation_rad)-sin(rotation_rad));
    qreal b=(qreal) radius * (cos(rotation_rad)+sin(rotation_rad));
    qreal X= this->pos().x()+a;
    qreal Y= this->pos().y()+b;
    QPointF point(X,Y);
    return point;
}
