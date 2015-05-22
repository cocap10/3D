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

    int getX() const;
    void setX(int value);

    int getY() const;
    void setY(int value);

    int getZ() const;
    void setZ(int value);

private:
    int x;
    int y;
    int z;
    GLUquadric *quadric;
    GLuint GLtexture;
};

#endif // BALLE_H
