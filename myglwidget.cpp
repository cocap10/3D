// myglwidget.cpp

#include <QtWidgets>
#include <QtOpenGL>

#include "myglwidget.h"

#include <GL/glu.h>
#include <QDebug>
#include <QTimer>

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

void MyGLWidget::deplacerBras(double a, double b, double t, int p, int o, int nbPas)
{
    double initA=leBras.getAlpha();
    double initB=leBras.getBeta();
    double initT=leBras.getTeta();
    int initP=leBras.getPi();
    int initO=leBras.getOmega();
    double tmpA;
    double tmpB;
    double tmpT;
    int tmpP;
    int tmpO;
    /*for (int i=0; i<nbPas+1; i++)
    {
        tmpA=(initA*(nbPas-i)+(a*i))/(double)nbPas;
        tmpT=(initT*(nbPas-i)+(t*i))/(double)nbPas;
        updateGL();
    }*/
    for (int i=0; i<nbPas+1; i++)
    {
        tmpA=(initA*(nbPas-i)+(a*i))/(double)nbPas;
        tmpB=(initB*(nbPas-i)+(b*i))/(double)nbPas;
        tmpT=(initT*(nbPas-i)+(t*i))/(double)nbPas;
        tmpP=(initP*(nbPas-i)+(p*i))/nbPas;
        tmpO=(initO*(nbPas-i)+(o*i))/nbPas;
        leBras.setAlpha(tmpA);
        leBras.setBeta(tmpB);
        leBras.setTeta(tmpT);
        leBras.setPi(tmpP);
        leBras.setOmega(tmpO);
        leBras.draw();
        //qDebug()<<i <<"   a: "<<tmpA<<" b: "<<tmpB<<" t: "<<tmpT<<" p: "<<tmpP<<" o: "<<tmpO;
        updateGL();
        QThread::usleep(100);
    }
}


void MyGLWidget::brasAttrapeBalle()
{

    double rayon= sqrt (laBalle.getX()*laBalle.getX()+laBalle.getY()*laBalle.getY())+1;
    double beta=fmod(M_PI/2+(2*atan(laBalle.getY()/(laBalle.getX()+sqrt(laBalle.getX()*laBalle.getX()+laBalle.getY()*laBalle.getY())))),2.0*M_PI);
    beta=beta*180/M_PI;
    double a=5.0;
    double b=rayon;
    double c=8.6;
    double alpha=acos((a*a+b*b-c*c)/(2.0*a*b));
    alpha=M_PI/2-alpha;
    alpha=alpha*180/M_PI;
    a=8.6;
    b=5.0;
    c=rayon;
    double teta=M_PI-acos((a*a+b*b-c*c)/(2.0*a*b));
    teta=teta*180/M_PI;

    qDebug()<<alpha<<" "<<beta<<" "<<teta;
    deplacerBras(alpha,beta,teta);
    balleAttrapee=true;
    deplacerBras(-12.4742,90,137.062);
    laBalle.setX(5.0);
    laBalle.setY(0);
    laBalle.setZ(0);
    balleAttrapee=false;
    updateGL();




}

void MyGLWidget::deplacerBalle(double posX, double posY, double posZ, int nbPas)
{
    double initX=laBalle.getX();
    double initY=laBalle.getY();
    double initZ=laBalle.getZ();
    double tmpX;
    double tmpY;
    double tmpZ;
    for (int i=0; i<nbPas+1; i++)
    {
        tmpX=(initX*(nbPas-i)+(posX*i))/nbPas;
        tmpY=(initY*(nbPas-i)+(posY*i))/nbPas;
        tmpZ=(initZ*(nbPas-i)+(posZ*i))/nbPas;
        laBalle.setX(tmpX);
        laBalle.setY(tmpY);
        laBalle.setZ(tmpZ);
        laBalle.draw();
        //qDebug()<<i <<"   x: "<<tmpX<<" y: "<<tmpY;
        updateGL();
        QThread::usleep(100);
        //qDebug()<<"balle :"<<(int)laBalle.getX()<<" "<<(int)laBalle.getY();
        //qDebug()<<"cible :"<<(int)lArene.getXCible()<<" "<<(int)lArene.getYCible();
        if((int)laBalle.getX()==(int)lArene.getXCible() && (int)laBalle.getY()==(int)lArene.getYCible())
        {
            qDebug()<<"BALLE SUR CIBLE";
            emit finPartie();
            brasAttrapeBalle();
            reinitJeu();

        }
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
    if (event->key() == Qt::Key_A)
    {
        this->brasAttrapeBalle();
    }

    if (event->key() == Qt::Key_Y)
    {
        lArene.positionnerCible();
    }


    updateGL();
}


void MyGLWidget::draw()
{
    if (!balleAttrapee)
    {

        laBalle.draw();
        leBras.draw();
    }

    else
    {
        leBras.draw2();
    }
    lArene.draw();
}

void MyGLWidget::reinitJeu()
{
    deplacerBras();
    lArene.positionnerCible();
    laBalle.setX(0);
    laBalle.setY(0);
    laBalle.setZ(0);

}
