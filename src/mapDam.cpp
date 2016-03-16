#include "mapDam.h"
#include "Dam.h"

//#include "qMercatorTransform.h"
#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsItem>
#include <QtGui/QMenu>
#include <QPainter>
#include <QtGui/QGraphicsSceneMouseEvent>
#include <QtGui/QGraphicsSceneHoverEvent>

mapDam::mapDam(QGraphicsItem *par)
    : mapObject(par)
{
	mouseOver = false;
    itemErrors = NULL;
    angle = 0;
}

mapDam::mapDam(RiverSegment *rseg, mapTransform *xform_, QGraphicsItem *par)
    : mapObject(rseg, xform_, par)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::RightButton | Qt::LeftButton);

    width = 3;
    backgroundPen = QPen(Qt::black, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    normalPen = QPen(Qt::blue, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    highlightPen = QPen(Qt::cyan, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    errorPen = QPen(Qt::magenta, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    errorHighlightPen = QPen(Qt::darkRed, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

	mouseOver = false;

    origin = getOriginPoint();
    highlightPath = path();
    backgroundShape = shape();

    itemErrors = NULL;
//    itemErrors = createInfo();
    //screen coordinates
    setAngle();
    setBoundingRect();
//    trans = trans.translate(origin.x(), origin.y());
//    setTransform(trans);
}

QPointF mapDam::getOriginPoint()
{
    RiverPoint *p0;
    QPointF qp0;
    p0 = rv_seg->bottom();
    qp0 = (*xform)(p0->longitude->value(), p0->latitude->value());

    return qp0;
}

QPointF mapDam::getBackingPoint()
{
    RiverPoint *p1;
    QPointF qp1;
    // first, look at upstream segment
    if (rv_seg->up != NULL &&
        rv_seg->up->type != RiverSegment::HeadwaterSegment &&
        rv_seg->up->course.count() > 1)
    {
        rv_seg->up->bottom();
        p1 = rv_seg->up->nextPointUp();
        qp1 = (*xform)(p1->longitude->value(), p1->latitude->value());
    }
    else
    {
        // have to look downstream
        if (rv_seg->down != NULL &&
            rv_seg->down->course.count() > 1)
        {
            rv_seg->down->top();
            p1 = rv_seg->down->nextPointDn();
        }
        else if (rv_seg->down->down != NULL &&
                rv_seg->down->down->course.count() > 1)
        {
            rv_seg->down->down->top();
            p1 = rv_seg->down->down->nextPointDn();
        }
        else
        {
            // cannot determine point
            p1 = NULL;
        }
        if (p1 != NULL)
        {
            qp1 = (*xform)(p1->longitude->value(), p1->latitude->value());
            qp1.setX(origin.x() + origin.x() - qp1.x());
            qp1.setY(origin.y() - origin.y() - qp1.y());
        }
        else
        {
            qp1.setX(origin.x() + 2);
            qp1.setY(origin.y());
        }
    }

    return qp1;
}

void mapDam::setAngle()
{
    RiverPoint *p0, *p1;
    double dx, dy, slope;

    p0 = rv_seg->top();
    origin = (*xform) (p0->longitude->value(), p0->latitude->value());

    if (rv_seg->up != NULL)
    {
        p1 = rv_seg->up->bottom();
        p1 = rv_seg->up->nextPointUp();
        dx = p1->longitude->value() - p0->longitude->value();
        dy = p1->latitude->value() - p0->latitude->value();
    }
    else
    {
        p1 = rv_seg->down->top();
        p1 = rv_seg->nextPointDn();
        dx = p0->longitude->value() - p1->longitude->value();
        dy = p0->latitude->value() - p1->latitude->value();
    }

    slope = -dx / dy; // perpendicular to river
    angle = atan(slope);

    dx = DAM_LENGTH * cos (angle);
    dy = DAM_LENGTH * sin (angle);

    point1.setX(origin.x() + dx);
    point1.setY(origin.y() + dy);

    point2.setX(origin.x() - dx);
    point2.setY(origin.y() - dy);
    /*
    origin = getOriginPoint();
    back = getBackingPoint();

    dx = (back.x() - origin.x());
    dy = (back.y() - origin.y());

    ang = atan (dy/dx);

    if (dy < 0.0)
    {
        if (dx < 0.0)
            angle = 180.0 + ang;
        else
            angle = 360.0 + ang;
    }
    else
    {
        if (dx < 0.0)
            angle = 90.0 - ang;
        else
            angle = ang;
    }*/
}

/*
QPixmap mapDam::icon()
{
	return QPixmap( ":/images/map_dam_lg.png"  );
}
*/
/* This is the (scaled) shape of the spillway.
   It will highlight when the mouse hovers over. */
QPainterPath mapDam::path() const
{
    QPainterPath spill;
    QPointF qp;


    int seg_w = 0;
    int spl_w = 0;
//    float half_length, half_width;
    qreal nextx, nexty;
    qreal depx, depy, widx, widy, s_widx, s_widy;
//    QRect spill_rect;

//    spill_rect = QRect(0, 0, DAM_LENGTH, 5);

    if(rv_seg != NULL && xform != NULL)
    {
        Dam *dam_seg = (Dam *)rv_seg;

//        qp = (*xform)(dam_seg->bottom()->longitude->value(), dam_seg->bottom()->latitude->value());
        spill.moveTo(origin);
        if (dam_seg->spill_side == Left)
        {
//            spill.lineTo(point1);
 /*           spill.moveTo(origin.x() +  6.0, origin.y());
            spill.lineTo(origin.x() +  8.0, origin.y());
            spill.lineTo(origin.x() +  8.0, origin.y() +  6.0);
            spill.lineTo(origin.x() +  6.0, origin.y() +  6.0);
            spill.lineTo(origin.x() +  6.0, origin.y());*/
            spill.moveTo(origin.x() +  6.0, origin.y());
            spill.lineTo(origin.x() +  8.0, origin.y());
            spill.lineTo(origin.x() +  8.0, origin.y() +  6.0);
            spill.lineTo(origin.x() +  6.0, origin.y() +  6.0);
            spill.lineTo(origin.x() +  6.0, origin.y());
        }
        else
        {
//            spill.lineTo(point2);
            spill.moveTo(origin.x() +  4.0, origin.y());
            spill.lineTo(origin.x() +  6.0, origin.y());
            spill.lineTo(origin.x() +  6.0, origin.y() +  6.0);
            spill.lineTo(origin.x() +  4.0, origin.y() +  6.0);
            spill.lineTo(origin.x() +  4.0, origin.y());
        }
        /*
        seg_w = dam_seg->width / WIDTH_FACTOR;
        spl_w = dam_seg->spillway_width / WIDTH_FACTOR;
        //mapCoordinate mp;
        depx = cos(angle) * DAM_LENGTH;
        depy = sin(angle) * DAM_LENGTH;
        widx = cos(angle + 90.0) * seg_w;
        widy = sin(angle + 90.0) * seg_w;
        s_widx = cos(angle + 90.0) * spl_w;
        s_widy = sin(angle + 90.0) * spl_w;

        nextx = origin.x();
        nexty = origin.y();
        spill.moveTo (origin);

        // the water shape (spill side)
//        spl_w = dam_seg->spillway_width / WIDTH_FACTOR + 1;
//        half_length = DAM_LENGTH / 2.0;
//        half_width = seg_w / 2.0;

        if (dam_seg->spill_side == Left)
        {
//            spill_rect = QRect (-half_length, -(half_width - spl_w), half_length, -half_width);
//            spill_rect = QRect (qp.x(), qp.y(), DAM_LENGTH, spl_w);
            nextx = nextx + (widx / 2.0);
            nexty = nexty - (widy / 2.0);
            spill.moveTo(nextx, nexty);
            nextx = nextx + depx;
            nexty = nexty + depy;
            spill.lineTo(nextx, nexty);
            nextx = nextx - s_widx;
            nexty = nexty + s_widy;
            spill.lineTo(nextx, nexty);
            nextx = nextx - depx;
            nexty = nexty - depy;
            spill.lineTo(nextx, nexty);
            nextx = nextx + s_widx;
            nexty = nexty - s_widy;
            spill.lineTo(nextx, nexty);
        }
        else
        {
//            spill_rect = QRect (-half_length, half_width, half_length, (half_width - spl_w));
//            spill_rect = QRect (qp.x(), qp.y()+seg_w-spl_w, DAM_LENGTH, spl_w);
            nextx = nextx - (widx / 2.0);
            nexty = nexty + (widy / 2.0);
            spill.moveTo(nextx, nexty);
            nextx = nextx + depx;
            nexty = nexty + depy;
            spill.lineTo(nextx, nexty);
            nextx = nextx + s_widx;
            nexty = nexty - s_widy;
            spill.lineTo(nextx, nexty);
            nextx = nextx - depx;
            nexty = nexty - depy;
            spill.lineTo(nextx, nexty);
            nextx = nextx - s_widx;
            nexty = nexty + s_widy;
            spill.lineTo(nextx, nexty);
        }*/
    }

    spill.setFillRule(Qt::WindingFill);

    return spill;
}

QPainterPath mapDam::shape() const
{
    QPainterPath path;
    QPointF qp;
//    RiverPoint *p0;
    if (rv_seg != NULL)
    {
/*        path.moveTo(point1);
        path.lineTo(point2);*/
//        qp = (*xform)(rv_seg->bottom()->longitude->value(), rv_seg->bottom()->latitude->value());
        path.moveTo(origin);
        path.lineTo(origin.x() + 12.0, origin.y());
        path.lineTo(origin.x() + 11.0, origin.y() +  6.0);
        path.lineTo(origin.x() +  1.0, origin.y() +  6.0);
        path.lineTo(origin.x(), origin.y());
    }
/*
    int seg_w = 0;
//    float half_length, half_width;
//    QRect dam_rect;

//    dam_rect = QRect(0, 0, DAM_LENGTH, 10);
    qreal nextx, nexty;
    qreal depx, depy, widx, widy;

    if(rv_seg != NULL && xform != NULL)
    {
/*        // map coordinates
        p0 = rv_seg->bottom();
        // screen coordinates
        qp = (*xform)(p0->longitude->value(), p0->latitude->value());

        path.moveTo(qp);

        // the background shape (rect)
        seg_w = rv_seg->width / WIDTH_FACTOR + 3;
        half_length = DAM_LENGTH / 2.0;
        half_width = seg_w / 2.0;
//        dam_rect = QRect (-half_length, half_width, half_length, -half_width);
        dam_rect = QRect (qp.x(), qp.y()-half_width, DAM_LENGTH, seg_w);
*/
/*        Dam *dam_seg = (Dam *)rv_seg;
        seg_w = dam_seg->width * 2.0 / WIDTH_FACTOR;

        depx = cos(angle) * DAM_LENGTH;
        depy = sin(angle) * DAM_LENGTH;
        widx = cos(angle + 90.0) * seg_w;
        widy = sin(angle + 90.0) * seg_w;

        nextx = origin.x();
        nexty = origin.y();
        path.moveTo (origin);

        nextx = nextx + (widx / 2.0);
        nexty = nexty - (widy / 2.0);
        path.moveTo(nextx, nexty);

        nextx = nextx + depx;
        nexty = nexty + depy;
        path.lineTo(nextx, nexty);

        nextx = nextx - widx;
        nexty = nexty + widy;
        path.lineTo(nextx, nexty);

        nextx = nextx - depx;
        nexty = nexty - depy;
        path.lineTo(nextx, nexty);

        nextx = nextx + widx;
        nexty = nexty - widy;
        path.lineTo(nextx, nexty);
    }
*/
    path.setFillRule(Qt::WindingFill);

	return path;
}

void mapDam::setBoundingRect()
{
    bounds = backgroundShape.boundingRect();
//    mapObject::setBoundingRect();
    bounds.setTop(bounds.top() - 1);
    bounds.setBottom(bounds.bottom() + 1);
    bounds.setLeft(bounds.left() - 1);
    bounds.setRight(bounds.right() + 1);
}

//QRectF mapDam::boundingRect() const
//{
//	return QRectF( maxLon, maxLat,
//			(maxLon - minLon), 
//			(maxLat - minLat) );
//}

void mapDam::paint(QPainter *paintr, const QStyleOptionGraphicsItem *opt, QWidget *w)
{
    QColor color;
    paintr->setPen(backgroundPen);
    paintr->drawPath(backgroundShape);
    paintr->fillPath(backgroundShape, QBrush(Qt::darkGray));

    if (rv_seg->error == 0)
    {
        if (mouseOver)
        {
            paintr->setPen (highlightPen);
            color = Qt::cyan;
        }
        else
        {
            paintr->setPen (normalPen);
            color = Qt::blue;
        }
    }
    else
    {
        if (mouseOver)
        {
            paintr->setPen(errorHighlightPen);
            color = Qt::darkRed;
        }
        else
        {
            paintr->setPen(errorPen);
            color = Qt::magenta;
        }
    }
    paintr->drawPath(highlightPath);
    paintr->fillPath(highlightPath, QBrush(color));
}
/*
QDialog * mapDam::createInfo()
{
    if(itemErrors != NULL)
    {
        delete itemErrors;
        itemErrors = NULL;
    }

    itemErrors = new QDialog();

    return itemErrors;
}

QMenu *mapDam::createMenu()
{
    if(itemOptions != NULL)
    {
        delete itemOptions;
        itemOptions = NULL;
    }

    itemOptions = new QMenu();
    itemOptions->addAction (name());
    itemOptions->addSeparator();
    actionShowErrors = itemOptions->addAction("Show Error Detail");
    actionShowDetail = itemOptions->addAction("Show Detail Views");
    actionDeleteDam =  itemOptions->addAction("Delete Dam");

//    connect (actionShowErrors, SIGNAL(triggered()), SLOT(showErrors()));
//    connect (actionShowDetail, SIGNAL(triggered()), SLOT(showViews()));
//    connect (actionDeleteDam, SIGNAL(triggered()), SLOT(deleteDam()));

    return itemOptions;
}*/

void mapDam::contextMenuEvent(QGraphicsSceneContextMenuEvent *evnt)
{
    QMenu menu;
    menu.addAction(name());
    menu.addSeparator();
    actionShowErrors = menu.addAction("Show Error Detail");
    actionShowDetail = menu.addAction("Show Segment Views");
    actionDeleteDam = menu.addAction("Delete Dam");

    QAction *selectedAction = menu.exec(evnt->screenPos());

    if      (selectedAction == actionShowErrors)
    {
        showErrors(evnt->pos());
    }
    else if (selectedAction == actionShowDetail)
    {
        showViews(evnt->pos());
    }
    else if (selectedAction == actionDeleteDam)
    {
        emit deleteDam(this);
    }
}

/*
void mapDam::infoPanel()
{
    QDialog errorDetail;
    errorDetail.show();
}
*/
