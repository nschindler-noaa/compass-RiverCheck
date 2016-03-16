#ifndef MAP_REACH_H
#define MAP_REACH_H


#include "mapobject.h"
//#include "compass.h"
#include "mapScene.h"
#include "mapTransform.h"

/** Graphic representation of a reach.  Includes icon, bounding rectangle, and context menu. */
class mapReach :
    public mapObject
{
    Q_OBJECT

public:
	/** Constructor with parent (mapScene) */
    mapReach(QGraphicsItem *parent = 0);
    /** Constructor with parent, river segment, and transformation */
    mapReach(RiverSegment *rseg, mapTransform *xform, QGraphicsItem *parent = 0);

    /** Path of the river  - highlights when cursor hovers over it.*/
    QPainterPath path() const;
/*	* Paint the object on the map.
    void paint( QPainter *paintr, const QStyleOptionGraphicsItem *opt, QWidget *w );*/
//	/** Show the context menu. */
//    void contextMenu ();

//    void infoPanel();

public slots:
//    void showErrors(QPointF pt);
//    void showViews();

signals:
//    void showDetail (RiverSegment *seg);

protected:
    /** Shape of the item (used to be an icon) */
    QPainterPath shape() const;
    /** Create the context menu. */
//    QMenu *createMenu();
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *evnt);
    QDialog *createInfo();
//    QDialog *createViews();

};

#endif // MAP_REACH_H
