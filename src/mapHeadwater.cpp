#include "mapHeadwater.h"
//#include "qMercatorTransform.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMenu>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>

mapHeadwater::mapHeadwater(QGraphicsItem *par)
    : mapItem(par)
{
//	setData( SEGTYPE, HEADWATER );
    mouseOver = false;
    itemErrors = nullptr;
}

mapHeadwater::mapHeadwater(RiverSegment *rseg, mapTransform *xform_, QGraphicsItem *par)
    : mapItem(rseg, xform_, par)
{
//	setData( SEGTYPE, HEADWATER );
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::RightButton | Qt::LeftButton);

    width = 1;
    normalPen = QPen(QBrush(Qt::blue), width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    highlightPen = QPen(QBrush(Qt::cyan), width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    mouseOver = false;

    path = shape();

    itemErrors = nullptr;
    itemErrors = createInfo();
    setBoundingRect();
}


QPainterPath mapHeadwater::shape() const
{
    QPainterPath path;
    QPointF qp;

    if( rv_seg != nullptr && xform != nullptr )
    {
//		point *p = rv_seg->top;
//		qp = (*xform)( p->lon, p->lat );
        qp = (*xform) (rv_seg->top()->longitude,
                       rv_seg->top()->latitude);
        //path.addEllipse( qp.x() - 1, qp.y() - 1, 2.0, 2.0 );
        path.addEllipse( qp.x() - .5, qp.y() - .5, 1.0, 1.0 );
        //path.addRect( qp.x() - .5, qp.y() - .5, 1.0, 1.0 );
    }
    return path;
}

void mapHeadwater::paint (QPainter *paintr, const QStyleOptionGraphicsItem *opt, QWidget *w)
{
    paintr->setPen(mouseOver? highlightPen : normalPen);

    paintr->drawPath(path);
}

/*QDialog * mapHeadwater::createInfo()
{
    if(itemErrors == nullptr)
    {
        itemErrors = new QDialog();
        itemErrors->addAction( name() );
        itemErrors->addSeparator();
        QAction *actionFlowRate =  itemOptions->addAction( "Headwater Flow" );
        QAction *actionWaterTemp = itemOptions->addAction( "Headwater Temperature" );
        QAction *actionTurbidity = itemOptions->addAction( "Headwater Turbidity" );
    }
    return itemOptions;
}*/

void mapHeadwater::infoPanel()
{
    QDialog menu;
//	QAction *selectAction = menu.addAction("Select");
    menu.show();
}


