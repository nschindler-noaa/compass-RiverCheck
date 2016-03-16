#include "seeview.h"

SeeView::SeeView(QObject *parent) :
    QGraphicsScene(parent)
{
    scale = 1.0;
}

void SeeView::wheelEvent(QGraphicsSceneWheelEvent *wh_evnt)
{
    scale = (float)(wh_evnt->delta()) / 10.0;
    emit scaleChanged (scale);
}
