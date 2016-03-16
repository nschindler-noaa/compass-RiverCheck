// mapView.cpp
//
// Last modified, 10-28-2009, Neal Schindler
#include <QtGui\QPaintEvent>
#include <QtGui\QResizeEvent>
#include <QtGui\QMouseEvent>
#include <qpainter.h>
#include <qprinter.h>
#include <QPrintDialog>
#include <QPointF>


#include "mapView.h"
#include "mapScene.h"
#include "mapItem.h"
//#include "QPointTransform.h"
//#include "qMercatorTransform.h"
//#include "qGraphDataTokenTypes.h"
//#include "qMediatorBuilder.h"
//#include "qMapMediator.h"
#include "log.h"

mapView::mapView (QWidget *p) 
	: QGraphicsView(p) 
{
	map = new mapScene (p);
	setScene (map);
	this->setSceneRect (map->boundingRect());
	resetZoom();
	connect(map, SIGNAL(evAnnounceLon(QString)), SIGNAL(evAnnounceLon(QString)));
	connect(map, SIGNAL(evAnnounceLat(QString)), SIGNAL(evAnnounceLat(QString)));
	connect(map, SIGNAL(evAnnounceSeg(QString)), SIGNAL(evAnnounceSeg(QString)));
	connect(map, SIGNAL(evAnnounceDam(QString)), SIGNAL(evAnnounceDam(QString)));
	connect(map, SIGNAL(evAnnounceRelease(QString)), SIGNAL(evAnnounceRelease(QString)));
	connect(map, SIGNAL(evAnnounceFeature(QString)), SIGNAL(evAnnounceFeature(QString)));
    connect (map, SIGNAL(deleteDam(RiverSegment*), SIGNAL(del))
	connect(this, SIGNAL(evMouseMoved(QPointF)), map, SLOT(mouseMoved(QPointF)));

	leftMouseButtonPressed_ = 0;
	middleMouseButtonPressed_ = 0;
	rightMouseButtonPressed_ = 0;
	
	currentSeg = NULL;

	createActions();
	itemOptions = new QMenu (this);
	connect(itemOptions, SIGNAL(triggered(QAction *)), SLOT(actionTriggered(QAction *)));
}

mapView::~mapView() 
{
	//clearTransforms();
}

mapLocalTransform * mapView::getTransform()
{
	return map->getTransform();
}

/*
void mapView::printMap( QPrinter *pnter )
{
	isPrintMode_ = true;
	QPainter *old_painter = currPainter;

/*	QPrinter printer(QPrinter::PrinterResolution);
	printer.setOrientation(QPrinter::Landscape) ;
	printer.setPageSize(QPrinter::Letter) ;
//	printer.setMinMax ( 1,1 );
	printer.setFromTo( 1, 1 );
	printer.setPrintRange(QPrinter::AllPages);

	QPrintDialog dialog( &printer, this );
	dialog.setMinMax( 1, 1 );
	if( dialog.exec() ) //printer.setup (0))
*/	
/*	{
		QPainter p;
        if( !p.begin( pnter ) )//&printer ) ) 
		{               // paint on printer
            return;
        }
	
//        Q3PaintDeviceMetrics metrics( p.device() );
//        int dpiy = metrics.logicalDpiY();
		int dpiy = p.device()->logicalDpiY();
        int margin = (int) ( (2/2.54)*dpiy ); // 2 cm margins
        
//		QRect body( 0,0, metrics.width(), metrics.height() );
		QRect body( 0, 0, p.device()->width(), p.device()->height() );
		currPainter = &p; //set the painter
		drawArea = body;
		
		qMapMediator* mapMed = (qMapMediator*) ((/*qMapWindow*//*qMapWidget*)parentWidget() )->getMapMediator();
		QStack <mapCordset*> mapStack_;
		mapStack_ =  mapMed->getCordStack() ;//= ;

		qMercatorTransform *trans;
		mapCordset *defaultCord_ = new mapCordset(124.3,49.0,113.2,43.50);
		if(mapStack_.top())
			trans = new qMercatorTransform(body,mapStack_.top());
		else	  
			trans = new qMercatorTransform(body,defaultCord_);

		pushTransform(trans);
		emit evRefresh();
		//done printing
		//popTransform();
		delete defaultCord_;
	}
	currPainter = old_painter;
	isPrintMode_ = false;
}


//	mapView::mouseButtonDown(zMouseClickEvt *ev)
//
//	Pretty straight forward.. this is the virtual zPane::mouseButtonDown
//  it's been modified so that it remembers which mouse button was pressed
//  and captures the mouse in case the user does an area selection.


void mapView::resizeEvent ( QResizeEvent * qre )
{
	QPaintEvent  *p = new QPaintEvent(QRect());
	paintEvent(p);
}
*/

void mapView::mousePressEvent (QMouseEvent * qme)
{
    switch(qme->button())
	{
	case Qt::LeftButton:
		leftMouseButtonPressed_ = 1;
		p0_ = p1_ = p2_ = qme->pos();
		break;
	case Qt::RightButton:
	case Qt::MidButton:	
	default:
		break;
	}
}

//	mapView::mouseReleaseEvent ( QMouseEvent * qme )
//  
//	This function looks a little involved but it basically handles notification
//  of the button pressed and the area selection events based on whether an area
//  was selected or a single button was pressed.  It does this for both the left
//  and the right mouse buttons, and the AreaSelection_ notifications always send
//  a QRect with the upper left coordinate < the lower right so it's a bit long.

void mapView::mouseReleaseEvent ( QMouseEvent * qme )
{
	const int minZoomSize = 10;
	int b = qme->button();
	//p1_ = original click point
	//p2_ and p0_ = last point released on
	p0_ = p2_ = qme->pos();

	switch( qme->button() )
	{
	case Qt::LeftButton:
		if( leftMouseButtonPressed_ )
		{
			leftMouseButtonPressed_ = 0;
			map->removeSelectRect();
			if( p2_ != p1_ ) 
			{  // we want to center and scale the view
				scaleView( p1_, p2_ );
			}
		}
		break;
	case Qt::RightButton:
	default:
		break;
	}

    return;
}

//  mapView::mouseMove(zMouseMoveEvt *ev)
//
//  This function is an override of the zPane::mouseMove event.
//  It's been customized to handle area selections with the left and right 
//  mouse buttons, and does a notification to the evMouseMoved_ event
//  to notify the registered ZatMapSubMediators of the change


void mapView::mouseMoveEvent( QMouseEvent * qme )
{
	p0_ = qme->pos();
	if( p0_ != p2_ )
	{
		// update mapWidget
		emit evAnnounceX( QString::number( p0_.x() ) );
		emit evAnnounceY( QString::number( p0_.y() ) );

		emit evMouseMoved( mapToScene( p0_ ) );

		if( currentSeg != NULL )
			currentSeg->normal();

		if( leftMouseButtonPressed_ )
		{
			map->removeSelectRect();
			map->addSelectRect( mapToScene(p1_), mapToScene(p0_) );
		}
		else
		{
			mapItem *newSeg = (mapItem *)itemAt(p0_);
			if( newSeg == NULL || newSeg->zValue() < 1.0 )
			{
				emit evAnnounceSeg( QString( "" ) );
				currentSeg = NULL;
			}
			else if( newSeg->riverSegment() != NULL )
			{
				emit evAnnounceSeg( newSeg->name() );
				newSeg->highlight();
				currentSeg = newSeg;
			}
		}
	}
	p2_ = p0_;
}
	

void mapView::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, event->delta() / 240.0));
}

