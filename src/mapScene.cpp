// mapScene.cpp
//
// Last modified, 05-21-2009, Neal Schindler
#include <QPaintEvent>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QRectF>
#include <qpainter.h>
#include <QtPrintSupport/QPrintDialog>
//#include <qprinter.h>
//#include <QPrintDialog>
#include <QGraphicsSceneEvent>

//#include "compass.h"
#include "mapScene.h"
#include "mapPoint.h"
//#include "QPointTransform.h"
//#include "qMercatorTransform.h"
#include "mapLocalTransform.h"
//#include "qMapMediator.h"
#include "Log.h"
//#include "qDefines.h"
//#include "qMapWidget.h"
#include "mapDam.h"
#include "mapReach.h"
#include "mapHeadwater.h"
#include "mapTransport.h"
#include "mapRelease.h"

mapScene::mapScene(QObject *p)
    : QGraphicsScene(p)
{
    xform = nullptr;
    selectRect = nullptr;
    selection = nullptr;
    currentSeg = nullptr;
}

mapScene::mapScene (RiverSystem *rsys, QObject *p)
    : QGraphicsScene(p)
{
    xform = nullptr;
    selectRect = nullptr;
    selection = nullptr;
    currentSeg = nullptr;

    createTransform(rsys);
    xform = getTransform();

    addRiverSystem (rsys);

    riverRect = itemsBoundingRect();

    drawGrid();
    grid.setEnabled(false);
    addItem((QGraphicsItem *)&grid);
    showGrid();
}

mapScene::~mapScene()
{
    clearTransforms();
}

void mapScene::addRiverSystem(RiverSystem *rsys)
{
    mapObject *segment;
    // Add all rivers
    for (int i = 0; i < rsys->rivers->count(); i++)
    {
        River * river = rsys->rivers->at(i);
        // add all segments on the river
        for (int j = 0; j < river->segments->count(); j++)
        {
            segment = nullptr;
            RiverSegment * seg = river->segments->at(j);
            switch (seg->type)
            {
            case RiverSegment::ReachSegment:
                segment = new mapReach(seg, xform);
                break;
            case RiverSegment::DamSegment:
                segment = new mapDam(seg, xform);
                break;
            case RiverSegment::HeadwaterSegment:
            default:
                break;
            }
            if (segment != nullptr)
            {
                addItem(segment);
                connect (segment, SIGNAL(showDetail(RiverSegment *)),SLOT(showSegmentDetail(RiverSegment*)));
                connect (segment, SIGNAL(deleteDam(mapObject *)), SLOT(removeObject(mapObject*)));
            }
        }
    }

    // Add all release sites

}

QRectF mapScene::boundingRect()
{
    return riverRect;
}

void mapScene::drawGrid()
{
    int xstart, xend;
    int ystart, yend;
    QPainterPath * gridPath = new QPainterPath();
    QPen pen (Qt::gray, 1, Qt::DashDotLine);
    QPointF bl (xform->reverse (riverRect.bottomLeft()));
    QPointF tl (xform->reverse (riverRect.topLeft()));
    QPointF br (xform->reverse (riverRect.bottomRight()));
    QPointF tr (xform->reverse (riverRect.topRight()));
    if( bl.x() < tl.x() )
        xstart = (int)bl.x();
    else
        xstart = (int)tl.x();
    if( br.x() < tr.x() )
        xend = (int)tr.x();
    else
        xend = (int)br.x();

    ystart = (int)br.y();
    yend = (int)tl.y() + 1;

    for (int i = xstart; i <= xend; i++)
    {
        gridPath->moveTo((*xform)(i, ystart));
        for (int j = ystart + 1; j <= yend; j++)
            gridPath->lineTo ((*xform)(i, j));
    }
    for (int j = ystart; j <= yend; j++)
    {
        gridPath->moveTo((*xform)(xstart, j));
        for (int i = xstart + 1; i <= xend; i++)
            gridPath->lineTo((*xform)(i, j));
    }
    grid.setPath (*gridPath);
    grid.setPen (pen);
    grid.setZValue (0);
}

void mapScene::showGrid()
{
    grid.setVisible (true);
}

void mapScene::hideGrid()
{
    grid.setVisible (false);
}

void mapScene::showSegmentDetail(RiverSegment *seg)
{
    emit showDetail(seg);
}

/*void mapScene::deleteSegment(RiverSegment *seg)
{
    emit deleteDam(seg);
}*/

void mapScene::removeObject(mapObject *obj)
{
    if (obj->riverSegment() != nullptr)
        emit deleteSegment(obj->riverSegment());
    removeItem(obj);
    delete obj;
}

/*
void mapScene::setReleases (QList<struct release *> new_rls)
{
    addTransports();
    addReleases (release_sites);
}

void mapScene::clearData()
{
    removeTransports();
    removeReleases();
}

void mapScene::addTransports()
{
    int i, k;
    mapTransport * maptrns;*/
    /* Loop through dams */
