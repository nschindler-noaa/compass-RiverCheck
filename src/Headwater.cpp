#include "Headwater.h"
#include "RiverFile.h"

Headwater::Headwater (QString hname, QString rivName, QObject *parent) :
    RiverSegment (rivName, parent)
{
    name = new QString(hname);
    type = RiverSegment::HeadwaterSegment;

    clear ();
}

void Headwater::clear()
{
    regulated = false;  // default setting
    flow_coefficient = 0.0;
    flow_mean = 0.0;
}


bool Headwater::parse (RiverFile *rfile)
{
    bool okay = true, end = false;
    QString token ("");

    while (okay && !end)
    {
        token = rfile->popToken ();
        if (token.compare ("eof", Qt::CaseInsensitive) == 0)
        {
            rfile->printEOF("Headwater data.");
            okay = false;
        }
        else if (token.compare("end", Qt::CaseInsensitive) == 0)
        {
            okay = rfile->checkEnd("headwater", *name);
            end = true;
        }
        else
        {
            okay = parseToken(token, rfile);
        }
    }

    return okay;
}

bool Headwater::parseToken (QString token, RiverFile *rfile)
{
    bool okay = true;
    QString na("");

    if (token.compare ("elevation_change", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readFloatArray (elev_change);
    }
    else if (token.compare("flow_coefficient", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readFloatOrNa(na, flow_coefficient);
    }
    else
    {
        okay = RiverSegment::parseToken(token, rfile);
    }

    return okay;
}

bool Headwater::initialize()
{
    bool okay = true;

    return okay;
}

bool Headwater::output(int indent, RiverFile *rfile)
{
    bool okay = true;


    return okay;
}

void Headwater::mapView()
{

}

void Headwater::topView()
{

}

void Headwater::sideView()
{

}

void Headwater::sectionA()
{

}

void Headwater::sectionB()
{

}
