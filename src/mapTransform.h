//	qmapTransform : transforms screen coordinates to map lat lon. This transform isn't a true
//						   Lambert Conformal Conic as we are not adding in the longitudinal curvature.
//						   
//	 Lambert Conformal Conic (Johanne Heinrich)
//    "Developed by J.H. Lambert in 1772 (fig. 2.7). The projection was almost unknown as a Lambert Projection for over a century. Harding, Herschel and
//     Boole had developed it independently in both spherical and ellipsoidal forms during the 19th century. World War I gave this projection new life, making
//     it the standard projection for intermediate - and large-scale maps of regions in midlatitudes for which the transverse no is not used."
//


#ifndef _mapTransform_h_
#define _mapTransform_h_

#include <qrect.h>
#include <qpoint.h>
#include "mapPoint.h"

/** Superclass for all transformations between map and geographic points. */
class mapTransform 
{
public:
	/** Constructor from a rectangle (screen) and set of map points. */
	mapTransform( QRect rv, mapCordset *mpc, int PO=0 );
	/** Constructor from a rectangle (screen) and four double values. */
	mapTransform( QRect rv, double x1, double y1, double x2, double y2, int PO=0 );
	/** Destructor */
    ~mapTransform(){}

	/** Returns the screen to map scale. \return Scale of map. */
    double getScale(){ return _scale; }

	/** Calculates a longitude from a screen position (x, y). \return longitude */
    double reverseX(double x, double y);
	/** Calculates a lattitude from a screen position (x, y). \return lattitude */
    double reverseY(double x, double y);

	/** Calculates a map location from a screen position (x, y). \return map location */
    virtual QPointF reverse(double x, double y);
	/** Calculates a map location from a screen position (QPointF). \return map location */
    QPointF reverse(QPointF &qp);

	/** Calculates a screen position from a map location (x, y). \return Screen position  */
    virtual QPointF operator()(double x, double y);
	/** Calculates a screen position from a map location (mapPoint). \return Screen position */
    QPointF operator()(mapPoint &p);
	/** Calculates a screen position from a map location (QPointF). \return Screen position */
    QPointF operator()(QPointF &qp);

protected:
    void basics(QRect rv, double x1, double y1, double x2, double y2);
	QRect qrect;                  // pseudo screen coordinates
	double scXcenter, scYcenter;  // center of "screen"
	double xmin, xmax, xcenter;   // x values
	double ymin, ymax, ycenter;   // y values
	double width, height;         // width and height of transformed map
    double _scale;                // default scale factor  (screen)/(map)
	mapCordset *mapcrds;          // map coordinates
    int processOrder;             // Process order is here in case multiple transforms are used. 

};

#endif
