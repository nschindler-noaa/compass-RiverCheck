#ifndef MAP_HEADWATER_H
#define MAP_HEADWATER_H


#include "mapItem.h"
//#include "compass.h"
#include "mapScene.h"
#include "mapTransform.h"

/** Graphic representation of a headwater.  Includes icon, bounding rectangle, and context menu. */
class mapHeadwater :
	public mapItem
{
public:
	/** Constructor with parent (mapScene) */
    mapHeadwater(QGraphicsItem *parent = 0);
    /** Constructor with parent, river segment, and transformation */
    mapHeadwater(RiverSegment *rseg, mapTransform *xform, QGraphicsItem *parent = 0);

	/** Shape of the headwater (circle) - highlights when cursor hovers over it. */
	QPainterPath shape() const;
	/** Paint the object on the map. */
	void paint( QPainter *paintr, const QStyleOptionGraphicsItem *opt, QWidget *w );
	/** Show the context menu. */
    void infoPanel();

protected:
	/** Create the context menu. */
//    QDialog * createInfo();


};

#endif // MAP_HEADWATER_H
