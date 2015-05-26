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
    x=x*20-10;
    y=y*20-10;
    qDebug()<<"balle (x,y)  : "<<x<<", "<<y;
    double angle=atan(y/x);
    double maxX=10*cos(angle)-1;
    double maxY=10*sin(angle)-1;
    if (x>0)
        x=std::min(x,maxX);
    else
        x=std::max(x,-maxX);
    if (y>0)
        y=std::min(y,maxY);
    else
        y=std::max(y,-maxY);

    ui->myGLWidget->deplacerBalle(x, y,1,4);
}
