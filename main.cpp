#include "dialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    printf("Main \n");
    QApplication a(argc, argv);
    QWidget *parent=new QWidget;
    Dialog *w= new Dialog(parent, 600, 600);
    w->show();

    return a.exec();
}
