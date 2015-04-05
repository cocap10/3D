#ifndef BRAS_H
#define BRAS_H

#include <GL/glu.h>

class Bras
{
public:
    Bras();
    ~Bras();
    void construir();
    GLuint getListCylindre() const;
    void setListCylindre(const GLuint &value);

    GLuint getListDemiBras() const;
    void setListDemiBras(const GLuint &value);

private:
    // pour utiliser gluSphere gluCylinder  et gluDisk
    GLUquadricObj *quadric;
    // pour les display lists
    GLuint listCylindre;
    GLuint listDemiBras;
    //pour bouger le bras
    int alpha;
    int beta;
    int teta;
    int pi;
    int omega;
};

#endif // BRAS_H
