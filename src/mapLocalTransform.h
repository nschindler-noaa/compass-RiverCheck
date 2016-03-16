//	qmapLocalTransform : transforms screen coordinates to map lat lon. This transform isn't a true
//						   Lambert Conformal Conic as we are not adding in the longitudinal curvature.
//						   
//	 Lambert Conformal Conic (Johanne Heinrich)
//    "Developed by J.H. Lambert in 1772 (fig. 2.7). The projection was almost unknown as a Lambert Projection for over a century. Harding, Herschel and
//     Boole had developed it independently in both spherical and ellipsoidal forms during the 19th century. World War I gave this projection new life, making
//     it the standard projection for intermediate - and large-scale maps of regions in midlatitudes for which the transverse Mercator is not used."
//


#ifndef _mapLocalTransform_h_
#define _mapLocalTransform_h_

#include <qrect.h>
#include <qpoint.h>
#include "mapPoint.h"
#include "mapTransform.h"

/** This is the official transformation. Transform points between map and geographic points. */
class mapLocalTransform : public mapTransform
{
public:
	/** Constructor from a rectangle (screen) and set of map points. */
    mapLocalTransform(QRect rv, mapCordset *mpc, int PO=0);
	/** Constructor from a rectangle (screen) and four double values. */
    mapLocalTransform(QRect rv, double x1, double y1, double x2, double y2, int PO=0);
	/** Destructor */
    ~mapLocalTransform(){}

	/** Calculates a screen position from a map location (x, y). \return Screen position  */
    QPointF operator()(double x, double y);
    /** Calculates a screen position from a map location (QPointF). \return Screen position */
    QPointF operator()(QPointF qp);

	/** Calculates a map location from a screen position (x, y). \return map location */
    QPointF reverse(double x, double y);
    /** Calculates a map location from a screen position (QPointF). \return map location */
    QPointF reverse(QPointF qp);

protected:
    void basics(QRect rv, double x1, double y1, double x2, double y2);
};

#endif
