#ifndef BRAS_H
#define BRAS_H

#include <GL/glu.h>

class Bras
{
public:
    Bras();
    ~Bras();
    void construir();
private:
    // pour utiliser gluSphere gluCylinder  et gluDisk
    GLUquadricObj *quadric;
    // pour les display lists
    GLuint listCylindre;
    //pour bouger le bras
    int alpha;
    int beta;
};

#endif // BRAS_H
