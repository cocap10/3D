// myglwidget.cpp

#include <QtWidgets>
#include <QtOpenGL>

#include "myglwidget.h"

#include <GL/glu.h>
#include <QDebug>

MyGLWidget::MyGLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    xRot = -120;
    yRot = 270;
    zRot = 0;

	xTrans = 0;
    yTrans = 0;
    zTrans = 0;
    setFocus();
}

MyGLWidget::~MyGLWidget()
{
    qDebug()<<"Fin myglwidget";
}

void MyGLWidget::deplacerBras(int a, int b, int t, int p, int o, int nbPas)
{
    int initA=leBras.getAlpha();
    int initB=leBras.getBeta();
    int initT=leBras.getTeta();
    int initP=leBras.getPi();
    int initO=leBras.getOmega();
    int tmpA;
    int tmpB;
    int tmpT;
    int tmpP;
    int tmpO;
    for (int i=0; i<nbPas+1; i++)
    {
        tmpA=(initA*(nbPas-i)+(a*i))/nbPas;
        tmpB=(initB*(nbPas-i)+(b*i))/nbPas;
        tmpT=(initT*(nbPas-i)+(t*i))/nbPas;
        tmpP=(initP*(nbPas-i)+(p*i))/nbPas;
        tmpO=(initO*(nbPas-i)+(o*i))/nbPas;
        leBras.setAlpha(tmpA);
        leBras.setBeta(tmpB);
        leBras.setTeta(tmpT);
        leBras.setPi(tmpP);
        leBras.setOmega(tmpO);
        leBras.draw();
        qDebug()<<i <<"   a: "<<tmpA<<" b: "<<tmpB<<" t: "<<tmpT<<" p: "<<tmpP<<" o: "<<tmpO;
        updateGL();
        QThread::usleep(100);
    }
}

void MyGLWidget::deplacerBalle(int posX, int posY, int posZ, int nbPas)
{
    int initX=laBalle.getX();
    int initY=laBalle.getY();
    int initZ=laBalle.getZ();
    int tmpX;
    int tmpY;
    int tmpZ;
    for (int i=0; i<nbPas+1; i++)
    {
        tmpX=(initX*(nbPas-i)+(posX*i))/nbPas;
        tmpY=(initY*(nbPas-i)+(posY*i))/nbPas;
        tmpZ=(initZ*(nbPas-i)+(posZ*i))/nbPas;
        laBalle.setX(tmpX);
        laBalle.setY(tmpY);
        laBalle.setZ(tmpZ);
        laBalle.draw();
        qDebug()<<i <<"   x: "<<tmpX<<" y: "<<tmpY;
        updateGL();
        QThread::usleep(100);
    }
}

QSize MyGLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize MyGLWidget::sizeHint() const
{
    return QSize(400, 400);
}

static void qNormalizeAngle(int &angle)
{

    while (angle < 0)
        angle += 360 * 1;
    while (angle > 360)
        angle -= 360 * 1;
    //qDebug()<<angle;
}

void MyGLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::initializeGL()
{
    qglClearColor(Qt::black);//couleur de fond

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable ( GL_NORMALIZE );
    glDepthMask ( GL_TRUE );

    static GLfloat lightPosition[4] = { 100, 0, 0, 5.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA);
    glPointSize ( 1.0f );
    glLineWidth ( 1.0f );
    glEnable(GL_COLOR_MATERIAL);
    leBras.init();
    lArene.init();
    laBalle.init();

}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    //Init le system de coordonnee
    glRotatef(90.0,1.0,0.0,0.0);
    glRotatef(90.0,0.0,0.0,1.0);

    //Realiser les transfo du monde
    glTranslatef(-15, 0, 0);
    glRotatef(-xRot , 0.0, 1.0, 0.0);//theta
    glRotatef(-yRot , 0.0, 0.0, 1.0);//phi
    glRotatef(-zRot , 1.0, 0.0, 0.0);

    /*    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);*/

    glTranslatef(xTrans, yTrans, zTrans);

    draw();
}

void MyGLWidget::resizeGL(int width, int height)//propriete camera
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /*#ifdef QT_OPENGL_ES_1
    glOrthof(-2, +2, -2, +2, 1.0, 15.0);
#else
    glOrtho(-2, +2, -2, +2, 1.0, 15.0);
#endif*/
    gluPerspective(70,((float)width/(float)height),0.01,30);
    glMatrixMode(GL_MODELVIEW);
}

void MyGLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + dy);
        setYRotation(yRot + dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + dy);
        setZRotation(zRot + dx);
    }

    lastPos = event->pos();
}

void MyGLWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left)
    {
        yTrans -= 2;
    }
    if (event->key() == Qt::Key_Right)
    {
        yTrans += 2;
    }
    if (event->key() == Qt::Key_Up)
    {
        xTrans -= 2;
    }
    if (event->key() == Qt::Key_Down)
    {
        xTrans += 2;
    }

    if (event->key() == Qt::Key_8)
    {
        zTrans += 2;
    }
    if (event->key() == Qt::Key_2)
    {
        zTrans -= 2;
    }
    if (event->key() == Qt::Key_D)
    {
        this->deplacerBras(20,45,45);
        this->deplacerBalle(-5,8);
    }
    if (event->key() == Qt::Key_I)
    {
        this->deplacerBras();
        this->deplacerBalle();
    }


    updateGL();
}


void MyGLWidget::draw()
{

   leBras.draw();
   laBalle.draw();
   lArene.draw();
}

int MyGLWidget::calculerAngle(int a, int b, int c)
{
    //return acos (param) * 180.0 / PI;
}
