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
    void draw(int a=0, int b=0,int t=0,int p=0,int o=45);
    GLuint getListCylindre() const;
    void setListCylindre(const GLuint &value);

    GLuint getListDemiBras() const;
    void setListDemiBras(const GLuint &value);

private:
    // pour utiliser gluSphere gluCylinder  et gluDisk
    GLUquadric *quadric;
    // pour les display lists
    GLuint GLtexture[2];
    GLuint listCylindre;
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
