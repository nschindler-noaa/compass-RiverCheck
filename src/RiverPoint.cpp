#include "RiverPoint.h"
#include "Log.h"
#include "definitions.h"
#include <cmath>

#include <QString>
#include <QStringList>


float dms2float (QString d, QString m, QString s, QString dir)
{
    float val = 0.0;
    float deg = d.toFloat();
    float min = m.toFloat();
    float sec = s.toFloat();
    int sign = 1;
    if (dir.contains("S") || dir.contains("W"))
        sign = -1;

    val = deg + min/60 + sec/3600;
    val *= sign;

    return val;
}

QStringList &float2dms (float val)
{
    QStringList *ql = new QStringList ();
    int d = 0, m = 0, s = 0, sign = 1;
    float min = 0, sec = 0;
    QString dir ("EN");

    if (val < 0)
    {
        dir = QString ("WS");
        sign = -1;
        val *= sign;
    }
    d = static_cast<int>(val);
    min = (val - d) * 60;
    m = static_cast<int>(min);
    sec = (min - m) * 60;
    s = static_cast<int>(sec);

    ql->append(QString::number(d));
    ql->append(QString::number(m));
    ql->append(QString::number(s));
    ql->append(dir);

    return *ql;
}

/*dms::dms ()
{
    setup ();
    setText();
}

dms::dms (QString str)
{
    setup();
    QStringList list (str.split (' ', QString::SkipEmptyParts));
    switch (list.count())
    {
    case 4:
        setValue(list.at(0), list.at(1), list.at(2), list.at(3));
        break;
    case 2:
    case 1:
        setValue (list.at(0).toFloat());

    }
    if (list.count() == 4)
    {
        setValue (
    }
    else if (list.count() == 1)
    {
        setValue (list.at(0).toFloat());
    }
    setText();
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

float dms::setValue(QString val, QString dir)
{
    float degval = val.toFloat();
    setValue(degval);
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
}*/

RiverPoint::RiverPoint()
{
    initialize ();
}
RiverPoint::RiverPoint(const RiverPoint &other)
{
    longitude = other.longitude;
    latitude = other.latitude;
    width = other.width;
}
RiverPoint::~RiverPoint ()
{
    clear ();
}
void RiverPoint::initialize ()
{
    longitude = 0.0;
    latitude = 0.0;
    width = 0.0;
}
void RiverPoint::clear ()
{
    initialize();
}

