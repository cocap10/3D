#include "arene.h"
#include <QDebug>
Arene::Arene()
{
    rArenne=10.0;
    oTrou=0.0;
    dTrou=5.0;
    rTrou=1.5;
    pas=10;
    qDebug()<<"Debut arene";
}

Arene::~Arene()
{
    qDebug()<<"Fin arene";
}

void Arene::init()
{
    //Texture du sol
    GLtexture= loadtgadisplayCDV("BDS.tga");
}

void Arene::draw()
{


    glColor3f(1,1,0);
    std::vector<Point> pointsTrou = calculerPointsCercles(oTrou, dTrou, rTrou, pas);
    std::vector<Point> pointsCercle = calculerPointsCercles(0,0,rArenne,pas);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_CULL_FACE);
    glEnable ( GL_NORMALIZE );
    glDepthMask ( GL_TRUE );
    glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA);
    glPointSize ( 1.0f );
    glLineWidth ( 1.0f );
    glEnable(GL_COLOR_MATERIAL);
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_CULL_FACE );
    glColor3f(1,1,1);
    glEnable( GL_TEXTURE_2D );
    glDisable( GL_CULL_FACE );
    glBindTexture(GL_TEXTURE_2D, GLtexture);
    glBegin(GL_TRIANGLE_STRIP);
    //Boucle de construction
    for(int i=0; (i<pointsTrou.size() || i<pointsCercle.size()); i++)
    {

        Point pointCercle=pointsCercle[i];
        Point pointTrou=pointsTrou[i];

        glTexCoord2f((1+pointCercle.getX())/2, (1+pointCercle.getY())/2);
        glVertex3f(pointCercle.getX(),pointCercle.getY(),pointCercle.getZ());
        //glTexCoord2f((1+pointCercle.getX()/rArenne)/2,);
        glTexCoord2f((1+pointTrou.getX())/2, (1+pointTrou.getY())/2);
        glVertex3f(pointTrou.getX(),pointTrou.getY(),pointTrou.getZ());
    }
    glEnd();
    glDisable( GL_TEXTURE_2D );
    glEnable( GL_CULL_FACE );


    glDisable( GL_CULL_FACE );
    glBegin(GL_QUAD_STRIP);
    for(int i=0;  i<pointsCercle.size(); i++)
    {
        Point pointCercle=pointsCercle[i];
        glVertex3f(pointCercle.getX(),pointCercle.getY(),pointCercle.getZ()+5);
        glVertex3f(pointCercle.getX(),pointCercle.getY(),pointCercle.getZ());
    }
    glEnd();
    glEnable( GL_CULL_FACE );





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

