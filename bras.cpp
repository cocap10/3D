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
    listCylindre=glGenLists(1);

    glNewList(listCylindre, GL_COMPILE);
    /*glPushMatrix();
        gluDisk(quadric,0,0.5,20,10);
        gluCylinder(quadric,0.5,0.5,1,20,20);
        glTranslatef(0,0,1);
        glColor3f(0,1,0);
        gluDisk(quadric,0,0.5,20,10);
        glPopMatrix();*/
        glBegin(GL_TRIANGLES);
            glColor3f(0.0f,1.0f,0.0f);
            glVertex3f(0,5,0);
            glColor3f(0.0f,0.0f,1.0f);
            glVertex3f(0,0,0);
            glColor3f(1.0f,0.0f,0.0f);
            glVertex3f(5,0,0);
        glEnd();
    glEndList();


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glCallList(listCylindre);
    glFlush();
    /*glBegin(GL_TRIANGLES);
        glColor3f(0.0f,1.0f,0.0f);
        glVertex3f(0,5,0);
        glColor3f(0.0f,0.0f,1.0f);
        glVertex3f(0,0,0);
        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f(5,0,0);
    glEnd();*/
    /*quadric = gluNewQuadric();
        gluQuadricDrawStyle(quadric, GLU_FILL );
        int alpha =0;
        int beta=0;
        glPushMatrix();
            glPushMatrix();
                glColor3f(0.9,0.6,0.4);
                glScalef(5,5, 0.5);
                gluCylinder(quadric,0.5,0.5,1,20,20);
                glTranslatef(0,0,1);
                gluDisk(quadric,0,0.5,20,10);
            glPopMatrix();
            glPushMatrix();
                glRotatef(alpha,1,0,0);
                glRotatef(beta, 0,1,0);
                glPushMatrix();
                    glColor3f(1,1,1);
                    glTranslatef(0,0,1);
                    glScalef(2,2,2);
                    gluSphere(quadric,0.5,10,10);
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();*/

}
GLuint Bras::getListCylindre() const
{
    return listCylindre;
}

void Bras::setListCylindre(const GLuint &value)
{
    listCylindre = value;
}


