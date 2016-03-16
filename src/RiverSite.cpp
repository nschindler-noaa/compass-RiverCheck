#include "RiverSite.h"
#include "RiverPoint.h"
#include "RiverSegment.h"

#include "Log.h"

RiverSite::RiverSite(QString sitetype, QString sitename)
{
    reset();
    name = new QString (sitename);
    type = new QString (sitetype);
}

RiverSite::~RiverSite()
{
    if (name != NULL)
        delete name;
    if (type != NULL)
        delete type;
    if (location != NULL)
        delete location;
    if (segment != NULL)
        delete segment;
    reset();
}

void RiverSite::reset()
{
    name = NULL;
    type = NULL;
    location = NULL;
    segment = NULL;
    distance = 0.0;
}

bool RiverSite::parse(RiverFile *rfile)
{
    bool okay = true, end = false;
    QString token (""), val ("");

    while (okay && !end)
    {
        token = rfile->popToken ();
        if (token.compare ("latlon") == 0)
        {
            if (location != NULL)
                delete location;
            location = new RiverPoint ();
            okay = rfile->readString(token);
            location->readLatLon(&token);
        }
        else if (token.contains ("end"))
        {
            rfile->checkEnd (*type, *name);
//            token = rfile->popToken();
//            rfile->skipLine ();
            end = true;
        }
        else if (token.compare ("EOF", Qt::CaseInsensitive) == 0)
        {
            rfile->printMessage(EOF_MSG);
            end = true;
            okay = false;
        }
        else
        {
            rfile->handle_unknown_token (token);
            rfile->skipLine ();
        }
    }
    return okay;
}

void RiverSite::setName(QString sitename)
{
    if (name != NULL)
        delete name;
    name = new QString (sitename);
}

void RiverSite::setLocation(RiverPoint *loc)
{
    if (location != NULL)
        delete location;
    location = loc;
}

void RiverSite::setSegment (RiverSegment *seg)
{
    segment = seg;
}

float RiverSite::calcDistance()
{
    distance = segment->distance (location);
    return distance;
}

bool RiverSite::output(int indent, RiverFile *rfile)
{
    bool okay = true;

    rfile->writeString(indent, *type, *name);
    location->output (indent + 1, rfile);
    rfile->writeEnd(indent, "", *name);

    return okay;
}

