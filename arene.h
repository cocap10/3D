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
private:
    //Propriete de l'arenne
    float rArenne;
    float oTrou;
    float dTrou;
    float rTrou;
    int pas;
    GLuint GLtexture;


};

std::vector<Point> calculerPointsCercles(float o, float d, float r, int pas);
#endif // ARENE_H
