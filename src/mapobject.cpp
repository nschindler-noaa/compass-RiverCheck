#include <QPushButton>
#include <QGraphicsSceneContextMenuEvent>
#include <QLabel>
#include <QListWidget>

#include "mapobject.h"

mapObject::mapObject(QGraphicsItem *parent) :
    QGraphicsObject(parent)
{
        rv_seg = nullptr;
        xform = nullptr;
        setAcceptHoverEvents (true);
        setAcceptedMouseButtons (Qt::LeftButton);
        itemName = QString("");

        width = 0.0;
        normalPen = QPen(Qt::blue, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        highlightPen = QPen(Qt::cyan, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        errorPen = QPen(Qt::magenta, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        errorHighlightPen = QPen(Qt::darkRed, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

        mouseOver = false;
        itemOptions = nullptr;
}

mapObject::mapObject(RiverSegment *rseg, mapTransform *xform_, QGraphicsItem *parent)
    : QGraphicsObject(parent)
{
    rv_seg = rseg;
    xform = xform_;
    setAcceptHoverEvents (true);
    setAcceptedMouseButtons (Qt::LeftButton);
    itemName = *(rseg->name);

    width = (int) (rseg->width / 1500) + 1;
    normalPen = QPen(Qt::blue, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    highlightPen = QPen(Qt::cyan, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    errorPen = QPen(Qt::magenta, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    errorHighlightPen = QPen(Qt::darkRed, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    mouseOver = false;

//	pix = icon();
    backgroundShape = shape();
    highlightPath = path();

    itemOptions = nullptr;
//    itemOptions = createMenu();
    itemErrors = nullptr;
    setBoundingRect();
    setToolTip(itemName);
}

mapObject::~mapObject()
{
    if (itemErrors)
        delete itemErrors;
    if (itemOptions)
        delete itemOptions;
}

RiverSegment *mapObject::riverSegment()
{
    return rv_seg;
}

QString mapObject::name()
{
    return QString(itemName);
}
/*
QPixmap mapItem::icon()
{
    return QPixmap(":/images/river.png");
}*/

QPainterPath mapObject::shape() const
{
    QPainterPath shapePath;
    QPointF qp;

    if (rv_seg != nullptr && xform != nullptr)
    {
        RiverPoint *p = rv_seg->course.at(0);
        qp = (*xform)(p->getLongitude(), p->getLatitude());
        shapePath.moveTo(qp);
    }
    return shapePath;
}

QPainterPath mapObject::path() const
{
    QPainterPath pathPath;
    QPointF qp;

    if (rv_seg != nullptr && xform != nullptr)
    {
        for (int i = 0; i < rv_seg->course.count(); i++)
        {
            qp = (*xform)(rv_seg->course.at(i)->getLongitude(),
                          rv_seg->course.at(i)->getLatitude());
            if (i == 0)
                pathPath.moveTo(qp);
            else
                pathPath.lineTo(qp);
        }
    }
    return pathPath;
}


void mapObject::setBoundingRect()
{
    QPainterPath p = path();
    bounds = p.boundingRect();
    minX = bounds.x();
    maxX = bounds.x() + bounds.width();
    maxY = bounds.y();
    minY = bounds.y() - bounds.height();
}

QRectF mapObject::boundingRect() const
{
    return bounds;
}

void mapObject::paint (QPainter *paintr, const QStyleOptionGraphicsItem *opt, QWidget *w)
{
    paintr->setPen(normalPen);
    paintr->drawPath(backgroundShape);

    if (rv_seg->errors.count() == 0)
        paintr->setPen(mouseOver? highlightPen : normalPen);
    else
        paintr->setPen(mouseOver? errorHighlightPen : errorPen);
    paintr->drawPath(highlightPath);
//    paintr->drawPixmap(QPointF(minX, minY), pix);
}
/*
QMenu * mapObject::createMenu()
{
    if (itemOptions != nullptr)
    {
        delete itemOptions;
        itemOptions = nullptr;
    }
    itemOptions = new QMenu();
    itemOptions->addAction(name());
    itemOptions->addSeparator();

    actionShowErrors = itemOptions->addAction("Show Error Detail");
    actionShowDetail = itemOptions->addAction("Show Segment Views");

    return itemOptions;
}

void mapObject::displayMenu (QPoint pos)
{
    itemOptions->popup (QPoint((int)pos.x(), (int)pos.y()));
}*/

void mapObject::hoverEnterEvent (QGraphicsSceneHoverEvent *evnt)
{
    mouseOver = true;
    update (boundingRect());
}

void mapObject::hoverLeaveEvent (QGraphicsSceneHoverEvent *evnt)
{
    mouseOver = false;
    update (boundingRect());
}

void mapObject::highlight()
{
    mouseOver = true;
    update (boundingRect());
}

void mapObject::normal()
{
    mouseOver = false;
    update (boundingRect());
}

/*
void mapObject::contextMenu()
{
    QMenu menu;
    QAction *selectAction = menu.addAction("Select");
    menu.show();
}*/

void mapObject::contextMenuEvent(QGraphicsSceneContextMenuEvent *evnt)
{
    QMenu menu;
    menu.addAction(name());
    menu.addSeparator();
    actionShowErrors = menu.addAction("Show Error Detail");
    actionShowDetail = menu.addAction("Show Segment Views");

    QAction *selectedAction = menu.exec(evnt->screenPos());

    if      (selectedAction == actionShowErrors)
    {
        showErrors(evnt->screenPos());
    }
    else if (selectedAction == actionShowDetail)
    {
        showViews(evnt->pos());
    }
}

/*void mapObject::infoPanel()
{

}*/

QDialog *mapObject::createInfo()
{
    if(itemErrors != nullptr)
    {
        delete itemErrors;
        itemErrors == nullptr;
    }

//    QString *message;
    QVBoxLayout *panel;
    QVBoxLayout *lyout;
    QSpacerItem *hspacer;
    QHBoxLayout *buttons;
    QPushButton *ok;
    QPushButton *detail;

    itemErrors = new QDialog();
    itemErrors->setWindowTitle("River Segment Error Information");
    itemErrors->setGeometry(0, 0, 300, 100);

    panel = new QVBoxLayout ();
    panel->addLayout (getErrorList (rv_seg));

    hspacer = new QSpacerItem (0, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

    buttons = new QHBoxLayout ();
    ok = new QPushButton ("OK", itemErrors);
    itemErrors->connect(ok, SIGNAL(clicked()), itemErrors, SLOT(close()));
    detail = new QPushButton ("See Segment Detail", itemErrors);
    itemErrors->connect(detail, SIGNAL(clicked()), this, SLOT(showViews()));
    buttons->addWidget((QWidget *)ok);
    buttons->addSpacerItem(new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    buttons->addWidget((QWidget *)detail);

    lyout = new QVBoxLayout(itemErrors);
    lyout->insertLayout (0, panel);
    lyout->insertSpacerItem (1, hspacer);
    lyout->insertLayout (2, buttons);

/*    itemErrors->layout()->addWidget(new QLabel(*rv_seg->name));
    itemErrors->layout()->addWidget(new QLabel(*message));
    itemErrors->layout()->addLayout(panel);
    itemErrors->layout()->addSpacerItem(hspacer);
    itemErrors->layout()->addLayout(buttons);*/

    itemErrors->setLayout(lyout);
    return itemErrors;
}

void mapObject::displayInfo (QPoint pos)
{
}


void mapObject::showErrors(QPoint pt)
{
    itemErrors = createInfo();
    itemErrors->setGeometry(pt.x(), pt.y(),
                            itemErrors->geometry().width(),
                            itemErrors->geometry().height());
    itemErrors->exec();
}

void mapObject::showViews(QPointF pt)
{
    emit showDetail (rv_seg);
}

void mapObject::showViews()
{
    itemErrors->close();
    emit showDetail (rv_seg);
}

QVBoxLayout * mapObject::getErrorList(RiverSegment *seg)
{
    QVBoxLayout *lay = new QVBoxLayout();
    QListWidget *errList = new QListWidget();
    seg->findErrors();
    QStringList elist = seg->getErrorList();
    int count = elist.count();

    for (int i = 0; i < count; i++)
        errList->addItem(elist.at(i));
/*    if (seg->error & LatLonUpper)
    {
        errList->addItem(new QListWidgetItem("Upper longitude/latitude mismatch."));
        count ++;
    }
    if (seg->error & LatLonLower)
    {
        errList->addItem(new QListWidgetItem("Lower longitude/latitude mismatch."));
        count ++;
    }
    if (seg->error & ElevUpper)
    {
        errList->addItem(new QListWidgetItem("Upper elevation mismatch."));
        count ++;
    }
    if (seg->error & ElevLower)
    {
        errList->addItem(new QListWidgetItem("Lower elevation mismatch."));
        count ++;
    }
    if (seg->error & DepthUpper)
    {
        errList->addItem(new QListWidgetItem("Upper depth mismatch."));
        count ++;
    }
    if (seg->error & DepthLower)
    {
        errList->addItem(new QListWidgetItem("Lower depth mismatch."));
        count ++;
    }
    if (seg->error & SlopeIncorrect)
    {
        errList->addItem(new QListWidgetItem("Incorrect slope."));
        count ++;
    }
    if (seg->error & SpillwayWidth)
    {
        errList->addItem(new QListWidgetItem("Spillway width and number and size of spillways do not match."));
        count ++;
    }*/
    if (count == 0)
    {
        lay->addWidget((QWidget *)new QLabel (QString("%1 has no errors.").arg(*seg->name)));
    }
    else if (count == 1)
    {
        lay->addWidget((QWidget *)new QLabel (QString("%1 has one error.").arg(*seg->name)));
        lay->addWidget((QWidget *) errList);
        lay->setGeometry(QRect (0, 0, 500, 40));
    }
    else
    {
        lay->addWidget((QWidget *)new QLabel (QString("%1 has %2 errors").arg(*seg->name, QString::number(count))));
        lay->addWidget((QWidget *) errList);
        lay->setGeometry(QRect (0, 0, 500, 40 * count));
    }

    return lay;
}

QDialog * mapObject::createViews()
{
    QDialog *views = new QDialog((QWidget *)this);
    return views;
}
