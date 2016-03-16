#include "RiverPoint.h"
#include "Log.h"
#include "definitions.h"
#include <cmath>

#include <QString>
#include <QStringList>

dms::dms ()
{
    setup ();

    setText();
}

dms::dms (QString str)
{
    setup();
    QStringList list (str.split (' ', QString::SkipEmptyParts));
    int d, m, s;
    if (list.count() == 4)
    {
        setValue (list.at(0), list.at(1), list.at(2), list.at(3));
    }
    else
    {
        d = 0; m = 0; s = 0; sign = 1; degrees = 0.0;
        setText();
    }
}

dms::dms (QString d, QString m, QString s, QString dir)
{
    setup();
    setValue (d, m, s, dir);
}

dms::dms (int d, int m, int s, QString dir)
{
    setup();
    setValue (d, m, s, dir);
}

dms::dms (float val)
{
    setup();
    setValue (val);
}

dms::dms (const dms &rhs)
{
    deg = rhs.deg;
    min = rhs.min;
    sec = rhs.sec;
    degrees = rhs.degrees;
    direction = new QString (*rhs.direction);
    sign = rhs.sign;

    setText();
}

dms::~dms ()
{
//    delete direction;
}

void dms::setup()
{
    deg = 0;
    min = 0;
    sec = 0;
    degrees = 0.0;
    direction = new QString ("");
    sign = 1;
}

float dms::setValue(float val)
{
    float m, s;
    if (val < 0)
    {
        sign = -1;
        val = val * sign;
    }
    degrees = val;
    deg = (int) val;
    m = (val - deg) * 60.0;
    min = (int) m;
    s = (m = min) * 60.0;
    sec = (int) s;

    setText();

    return degrees;
}

float dms::setValue(int degs, int mins, int secs, QString dir)
{
    deg = degs;
    min = mins;
    sec = secs;
    direction->clear();
    direction->append(dir);

    if     (dir.contains("W", Qt::CaseInsensitive) ||
            dir.contains("S", Qt::CaseInsensitive))
        sign = -1;

    degrees = (float)degs + (float)min / 60.0 + (float)sec / 3600.0;

    setText();

    return degrees;
}

float dms::setValue(QString degs, QString mins, QString secs, QString dir)
{
    int d, m, s;
    bool okay = true;
    d = degs.toInt (&okay);
    if (okay)
        m = mins.toInt (&okay);
    if (okay)
        s = secs.toInt (&okay);
    if (okay)
        setValue (d, m, s, dir);

    return degrees;
}

float dms::value()
{
    return (sign * degrees);
}

void dms::setText ()
{
    line.clear();
    line.append(QString ("%1 %2 %3 %4").arg
                (QString::number(deg),
                 QString::number(min),
                 QString::number(sec),
                 *direction));
}

QString dms::text()
{
    return line;
}

bool dms::equals(const dms rhs)
{
    bool equal;

    equal = (deg == rhs.deg &&
             min == rhs.min &&
             sec == rhs.sec &&
             sign == rhs.sign &&
             direction->compare(*rhs.direction) == 0);

    return equal;
}

RiverPoint::RiverPoint()
{
    initialize ();
}
RiverPoint::RiverPoint(const RiverPoint &other)
{
    longitude = new dms (*other.longitude);
    latitude = new dms (*other.latitude);
    width = other.width;
}
RiverPoint::~RiverPoint ()
{
    clear ();
}
void RiverPoint::initialize ()
{
    longitude = new dms ();
    latitude = new dms ();
    width = 0.0;
}
void RiverPoint::clear ()
{
    if (longitude != NULL)
        delete longitude;
    if (latitude != NULL)
        delete latitude;
}

bool RiverPoint::readLatLon (QString *line)
{
    bool okay = true;
    QStringList list(line->split(' ', QString::SkipEmptyParts));

    if (list.count() == 8)
    {
        latitude->setValue(list.at(0), list.at(1), list.at(2), list.at(3));
        longitude->setValue(list.at(4), list.at(5), list.at(6), list.at(7));
/*        setLat(list.at(0), list.at(1), list.at(2));
        setLatDir(list.at(3));
        setLon(list.at(4), list.at(5), list.at(6));
        setLonDir(list.at(7));*/
    }
    else
    {
        Log::instance()->add(Log::Error, "Wrong number of items for latlon point.");
        okay = false;
    }
    return okay;
}

float RiverPoint::setLongitude (const float x)
{
    return longitude->setValue(x);
/*    lon = x;
    return lon;*/
}

float RiverPoint::setLongitude (int d, int m, int s, QString dir)
{
    return longitude->setValue(d, m, s, dir);
/*    lon = (double)d + (((double)m + ((double)s / 60.0)) / 60.0);
    return lon;*/
}

float RiverPoint::setLongitude (QString deg, QString min, QString sec, QString dir)
{
    return longitude->setValue(deg, min, sec, dir);
/*    int d = deg.toInt ();
    int m = min.toInt ();
    int s = sec.toInt ();
    return setLon (d, m, s);*/
}

void RiverPoint::setLonDir (QString ew)
{
    if (ew.contains ("W", Qt::CaseInsensitive))
        longitude->sign = -1;
    else
        longitude->sign =  1;
}


