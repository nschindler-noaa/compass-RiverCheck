#include "mapHeadwater.h"
//#include "qMercatorTransform.h"
#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsItem>
#include <QtGui/QMenu>
#include <QPainter>
#include <QtGui/QGraphicsSceneMouseEvent>
#include <QtGui/QGraphicsSceneHoverEvent>

mapHeadwater::mapHeadwater(QGraphicsItem *par)
    : mapItem(par)
{
//	setData( SEGTYPE, HEADWATER );
	mouseOver = false;
    itemErrors = NULL;
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

    itemErrors = NULL;
    itemErrors = createInfo();
	setBoundingRect();
}


QPainterPath mapHeadwater::shape() const
{
	QPainterPath path;
	QPointF qp;

	if( rv_seg != NULL && xform != NULL )
	{
//		point *p = rv_seg->top;
//		qp = (*xform)( p->lon, p->lat );
        qp = (*xform) (rv_seg->top()->longitude->value(),
                       rv_seg->top()->latitude->value());
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
    if(itemErrors == NULL)
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


