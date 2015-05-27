// window.cpp

#include <QtWidgets>
#include "window.h"
#include "ui_window.h"

#include "myglwidget.h"

Window::Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
    connect(ui->widget, SIGNAL(posUpdated()),this, SLOT(setPos()));
    //connect(ui->webCamWidget, SIGNAL(locChanged()), , SLOT(updatePointeur()));
}

Window::~Window()
{
    delete ui;
}

void Window::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}
void Window::setPos() {
    double x = ui->widget->x();
    double y = ui->widget->y();
    qDebug()<<"balle1 (x,y)  : "<<x<<", "<<y;
    x=10-x*20;
    y=10-y*20;
    //qDebug()<<"balle (x,y)  : "<<x<<", "<<y;
    /*double angle=fmod((2*atan(y/(x+sqrt(x*x+y*y)))+M_PI),2.0*M_PI);


    //qDebug()<<"angle   : "<<angle;
    double maxX=10*cos(angle);
    double maxY=10*sin(angle);
    qDebug()<<"Max (x,y)  : "<<maxX<<", "<<maxY;
    qDebug()<<"balle1 (x,y)  : "<<x<<", "<<y;
    if (x>0)
        x=std::min(x,maxX-1);
    else
        x=std::max(x,maxX+1);
    if (y>0)
        y=std::min(y,maxY-1);
    else
        y=std::max(y,maxY+1);
    qDebug()<<"balle2 (x,y)  : "<<x<<", "<<y;*/

    ui->myGLWidget->deplacerBalle(x, y,1,4);
}
