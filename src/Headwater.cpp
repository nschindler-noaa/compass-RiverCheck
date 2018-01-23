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
    flowCoefficient = 0.0;
    flowMean = 0.0;
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
        okay = rfile->readFloatArray (elevChange);
    }
    else if (token.compare("flow_coefficient", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readFloatOrNa(na, flowCoefficient);
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

float Headwater::getFlowMean() const
{
    return flowMean;
}

void Headwater::setFlowMean(float value)
{
    flowMean = value;
}

float Headwater::getFlowCoefficient() const
{
    return flowCoefficient;
}

void Headwater::setFlowCoefficient(float value)
{
    flowCoefficient = value;
}

bool Headwater::getRegulated() const
{
    return regulated;
}

void Headwater::setRegulated(bool value)
{
    regulated = value;
}

bool Headwater::getReadFlows() const
{
    return readFlows;
}

void Headwater::setReadFlows(bool value)
{
    readFlows = value;
}

float Headwater::getElevChange (int index) const
{
    return elevChange[index];
}

void Headwater::setElevChange (int index, float value)
{
    elevChange[index] = value;
}
