// mapView.h
//


#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QtCore/QObject>//qobject.h>
#include <QtGui/QApplication>//qapplication.h>
#include <QtGui/QPaintEvent>
#include <QtGui/QResizeEvent>
#include <QtGui/QMouseEvent>
#include <QtGui/QPixmap>//qpixmap.h>
#include <QtGui/QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMenu>

#include "mapScene.h"
#include "mapItem.h"

class mapItem;
class mapNoTransform;

/** Class that deals with zooming, panning, etc. */
class mapView : public  QGraphicsView
{
	Q_OBJECT

public:
	/** Constructor \param p Parent widget */
	mapView(QWidget *p);
	/** Destructor */
	~mapView();

	/** Point used to track mouse movement */
	QPoint p0_;  // used by the DrawSelect function for area selections (zooming, etc)
	/** Point used to track mouse movement for area selection */
	QPoint p1_;
	/** Point used to track mouse movement for area selection */
	QPoint p2_;
	/** Track left mouse button press */
    int leftMouseButtonPressed_;
	/** Track right mouse button press */
	int rightMouseButtonPressed_;
	/** Track middle mouse button press */
	int	middleMouseButtonPressed_;

	/** Get the transform from the mapScene \return Pointer to the transform*/
	mapLocalTransform *getTransform();

	/** The mouse button is pressed \param e Mouse event*/
	void mousePressEvent( QMouseEvent * e );
	/** The mouse button is released \param e Mouse event*/
	void mouseReleaseEvent( QMouseEvent * e );
	/** The mouse moves \param e Mouse event*/
    void mouseMoveEvent( QMouseEvent * e );

	/** Display a context menu \param mpsg Current item \param pos Mouse position*/
	void displayMenu( mapItem *mpsg, QPoint pos );

public slots:
	/** Reset zoom level to 0, bounding rectangle for whole scene*/
	void resetZoom();
	/** Show the map grid*/
	void showGrid();
	/** Hide the map grid */
	void hideGrid();

	/** Set new release information \param new_releases List of new releases*/
	void setReleases (QList<struct release *>new_releases );
	/** Remove all transport and release data from map */
	void clearData();
	
	/** Something happened \param act The action triggered*/
	void actionTriggered( QAction *act );

	/** Show the release tool dialog*/
	void releaseTool();
	/** Show the transport tool dialog*/
	void transportTool();

signals:
	void evAnnounceSeg( QString );
	void evAnnounceDam( QString );
	void evAnnounceFeature( QString );
	void evAnnounceRelease( QString );
	void evAnnounceLon( QString );
	void evAnnounceLat( QString );
	void evAnnounceX( QString );
	void evAnnounceY( QString );

	void evMouseMoved( QPointF );

protected:  
	void wheelEvent( QWheelEvent *evnt );
//	void mouseEvent( QMouseEvent *evnt );
//	void drawBackground( QPainter *paintr, const QRectF &rct );
	void scaleView( QPoint p1, QPoint p2 );
	void scaleView( qreal scaleFactor );
	void createActions();
	mapItem * currentSeg;
	QMenu * itemOptions;
	QAction *actionDamFlowRate;
	QAction *actionDamSpllRate;
	QAction *actionDamTDGSat;
	QAction *actionDamWaterTemp;
	QAction *actionDamTurbidity;
	QAction *actionDamBasinVol;
	QAction *actionDamSpillEq;
	QAction *actionDamDelayEq;
	QAction *actionDamDayTDBSatEq;
	QAction *actionDamNghtTDGSatEq;
	QAction *actionDamBackupTDGSatEq;
	QAction *actionDamFGEEq;
	QAction *actionDamTrnsMortEq;
	QAction *actionDamPassHist;
	QAction *actionDamBypsHist;
	QAction *actionDamTrnsHist;
	QAction *actionDamSplwHist;
	QAction *actionDamTurbHist;
	QAction *actionRchFlowRate;
	QAction *actionRchWaterTemp;
	QAction *actionRchTurbidity;
	QAction *actionRchTDGSat;
	QAction *actionRchVelocity;
	QAction *actionRchElevChng;
	QAction *actionRchLoss;
	QAction *actionRchPassHist;
	QAction *actionRchLengHist;
	QAction *actionRchGasDist;
	QAction *actionHwtFlowRate;
	QAction *actionHwtWaterTemp;
	QAction *actionHwtTurbidity;
	QAction *actionRelTool;
	QAction *actionTrnTool;

signals:
	void currentLocation( int, int );
	void currentLocation( float, float );
	void currentRelease( QString );
	void currentFeature( QString );
	void currentSegment( QString );

private:
	mapScene *map;
//    void drawSelect(bool openPainter);

};



#endif // MAPVIEW_H

