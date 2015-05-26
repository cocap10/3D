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
    void cible(int cotes, double rayon, GLint texture, double gamma);
    void positionnerCible();
    double calcul_alpha(double x, double y);

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

    double angleTrou;


};

std::vector<Point> calculerPointsCercles(float o, float d, float r, int pas);
#endif // ARENE_H
