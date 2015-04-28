#ifndef POINT_H
#define POINT_H


class Point
{
public:
    Point(float fx=0,float fy=0,float fz=0);
    ~Point();
    float getX() const;
    void setX(float value);

    float getY() const;
    void setY(float value);

    float getZ() const;
    void setZ(float value);

private:
    float x;
    float y;
    float z;
};

#endif // POINT_H
