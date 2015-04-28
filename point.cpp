#include "point.h"

Point::Point(float fx,float fy,float fz)
{
    x=fx;
    y=fy;
    z=fz;

}

Point::~Point()
{

}
float Point::getX() const
{
    return x;
}

void Point::setX(float value)
{
    x = value;
}
float Point::getY() const
{
    return y;
}

void Point::setY(float value)
{
    y = value;
}
float Point::getZ() const
{
    return z;
}

void Point::setZ(float value)
{
    z = value;
}




