#ifndef MAP_ITEM_H
#define MAP_ITEM_H

#include <QtGui/QGraphicsItem>
#include <QtGui/QDialog>
#include <QtGui/QListWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QToolTip>

#include "RiverSegment.h"
//#include "compass.h"
//#include "mapScene.h"
#include "mapTransform.h"
#include "mapConstants.h"

#ifndef WIDTH_FACTOR
#define WIDTH_FACTOR   1500
#endif

enum datatype{
	SEGTYPE 
};

/** Extends QGraphics item for our map. */
class mapItem :
	public QGraphicsItem
{
//    Q_OBJECT

public:
	/** Constructor with parent (mapScene) */
    mapItem (QGraphicsItem *parent = 0);
	/** Constructor with parent, river segment, and transformation */
    mapItem (RiverSegment *rseg, mapTransform *xform, QGraphicsItem *parent = 0);
	/** Destructor */
    ~mapItem ();

    /** Path of the river - highlights when cursor hovers over it.*/
    virtual QPainterPath getPath() const;
    /** Shape of the item (used to be an icon) */
    virtual QPainterPath getShape() const;
	/** The shape bounding rectangle. */
	QRectF boundingRect() const;
	/** Paint the object on the map. */
    virtual void paint (QPainter *paintr, const QStyleOptionGraphicsItem *opt, QWidget *w);
	/** Show the itme highlighted. */
	void highlight();
	/** Show the item without highlight. */
	void normal();
	/** Add Select option to the context menu. */
    virtual void infoPanel();
	/** The river_segment associated with this item. \return Pointer to the segment or 0 */
    RiverSegment * riverSegment();
	/** The name of the item. \return Item name.*/
	QString name();
    /** Display the segment information at a point. */
    void displayInfo (QPoint);
    /** Display the context menu at a point. */
    void displayMenu (QPoint);

//public slots:
    void showViews(QPointF pt);
    void showErrors(QPointF pt);
    void deleteDam();

protected:
    QAction *actionShowErrors;
    QAction *actionShowDetail;
    QAction *actionDeleteDam;
/*    void mousePressEvent (QGraphicsSceneMouseEvent *evnt);
    void mouseReleaseEvent (QGraphicsSceneMouseEvent *evnt);
    void mouseMoveEvent (QGraphicsSceneMouseEvent *evnt);
    void displayMenu (QPointF pos);*/
	void setBoundingRect();// double lon, double lat ) ;
    void contextMenuEvent (QGraphicsSceneContextMenuEvent *evnt);
    void hoverEnterEvent (QGraphicsSceneHoverEvent * evnt);
    void hoverLeaveEvent (QGraphicsSceneHoverEvent * evnt);
    QDialog * createInfo();
    virtual QMenu * createMenu();
//    virtual void contextMenu();
    QVBoxLayout * getErrorList (RiverSegment * seg);
    QDialog * createViews();

//	QPixmap pix;
    QPainterPath shape;
	QPainterPath path;
	QString itemName;
    QPen backgroundPen;
    QPen normalPen;
    QPen highlightPen;
    QPen errorPen;
    QPen errorHighlightPen;
    QDialog *itemErrors;
    QMenu *itemOptions;
    RiverSegment *rv_seg;
	mapTransform *xform;
//	mapScene *map;
	bool mouseOver;
    int width;
	float minX, maxX;
	float minY, maxY;

	QRectF bounds;

};

#endif //MAP_ITEM_H
