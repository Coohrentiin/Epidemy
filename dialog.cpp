#include "dialog.h"
#include "ui_dialog.h"
#include "person.h"
#include "states.h"
#include <cmath>
#include <sstream>
#include <iostream>

Dialog::Dialog(QWidget *parent,int width, int height) :QDialog(parent), ui(new Ui::Dialog){
    ui->setupUi(this);
    ui->startButton->setEnabled(false);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setFixedSize(width+5,height+5);
    ui->information->setText("Coucou");
    scene->setSceneRect(-width/2,-height/2,width,height);
    QPen mypen = QPen(Qt::blue);
//    mypen.setWidth(5);
    QLineF TopLine(scene->sceneRect().topLeft(), scene->sceneRect().topRight());
    QLineF LeftLine(scene->sceneRect().topLeft(), scene->sceneRect().bottomLeft());
    QLineF RightLine(scene->sceneRect().topRight(), scene->sceneRect().bottomRight());
    QLineF BottomLine(scene->sceneRect().bottomLeft(), scene->sceneRect().bottomRight());

    scene->addLine(TopLine,mypen);
    scene->addLine(LeftLine,mypen);
    scene->addLine(RightLine,mypen);
    scene->addLine(BottomLine,mypen);


    std::vector<Person *> listOfItems;
    int radius=5;

    int nbHealthy = 196;
    int nbSick = 20;
    int count=0;
    Disease * sceneDisease=new Disease(ui,nbHealthy+nbSick);

    bool mobility=true;

    int L=(int) sqrt(nbHealthy);
    printf("%d",L);
    L=L+1;
    int dx=width/L;
    int dy;
    if(nbHealthy%(L-1) !=0){
        dy=height/(nbHealthy/(L-1)+2);
    }
    else{
        dy=height/(nbHealthy/(L-1)+1);
    }
    int x=-width/2;
    int y=-height/2;
    x+=dx;
    y+=dy;
    count=0;
    for(int i = 0; i < nbHealthy; i++)
    {
        States state=States(State::Healthy,sceneDisease);
        Person *item = new Person(width,height,state,radius,x,y,mobility);
        count+=1;
        if(count>=L-1){
            y+=dy;
            x=-width/2+dx;
            count=0;
        }
        else{
            x+=dx;
        }
        listOfItems.push_back(item);
        scene->addItem(item);
    }
    for(int i = 0; i < nbSick; i++)
    {
        States state=States(State::Carrier,sceneDisease);
        Person *item = new Person(width,height,state,radius,true);
        count++;
        item->nextState();
        listOfItems.push_back(item);
        scene->addItem(item);
    }
    for (int i=0; i<nbHealthy+nbSick;i++) {
        listOfItems[i]->setListOfPerson(listOfItems);
    }
    printf("\n\n ############ Simulation begining #################### \n\n");
//    QPushButton *bouton = new QPushButton(ui->startButton);
//    connect(bouton, SIGNAL(clicked()), this, SLOT(advance()));
    ui->startButton->setEnabled(true);

}


void Dialog::on_startButton_clicked()
{
    ui->startButton->setEnabled(false);
//    ui->startButton->setText("Stop simulation");
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), scene,SLOT(advance()));
    timer->start(50);
}

Dialog::~Dialog()
{
    delete ui;
}
