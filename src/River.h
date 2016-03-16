#ifndef RIVER_H
#define RIVER_H

#include <QObject>
#include <QStringList>
#include <QList>

#include "definitions.h"
#include "Dam.h"
#include "Headwater.h"
#include "Reach.h"

#define DEFAULT_SLOPE    40.0

class Reach;

class River : public QObject
{
    Q_OBJECT

public:
    River (QObject *parent = 0);
    River (QString name, QObject *parent = 0);
    ~River ();

    QString * name;           /**< name of the river */
    float flowMax;            /**< maximum water flow for this river in KCFS */
    float flowMin;            /**< minimum water flow for this river in KCFS */
    float slope;              /**< a default slope in the case one is not given for a reach. */
    QList <RiverSegment *> *segments; /**< list of segments in this river. */
    QList <Dam *> dams;
    QList <Reach *> reaches;

    RiverSegment *firstSegment () {return segments->at(0);}
    bool parse (RiverFile *rfile);
    bool initialize ();
    bool construct ();
    void markRegulationPts();
    RiverSegment *findSegment (QString name);
    RiverSegment *findSegment (RiverPoint *pt);
    bool output (int indent, RiverFile *rfile);

//public slots:
    bool deleteSegment (RiverSegment *seg);

signals:
    void addedDam (Dam *);
    void addedReach (Reach *);
    void addedHeadwater (Headwater *);

};


#endif // RIVER_H
