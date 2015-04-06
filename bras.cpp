#include "bras.h"
#include <QtGlobal>
Bras::Bras()
{
    /*quadric=gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL);
    alpha=0;
    beta=0;
    listCylindre=glGenLists(1);*/



}

Bras::~Bras()
{

}

void Bras::construir()
{

    quadric=gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL);
    alpha=0;
    beta=0;
    teta=0;
    pi=0;
    listCylindre=glGenLists(1);
    listDemiBras=glGenLists(2);

    glNewList(listCylindre, GL_COMPILE);
    glPushMatrix();
        gluDisk(quadric,0,0.5,20,10);
        gluCylinder(quadric,0.5,0.5,1,20,20);
        glTranslatef(0,0,1);
        gluDisk(quadric,0,0.5,20,10);
    glPopMatrix();
    glEndList();

    glNewList(listDemiBras, GL_COMPILE);
    glPushMatrix();
        glPushMatrix();
            glScalef(2,2,2);
            gluSphere(quadric,0.5,10,10);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,0,1);
            glScalef(2,2,6);
            glCallList(listCylindre);
        glPopMatrix();
    glPopMatrix();
    glEndList();






    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    //socle
    glColor3f(1,1,1);
    glPushMatrix();
        glScalef(5,5, 0.5);
        glCallList(listCylindre);
    glPopMatrix();


    glRotatef(alpha,1,0,0);
    glRotatef(beta, 0,1,0);
    //bras
    glPushMatrix();
        //debut-bras
        glTranslatef(0,0,1.5);
        glColor3f(1,0,0);glCallList(listDemiBras);
        glTranslatef(0,0,8);
        glRotatef(teta,1,0,0);
        glPushMatrix();
            //avant-bras
            glColor3f(0,1,0);glCallList(listDemiBras);
            glTranslatef(0,0,8);
            glRotatef(pi,0,0,1);
            glPushMatrix();
                //main
                glPushMatrix();
                    glScalef(2,2,2);
                    glColor3f(1,0,0);gluSphere(quadric,0.5,10,10);
                glPopMatrix();
                glTranslatef(0,-0.7,0.7);
                glRotatef(omega+45,1,0,0);
                glPushMatrix();
                    //doigt1
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



