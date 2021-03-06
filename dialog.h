#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <vector>
#include "person.h"
#include "disease.h"

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog(QWidget *parent = 0);
    explicit Dialog(QWidget *parent = 0,int width=200, int height=200);
    explicit Dialog(int width=200, int height=200);
    ~Dialog();
    void PrintFunction(Ui::Dialog *ui);

private slots:
    void on_startButton_clicked();

private:
    Ui::Dialog *ui;
    QGraphicsScene *scene;
    QTimer *timer;
};

#endif // DIALOG_H
