#include "mapSite.h"
//#include "qMercatorTransform.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMenu>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>

mapSite::mapSite(QGraphicsItem *par)
    : QGraphicsItem(par)
{
//	setData( SEGTYPE, REACH );
	mouseOver = false;
	itemOptions = NULL;
}

mapSite::mapSite(RiverSite *rsite, mapTransform *xform_, QGraphicsItem *par)
    : QGraphicsItem(par)
{
    rv_site = rsite;
    xform = xform_;

//    setData(SEGTYPE, REACH);
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::RightButton | Qt::LeftButton);

    width = 2;//(int)(rseg->current->reach.width / 1500) + 1;
    normalPen = QPen( Qt::black, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin );
    highlightPen = QPen( Qt::gray, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin );
    errorPen = QPen( Qt::red, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin );

	mouseOver = false;

	path = shape();

	itemOptions = NULL;
	itemOptions = createMenu();
//	setBoundingRect();
}

QPainterPath mapSite::shape() const
{
	QPainterPath path;
	QPointF qp;

    if (rv_site != NULL && xform != NULL)
	{
        qp = (*xform) (rv_site->location->longitude->value(),
                       rv_site->location->latitude->value());
		path.moveTo (qp);
/*		for (p = p->next; p != NULL; p = p->next)
		{
			qp = (*xform) (p->lon, p->lat);
			path.lineTo (qp);
			if (p->lat == rv_seg->top->lat && p->lon == rv_seg->top->lon)
				break;
        }*/
	}
	return path;
}

void mapSite::paint(QPainter *paintr, const QStyleOptionGraphicsItem *opt, QWidget *w)
{
    paintr->setPen(mouseOver? highlightPen : normalPen);

    paintr->drawPath(path);
}

QMenu * mapSite::createMenu()
{
    if(itemOptions == NULL)
	{
		itemOptions = new QMenu();
/*		itemOptions->addAction( name() );//QString(rv_seg->seg_name) );
		itemOptions->addSeparator();
		QAction *actionFlowRate =  itemOptions->addAction( "Flow Rate" );
		QAction *actionWaterTemp = itemOptions->addAction( "Water Temperature" );
		QAction *actionTurbidity = itemOptions->addAction( "Turbidity" );
		//QAction *actionTDGSat =    itemOptions->addAction( "TDG Saturation > 100%" );
		QAction *actionVelocity =  itemOptions->addAction( "Velocity" );
		QAction *actionElevChng =  itemOptions->addAction( "Elevation Change" );
		QAction *actionLoss =      itemOptions->addAction( "Loss" );
		QAction *actionPassHist =  itemOptions->addAction( "Passage Histogram" );
		QAction *actionLengHist =  itemOptions->addAction( "Length Histogram" );
        QAction *actionGasDist =   itemOptions->addAction( "Gas Distribution" );*/
	}
	return itemOptions;
}


void mapSite::contextMenu()
{
	QMenu menu;
//	QAction *selectAction = menu.addAction("Select");
	menu.show();
}


