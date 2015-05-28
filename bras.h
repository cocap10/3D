#ifndef BRAS_H
#define BRAS_H

#include <GL/glu.h>
#include <loadtgadisplaycdv.h>
#include <math.h>

class Bras
{
public:
    Bras();
    ~Bras();
    void init();
    void draw();
    void draw2();
    GLuint getListCylindre() const;
    void setListCylindre(const GLuint &value);

    GLuint getListDemiBras() const;
    void setListDemiBras(const GLuint &value);

    int getPi() const;
    void setPi(int value);

    int getOmega() const;
    void setOmega(int value);

    double getTeta() const;
    void setTeta(double value);

    double getBeta() const;
    void setBeta(double value);

    double getAlpha() const;
    void setAlpha(double value);

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
    double alpha;
    double beta;
    double teta;
    int pi;
    int omega;

};

#endif // BRAS_H
