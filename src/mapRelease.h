#pragma once

#define MAX_SEGS     200

#include "mapItem.h"
//#include "compass.h"
#include "mapScene.h"
#include "mapTransform.h"

/** graphic representation of a release. */
class mapRelease :
	public mapItem
{
public:
	/** Constructor with parent (mapScene) */
	mapRelease( mapScene *m );
	/** Constructor with parent, release site, and transformation */
	mapRelease( mapScene *m, struct release_site *site, mapTransform *xform );
	/** Constructor with parent, release, and transformation */
	mapRelease( mapScene *m, struct release *rel, mapTransform *xform );

	/** The icon. */
	QPixmap icon();
	/** Shape of the icon - highlights when cursor hovers over it. */
	QPainterPath shape() const;
	/** Paint the object on the map. */
	void paint( QPainter *paintr, const QStyleOptionGraphicsItem *opt, QWidget *w );
	/** Show the context menu. */
	void contextMenu();
	/** Change the icon \param px New icon*/
	void setIcon( QPixmap px );

protected:
	/** Set the bounding rectangle around the dam shape. */
	void setBoundingRect();
	/** Create the context menu. */
	QMenu * createMenu();

private:
	struct release *rls;

};
