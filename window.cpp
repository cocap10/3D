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
    x=x*20-10;
    y=y*20-10;
    //qDebug()<<"balle (x,y)  : "<<x<<", "<<y;
    double angle=fmod((2*atan(y/(x+sqrt(x*x+y*y)))),2.0*M_PI);


    //qDebug()<<"angle   (en degre) : "<<angle*180.0/M_PI;
    double maxX=9*cos(angle);
    double maxY=9*sin(angle);
    if (x>0)
        x=std::min(x,maxX);
    else
        x=std::max(x,maxX);
    if (y>0)
        y=std::min(y,maxY);
    else
        y=std::max(y,maxY);
    ui->myGLWidget->deplacerBalle(x, y,1,4);
}
