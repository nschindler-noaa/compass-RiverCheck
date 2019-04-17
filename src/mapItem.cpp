#include "mapItem.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMenu>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QListWidgetItem>


mapItem::mapItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
//	map = m;
    rv_seg = nullptr;
    xform = nullptr;
    itemName = QString("");

//	pix = nullptr;
    mouseOver = false;
    itemOptions = nullptr;
}

mapItem::mapItem(RiverSegment *rseg, mapTransform *xform_, QGraphicsItem *parent)
    : QGraphicsItem(parent)
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
    shape = getShape();
    path = getPath();

    itemOptions = nullptr;
    itemOptions = createMenu();
    itemErrors = nullptr;
    setBoundingRect();
    setToolTip(itemName);
}

mapItem::~mapItem()
{
    if (itemErrors)
        delete itemErrors;
    if (itemOptions)
        delete itemOptions;
}

RiverSegment *mapItem::riverSegment()
{
    return rv_seg;
}

QString mapItem::name()
{
    return QString(itemName);
}
/*
QPixmap mapItem::icon()
{
    return QPixmap(":/images/river.png");
}*/

QPainterPath mapItem::getShape() const
{
    QPainterPath shapePath;
    QPointF qp;

    if (rv_seg != nullptr && xform != nullptr)
    {
        RiverPoint *p = rv_seg->course.at(0);
        qp = (*xform)(p->longitude, p->latitude);
        shapePath.moveTo(qp);
    }
    return shapePath;
}

QPainterPath mapItem::getPath() const
{
    QPainterPath pathPath;
    QPointF qp;

    if (rv_seg != nullptr && xform != nullptr)
    {
        for (int i = 0; i < rv_seg->course.count(); i++)
        {
            qp = (*xform)(rv_seg->course.at(i)->longitude,
                          rv_seg->course.at(i)->latitude);
            if (i == 0)
                pathPath.moveTo(qp);
            else
                pathPath.lineTo(qp);
        }
    }
    return pathPath;
}


void mapItem::setBoundingRect()
{
    QPainterPath p = getPath();
    bounds = p.boundingRect();
    maxX = bounds.x();
    minX = bounds.x() - bounds.width();
    maxY = bounds.y();
    minY = bounds.y() - bounds.height();
}

QRectF mapItem::boundingRect() const
{
    return bounds;
}

void mapItem::paint (QPainter *paintr, const QStyleOptionGraphicsItem *opt, QWidget *w)
{
    paintr->setPen(normalPen);
    paintr->drawPath(shape);

    if (rv_seg->error == 0)
        paintr->setPen(mouseOver? highlightPen : normalPen);
    else
        paintr->setPen(mouseOver? errorHighlightPen : errorPen);
    paintr->drawPath(path);
//    paintr->drawPixmap(QPointF(minX, minY), pix);
}

QMenu * mapItem::createMenu()
{
    if (itemOptions != nullptr)
    {
        delete itemOptions;
        itemOptions = nullptr;
    }
    itemOptions = new QMenu();
    itemOptions->addAction(name());
    itemOptions->addSeparator();

    actionShowErrors = itemOptions->addAction("Show Errors");
    actionShowDetail = itemOptions->addAction("Show Detail");

    return itemOptions;
}

void mapItem::displayMenu (QPoint pos)
{
    itemOptions->popup (QPoint((int)pos.x(), (int)pos.y()));
}

void mapItem::hoverEnterEvent (QGraphicsSceneHoverEvent *evnt)
{
    mouseOver = true;
    update (boundingRect());
}

void mapItem::hoverLeaveEvent (QGraphicsSceneHoverEvent *evnt)
{
    mouseOver = false;
    update (boundingRect());
}

void mapItem::highlight()
{
    mouseOver = true;
    update (boundingRect());
}

void mapItem::normal()
{
    mouseOver = false;
    update (boundingRect());
}

/*
void mapItem::contextMenu()
{
    QMenu menu;
    QAction *selectAction = menu.addAction("Select");
    menu.show();
}*/

void mapItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *evnt)
{
    QAction *selectedAction = itemOptions->exec(evnt->screenPos());

    if      (selectedAction == actionShowErrors)
        showErrors(evnt->pos());
    else if (selectedAction == actionShowDetail)
        showViews(evnt->pos());
    else
        itemOptions->close();
}

void mapItem::infoPanel()
{

}

QDialog *mapItem::createInfo()
{
    if(itemErrors != nullptr)
    {
        delete itemErrors;
        itemErrors == nullptr;
    }

    QString *message;
    QVBoxLayout *panel;
    QVBoxLayout *layout;
    QSpacerItem *hspacer;
    QHBoxLayout *buttons;
    QPushButton *ok;
    QPushButton *detail;

    itemErrors = new QDialog();
    itemErrors->setWindowTitle("River Segment Error Information");

    hspacer = new QSpacerItem (0, 10, QSizePolicy::Expanding);
    buttons = new QHBoxLayout (itemErrors);
    ok = new QPushButton ("OK", itemErrors);
    itemErrors->connect(ok, SIGNAL(clicked()), itemErrors, SLOT(close()));
    detail = new QPushButton ("See Detail", itemErrors);
    itemErrors->connect(detail, SIGNAL(clicked()), SLOT(showView()));
    buttons->addWidget((QWidget *)ok);
    buttons->addSpacerItem(new QSpacerItem(10, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    buttons->addWidget((QWidget *)detail);

    if (rv_seg->error == 0)
    {
        message = new QString ("This segment has no errors.");
    }
    else
    {
        message = new QString("This segment has at least one error.");
    }

    layout = new QVBoxLayout(itemErrors);
    layout->addWidget(new QLabel(*rv_seg->name));
    layout->addWidget(new QLabel(*message));
    //layout->addLayout(panel);
    layout->addSpacerItem(hspacer);
    layout->addLayout(buttons);

    itemErrors->setLayout(layout);

    return itemErrors;
}

void mapItem::displayInfo (QPoint pos)
{
}


void mapItem::showErrors(QPointF pt)
{
    createInfo();
    itemErrors->show();
}

void mapItem::showViews(QPointF pt)
{

}

void mapItem::deleteDam()
{

}


QVBoxLayout * mapItem::getErrorList(RiverSegment *seg)
{
    QVBoxLayout *lay = new QVBoxLayout();
    int count = 0;
    QListWidget *errList = new QListWidget();

    if (seg->error & LatLonUpper)
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
    }
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

QDialog * mapItem::createViews()
{
    QDialog *views = new QDialog((QWidget *)this);
    return views;
}
