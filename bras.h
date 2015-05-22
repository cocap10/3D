#ifndef BRAS_H
#define BRAS_H

#include <GL/glu.h>
#include <loadtgadisplaycdv.h>

class Bras
{
public:
    Bras();
    ~Bras();
    void init();
    void draw();
    GLuint getListCylindre() const;
    void setListCylindre(const GLuint &value);

    GLuint getListDemiBras() const;
    void setListDemiBras(const GLuint &value);

    int getAlpha() const;
    void setAlpha(int value);

    int getBeta() const;
    void setBeta(int value);

    int getTeta() const;
    void setTeta(int value);

    int getPi() const;
    void setPi(int value);

    int getOmega() const;
    void setOmega(int value);

private:
    // pour utiliser gluSphere gluCylinder  et gluDisk
    GLUquadric *quadric;
    // pour les display lists
    GLuint GLtexture[2];
    GLuint listCylindre;
    GLuint listCylindre2;
    GLuint listDemiBras;
    GLuint listDoigt;
    //pour bouger le bras
    int alpha;
    int beta;
    int teta;
    int pi;
    int omega;

};

#endif // BRAS_H
