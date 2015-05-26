#ifndef BALLE_H
#define BALLE_H
#include <GL/glu.h>
#include <loadtgadisplaycdv.h>

class Balle
{
public:
    Balle();
    ~Balle();
    void init();
    void draw();

    double getX() const;
    void setX(double value);

    double getY() const;
    void setY(double value);

    double getZ() const;
    void setZ(double value);

private:
    double x;
    double y;
    double z;
    GLUquadric *quadric;
    GLuint GLtexture;
};

#endif // BALLE_H
