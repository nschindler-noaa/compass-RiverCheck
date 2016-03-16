#include "mapPoint.h"
#include "mercatorTransform.h"

#define PI 3.1415927

mercatorTransform::mercatorTransform( double x1, double y1, double x2, double y2, int PO )
{
	_ox = x1;
	_oy = y1;
	_ProcessOrder = PO;
	width = x1 - x2;
	height = y1 - y2;
	_centerLong = x1-(x1-x2)/2.0;
	_centerScreen = _centerLong;
	double sx = 1;//(double)rv.width()/(x1-x2);
	double sy = 1;//(double)rv.height()/(y1-y2);
	if(sx<sy)_scale = sx;
	else _scale = sy;
}

mercatorTransform::mercatorTransform( mapCordset *mpc, int PO )
{
	orgx = mpc->X2();
	orgy = mpc->Y2();
	width = mpc->X1() - mpc->X2();
	height = mpc->Y1() - mpc->Y2();
	centx = orgx + width / 2 ;
	centy = orgy + height / 2 ;
	_latScale = cos( (centy / 180.0) * PI );
	width = 
	_ox = mpc->X1();
	_oy = mpc->Y1();
	_ProcessOrder = PO;
	_mpc = mpc;
	_latScale = cos((_oy/180.0)*PI);
//	atoi( "" ); /* KLUDGE - prevents optimization bug */
	_centerLong = _ox-(_ox-_mpc->X2())/2.0;
	_centerScreen = _centerLong ;//(double)_rv.width()/2.0;
	double sx = width/(_latScale*(_ox-mpc->X2()));
	double sy = height/(_oy-mpc->Y2());
	if(sx<sy)_scale = sx;
	else _scale = sy;
}

// operator(int,int)  returns a screen x, y given a map coordinate.
QPointF mercatorTransform::operator()(mapPoint &p)
{
	return (*this)(p.lon(),p.lat());
}

// operator(int,int)  returns a screen x, y given a map coordinate.
QPointF mercatorTransform::operator()(double x, double y)
{
	_latScale = cos((y/180.0)*PI);
//	atoi( "" ); /* KLUDGE - prevents optimization bug */
    return QPointF(
			(_centerLong-x)*_latScale*_scale+_centerScreen
			,(_oy-y)*_scale );
}

QPointF mercatorTransform::reverse(double x, double y)
{
	_latScale = cos(((_oy- (y/_scale))/180.0)*PI);
//	atoi( "" ); /* KLUDGE - prevents optimization bug */
	return QPointF(_centerLong-(x-_centerScreen)/(_latScale*_scale),(_oy-(double(y)/_scale)));
}

//revX: Returns the map longitude given a screen x
double mercatorTransform::reverseX(double x)
{
	//WARNING: This is not a proper calculation.. 
	//  	   the 0.67 is an estimate so please use revX(int,int) or revX(int,double)
	return (_ox-(double(x)/(0.67*_scale)));
}

//revX: Returns the map longitude given a screen x and a screen y coordinate
double mercatorTransform::reverseX(double x, double y)
{
	_latScale = cos(((_oy-((y)/_scale))/180.0)*PI);
//	atoi( "" ); /* KLUDGE - prevents optimization bug */
	return _centerLong-(x-_centerScreen)/(_latScale*_scale);
}

//revX: Returns the map longitude given a screen x and a map y(latitude)
//
//  Mercator projection is done by taking the cosine of the latitude and multiplying your
//  x scale factor accordingly.  In this function we have to recalculate the latScale as it is 
//  based on the y coordinate passed in.

//revY: Returns the map longitude given a screen y
double mercatorTransform::reverseY(double y)
{
    return (_oy-((y)/_scale));
}
