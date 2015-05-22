#include "balle.h"

Balle::Balle()
{
    x=5.0;
    y=5.0;
    z=1.0;


}
void Balle::init()
{
    //Texture de la balle
    GLtexture= loadtgadisplayCDV("earth.tga");
}
int Balle::getX() const
{
    return x;
}

void Balle::setX(int value)
{
    x = value;
}
int Balle::getY() const
{
    return y;
}

void Balle::setY(int value)
{
    y = value;
}
int Balle::getZ() const
{
    return z;
}

void Balle::setZ(int value)
{
    z = value;
}



void Balle::draw()
{
    glPushMatrix();
        glTranslatef(x,y,z);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, GLtexture);
        quadric=gluNewQuadric();
        gluQuadricDrawStyle(quadric, GLU_FILL);
        gluQuadricTexture(quadric,1);
        glScalef(2,2,2);
        gluSphere(quadric,0.5,10,10);
        gluDeleteQuadric(quadric);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}

Balle::~Balle()
{

}

