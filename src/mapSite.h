#ifndef MAP_SITE_H
#define MAP_SITE_H

#include <QtGui/QGraphicsItem>

//#include "mapItem.h"
//#include "compass.h"
#include "mapScene.h"
#include "mapTransform.h"

/** Graphic representation of a reach.  Includes icon, bounding rectangle, and context menu. */
class mapSite :
    public QGraphicsItem
{
public:
    /** Constructor with parent  */
    mapSite(QGraphicsItem *parent = 0);
	/** Constructor with parent, river segment, and transformation */
    mapSite(RiverSite *rsite, mapTransform *xform, QGraphicsItem *parent = 0);

	/** Shape of the icon - highlights when cursor hovers over it. */
	QPainterPath shape() const;
	/** Paint the object on the map. */
    void paint(QPainter *paintr, const QStyleOptionGraphicsItem *opt, QWidget *w);
	/** Show the context menu. */
	void contextMenu();

protected:
	/** Create the context menu. */
	QMenu * createMenu();

    QPainterPath path;
    QString itemName;
    QPen backgroundPen;
    QPen normalPen;
    QPen highlightPen;
    QPen errorPen;
    QMenu *itemOptions;
    RiverSite *rv_site;
    mapTransform *xform;
//	mapScene *map;
    bool mouseOver;
    int width;
    float minX, maxX;
    float minY, maxY;

};

#endif // MAP_SITE_H
