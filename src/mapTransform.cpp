#include <QRect>
#include <QPointF>

#include "mapPoint.h"
#include "mapTransform.h"
#ifndef PI
#define PI 3.1415927
#endif

mapTransform::mapTransform(QRect rv, double x1, double y1, double x2, double y2, int PO)
        : qrect(rv), processOrder(PO)
{
    mapcrds = new mapCordset(x1, y1, x2, y2);
    basics(rv, x1, y1, x2, y2);
}

mapTransform::mapTransform(QRect rv, mapCordset *mpc, int PO)
        : qrect(rv), processOrder(PO)
{
    mapcrds = new mapCordset(mpc->X1(), mpc->Y1(), mpc->X2(), mpc->Y2());
    basics(rv, mpc->X1(), mpc->Y1(), mpc->X2(), mpc->Y2());
}

void mapTransform::basics(QRect rv, double x1, double y1, double x2, double y2)
{
	double xscale, yscale;

    if(x1 < x2)
	{
		xmin = x1;
		xmax = x2;
	}
	else
	{
		xmin = x2;
		xmax = x1;
	}
    if(y1 < y2)
	{
		ymin = y1;
		ymax = y2;
	}
	else
	{
		ymin = y2;
		ymax = y1;
	}

	width = xmax - xmin;
    xcenter = xmin + (width / 2);
	height = ymax - ymin;
    ycenter = ymin + (height / 2);

	xscale = rv.width() / width;
	yscale = rv.height() / height;
	_scale = yscale < xscale ? yscale : xscale;
	scXcenter = rv.left() + (double)rv.width() / 2.0;
	scYcenter = rv.bottom() - (double)rv.height() / 2.0;
}
// operator(int,int)  returns a screen x, y given a map coordinate.
QPointF mapTransform::operator()(mapPoint &p)
{
    return (*this)(p.lon(), p.lat());
}

QPointF mapTransform::operator()(QPointF &qp)
{
    return (*this)(qp.x(), qp.y());
}


// operator(int,int)  returns a screen x, y given a map coordinate.
QPointF mapTransform::operator()(double x, double y)
{
    return QPointF(
        scXcenter + (x - xcenter) * _scale,
        scYcenter + (y - ycenter) * _scale);
}

QPointF mapTransform::reverse(QPointF &qp)
{
    return reverse(qp.x(), qp.y());
}

QPointF mapTransform::reverse(double x, double y)
{
	return QPointF(
        xcenter + (x - scXcenter) / _scale,
        ycenter + (y - scYcenter) / _scale);
}

//revX: Returns the map longitude given a screen x and a screen y coordinate
double mapTransform::reverseX(double x, double y)
{
    QPointF qp = reverse(x, y);
	return qp.x();
}

//revX: Returns the map longitude given a screen x and a map y(latitude)
//
//  no projection is done by taking the cosine of the latitude and multiplying your
//  x scale factor accordingly.  In this function we have to recalculate the latScale as it is 
//  based on the y coordinate passed in.

//revY: Returns the map longitude given a screen y
double mapTransform::reverseY(double x, double y)
{
    QPointF qp = reverse(x, y);
	return qp.y();
}