bool RiverPoint::readLatLon (QString *line)
{
    bool okay = true;
    QStringList list(line->split(' ', QString::SkipEmptyParts));

    if (list.count() == 8)
    {
        latitude = dms2float(list.at(0), list.at(1), list.at(2), list.at(3));
        longitude = dms2float(list.at(4), list.at(5), list.at(6), list.at(7));
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
    return longitude = x;
/*    lon = x;
    return lon;*/
}

float RiverPoint::setLongitude (int d, int m, int s, QString dir)
{
    longitude = d + m/60.0 + s/3600.0;
    setLonDir(dir);
    return longitude;
}

float RiverPoint::setLongitude (QString deg, QString min, QString sec, QString dir)
{
    int d = deg.toInt ();
    int m = min.toInt ();
    int s = sec.toInt ();
    return setLongitude (d, m, s, dir);
}

void RiverPoint::setLonDir (QString ew)
{
    if (ew.contains ("W", Qt::CaseInsensitive))
        longitude = longitude < 0.0? -longitude: longitude;
    else
        longitude = longitude > 0.0? -longitude: longitude;
}


float RiverPoint::setLatitude (const float x)
{
    return latitude = x;
}

float RiverPoint::setLatitude (int d, int m, int s, QString dir)
{
    latitude = d + m/60.0 + s/3600.0;
    setLatDir(dir);
    return latitude;
}

float RiverPoint::setLatitude (QString deg, QString min, QString sec, QString dir)
{
    int d = deg.toInt ();
    int m = min.toInt ();
    int s = sec.toInt ();
    return setLatitude (d, m, s, dir);
}

void RiverPoint::setLatDir (QString ns)
{
    if (ns.compare ("N", Qt::CaseInsensitive) == 0)
        latitude = latitude < 0.0? -latitude: latitude;
    else
        latitude = latitude > 0.0? -latitude: latitude;
}

float RiverPoint::setWidth (const float wd)
{
    width = wd;
    return width;
}

bool RiverPoint::equals (const RiverPoint rhs)
{
    float prec = .0001;
    bool equal = true;
    if (longitude < rhs.longitude - PREC || longitude > rhs.longitude + PREC)
        equal = false;
    if (latitude < rhs.latitude - PREC || latitude > rhs.latitude + PREC)
        equal = false;
    if (width < rhs.width - PREC || width > rhs.width + PREC)
        equal = false;

    return equal;
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
 * using a latitude adjusted cartesian distance (the cos(y0(pi/180)) factor).
 * The result is multiplied by 69.0468 to get statute miles.
 * \param y0 latitude of first point
 * \param x0 longitude of first point
 * \param y1 latitude of second point
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
    result = gc_dist (latitude, longitude,
                  pt->latitude, pt->longitude);

/*    double londiff, dy, dx, result = 0.0;

    dy = fabs (latitude->value()) - fabs (pt->latitude->value());
    londiff = fabs (longitude->value()) - fabs(pt->longitude->value());

    dx = londiff * cos (latitude->value() * (M_PI_180));

    result = sqrt ((dx * dx) + (dy * dy));
    result *= 69.0468;    // statute miles */

    return result;
}

QString RiverPoint::text ()
{
    QString *txt = new QString ("");
    QStringList lat = float2dms(latitude);
    QStringList lon = float2dms(longitude);
    QString latdir = latitude < 0? QString("S") : QString("N");
    QString londir = longitude < 0? QString ("W") : QString ("E");
    txt->append(QString("%1 %2 %3 %4 %5 %6 %7 %8").arg (
                    lat.at(0), lat.at(1), lat.at(2), latdir,
                    lon.at(0), lon.at(1), lon.at(2), londir));
    return *txt;
}
void RiverPoint::setText(const QString txt)
{
    QStringList items;
    items = txt.split(' ', QString::SkipEmptyParts);
    if (items.count() == 8)
    {
        setLongitude (items.at(0), items.at(1), items.at(2), items.at(3));
        setLatitude (items.at(4), items.at(5), items.at(6), items.at(7));
    }
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

bool RiverPoint::output(int indent, RiverFile *rfile)
{
    bool okay = true;

    rfile->writeString(indent, "latlon", text());

    return okay;
}

bool parseLatLon (RiverFile *cfile, RiverPoint *pt)
{
    bool okay = true, end = false;

    QString latd, latm, lats, latdir;
    QString lond, lonm, lons, londir;

    latd = cfile->popToken ();
    latm = cfile->popToken ();
    lats = cfile->popToken ();
    latdir = cfile->popToken ();
    if (latd.compare ("EOF", Qt::CaseInsensitive) == 0 ||
            latm.compare ("EOF", Qt::CaseInsensitive) == 0 ||
            lats.compare ("EOF", Qt::CaseInsensitive) == 0 ||
            latdir.compare ("EOF", Qt::CaseInsensitive) == 0)
    {
        okay = false;
        cfile->printError ("Found EOF looking for lattitude data.");
    }
    else
    {
        pt->setLatitude(latd, latm, lats);
        pt->setLatDir (latdir);

        lond = cfile->popToken ();
        lonm = cfile->popToken ();
        lons = cfile->popToken ();
        londir = cfile->popToken ();
        if (lond.compare ("EOF", Qt::CaseInsensitive) == 0 ||
                lonm.compare ("EOF", Qt::CaseInsensitive) == 0 ||
                lons.compare ("EOF", Qt::CaseInsensitive) == 0 ||
                londir.compare ("EOF", Qt::CaseInsensitive) == 0)
        {
            okay = false;
            cfile->printError ("Found EOF looking for longitude data.");
        }
        else
        {
            end = true;
            pt->setLongitude(lond, lonm, lons);
            pt->setLonDir (londir);
        }
    }
    return okay;
}

