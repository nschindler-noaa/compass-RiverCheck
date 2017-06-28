#include "RiverSegment.h"
#include "Log.h"
//#include "Dam.h"
#include "Species.h"
//#include "Reach.h"
//#include "Headwater.h"
#include "Stock.h"
#include "RiverFile.h"
#include "River.h"

RiverSegment::RiverSegment (QString rivName, QObject *parent) :
    QObject (parent)
{
    if (!rivName.isEmpty ())
    {
        riverName = new QString (rivName);
    }
    name = new QString ("");
    abbrev = new QString ("");
    setup ();
}

RiverSegment::RiverSegment (const RiverSegment &rhs) :
    QObject (rhs.parent ())
{
    riverName = new QString (*rhs.riverName);
    name = new QString (*rhs.name);
    abbrev = new QString (*rhs.abbrev);

    setup ();
}
void RiverSegment::setup ()
{
    clear ();
    reset ();
    width = 0.0;
    type = (SegmentType) -1;
    up = (RiverSegment *)NULL;
    down = (RiverSegment *)NULL;
    fork = (RiverSegment *)NULL;
    backgroundPen = QPen(Qt::darkGray, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    normalPen = QPen(Qt::blue, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

}
void RiverSegment::clear()
{
    flow_max = 0.0;
    flow_min = 0.0;
    lowerDepth = 0.0;
    upperDepth = 0.0;
    lowerElev = 0.0;
    upperElev = 0.0;
    upperWidth = 0.0;
    width = 0.0;
}

void RiverSegment::reset()
{
    currentPoint = -1;
    error = 0;
}

RiverSegment::~RiverSegment ()
{
    delete riverName;
//    delete name;
    delete abbrev;
    while (course.count() > 0)
        delete course.takeLast();
    setup ();
}

bool RiverSegment::parse (RiverFile *rfile)
{
    clear ();
    bool okay = true, end = false;
    QString token ("");
    QString na("");

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
            rfile->checkEnd(QString(""), *name);
            end = true;
        }
        else
        {
            parseToken (token, rfile);
        }
    }
    return okay;
}

