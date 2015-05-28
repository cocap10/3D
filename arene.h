#ifndef ARENE_H
#define ARENE_H
#include <math.h>
#include <vector>
#include <point.h>
#include <GL/glu.h>
#include <loadtgadisplaycdv.h>

class Arene
{
public:
    Arene();
    ~Arene();
    void draw();
    void init();
    void cible(int cotes, double rayon, GLint texture);
    void positionnerCible();
    double calcul_angle(double x, double y);

    double getYCible() const;
    void setYCible(double value);

    double getXCible() const;
    void setXCible(double value);

private:
    //Propriete de l'arenne
    float rArenne;
    float oTrou;
    float dTrou;
    float rTrou;
    int pas;
    GLuint GLtexture[3];

    double xCible;
    double yCible;

    double angleT;


};

std::vector<Point> calculerPointsCercles(float o, float d, float r, int pas);
#endif // ARENE_H
