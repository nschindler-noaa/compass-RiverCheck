#include "mapPoint.h"
#include "mapLocalTransform.h"
#ifndef PI
#define PI 3.1415927
#endif
mapLocalTransform::mapLocalTransform(QRect rv, double x1, double y1, double x2, double y2, int PO)
    : mapTransform(rv, x1, y1, x2, y2, PO)
{
}

mapLocalTransform::mapLocalTransform(QRect rv, mapCordset *mpc, int PO)
    : mapTransform(rv, mpc->X1(), mpc->Y1(), mpc->X2(), mpc->Y2(), PO )
{
}

QPointF mapLocalTransform::operator()(double mapX, double mapY)
{
	double scX, scY, flatX, flatY;
    flatX = (xcenter - mapX) * cos(mapY / 180.0 * PI);
    flatY = (ycenter - mapY);
	scX = scXcenter - flatX * _scale;
	scY = scYcenter + flatY * _scale;

    return QPointF(scX, scY);
}

QPointF mapLocalTransform::operator()(QPointF qp)
{
    return (*this)(qp.x(), qp.y());
}

QPointF mapLocalTransform::reverse(double scX, double scY)
{
	double mapX, mapY, flatX, flatY;
    flatY = (scYcenter - scY) / _scale;
    flatX = (scX - scXcenter) / _scale;
	mapY = flatY + ycenter;
    mapX = flatX / cos(mapY / 180.0 * PI) + xcenter;

    return QPointF(mapX, mapY);
}

QPointF mapLocalTransform::reverse(QPointF qp)
{
    return reverse(qp.x(), qp.y());
}


