//	qMercatorTransform : transforms screen coordinates to map lat lon. This transform isn't a true
//						   Lambert Conformal Conic as we are not adding in the longitudinal curvature.
//						   
//	 Lambert Conformal Conic (Johanne Heinrich)
//    "Developed by J.H. Lambert in 1772 (fig. 2.7). The projection was almost unknown as a Lambert Projection for over a century. Harding, Herschel and
//     Boole had developed it independently in both spherical and ellipsoidal forms during the 19th century. World War I gave this projection new life, making
//     it the standard projection for intermediate - and large-scale maps of regions in midlatitudes for which the transverse Mercator is not used."
//


#ifndef _mercatorTransform_h_
#define _mercatorTransform_h_

#include <qrect.h>
#include <qpoint.h>
#include "mapPoint.h"

class mercatorTransform 
{
public:
	mercatorTransform(mapCordset *mpc, int PO=0);
	mercatorTransform(double x1, double y1, double x2, double y2, int PO=0);
    ~mercatorTransform(){}

    double getScale(){ return _scale; }
    double getOffsetX(){ return _ox; }
    double getOffsetY(){ return _oy; }

	double reverseX(double x);
    double reverseX(double x, double y);
	double reverseY(double y);

	QPointF reverse(double x, double y);

    QPointF operator()(double x, double y);
	QPointF operator()(mapPoint &p);

protected:
	double orgx, orgy;   // lower left of data (least value)
	double centx, centy; // center of data (transform from here)  (longest longitude)
	double width, height;
    double _scale;  // default scale factor  (screen width)/(map width)
	double _centerLong, _centerScreen;  // map center coordinate (lon) and the screen center (x)
	double _latScale; // x scale factor.. based on y with Mercator
    double _ox, _oy;  // upper left hand coordinates of the map taken from _mpc
	mapCordset *_mpc; // map coordinates
    int _ProcessOrder; // Process order is here incase multiple transforms are used.  In such a case it

};

#endif
