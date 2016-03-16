#pragma once

#define MAX_SEGS     200

#include "mapItem.h"
//#include "compass.h"
#include "mapScene.h"
#include "mapTransform.h"

/** Graphic representation of a transport. Includes icon (barge), bounding rectangle, and context menu. */
class mapTransport :
	public mapItem
{
public:
	/** Constructor with parent (mapScene) */
	mapTransport( mapScene *m );
	/** Constructor with parent, river segment, and transformation */
	mapTransport( mapScene *m, struct river_segment *rseg, mapTransform *xform );

	/** The icon. */
	QPixmap icon();
	/** Shape of the icon - highlights when cursor hovers over it. */
	QPainterPath shape() const;
	/** Paint the object on the map. */
	void paint( QPainter *paintr, const QStyleOptionGraphicsItem *opt, QWidget *w );
	/** Shows the context menu. */
	void contextMenu();

protected:
	/** Set the bounding rectangle around the dam shape. */
	void setBoundingRect();
	/** Create the context menu. */
	QMenu * createMenu();


};
