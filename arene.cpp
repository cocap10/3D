#include "arene.h"

Arene::Arene()
{

}

Arene::~Arene()
{

}

void Arene::constuire(float rArenne, float oTrou, float dTrou, float rTrou, int pas)
{
    glColor3f(1,1,0);
    std::vector<QPoint> pointsTrou = calculerPointsCercles(oTrou, dTrou, rTrou, pas);
    //std::vector<QPoint> pointsCercle = calculerPointsCercles(0,0,)

    //Boucle de construction

    //glVertex3f();



}

std::vector<QPoint> calculerPointsCercles(float o, float d, float r, int pas)
{
    std::vector<QPoint> result;
    QPoint pts;
    for(int angle=0; angle < 360; angle+=pas)
    {
        pts.setX(d*cos(o*M_PI/180.0)+r*cos(angle*M_PI/180.0));
        pts.setY(d*sin(o*M_PI/180.0)+r*sin(angle*M_PI/180.0));
    }
    return result;
}