void mapView::scaleView( QPoint p1, QPoint p2 )
{
	int x1, y1, x2, y2;
	QRect qr = rect();
	if( p1.x() < p2.x() )
	{	x1 = p1.x(); x2 = p2.x();	}
	else
	{	x1 = p2.x(); x2 = p1.x();	}
	if( p1.y() < p2.y() )
	{	y1 = p1.y(); y2 = p2.y();	}
	else
	{	y1 = p2.y(); y2 = p1.y();	}

	qreal xdist = (qreal)x2 - x1;
	qreal ydist = (qreal)y2 - y1;

	centerOn( mapToScene( QPoint( x1 + (int)xdist/2.0, y1 + (int)ydist/2.0 ) ) );

	qreal xscalefactor = qr.width() / xdist;
	qreal yscalefactor = qr.height() / ydist;
	scaleView( xscalefactor < yscalefactor ? xscalefactor : yscalefactor );
}

void mapView::scaleView(qreal scaleFactor)
{
    qreal factor = matrix().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if ( factor < 1.0 || factor > 100.0 )
        return;

    scale(scaleFactor, scaleFactor);
}

void mapView::resetZoom()
{
	QMatrix m(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);// = matrix();
	setMatrix( m, false );
}

void mapView::showGrid()
{
	map->showGrid();
}

