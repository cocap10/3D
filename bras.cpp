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
    alpha=45;
    beta=0;
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
            glTranslatef(0,0,2);
            glScalef(2,2,2);
            gluSphere(quadric,0.5,10,10);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,0,3);
            glScalef(2,2,6);
            glCallList(listCylindre);
        glPopMatrix();
    glEndList();






    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    //socle
    glPushMatrix();
        glScalef(5,5, 0.5);
        glCallList(listCylindre);
    glPopMatrix();


    glRotatef(alpha,1,0,0);
    glRotatef(beta, 0,1,0);
    //avant-bras
    glCallList(listDemiBras);



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


