#ifndef ARENE_H
#define ARENE_H
#include <math.h>
#include <vector>
#include <point.h>
#include <GL/glu.h>

class Arene
{
public:
    Arene();
    ~Arene();
    void constuire(float rArenne, float oTrou, float dTrou, float rTrou=2.0, int pas=10);


};

std::vector<Point> calculerPointsCercles(float o, float d, float r, int pas);
#endif // ARENE_H