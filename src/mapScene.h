// mapScene.h
//


#ifndef MAPSCENE_H
#define MAPSCENE_H

#include <QtCore/QObject>//qobject.h>
#include <QtGui/QApplication>//qapplication.h>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QPixmap>//qpixmap.h>
#include <QtGui/QWidget>
#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsItem>

#include "RiverSystem.h"
#include "mapObject.h"
#include "mapLocalTransform.h"

class RiverSystem;

/** Class that holds all the graphic items */
class mapScene : public  QGraphicsScene
{
	Q_OBJECT

public:
	
    /** Constructor \param p Parent QObject pointer */
    mapScene (QObject *p = 0);
    /** Constructor \param rsys River system pointer and \param p Parent QObject pointer */
    mapScene (RiverSystem *rsys, QObject *p = 0);
	/** Destructor */
	~mapScene();

    /** Add all info from a river system to current scene */
    void addRiverSystem (RiverSystem *rsys);

	/** This is the current point transformation from map to screen coordinates */
    mapLocalTransform *xform;
	
	//Transform Methods
	/** Create the transform */
    void createTransform(RiverSystem *rsys);
	/** Put a transform onto the stack \param zpt Pointer to a transformation */
    void pushTransform(mapLocalTransform *zpt);
	/** Take a transform from the stack \return Pointer to a transformation*/
    mapLocalTransform *popTransform();
	/** Clear the stack of all transforms */
    void clearTransforms();
	/** Retrieve the current transform */
    mapLocalTransform *getTransform();
    

//	/** Add a selection rectangle to the map \param p1 Point in upper left \param p2 Point in lower right */
//	void addSelectRect( QPointF p1, QPointF p2 );
//	/** Remove a selection rectangle, if it exists from the map*/
//	void removeSelectRect();

	/** Use the current tranformation to transform a point \param qp Screen coordinates point \return Map coordinates point */
	QPointF transPoint( QPointF qp);
	//Print functions

//	/** Add all transports to the map. This checks all dams for transports. */
//	void addTransports();
//	/** Add all releases to the map \param sites The list of release sites */
//	void addReleases(QList <struct release_site *>sites);
//	/** Remove all transports from the map */
//	void removeTransports();
//	/** Remove all releases from the map*/
//	void removeReleases();

    /*
	We'll handle printing later
	void printMap(QPrinter *p);
	virtual int isPrintMode(){ return isPrintMode_; }
  */
 // public signals:
	//User Events

	/** Create the map grid - lattitude and longitude lines. */
	void drawGrid();
	/** Variable that points to the current river segment */
    void * currentSeg;
    //mapItem * currentSeg;

	/** Find the bounding rectangle for all graphic items. \return The outside rectangle*/
	QRectF boundingRect();

public slots:
	/** Show the map grid. */
	void showGrid();
	/** Hide the map grid. */
	void hideGrid();
	/** Change the releases shown on the map \param new_rls List of releases*/
//	void setReleases (QList<struct release *> new_rls);
//	/** Remove all transports and releases */
//	void clearData();
	/** When the mouse moves, update the displayed map coordinates. \param qpf Current mouse position */
	void mouseMoved (QPointF qpf);

    void showSegmentDetail(RiverSegment *seg);
//    void deleteSegment (RiverSegment *seg);
    void removeObject (mapObject *obj);

signals:
    void evAnnounceSeg(QString);
    void evAnnounceDam(QString);
    void evAnnounceFeature(QString);
    void evAnnounceRelease(QString);
    void evAnnounceLon(QString);
    void evAnnounceLat(QString);
/*	void evRefresh();
	void evConfigure();
	void evDisplay();
	void evDraw();
	void evAnnounce(const int , void* );
	void evLButtonPressed( QPoint);
	void evMButtonPressed( QPoint);
	void evRButtonPressed( QPoint);
	void evMouseMoved(const QPoint );
	void evRButtonAreaSelection(const QRect );
	void evLButtonAreaSelection(const QRect );
*/  
    void showDetail(RiverSegment *seg);
    void deleteSegment (RiverSegment *seg);

private:
	QGraphicsPathItem grid;
	QRectF *selectRect;
	QRectF riverRect;
	QGraphicsRectItem *selection;
    void drawSelect(bool openPainter);
//	mapTransport* maptransports[MAX_TRNS];
//	mapRelease* mapreleases[MAX_RELS];

};



#endif // MAPSCENE_H