float RiverPoint::setLatitude (const float x)
{
    return longitude->setValue(x);
/*    lat = x;
    return lat;*/
}

float RiverPoint::setLatitude (int d, int m, int s, QString dir)
{
    return longitude->setValue(d, m, s, dir);
/*    lat = (double)d + (((double)m + ((double)s / 60.0)) / 60.0);
    return lat;*/
}

float RiverPoint::setLatitude (QString deg, QString min, QString sec, QString dir)
{
    return longitude->setValue(deg, min, sec, dir);
/*    int d = deg.toInt ();
    int m = min.toInt ();
    int s = sec.toInt ();
    return setLat (d, m, s);*/
}

void RiverPoint::setLatDir (QString ns)
{
    if (ns.compare ("S", Qt::CaseInsensitive) == 0)
        latitude->sign = -1;
    else
        latitude->sign =  1;
}

float RiverPoint::setWidth (const float wd)
{
    width = wd;
    return width;
}

bool RiverPoint::equals (const RiverPoint rhs)
{
    return (latitude->equals (*(rhs.latitude)) &&
            longitude->equals (*(rhs.longitude)) &&
            width == rhs.width);
/*    float prec = .0000001;
    bool equal = true;
    if (lon < rhs.lon - prec || lon > rhs.lon + prec)
        equal = false;
    if (lat < rhs.lat - prec || lat > rhs.lat + prec)
        equal = false;
    if (width < rhs.width - prec || width > rhs.width + prec)
        equal = false;

    return equal;*/
}

bool RiverPoint::operator == (const RiverPoint rhs)
{
    return equals (rhs);
}
bool RiverPoint::operator != (const RiverPoint rhs)
{
    return !(equals (rhs));
}
/** \brief Compute distance between two geographic points.
 * If GREAT_CIRCLE is defined, it will calculate the distance
 * with great circles. If not, it will calculate the distance
 * using a lattitude adjusted cartesian distance (the cos(y0(pi/180)) factor).
 * The result is multiplied by 69.0468 to get statute miles.
 * \param y0 lattitude of first point
 * \param x0 longitude of first point
 * \param y1 lattitude of second point
 * \param x1 longitude of second point
 * \return distance
 */
double gc_dist (double y0, double x0, double y1, double x1)
{
    double result = 0.0;
#ifdef GREAT_CIRCLE
    x0 *= M_PI_180;
    y0 *= M_PI_180;
    x1 *= M_PI_180;
    y1 *= M_PI_180;

    result = (acos(sin(y0) * sin(y1) + cos(y0) * cos(y1) * cos(x1 - x0)) * M_180_PI * 69.0468);
#else
    double dx = (x0 - x1) * cos (y0 * (M_PI_180));
    double dy = (y0 - y1);

    result = (sqrt (dx*dx + dy*dy) * 69.0468);	/* statute miles */
#endif
    return result;
}

double RiverPoint::calcDistance(RiverPoint *pt)
{
    double result = 0.0;
    if (latitude->value() != pt->latitude->value()
            || longitude->value() != pt->longitude->value())
    {
        result = gc_dist (latitude->value(), longitude->value(),
                      pt->latitude->value(), pt->longitude->value());
    }

/*    double londiff, dy, dx, result = 0.0;

    dy = fabs (latitude->value()) - fabs (pt->latitude->value());
    londiff = fabs (longitude->value()) - fabs(pt->longitude->value());

    dx = londiff * cos (latitude->value() * (M_PI_180));

    result = sqrt ((dx * dx) + (dy * dy));
    result *= 69.0468;    /* statute miles */

    return result;
}

QString RiverPoint::text ()
{
    QString *txt = new QString ("");
    txt->append(QString("%1 %2").arg (latitude->text(), longitude->text()));

/*    int d, m, s;
    double min, sec;
    d = (int) (lon);
    min = (lon - d) * 60.0;
    m = (int) (min);
    sec = (min - m) * 60.0;
    s = (int) (sec);
    txt->append (QString ("%1 %2 %3 ").arg
                 (QString::number (d), QString::number (m), QString::number (s)));
    if (lon > 0.0)
        txt->append ("E ");
    else
        txt->append ("W ");

    d = (int) (lat);
    min = (lon - d) * 60.0;
    m = (int) (min);
    sec = (min - m) * 60.0;
    s = (int) (sec);
    txt->append (QString ("%1 %2 %3 ").arg
                 (QString::number (d), QString::number (m), QString::number (s)));
    if (lat > 0.0)
        txt->append ("N");
    else
        txt->append ("S");
*/
    return *txt;
}

bool RiverPoint::output(int indent, RiverFile *rfile)
{
    bool okay = true;

    rfile->writeString(indent, "latlon", text());

    return okay;
}

/*
RiverPoint *newPoint ()
{
    RiverPoint *p = new RiverPoint;// *) malloc (sizeof (RiverPoint));
    p->lat = 0.0;
    p->lon = 0.0;
    p->width = 0.0;
    return p;
}

void deletePoint (RiverPoint *&rpt)
{
    rpt->lat = 0.0;
    rpt->lon = 0.0;
    rpt->width = 0.0;
    delete (rpt);
    rpt = NULL;
}*/

