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

    xCible = 3;
    yCible = 5;

    angleT = calcul_angle(rTrou, rTrou);
}

Arene::~Arene()
{
    qDebug()<<"Fin arene";
}

void Arene::init()
{
    //Texture du sol
    GLtexture[1]= loadtgadisplayCDV("sable.tga");
    GLtexture[2]= loadtgadisplayCDV("cible.tga");
}

void Arene::draw()
{


    glColor3f(1,1,0);
    std::vector<Point> pointsTrou = calculerPointsCercles(oTrou, dTrou, rTrou, pas);
    std::vector<Point> pointsCercle = calculerPointsCercles(0,0,rArenne,pas);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable ( GL_NORMALIZE );
    glDepthMask ( GL_TRUE );
    glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA);
    glPointSize ( 1.0f );
    glLineWidth ( 1.0f );
    glEnable(GL_COLOR_MATERIAL);
    glEnable( GL_DEPTH_TEST );
    glColor3f(1,1,1);
    glEnable( GL_TEXTURE_2D );
    glBindTexture(GL_TEXTURE_2D, GLtexture[1]);
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


    glPushMatrix();
        glTranslatef(xCible, yCible, 0.6);
        cible(100,1,GLtexture[2]);
    glPopMatrix();


    glEnable(GL_COLOR_MATERIAL);
    glColor4f(0,0,1,0.7);
    glEnable(GL_BLEND);
    glBegin(GL_QUAD_STRIP);
    for(int i=0;  i<pointsCercle.size(); i++)
    {
        Point pointCercle=pointsCercle[i];
        glVertex3f(pointCercle.getX(),pointCercle.getY(),pointCercle.getZ()+5);
        glVertex3f(pointCercle.getX(),pointCercle.getY(),pointCercle.getZ());
    }
    glEnd();
    glColor3f(1,1,1);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_BLEND);

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

void Arene ::cible (int cotes, double rayon, GLint texture)
{
    if(cotes > 0 && rayon > 0)
    {


        glEnable( GL_TEXTURE_2D );

        glBindTexture(GL_TEXTURE_2D, texture);

        glBegin(GL_TRIANGLE_FAN);

        //-----centre-----
        glTexCoord2f(0.5,0.5);
        glVertex3f(0,0,-0.5);

        //-----sommets-----
        for(int i = 0; i<cotes; i++)
        {
            glTexCoord2f((1+cos(i*2*M_PI/cotes))/2, (1+sin(i*2*M_PI/cotes))/2);
            glVertex3f(rayon*cos(i*2*M_PI/cotes), rayon*sin(i*2*M_PI/cotes), -0.5);
        }
        glVertex3f(rayon,0,-0.5);

        glEnd();

        glDisable( GL_TEXTURE_2D );
    }
}

void Arene:: positionnerCible() {
    int angleC = (rand() % 360) - 180;

    if(angleC < angleT - 5 || angleC > angleT + 5) {
        int distanceCible = (rand() % 4) + 4;

        xCible = distanceCible*cos(angleC*M_PI/180);
        yCible = distanceCible*sin(angleC*M_PI/180);
    } else {
        positionnerCible();
    }
}

double Arene::calcul_angle(double x, double y) {
    double angle = atan(y/x)*180/M_PI;
    if(x<0){
        angle = angle + 180;
    }
    return angle;
}
double Arene::getYCible() const
{
    return yCible;
}

void Arene::setYCible(double value)
{
    yCible = value;
}
double Arene::getXCible() const
{
    return xCible;
}

void Arene::setXCible(double value)
{
    xCible = value;
}


