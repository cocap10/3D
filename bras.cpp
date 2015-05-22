#include "bras.h"
#include <QDebug>
Bras::Bras()
{
    alpha=0;
    beta=0;
    teta=0;
    pi=0;
    omega=0;



}

Bras::~Bras()
{
    qDebug()<<"Fin bras";

}

void Bras::init()
{
    GLtexture[0]= loadtgadisplayCDV("earth.tga");
    GLtexture[1]= loadtgadisplayCDV("BDS.tga");
    qDebug()<<"texture 0 : "<<GLtexture[0]<<"\ntexture 1 : "<<GLtexture[1];
    listCylindre=glGenLists(1);
    listCylindre2=glGenLists(1);
    listDemiBras=glGenLists(1);
    listDoigt=glGenLists(1);
    qDebug()<< "listCylindre"<<listCylindre << "\n";
    qDebug()<< "listDemiBras"<<listDemiBras << "\n";
    qDebug()<< "listDoigt"<<listDoigt << "\n";

    quadric=gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL);

    glNewList(listCylindre, GL_COMPILE);
    glPushMatrix();
        gluDisk(quadric,0,0.5,20,10);
        gluCylinder(quadric,0.5,0.5,1,20,20);
        glTranslatef(0,0,1);
        gluDisk(quadric,0,0.5,20,10);
    glPopMatrix();
    glEndList();

    glNewList(listCylindre2, GL_COMPILE);
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, GLtexture[1]);
    gluQuadricTexture(quadric,1);
        gluDisk(quadric,0,0.5,20,10);
        gluCylinder(quadric,0.5,0.5,1,20,20);
        glTranslatef(0,0,1);
        gluDisk(quadric,0,0.5,20,10);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glEndList();

    glNewList(listDemiBras, GL_COMPILE);
    glPushMatrix();
        glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, GLtexture[0]);
            gluQuadricTexture(quadric,1);
            glScalef(2,2,2);
            gluSphere(quadric,0.5,10,10);
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();

        glPushMatrix();

            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, GLtexture[1]);
            gluQuadricTexture(quadric,1);
            glTranslatef(0,0,1);
            glScalef(2,2,6);
            glCallList(listCylindre2);
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    glPopMatrix();
    glEndList();
    gluDeleteQuadric(quadric);

    glNewList(listDoigt, GL_COMPILE);
    glPushMatrix();
        glPushMatrix();
            //phalange 1
            glTranslatef(0,0,0.2);
            glScalef(0.3,0.3,1.5);
            glCallList(listCylindre);
        glPopMatrix();
        glTranslatef(0,0,2.2);
        glRotatef(-90,1,0,0);
        glPushMatrix();
            //phalange 2
            glTranslatef(0,0,0.4);
            glScalef(0.3,0.3,1.5);
            glCallList(listCylindre);
        glPopMatrix();
    glPopMatrix();
    glEndList();



}

void Bras::draw()
{

    qDebug()<<"Draw Bras";
       //socle
    glPushMatrix();
        glScalef(5,5, 0.5);
        glCallList(listCylindre);
    glPopMatrix();

    glPushMatrix();
        glRotatef(alpha,1,0,0);
        glRotatef(beta, 0,1,0);
        //bras
        glPushMatrix();
            //debut-bras
            glTranslatef(0,0,1.5);
            glCallList(listDemiBras);
            glTranslatef(0,0,8);
            glRotatef(teta,1,0,0);
            glPushMatrix();
                //avant-bras
                glCallList(listDemiBras);
                glTranslatef(0,0,8);
                glRotatef(pi,0,0,1);
                glPushMatrix();
                    //main
                    glPushMatrix();
                        glEnable(GL_TEXTURE_2D);
                        glBindTexture(GL_TEXTURE_2D, GLtexture[0]);
                        quadric=gluNewQuadric();
                        gluQuadricDrawStyle(quadric, GLU_FILL);
                        gluQuadricTexture(quadric,1);
                        glScalef(2,2,2);
                        gluSphere(quadric,0.5,10,10);
                        gluDeleteQuadric(quadric);
                        glDisable(GL_TEXTURE_2D);

                    glPopMatrix();
                    glPushMatrix();
                        glTranslatef(0,-0.7,0.7);
                        glRotatef(omega,1,0,0);
                        //doigt1
                        glCallList(listDoigt);
                    glPopMatrix();
                    glPushMatrix();
                        glTranslatef(0,0.7,0.7);
                        glRotated(omega,-1,0,0);
                        //doigt2
                        glRotatef(180,0,0,1);
                        glCallList(listDoigt);
                    glPopMatrix();

                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    glFlush();
}
GLuint Bras::getListCylindre() const
{
    return listCylindre;
}

void Bras::setListCylindre(const GLuint &value)
{
    listCylindre = value;
}
GLuint Bras::getListDemiBras() const
{
    return listDemiBras;
}

void Bras::setListDemiBras(const GLuint &value)
{
    listDemiBras = value;
}
int Bras::getAlpha() const
{
    return alpha;
}

void Bras::setAlpha(int value)
{
    alpha = value;
}
int Bras::getBeta() const
{
    return beta;
}

void Bras::setBeta(int value)
{
    beta = value;
}
int Bras::getTeta() const
{
    return teta;
}

void Bras::setTeta(int value)
{
    teta = value;
}
int Bras::getPi() const
{
    return pi;
}

void Bras::setPi(int value)
{
    pi = value;
}
int Bras::getOmega() const
{
    return omega;
}

void Bras::setOmega(int value)
{
    omega = value;
}








