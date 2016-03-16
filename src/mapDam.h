#ifndef MAP_DAM_H
#define MAP_DAM_H


#include "mapObject.h"
//#include "compass.h"
//#include "mapScene.h"
#include "mapTransform.h"
#include "Dam.h"

#define DAM_LENGTH  12.0

/** Graphic representation of a dam. Includes icon, bounding rectangle, and context menu. */
class mapDam :
    public mapObject
{
    Q_OBJECT

public:
	/** Constructor with parent (mapScene) */
    mapDam (QGraphicsItem *parent = 0);
    /** Constructor with parent, river segment, and transformation */
    mapDam (RiverSegment *rseg, mapTransform *xform, QGraphicsItem *parent = 0);
//	~mapDam( void );

    /** Shape of the item - highlights when cursor hovers over it. */
    QPainterPath path() const;
	/** Paint the object on the map. */
    void paint (QPainter *paintr, const QStyleOptionGraphicsItem *opt, QWidget *w);
//	/** Show the context menu. */
//    void infoPanel();

//    Dam *dam_seg;
    float angle;     // rise/run, or delta-longitude/delta-latitude

public slots:
//    void showErrors();
//    void showViews();
//    void deleteDam();

signals:
//    void showDetail (RiverSegment *seg);
    void deleteDam (mapObject *dam);

protected:
//    QPainterPath spillpath;
    QPointF origin;
    QPointF point1, point2;
    QTransform trans; // additional transformation to local coordinates

    QPainterPath shape() const;
	/** Set the bounding rectangle around the dam shape. */
	void setBoundingRect();
    void setAngle();
    QPointF getOriginPoint();
    QPointF getBackingPoint();
	/** Create the context menu. */
//    QMenu *createMenu();
    void contextMenuEvent (QGraphicsSceneContextMenuEvent *evnt);
};

#endif // MAP_DAM_H
