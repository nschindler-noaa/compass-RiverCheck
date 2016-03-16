#include "mapRelease.h"
//#include "qMercatorTransform.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMenu>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>

mapRelease::mapRelease( mapScene *m )
	: mapItem( m )
{
	setData( SEGTYPE, RELEASE );
	mouseOver = false;
	itemOptions = NULL;
}

mapRelease::mapRelease (mapScene *m, struct release_site *site, mapTransform *xform_)
	: mapItem (m, site->seg, xform_)
{
	setData(SEGTYPE, RELEASE);
	setAcceptHoverEvents(true);
	setAcceptedMouseButtons(Qt::RightButton);

	setIcon (QPixmap(":/images/map_relsite_lg.png"));
	itemName = *(site->name);

	for (int k = 0; k < current->release_list.count(); k++)// struct release *itr = current->release_list; itr != NULL; itr = itr->next )
	{
		struct release * itr = current->release_list[k];
		rls = NULL;
		if(site->seg->seg_name->compare (*(itr->rls_seg->river_segment->seg_name)) == 0)
		{
			rls = itr;
			setIcon (QPixmap(":/images/map_relsite_lg.png"));
			itemName = *(site->seg->seg_name) + QString(" (") + 
				*(rls->species->name) + QString(", ") +
				(&rls->stock? *(rls->stock->name) : QString("Generic")) + QString(")");
			break;
		}
	}

	width = 1;
	normalPen = QPen( Qt::blue, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin );
	highlightPen = QPen( Qt::cyan, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin );

	mouseOver = false;

	path = shape();

	itemOptions = NULL;
	itemOptions = createMenu();
	setBoundingRect();
}

mapRelease::mapRelease (mapScene *m, struct release *rel, mapTransform *xform_)
	: mapItem(m, rel->rls_seg->river_segment, xform_)
{
	setData(SEGTYPE, RELEASE);
	rls = rel;
	setAcceptHoverEvents(true);
	setAcceptedMouseButtons(Qt::RightButton);
	itemName = *(rls->site->seg->seg_name) + QString(" (") + 
			*(rel->species->name) + QString(", ") +
			(&rel->stock? *(rel->stock->name) : QString("Generic")) + QString(")");

	width = 1;
	normalPen = QPen(Qt::blue, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	highlightPen = QPen(Qt::cyan, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

	mouseOver = false;

	path = shape();
	setIcon(QPixmap(":/images/map_relsite_lg.png"));

	itemOptions = NULL;
	itemOptions = createMenu();
	setBoundingRect();
}

QPixmap mapRelease::icon()
{
	return pix;
}

void mapRelease::setIcon(QPixmap px)
{
	pix = px;
}


QPainterPath mapRelease::shape() const
{
	QPainterPath pth, outline;
	QPointF qp( 0.0, 0.0 );

	
	if(rv_seg != NULL && xform != NULL)
	{
		point *p = rv_seg->bottom;
		qp = (*xform)(p->lon, p->lat);
		pth.moveTo(qp);

		for(p = p->next; p != NULL; p = p->next)
		{
			qp = (*xform)(p->lon, p->lat);
			pth.lineTo(qp);
			if( p->lat == rv_seg->top->lat && p->lon == rv_seg->top->lon )
				break;
		}
	}
	qp = pth.pointAtPercent(.10);
	
	outline.moveTo (QPointF (qp.x() + 2, qp.y() - 2));
	outline.lineTo (QPointF (qp.x() + 11, qp.y() - 5));
	outline.lineTo (QPointF (qp.x() + 11, qp.y() - 4));
	outline.lineTo (QPointF (qp.x() + 15, qp.y() - 3));
	outline.lineTo (QPointF (qp.x() + 17, qp.y() - 5));
	outline.lineTo (QPointF (qp.x() + 17, qp.y() - 0));
	outline.lineTo (QPointF (qp.x() + 15, qp.y() - 1));
	outline.lineTo (QPointF (qp.x() + 13, qp.y() - 0));
	outline.lineTo (QPointF (qp.x() + 12, qp.y() - 0));
	outline.lineTo (QPointF (qp.x() + 7, qp.y() - 0));
	outline.lineTo (QPointF (qp.x() + 2, qp.y() - 1));
	outline.lineTo (QPointF (qp.x() + 2, qp.y() - 2));

	outline.setFillRule(Qt::WindingFill);

	return outline;
}

void mapRelease::setBoundingRect() 
{
	mapItem::setBoundingRect();
	bounds.setWidth(19);
	bounds.setHeight(6);
	bounds.setTop(bounds.top() - 3);
}


void mapRelease::paint(QPainter *paintr, const QStyleOptionGraphicsItem *opt, QWidget *w)
{
	paintr->setPen(	mouseOver? highlightPen : normalPen );

	paintr->drawPath( path );
	paintr->fillPath( path, QBrush( mouseOver? Qt::cyan : Qt::blue ) );
	paintr->drawPixmap( bounds, pix, QRectF( 0, 0, 72, 34 ) );
}

QMenu * mapRelease::createMenu()
{
	if( itemOptions == NULL )
	{
		itemOptions = new QMenu();
		itemOptions->addAction( name() );
		itemOptions->addSeparator();
		QAction *actionTool =  itemOptions->addAction( "Release Tool" );
	}
	return itemOptions;
}


void mapRelease::contextMenu()
{
	QMenu menu;
	QAction *selectAction = menu.addAction("Select");
	menu.show();
}

