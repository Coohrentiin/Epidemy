#include "dialog.h"
#include "ui_dialog.h"
#include "person.h"
#include "states.h"

Dialog::Dialog(QWidget *parent,int width, int height) :QDialog(parent), ui(new Ui::Dialog){
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    scene->setSceneRect(-width/2,-height/2,width,height);
    QPen mypen = QPen(Qt::blue);
    QLineF TopLine(scene->sceneRect().topLeft(), scene->sceneRect().topRight());
    QLineF LeftLine(scene->sceneRect().topLeft(), scene->sceneRect().bottomLeft());
    QLineF RightLine(scene->sceneRect().topRight(), scene->sceneRect().bottomRight());
    QLineF BottomLine(scene->sceneRect().bottomLeft(), scene->sceneRect().bottomRight());

    scene->addLine(TopLine,mypen);
    scene->addLine(LeftLine,mypen);
    scene->addLine(RightLine,mypen);
    scene->addLine(BottomLine,mypen);


    int ItemCount = 5;
    for(int i = 0; i < ItemCount; i++)
    {
        States state=States(State::Sick);
        Person *item = new Person(width,height,state);
        scene->addItem(item);
    }
    for(int i = 0; i < ItemCount; i++)
    {
        States state=States(State::Healthy);
        Person *item = new Person(width,height,state);
        scene->addItem(item);
    }

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), scene,SLOT(advance()));
    timer->start(100);

}

Dialog::~Dialog()
{
    delete ui;
}