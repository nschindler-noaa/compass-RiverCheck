#ifndef MAPOBJECT_H
#define MAPOBJECT_H

#include <QObject>
#include <QGraphicsObject>
#include <QAction>
#include <QVBoxLayout>
#include <QPainter>
#include <QRectF>
#include <QString>
#include <QPainterPath>
#include <QPen>
#include <QDialog>
#include <QMenu>

#include "RiverSegment.h"
#include "mapTransform.h"
#include "mapConstants.h"

#ifndef WIDTH_FACTOR
#define WIDTH_FACTOR   1500
#endif

/** Extends QGraphicsObject for our map, since we need the signals and slots. */
class mapObject : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit mapObject(QGraphicsItem *parent = 0);
    /** Constructor with parent, river segment, and transformation */
    mapObject (RiverSegment *rseg, mapTransform *xform, QGraphicsItem *parent = 0);
    /** Destructor */
    ~mapObject ();

    /** Path of the river - highlights when cursor hovers over it.*/
    QPainterPath path() const;
    /** The shape bounding rectangle. */
    QRectF boundingRect() const;
    /** Paint the object on the map. */
    void paint (QPainter *paintr, const QStyleOptionGraphicsItem *opt, QWidget *w);
    /** Show the itme highlighted. */
    void highlight();
    /** Show the item without highlight. */
    void normal();
//    /** Add Select option to the context menu. */
//    virtual void infoPanel();
    /** The river_segment associated with this item. \return Pointer to the segment or 0 */
    RiverSegment * riverSegment();
    /** The name of the item. \return Item name.*/
    QString name();
    /** Display the segment information at a point. */
    void displayInfo (QPoint);
    /** Display the context menu at a point. */
//    void displayMenu (QPoint);

public slots:
    void showViews(QPointF pt);
    void showViews();
    void showErrors(QPointF pt);

signals:
    void showDetail (RiverSegment *seg);
    void deleteDam (mapObject *obj);

protected:
    /** Shape of the item (used to be an icon) */
    QPainterPath shape() const;
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
//    virtual QMenu * createMenu();
//    virtual void contextMenu();
    QVBoxLayout * getErrorList (RiverSegment * seg);
    QDialog * createViews();

//	QPixmap pix;
    QPainterPath backgroundShape;
    QPainterPath highlightPath;
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

#endif // MAPOBJECT_H
