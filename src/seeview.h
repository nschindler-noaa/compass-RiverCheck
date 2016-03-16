#ifndef SEEVIEW_H
#define SEEVIEW_H

#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsSceneWheelEvent>


class SeeView : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit SeeView(QObject *parent = 0);
    
signals:
    void scaleChanged (float);

public slots:

protected:
    float scale;
    void wheelEvent (QGraphicsSceneWheelEvent *wh_evnt);
    
};

#endif // SEEVIEW_H
