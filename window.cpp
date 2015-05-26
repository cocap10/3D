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
    int x = ui->widget->x();
    int y = ui->widget->y();

    double xCursor = 10-(double)x/13.5;
    double yCursor = 10-(double)y/9.5;

    ui->myGLWidget->deplacerBalle(xCursor, yCursor,1,1);
}
