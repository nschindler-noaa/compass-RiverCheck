#include "mapTransport.h"
//#include "qMercatorTransform.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMenu>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>

mapTransport::mapTransport( mapScene *m )
	: mapItem( m )
{
	setData( SEGTYPE, TRANSPORT );
	mouseOver = false;
	itemOptions = NULL;
}

mapTransport::mapTransport (mapScene *m, struct river_segment *rseg, mapTransform *xform_)
	: mapItem (m, rseg, xform_)
{
	setData (SEGTYPE, TRANSPORT);
	setAcceptHoverEvents (true);
	setAcceptedMouseButtons (Qt::RightButton);
	itemName = *(rseg->seg_name) + QString (" Transport");

	width = 1;
	normalPen = QPen (Qt::blue, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	highlightPen = QPen (Qt::cyan, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

	mouseOver = false;

	path = shape();
	pix = icon();

	itemOptions = NULL;
	itemOptions = createMenu();
	setBoundingRect();
}

QPainterPath mapTransport::shape() const
{
	QPainterPath path;
	QPointF qp( 0, 0 );

	if( rv_seg != NULL && xform != NULL )
	{
		point *p = rv_seg->bottom;
		qp = (*xform)( p->lon, p->lat );
		qp = QPointF( qp.x()-12, qp.y()-12 );
	}
	// path to underlay truck
/*	path.moveTo( QPointF( qp.x() + 5, qp.y() ) );
	path.lineTo( QPointF( qp.x() + 15, qp.y() ) );
	path.lineTo( QPointF( qp.x() + 16, qp.y() + 1 ) );
	path.lineTo( QPointF( qp.x() + 16, qp.y() + 8 ) );
	path.lineTo( QPointF( qp.x(), qp.y() + 8 ) );
	path.lineTo( QPointF( qp.x(), qp.y() + 5 ) );
	path.lineTo( QPointF( qp.x() + 5, qp.y() + 5 ) );
	path.lineTo( QPointF( qp.x() + 5, qp.y() ) );
*/
	// path to underlay barge
	path.moveTo( QPointF( qp.x() + 1, qp.y() + 1 ) );
	path.lineTo( QPointF( qp.x() + 15, qp.y() + 1 ) );
	path.lineTo( QPointF( qp.x() + 15, qp.y() + 5 ) );
	path.lineTo( QPointF( qp.x() + 4, qp.y() + 5 ) );
	path.lineTo( QPointF( qp.x() + 1, qp.y() + 1 ) );

	return path;
}

QPixmap mapTransport::icon()
{
	return QPixmap( ":/images/map_barge_lg.png" );
}

void mapTransport::setBoundingRect()
{
	mapItem::setBoundingRect();
	bounds.setTop( bounds.top() - 7 );
	bounds.setBottom( bounds.bottom() + 5 );
	bounds.setLeft( bounds.left() - 1 );
	bounds.setRight( bounds.right() + 1 );
}

void mapTransport::paint( QPainter *paintr, const QStyleOptionGraphicsItem *opt, QWidget *w )
{
	paintr->setPen(	mouseOver? highlightPen : normalPen );

	paintr->drawPath( path );
	paintr->drawPixmap( bounds, pix, QRectF( 0, 0, 68, 50 ) );
}

QMenu * mapTransport::createMenu()
{
	if( itemOptions == NULL )
	{
		itemOptions = new QMenu();
		itemOptions->addAction( name() );
		itemOptions->addSeparator();
		QAction *actionTool =  itemOptions->addAction( "Transport Tool" );
	}
	return itemOptions;
}

void mapTransport::contextMenu()
{
	QMenu menu;
	QAction *selectAction = menu.addAction("Select");
	menu.show();
}


