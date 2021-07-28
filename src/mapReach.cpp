#include "mapReach.h"
//#include "qMercatorTransform.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMenu>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>

mapReach::mapReach(QGraphicsItem *par)
    : mapObject(par)
{
    mouseOver = false;
    itemErrors = nullptr;
}

mapReach::mapReach(RiverSegment *rseg, mapTransform *xform_, QGraphicsItem *par)
    : mapObject(rseg, xform_, par)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::RightButton | Qt::LeftButton);

    width = (int)(rseg->width / WIDTH_FACTOR) + 1;
    normalPen = QPen(Qt::blue, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    highlightPen = QPen(Qt::cyan, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    mouseOver = false;

    highlightPath = path();

    itemErrors = nullptr;
//    itemOptions = createMenu();
    setBoundingRect();
}

QPainterPath mapReach::shape() const
{
    QPainterPath shapePath;
    QPointF qp;

    if (rv_seg != nullptr && xform != nullptr)
    {
        RiverPoint *p = rv_seg->course.at(0);
        qp = (*xform)(p->getLongitude(), p->getLatitude());
        shapePath.moveTo(qp);
        for (int j = 1; j < rv_seg->course.count(); j++)
        {
            p = rv_seg->course.at(j);
            qp = (*xform) (p->getLongitude(), p->getLatitude());
            shapePath.lineTo(qp);
        }
    }
    return shapePath;
}

QPainterPath mapReach::path() const
{
    QPainterPath lpath;
    QPointF qp;

    if (rv_seg != nullptr && xform != nullptr)
    {
        RiverPoint *p = rv_seg->course.at(0);
        qp = (*xform) (p->getLongitude(), p->getLatitude());
        lpath.moveTo (qp);
        for (int j = 1; j < rv_seg->course.count(); j++)
        {
            p = rv_seg->course.at(j);
            qp = (*xform) (p->getLongitude(), p->getLatitude());
            lpath.lineTo(qp);
        }
    }
    return lpath;
}
/*
void mapReach::paint(QPainter *paintr, const QStyleOptionGraphicsItem *opt, QWidget *w)
{
    paintr->setPen(mouseOver? highlightPen : normalPen);

    paintr->drawPath(path);
}*/

QDialog * mapReach::createInfo()
{
    if(itemErrors != nullptr)
    {
        delete itemErrors;
        itemErrors = nullptr;
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
    detail = new QPushButton ("See Detail", itemErrors);
    itemErrors->connect(detail, SIGNAL(clicked()), SIGNAL(showViews()));
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

/*
void mapReach::infoPanel()
{
    QDialog menu;
}

QMenu * mapReach::createMenu()
{
    if (itemOptions != nullptr)
    {
        delete itemOptions;
        itemOptions = nullptr;
    }

    itemOptions = new QMenu();
    itemOptions->addAction (name());//QString(rv_seg->seg_name) );
    itemOptions->addSeparator();
    QAction *actionShowErrors = itemOptions->addAction("Show Error Detail");
    QAction *actionShowDetail = itemOptions->addAction("Show Detail Views");

//    connect (actionShowErrors, SIGNAL(triggered()), SLOT(showErrors()));
//    connect (actionShowDetail, SIGNAL(triggered()), SLOT(showViews()));

    return itemOptions;
}

void mapReach::contextMenu()
{
    QMenu menu;
    QAction *selectAction = menu.addAction("Select");
    menu.show();
}
*/
void mapReach::contextMenuEvent(QGraphicsSceneContextMenuEvent *evnt)
{
//    itemOptions->exec(evnt->screenPos());
    QMenu menu;
    menu.addAction(name());
    menu.addSeparator();
    actionShowErrors = menu.addAction("Show Error Detail");
    actionShowDetail = menu.addAction("Show Segment Views");

    QAction *selectedAction = menu.exec(evnt->screenPos());

    if      (selectedAction == actionShowErrors)
    {
        showErrors(evnt->pos());
    }
    else if (selectedAction == actionShowDetail)
    {
        showViews(evnt->pos());
    }
}
/*
void mapReach::showErrors(QPointF pt)
{
    if (itemErrors == nullptr)
        createInfo();
    itemErrors->setGeometry(pt.x(), pt.y(),
            itemErrors->geometry().width(), itemErrors->geometry().height());
    itemErrors->show();
}

void mapReach::showViews()
{
    if (itemErrors != nullptr)
        itemErrors->close();
    QDialog *itemViews = createViews();

    itemViews->setGeometry(pt.x(), pt.y(),
            itemViews->geometry().width(), itemViews->geometry().height());
    itemViews->show();

    delete itemViews;
    emit showDetail (rv_seg);
}*/
/*
QDialog *mapReach::createViews()
{
    QDialog *views = new QMessageBox ();


    return views;
}*/
