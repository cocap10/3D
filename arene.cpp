#include "arene.h"
#include <QDebug>
Arene::Arene()
{
    qDebug()<<"Debut arene";
}

Arene::~Arene()
{
    qDebug()<<"Fin arene";
}

void Arene::draw(float rArenne, float oTrou, float dTrou, float rTrou, int pas)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1,1,0);
    std::vector<Point> pointsTrou = calculerPointsCercles(oTrou, dTrou, rTrou, pas);
    std::vector<Point> pointsCercle = calculerPointsCercles(0,0,rArenne,pas);
    glBegin(GL_TRIANGLE_STRIP);
    //Boucle de construction
    for(int i=0; (i<pointsTrou.size() || i<pointsCercle.size()); i++)
    {

        Point pointCercle=pointsCercle[i];
        Point pointTrou=pointsTrou[i];
        glVertex3f(pointCercle.getX(),pointCercle.getY(),pointCercle.getZ());
        glVertex3f(pointTrou.getX(),pointTrou.getY(),pointTrou.getZ());
        /*qDebug()<<"p1(x,y): "<<pointCercle.getX()<<" "<< pointCercle.getY()
                <<",p2(x,y): "<<pointTrou.getX() <<" "<<pointTrou.getY();*/
    }
    glEnd();

    glBegin(GL_QUAD_STRIP);




}

std::vector<Point> calculerPointsCercles(float o, float d, float r, int pas)
{
    std::vector<Point> result;
    Point pts;
    for(int angle=0; angle <= 360; angle+=pas)
    {
        pts.setX(d*cos(o*M_PI/180.0)+r*cos(angle*M_PI/180.0));
        pts.setY(d*sin(o*M_PI/180.0)+r*sin(angle*M_PI/180.0));
        result.push_back(pts);
    }
    return result;
}