/*	for (i = 0, k = 0; k < MAX_TRNS && i < dams.count(); i++)
    {
        if (dams[i] == nullptr)
            break;
        else
        {
            if (dams[i]->current->dam.collector)
            {
                maptrns = new mapTransport(this, dams[i], xform);
                maptransports[k] = maptrns;
                maptrns->setZValue (4);
                addItem (maptrns);
                k++;
            }
        }
    }
    for (; k < MAX_TRNS; k++)
        maptransports[k] = nullptr;
}

void mapScene::addReleases( struct release * new_rls )
{
    struct release *itr;
    struct release_site *site = release_sites;
    int index;
    for( itr = new_rls; itr != nullptr; itr = itr->next )
    {
        QString itemName = QString( itr->site->seg->seg_name ) + QString( " (" ) +
            QString( itr->species->name ) + QString( ", " ) +
            (&itr->stock? QString( itr->stock->name ) : QString( "Generic" )) + QString( ")" );
        for( ; site != nullptr; site = site->next )
        {
            if( QString( site->name ) == itemName )

                break;
        }
    }
    addReleases( release_sites );
}

void mapScene::addReleases (QList<struct release_site *> sites)
{
    int k = 0;
//	struct release *rls, *itr;
//	struct release_site * site = sites ;
    mapRelease *maprls;

    *//* Loop through releases *//*
    for (k = 0; k < sites.count(); k++)
//	for( k = 0; site != nullptr && k < MAX_RELS; k++, site = site->next )
    {
        maprls = new mapRelease (this, sites[k], xform);
        mapreleases[k] = maprls;
        maprls->setZValue(4);
        addItem (maprls);
    }
    for (; k < MAX_RELS; k++)
        mapreleases[k] = nullptr;
}

void mapScene::removeTransports()
{
    for( int i = 0; i < MAX_TRNS; i++ )
    {
        if( maptransports[i] != nullptr )
        {
            this->removeItem( maptransports[i] );
            delete maptransports[i];
            maptransports[i] = nullptr;
        }
        else
            break;
    }
}

void mapScene::removeReleases()
{
    for( int k = 0; k < MAX_RELS; k++ )
    {
        if( mapreleases[k] != nullptr )
        {
            this->removeItem( mapreleases[k] );
            delete mapreleases[k];
            mapreleases[k] = nullptr;
        }
        else
            break;
    }
}
*/

void mapScene::pushTransform(mapLocalTransform *zpt)
{
    if (xform != nullptr)
        delete xform;
    xform = zpt;
}

mapLocalTransform *mapScene::popTransform()
{
    mapLocalTransform *temp = xform;
    xform = nullptr;
    return temp;
}

void mapScene::clearTransforms()
{
    if (xform != nullptr)
        delete xform;
    xform = nullptr;
}

//	mapScene::getTransform
//
//	No rocket science here.. this returns the current transform

mapLocalTransform *mapScene::getTransform()
{
    return xform;
}

//	mapScene::printMap()
//
/*
void mapScene::printMap( QPrinter *pnter )
{
    isPrintMode_ = true;
    QPainter *old_painter = currPainter;

    QPrinter printer(QPrinter::PrinterResolution);
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

//		qMapMediator* mapMed = (qMapMediator*) ((qMapWidget*)parentWidget() )->getMapMediator();
        QStack <mapCordset*> mapStack_;
//		mapStack_ =  mapMed->getCordStack() ;//= ;

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


*/

QPointF mapScene::transPoint(QPointF qp)
{
    return xform->reverse(qp);
}

void mapScene::createTransform(RiverSystem *rsys)
{
    mapCordset *mapLimits;
    QRect *sceneLimits;
    double minLat, maxLat, minLon, maxLon;
    minLat = minLon = 1000;
    maxLat = maxLon = -1000;
    mapLimits = new mapCordset(124.3, 49.0, 113.2, 43.50);
    sceneLimits = new QRect(0, 0, 700, 500);

    if (rsys->rivers->count() > 0)
    {
        for (int i = 0; i < rsys->rivers->count(); i++)
        {
            for (int j = 0; j < rsys->rivers->at(i)->segments->count(); j++)
            {
                RiverSegment *rseg = rsys->rivers->at(i)->segments->at(j);
                for (int k = 0; k < rseg->course.count(); k++)
                {
                    RiverPoint *p = rseg->course.at(k);
                    if (minLat > p->getLatitude()) minLat = p->getLatitude();
                    if (maxLat < p->getLatitude()) maxLat = p->getLatitude();
                    if (minLon > p->getLongitude()) minLon = p->getLongitude();
                    if (maxLon < p->getLongitude()) maxLon = p->getLongitude();
                }
            }
        }
        delete mapLimits;
        mapLimits = new mapCordset(maxLon, maxLat, minLon, minLat);
    }
    xform = new mapLocalTransform(*sceneLimits, mapLimits);
    delete mapLimits;
    delete sceneLimits;
}
/*
void mapScene::removeSelectRect()
{
    if( selectRect != nullptr )
        removeItem(selection);
        delete selectRect;
    selectRect = nullptr;
}

void mapScene::addSelectRect(QPointF p1, QPointF p2)
{
    QPen qp(Qt::lightGray, 1);
    selectRect = new QRectF(p1, p2);
    selection = addRect(*selectRect, qp);
}
*/
void mapScene::mouseMoved(QPointF qpf)
{
    QPointF latlon( xform->reverse(qpf) );
    emit evAnnounceLon(QString::number(latlon.x()));
    emit evAnnounceLat(QString::number(latlon.y()));
}
