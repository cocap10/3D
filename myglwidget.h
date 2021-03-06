// myglwidget.h

#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <GL/glu.h>
#include <QThread>
#include <bras.h>
#include <arene.h>
#include <balle.h>
#include <math.h>

class MyGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = 0);
    ~MyGLWidget();
    void deplacerBras(double a=0.0, double b=0.0,double t=0.0,int p=0,int o=45, int nbPas=50);
    void brasAttrapeBalle();
    void deplacerBalle(double posX=5.0, double posY=5.0, double posZ=1.0, int nbPas=100);
signals:

public slots:

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);



public slots:
    // slots for xyz-rotation slider
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

signals:
    // signaling rotation from mouse movement
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);
    void finPartie();

private:
    void draw();
    void reinitJeu();

    int xRot;
    int yRot;
    int zRot;

    int xTrans;
    int yTrans;
    int zTrans;

    QPoint lastPos;

    bool balleAttrapee;

    Bras leBras;
    Arene lArene;
    Balle laBalle;
};

#endif // MYGLWIDGET_H

