#ifndef MAP_GRID_H
#define MAP_GRID_H

#include <QGraphicsItem>


#include "mapScene.h"
#include "mapTransform.h"
#include "mapConstants.h"


/** Extends QGraphicsItem to create a grid for our map. */
class mapGrid :
	public QGraphicsItem
{
public:
	/** Constructor with parent (mapScene) */
    mapGrid (mapScene *m);
	/** Constructor with parent, river segment, and transformation */
    mapGrid (mapScene *m, mapTransform *xform);
	/** Destructor */
    ~mapGrid();

	/** Shape of the icon - highlights when cursor hovers over it. */
    QPainterPath shape() const;
	/** The shape bounding rectangle. */
	QRectF boundingRect() const;
    /** Set the limits of the grid */
    void setGridLimits (float xMin, float Ymin, float xMax, float yMax);
    /** Paint the object on the map. */
    void paint(QPainter *paintr, const QStyleOptionGraphicsItem *opt, QWidget *w);

protected:
    void setToolTip();
    void setBoundingRect();

	QPainterPath path;
    mapTransform *xform;
	mapScene *map;
    int minX, maxX;
    int minY, maxY;

	QRectF bounds;

};

#endif // MAP_GRID_H