bool RiverSegment::parseToken(QString token, RiverFile *rfile)
{
    bool okay = true;
    QString na("");

    if (token.compare("latlon", Qt::CaseInsensitive) == 0)
    {
        RiverPoint *lastPoint;
        RiverPoint *point = new RiverPoint();
        okay = rfile->readString(token);
        point->readLatLon(&token);
        if (course.isEmpty())
        {
            course.append(point);
        }
        else
        {
            lastPoint = course.at(course.count() - 1);
            if (point != lastPoint)
                course.append(point);
        }
    }
    else if (token.compare("flow_min", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readFloatOrNa(na, flow_min);
    }
    else if (token.compare("lower_elev", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readFloatOrNa(na, lowerElev);
    }
    else if (token.compare("upper_elev", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readFloatOrNa(na, upperElev);
    }
    else if (token.compare("width", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readFloatOrNa(na, width);
    }
    else if (token.compare("lower_width", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readFloatOrNa(na, lowerWidth);
    }
    else if (token.compare("upper_width", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readFloatOrNa(na, upperWidth);
    }
    else     if (token.compare("flow_max", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readFloatOrNa(na, flow_max);
    }
    else
    {
        rfile->handle_unknown_token(token);
    }

    return okay;
}

bool RiverSegment::initialize()
{
    if (flow_max == 0.0)
        flow_max = ((River *)parent())->flowMax;
    if (flow_min == 0.0)
        flow_min = ((River *)parent())->flowMin;

    return true;
}

bool RiverSegment::construct()
{
    reset ();
    currentPoint = 0;
    // calculate the length of the segment (dams length is 0.0)
    length = distance(top());
    return true;
}

short RiverSegment::findErrors ()
{
    error = 0;

    if (down != NULL)
    {
        if (*bottom() != *(down->top()))
            error |= LatLonLower;
        if (lowerElev != down->upperElev)
            error |= ElevLower;
        if (lowerDepth != down->upperDepth)
            error |= DepthLower;
    }
    if (up != NULL)
    {
        if (*top() != *(up->bottom()))
            error |= LatLonUpper;
        if (upperElev != up->lowerElev)
            error |= ElevUpper;
        if (upperDepth != up->lowerDepth)
            error |= DepthUpper;
    }
    if (fork != NULL)
    {
        if (*top() != *(up->bottom()))
            error |= LatLonUpper;
        if (upperElev != up->lowerElev)
            error |= ElevUpper;
        if (upperDepth != up->lowerDepth)
            error |= DepthUpper;
    }

    return error;
}

/** Write all segment information to an output file.
  * This is an example output routine and must be re-implemented for each child class. */
bool RiverSegment::output(int indent, RiverFile *rfile)
{
    bool okay = true;
    {
        rfile->writeString(indent, "river_segment", *name);
        if (!abbrev->isEmpty())
            rfile->writeString(indent + 1,"abbrev", *abbrev);
        rfile->writeString(indent + 1, "width", QString::number(width, 'f', 2));
        rfile->writeString(indent + 1, "flow_max", QString::number(flow_max, 'f', 2));
        rfile->writeString(indent + 1, "flow_min", QString::number(flow_min, 'f', 2));
        outputCourse (indent + 1, rfile);
        rfile->writeEnd(indent + 1, "river_segment", *name);
    }
    return okay;
}

/** Write the river segment course information. */
bool RiverSegment::outputCourse(int indent, RiverFile *rfile)
{
    bool okay = true;
    {
        if (course.count() == 0)
            okay = false;
        for (int i = 0; i < course.count(); i++)
            rfile->writeString(indent, QString("latlon"), course.at(i)->text());
    }
    return okay;
}

RiverPoint * RiverSegment::top ()
{
    currentPoint = course.count () - 1;
    return course.at (currentPoint);
}

RiverPoint * RiverSegment::bottom ()
{
    currentPoint = 0;
    return course.at (currentPoint);
}

RiverPoint * RiverSegment::nextPointUp ()
{
    currentPoint++;
    if (currentPoint >= course.count ())
        currentPoint = course.count () - 1;
    return course.at (currentPoint);
}

RiverPoint * RiverSegment::nextPointDn ()
{
    currentPoint--;
    if (currentPoint < 0)
        currentPoint = 0;
    return course.at (currentPoint);
}

float RiverSegment::distance(RiverPoint *loc)
{
    float dist = 0.0;
    bool okay = false;
    if (course.count() > 1)
    {
        for (int i = 1; i < course.count() && !okay; i++)
        {
            dist += course.at(i)->calcDistance(course.at(i - 1));
            if (course.at(i) == loc)
            {
                okay = true;
            }
        }
    }
    else
        okay = true;

    if (!okay)  // point not on this segment
    {
        dist = 0.0;
        Log::instance()->add (Log::Error, QString("Point does not lie on %1 segment").arg(*name));
    }
    return dist;
}

RiverSegment::Impounded RiverSegment::getImpound()
{
    impound = NotImpounded;
    RiverSegment *down_seg = down;
    while (down_seg != NULL &&
           down_seg->type != DamSegment)
    {
        down_seg = down_seg->down;
    }
    if (down_seg != NULL)
    {
        if (down_seg->type == DamSegment)
        {
            float top = down_seg->upperElev + down_seg->upperDepth;
            if (top >= (lowerElev + lowerDepth))
            {
                if (top >= (upperElev + upperDepth))
                    impound = FullyImpounded;
                else
                    impound = PartiallyImpounded;
            }
        }
    }
    return impound;
}

void RiverSegment::setImpound()
{
    impound = NotImpounded;
    RiverSegment *down_seg = down;
    while (down_seg != NULL &&
           down_seg->type != DamSegment)
    {
        down_seg = down_seg->down;
    }
    if (down_seg != NULL)
    {
        if (down_seg->type == DamSegment)
        {
            float top = down_seg->upperElev + down_seg->upperDepth;
            if (top >= (lowerElev + lowerDepth))
            {
                if (top >= (upperElev + upperDepth))
                    impound = FullyImpounded;
                else
                    impound = PartiallyImpounded;
            }
        }
    }
}

/*QGraphicsScene *RiverSegment::mapView()
{

}

QGraphicsScene *RiverSegment::topView()
{

}

QGraphicsScene *RiverSegment::sideView()
{

}

QGraphicsScene *RiverSegment::sectionA()
{

}

QGraphicsScene *RiverSegment::sectionB()
{

}*/
