#ifndef RIVERSITE_H
#define RIVERSITE_H

#include <QString>
#include <QList>


#include "RiverPoint.h"
#include "RiverSegment.h"

class RiverSite
{
public:
    RiverSite(QString type, QString sitename);
    ~RiverSite();

    QString *name;
    QString *type;
    RiverPoint *location;
    RiverSegment *segment;
    float distance;

    bool parse (RiverFile *rfile);
    void setName (QString sitename);
    void setLocation (RiverPoint *loc);
    void setSegment (RiverSegment *seg);
    void setDistance (float dist);

    float calcDistance ();

    bool output (int indent, RiverFile *rfile);

private:
    void reset ();
};



#endif // RIVERSITE_H