void mapView::hideGrid()
{
	map->hideGrid();
}

void mapView::clearData()
{
	map->clearData();
}

void mapView::setReleases (QList<struct release *> new_releases)
{
	map->clearData();
	map->setReleases (new_releases);
}

void mapView::createActions()
{
	actionDamFlowRate = new QAction( "Flow Rate", this );
	actionDamFlowRate->setData( GDTT_DAM_Flow );
	actionDamSpllRate = new QAction( "Spill Rate", this );
	actionDamSpllRate->setData( GDTT_DAM_Spill );
	actionDamTDGSat = new QAction( "TDG Saturation > 100%", this );
	actionDamTDGSat->setData( GDTT_DAM_NSat );
	actionDamWaterTemp = new QAction( "Water Temperature", this );
	actionDamWaterTemp->setData( GDTT_DAM_WaterTemp );
	actionDamTurbidity = new QAction( "Turbidity", this );
	actionDamTurbidity->setData( GDTT_DAM_Turbidity );
	actionDamBasinVol = new QAction( "Basin Volume", this );
	actionDamBasinVol->setData( GDTT_DAM_BasinVolume );
	actionDamSpillEq = new QAction( "Spill Equation", this );
	actionDamSpillEq->setData( GDTT_DAMEQUATION_Spill );
	actionDamDelayEq = new QAction( "Delay Equation", this );
	actionDamDelayEq->setData( GDTT_DAMEQUATION_Delay );
	actionDamDayTDBSatEq = new QAction( "Day TDG Sat Equation", this );
	actionDamDayTDBSatEq->setData( GDTT_DAMEQUATION_NSat );
	actionDamNghtTDGSatEq = new QAction( "Night TDG Sat Equation", this );
	actionDamNghtTDGSatEq->setData( GDTT_DAMEQUATION_NightNSat );
	actionDamBackupTDGSatEq = new QAction( "Backup TDG Sat Equation", this );
	actionDamBackupTDGSatEq->setData( GDTT_DAMEQUATION_BackupNSat );
	actionDamFGEEq = new QAction( "FGE Equation", this );
	actionDamFGEEq->setData( GDTT_DAMEQUATION_FGE );
	actionDamTrnsMortEq = new QAction( "Transport Mortality Equation", this );
	actionDamTrnsMortEq->setData( GDTT_DAMEQUATION_Trans );
	actionDamPassHist = new QAction( "Passage Histogram", this );
	actionDamPassHist->setData( GDTT_PASSAGE_Dam );
#ifdef ROUTE_TRACKING
	actionDamBypsHist = new QAction( "Bypass Histogram", this );
	actionDamBypsHist->setData( GDTT_PASSAGE_Bypass );
	actionDamTrnsHist = new QAction( "Transport Histogram", this );
	actionDamTrnsHist->setData( GDTT_PASSAGE_Transport );
	actionDamSplwHist = new QAction( "Spillway Histogram", this );
	actionDamSplwHist->setData( GDTT_PASSAGE_Spillway );
	actionDamTurbHist = new QAction( "Turbine Histogram", this );
	actionDamTurbHist->setData( GDTT_PASSAGE_Turbine );
#endif 

	actionRchFlowRate = new QAction( "Flow Rate", this );
	actionRchFlowRate->setData( GDTT_REACH_Flow );
	actionRchWaterTemp = new QAction( "Water Temperature", this );
	actionRchWaterTemp->setData( GDTT_REACH_WaterTemp );
	actionRchTurbidity = new QAction( "Turbidity", this );
	actionRchTurbidity->setData( GDTT_REACH_Turbidity );
	actionRchTDGSat = new QAction( "TDG Saturation > 100%", this );
	actionRchTDGSat->setData( GDTT_REACH_NSatOut );
	actionRchVelocity = new QAction( "Velocity", this );
	actionRchVelocity->setData( GDTT_REACH_Velocity );
	actionRchElevChng = new QAction( "Elevation Change", this );
	actionRchElevChng->setData( GDTT_REACH_ElevationChange );
	actionRchLoss = new QAction( "Loss", this );
	actionRchLoss->setData( GDTT_REACH_Loss );
	actionRchPassHist = new QAction( "Passage Histogram", this );
	actionRchPassHist->setData( GDTT_PASSAGE_Reach );
	actionRchLengHist = new QAction( "Length Histogram", this );
	actionRchLengHist->setData( GDTT_PASSAGE_ReachLength );
	actionRchGasDist = new QAction( "Gas Distribution", this );
	actionRchGasDist->setData( GDTT_REACH_GasDist );

	actionHwtFlowRate = new QAction( "Headwater Flow", this );
	actionHwtFlowRate->setData( GDTT_HEADWATER_Flow );
	actionHwtWaterTemp = new QAction( "Headwater Temperature", this );
	actionHwtWaterTemp->setData( GDTT_HEADWATER_WaterTemp );
	actionHwtTurbidity = new QAction( "Headwater Turbidity", this );
	actionHwtTurbidity->setData( GDTT_HEADWATER_Turbidity );

	actionRelTool = new QAction( "Release Data", this );
	connect( actionRelTool, SIGNAL( triggered() ), SLOT( releaseTool() ) );

	actionTrnTool = new QAction( "Transport Data", this );
	connect( actionTrnTool, SIGNAL( triggered() ), SLOT( transportTool() ) );
}
void mapView::displayMenu( mapItem *item, QPoint pos )
{  
	itemOptions->clear();
	QAction *name = itemOptions->addAction( currentSeg->name() );
	name->setEnabled( false );
	itemOptions->addSeparator();

	switch( currentSeg->data( SEGTYPE ).toInt() )
	{
	case DAM:
		itemOptions->addAction( actionDamFlowRate );
		itemOptions->addAction( actionDamSpllRate );
//		itemOptions->addAction( actionDamTDGSat );
		itemOptions->addAction( actionDamWaterTemp );
//		itemOptions->addAction( actionDamTurbidity );
		itemOptions->addAction( actionDamBasinVol );
//		itemOptions->addAction( actionDamSpillEq );
//		itemOptions->addAction( actionDamDelayEq );
//		itemOptions->addAction( actionDamDayTDBSatEq );
//		itemOptions->addAction( actionDamNghtTDGSatEq );
//		itemOptions->addAction( actionDamBackupTDGSatEq );
//		itemOptions->addAction( actionDamFGEEq );
//		itemOptions->addAction( actionDamTrnsMortEq );
		itemOptions->addAction( actionDamPassHist );
#ifdef ROUTE_TRACKING
		itemOptions->addAction( actionDamBypsHist );
		itemOptions->addAction( actionDamTrnsHist );
		itemOptions->addAction( actionDamSplwHist );
		itemOptions->addAction( actionDamTurbHist );
#endif 
		break;
	case REACH:
		itemOptions->addAction( actionRchFlowRate );
		itemOptions->addAction( actionRchWaterTemp );
//		itemOptions->addAction( actionRchTurbidity );
//		itemOptions->addAction( actionRchTDGSat );
		itemOptions->addAction( actionRchVelocity );
		itemOptions->addAction( actionRchElevChng );
		itemOptions->addAction( actionRchLoss );
		itemOptions->addAction( actionRchPassHist );
		itemOptions->addAction( actionRchLengHist );
//		itemOptions->addAction( actionRchGasDist );
		break;
	case HEADWATER:
		itemOptions->addAction( actionHwtFlowRate );
		itemOptions->addAction( actionHwtWaterTemp );
//		itemOptions->addAction( actionHwtTurbidity );
		break;
	case RELEASE:
		itemOptions->addAction( actionRelTool );
		break;
	case TRANSPORT:
		itemOptions->addAction( actionTrnTool );
	}
	itemOptions->popup( pos );
}

void mapView::releaseTool()
{
	qCompassWindow::instance()->ReleaseTool(*(currentSeg->riverSegment()->seg_name));
}

void mapView::transportTool()
{
	qCompassWindow::instance()->Transport(*(currentSeg->riverSegment()->seg_name));
}

void mapView::actionTriggered( QAction *qact )
{
	qMediatorBuilder::instance( qCompassWindow::instance() ) 
		->makeDialog( qact->data().toInt(), currentSeg->name() );
}
