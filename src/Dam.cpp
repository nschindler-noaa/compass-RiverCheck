#include "Dam.h"
#include "Log.h"

Dam::Dam(QString dname, QString rivName, QObject *parent) :
    RiverSegment (rivName, parent)
{
    name = new QString (dname);
    type = RiverSegment::DamSegment;
    abbrev = NULL;
    initialize();

    backgroundPen = QPen(Qt::darkGray, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    normalPen = QPen(Qt::blue, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
}

Dam::~Dam ()
{
    PowerHouse *phs = NULL;
    delete name;
    if (storage != NULL)
        delete_basin (storage);
    while (getNumPowerhouses() > 0)
    {
        phs = powerhouses.takeLast();
        delete phs;
    }

}

void Dam::reset()
{
    clear();
    RiverSegment::reset();

}

void Dam::clear()
{
    if (storage)
        delete storage;
    storage = NULL;
    width = 0.0;
    length = 20.0;
    tailraceLength = DAM_TAILRACE_DEFAULT;
//    base_elev = 0.0;
    forebayElev = 0.0;
    tailraceElev = 0.0;
    fullHead = 0.0;
    fullFbDepth = 0.0;
    bypassElev = 0.0;
    collector = 0;
    ngates = 0;
    gateWidth = 0.0;
    pergate = 0.0;
    spillwayWidth = 0.0;
    stillingLength = 0.0;
    sgr = 0.0;

    spillSide = (Location)-1;

    flow_max = 0.0;
}

bool Dam::parse (RiverFile *rfile)
{
    bool okay = true, end = false;
    QString token ("");

    while (okay && !end)
    {
        token = rfile->popToken ();
        if (token.compare ("eof", Qt::CaseInsensitive) == 0)
        {
            rfile->printEOF("Dam data.");
            okay = false;
        }
        else if (token.compare("end", Qt::CaseInsensitive) == 0)
        {
            okay = rfile->checkEnd("dam", *name);
            end = true;
        }
        else
        {
            okay = parseToken (token, rfile);
        }
    }

    return okay;
}

bool Dam::parseToken (QString token, RiverFile *rfile)
{
    bool okay = true;
    QString na ("");
    float fval = 0.0;
//    int ival = 0;

    if (token.compare ("powerhouse_capacity", Qt::CaseInsensitive) == 0)
    {
        if (getNumPowerhouses() < 1)
        {
            PowerHouse *phs = new PowerHouse();
            powerhouses.append(phs);
        }
        float cap;//*cap = (float *)calloc (1, sizeof(float));
        okay = rfile->readFloatOrNa(na, cap);//*cap);
//        powerhouse_cap.append(*cap);
        powerhouses.at(0)->setCapacity(cap);
    }
    else if (token.compare("powerhouse_2_capacity", Qt::CaseInsensitive) == 0)
    {
        while (getNumPowerhouses() < 2)
        {
            PowerHouse *phs = new PowerHouse();
            powerhouses.append(phs);
        }
        float cap;//*cap = (float *)calloc (1, sizeof(float));
        okay = rfile->readFloatOrNa(na, cap);//*cap);
//        powerhouse_cap.append(*cap);
        powerhouses.at(1)->setCapacity(cap);
    }
    else if (token.compare("floor_elevation", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readFloatOrNa(na, floorElev);
        if (okay) lower_elev = floorElev;
    }
    else if (token.compare("forebay_elevation", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readFloatOrNa(na, forebayElev);
    }
    else if (token.compare("tailrace_elevation", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readFloatOrNa(na, tailraceElev);
    }
    else if (token.compare("bypass_elevation", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readFloatOrNa(na, bypassElev);
    }
    else if (token.compare("forebay_depth", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readFloatOrNa(na, upper_depth);
    }
    else if (token.compare("full_pool_head", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readFloatOrNa(na, fullHead);
    }
    else if (token.compare("collector", Qt::CaseInsensitive) == 0)
    {
        collector = 1;
    }
    else if (token.compare("spillway_width", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readFloatOrNa(na, spillwayWidth);
    }
    else if (token.compare("spill_side", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readString(na);
        if (na.compare("right", Qt::CaseInsensitive) == 0)
            spillSide = Right;
        else if (na.compare("left", Qt::CaseInsensitive) == 0)
            spillSide = Left;
        else
        {
            spillSide = FlowDivisions;
            Log::instance()->add(Log::Error, QString ("Spill side %1 incorrect").arg(na));
        }
    }
    else if (token.compare("pergate", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readFloatOrNa(na, pergate);
    }
    else if (token.compare("ngates", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readFloatOrNa(na, fval);
        ngates = int (fval + .1);
    }
    else if (token.compare("gate_width", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readFloatOrNa(na, gateWidth);
    }
    else if (token.compare("basin_length", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readFloatOrNa(na, stillingLength);
    }
    else if (token.compare("sgr", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readFloatOrNa(na, sgr);
    }
    else if (token.compare("abbrev", Qt::CaseInsensitive) == 0)
    {
        abbrev = new QString("");
        okay = rfile->readString(*abbrev);
    }
    else if (token.compare("storage_basin", Qt::CaseInsensitive) == 0)
    {
        storage = new_basin();
        rfile->readFloatOrNa(na, storage->min_volume);
        rfile->readFloatOrNa(na, storage->max_volume);
    }
    else
    {
        okay = RiverSegment::parseToken (token, rfile);
    }

    return okay;
}

bool Dam::initialize()
{
    bool okay = true;

    clear();
    spillSide = Left;

    return okay;
}

bool Dam::construct ()
{
    bool okay = true;
    error = 0;

    // base elevation
    lower_elev = floorElev;
    upper_elev = lower_elev;

    // get widths from surrounding reaches
    tailraceWidth = down->upper_width;
//    width = tailrace_width;
    if (up != NULL)
    {
        width = up->width > tailraceWidth? up->width: tailraceWidth;
    }
    else
    {
        width = down->width > tailraceWidth? down->width: tailraceWidth;
    }
    upper_width = width;
    lower_width = width;

    // get forebay depth and head from elevation, or vice versa
    if (forebayElev == 0.0)
    {
        if (fullHead == 0.0)
            fullHead = 112.0;
        forebayElev = floorElev + fullHead;
    }
    else
    {
        fullHead = forebayElev - floorElev;
    }

    if (tailraceElev == 0.0 && floorElev > 0.0)
    {
        if (fullHead == 0.0)
            fullHead = 75.0;
        tailraceElev = forebayElev - fullHead;
    }
    else
    {
        fullHead = forebayElev - tailraceElev;
    }

    fullFbDepth = forebayElev - floorElev;
    upper_depth = fullFbDepth;
    lower_depth = tailraceElev - floorElev;

    // spillway width defaults if necessary
    if (ngates == 0 || gateWidth == 0.0)
    {
        if (spillwayWidth == 0.0)
            spillwayWidth = 1320;
        if (gateWidth == 0.0)
        {
            gateWidth = spillwayWidth;
            ngates = 1;
            pergate = 1.0;
        }
        else
        {
            ngates = (int)(spillwayWidth / gateWidth);
        }
    }

    if (spillwayWidth == 0.0)
        spillwayWidth = ngates * gateWidth;

    if (tailraceLength < stillingLength)
        tailraceLength = DAM_TAILRACE_DEFAULT;

    RiverSegment::construct();

//    error = findErrors();

    // Check values
    if (floorElev < -50 ||
            forebayElev <= 0.0 ||
            tailraceElev < 0.0 ||
            bypassElev > forebayElev ||
            fullHead < 0.0 ||
            fullFbDepth <= 0.0)
    {
        Log::instance()->add
                (Log::Error, QString("bad physical specifications at $1").arg(*name));
        error |= BadPhysics;
    }
    if (ngates * gateWidth != spillwayWidth)
    {
        Log::instance()->add(Log::Error, QString ("%1 spillway width not consistent with gate width and number of gates").arg(
                                 *name));
        error |= SpillwayWidth;
    }

    return okay;
}

bool Dam::output(int indent, RiverFile *rfile)
{
    bool okay = true;

    rfile->writeString(indent, "dam", *name);
    for (int i = 0; i < powerhouses.count(); i++)
    {
        QString string("powerhouse_");
        if (i > 0)
            string.append(QString("%1_").arg (QString::number(i+1)));
        string.append("capacity");
        rfile->writeString(indent + 1, string, QString::number(powerhouses.at(i)->getCapacity(), 'f', 2));
    }
    rfile->writeString(indent + 1, "floor_elevation", QString::number(floorElev, 'f', 2));
    rfile->writeString(indent + 1, "forebay_elevation", QString::number(forebayElev, 'f', 2));
    rfile->writeString(indent + 1, "tailrace_elevation", QString::number(tailraceElev, 'f', 2));
    if (bypassElev > 0.0)
        rfile->writeString(indent + 1, "bypass_elevation", QString::number(bypassElev, 'f', 2));
    rfile->writeString(indent + 1, "spillway_width", QString::number(spillwayWidth, 'f', 2));
    rfile->writeString(indent + 1, "spill_side", QString(spillSide? "left" : "right"));
    if (ngates > 0)
    {
        rfile->writeString(indent + 1, "pergate", QString::number(pergate, 'f', 2));
        rfile->writeString(indent + 1, "ngates", QString::number(ngates));
        rfile->writeString(indent + 1, "gate_width", QString::number(gateWidth, 'f', 2));
    }
    rfile->writeString(indent + 1, "basin_length", QString::number(stillingLength, 'f', 2));
    rfile->writeString(indent + 1, "sgr", QString::number(sgr, 'f', 2));
    if (abbrev != NULL && !abbrev->isEmpty())
        rfile->writeString(indent + 1,"abbrev", *abbrev);
    if (storage != NULL)
    {
        rfile->writeString(indent + 1, "storage_basin",
                           QString::number(storage->min_volume, 'f', 2),
                           QString::number(storage->max_volume, 'f', 2));
    }
    outputCourse (indent + 1, rfile);
    rfile->writeEnd(indent, "dam", *name);

    return okay;
}

Basin *Dam::getBasin() const
{
    return storage;
}

void Dam::setBasin(Basin *value)
{
    storage = value;
}

QList<PowerHouse *> Dam::getPowerhouses() const
{
    return powerhouses;
}

void Dam::setPowerhouses(const QList<PowerHouse *> &value)
{
    powerhouses = value;
}

int Dam::getNumPowerhouses()
{
    return powerhouses.count();
}

float Dam::getTailrace_width() const
{
    return tailraceWidth;
}

void Dam::setTailrace_width(float value)
{
    tailraceWidth = value;
}

float Dam::getTailraceWidth() const
{
    return tailraceWidth;
}

void Dam::setTailraceWidth(float value)
{
    tailraceWidth = value;
}

float Dam::getTailraceLength() const
{
    return tailraceLength;
}

void Dam::setTailraceLength(float value)
{
    tailraceLength = value;
}

float Dam::getTailraceElev() const
{
    return tailraceElev;
}

void Dam::setTailraceElev(float value)
{
    tailraceElev = value;
}

float Dam::getForebayElev() const
{
    return forebayElev;
}

void Dam::setForebayElev(float value)
{
    forebayElev = value;
}

float Dam::getFullFbDepth() const
{
    return fullFbDepth;
}

void Dam::setFullFbDepth(float value)
{
    fullFbDepth = value;
}

float Dam::getFullHead() const
{
    return fullHead;
}

void Dam::setFullHead(float value)
{
    fullHead = value;
}

float Dam::getBypassElev() const
{
    return bypassElev;
}

void Dam::setBypassElev(float value)
{
    bypassElev = value;
}

float Dam::getFloorElev() const
{
    return floorElev;
}

void Dam::setFloorElev(float value)
{
    floorElev = value;
}

int Dam::getCollector() const
{
    return collector;
}

void Dam::setCollector(int value)
{
    collector = value;
}

int Dam::getNgates() const
{
    return ngates;
}

void Dam::setNgates(int value)
{
    ngates = value;
}

float Dam::getGateWidth() const
{
    return gateWidth;
}

void Dam::setGateWidth(float value)
{
    gateWidth = value;
}

float Dam::getPergate() const
{
    return pergate;
}

void Dam::setPergate(float value)
{
    pergate = value;
}

float Dam::getSpillwayWidth() const
{
    return spillwayWidth;
}

void Dam::setSpillwayWidth(float value)
{
    spillwayWidth = value;
}

float Dam::getStillingLength() const
{
    return stillingLength;
}

void Dam::setStillingLength(float value)
{
    stillingLength = value;
}

float Dam::getSgr() const
{
    return sgr;
}

void Dam::setSgr(float value)
{
    sgr = value;
}

Location Dam::getSpillSide() const
{
    return spillSide;
}

void Dam::setSpillSide(const Location &value)
{
    spillSide = value;
}

QList<RSW *> Dam::getSpillWeirs() const
{
    return spillWeirs;
}

void Dam::setSpillWeirs(const QList<RSW *> &value)
{
    spillWeirs = value;
}

int Dam::getNumSpillWeirs()
{
    return spillWeirs.count();
}

Basin *new_basin ()
{
    return (Basin *) calloc (sizeof (Basin), 1);
}

void delete_basin (Basin *bsn)
{
    free (bsn);
}

/*QGraphicsScene *Dam::mapView()
{

}

QGraphicsScene *Dam::topView()
{
    QGraphicsScene *scene = new QGraphicsScene (-50, -(width+20)/2, 100, (width+20)/2, this);
    QRectF tailrace;
    QRectF dam;
    QRectF spill;
    QRectF bsn;

    tailrace = QRectF(-tailrace_length, -width/2,
                    tailrace_length, width);
    scene->addRect(tailrace, normalPen);
    dam = QRectF(0, -width/2, 40, width);
    scene->addRect(dam, backgroundPen);

    switch (spill_side)
    {
    case Middle:
        spill = QRectF(0, -spillway_width/2, 40, spillway_width/2);
        break;
    case Right:
        spill = QRectF(0, width-spillway_width, 40, spillway_width);
        break;
    case Left:
    default:
        spill = QRectF(0, -spillway_width, 40, spillway_width);
        break;
    }
    scene->addRect(spill, normalPen);

    return scene;
}

QGraphicsScene *Dam::sideView()
{
    QGraphicsScene *scene = new QGraphicsScene (-50, -20, 100, upper_depth+20, this);
    QRectF tailrace;
    QRectF dam;

    tailrace = QRectF (-tailrace_length, (floor_elev - tailrace_elev),
                    tailrace_length, lower_depth);
    scene->addRect(tailrace, normalPen);
    dam = QRectF (0, 0, 40, upper_depth);
    scene->addRect(dam, backgroundPen);

    if (basin != NULL)
    {
        QRectF bsn (-(basin_length), -20, basin_length, 20);
        scene->addRect(bsn, normalPen);
    }
    if (bypass_elev > floor_elev)
    {
        float elev = bypass_elev - floor_elev;
        QRectF bypass(20, elev-20, 20, elev+20);
        scene->addRect(bypass, backgroundPen);
    }

    return scene;
}

QGraphicsScene *Dam::sectionA()
{
    QGraphicsScene *scene = new QGraphicsScene (-(width+20)/2, -20, (width+20)/2, upper_depth+20, this);
    QRectF dam;
    QRectF spill;

    dam = QRectF (0, 0, width, upper_depth);
    scene->addRect(dam, backgroundPen);

    switch (spill_side)
    {
    case Middle:
        spill = QRectF((width-spillway_width)/2, 0, spillway_width, upper_depth);
        break;
    case Right:
        spill = QRectF(0, 0, spillway_width, upper_depth);
        break;
    case Left:
    default:
        spill = QRectF(width-spillway_width, 0, spillway_width, upper_depth);
        break;
    }
    scene->addRect(spill, normalPen);

    if (basin != NULL)
    {
        QRectF bsn (-(basin_length), -20, basin_length, 20);
        scene->addRect(bsn, normalPen);
    }
    if (bypass_elev > floor_elev)
    {
        float elev = bypass_elev - floor_elev;
        QRectF bypass(20, elev-20, 20, elev+20);
        scene->addRect(bypass, backgroundPen);
    }

    return scene;
}

QGraphicsScene *Dam::sectionB()
{
    QGraphicsScene *secb = NULL;
    return secb;
}
*/
