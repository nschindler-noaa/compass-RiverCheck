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
    delete name;
    powerhouse_cap.clear();
    if (basin != NULL)
        delete_basin (basin);
}

void Dam::reset()
{
    clear();
    RiverSegment::reset();

}

void Dam::clear()
{
    basin = NULL;
    width = 0.0;
    length = 20.0;
    tailrace_length = DAM_TAILRACE_DEFAULT;
//    base_elev = 0.0;
    forebay_elev = 0.0;
    tailrace_elev = 0.0;
    full_head = 0.0;
    full_fb_depth = 0.0;
    bypass_elev = 0.0;
    collector = 0;
    ngates = 0;
    gate_width = 0.0;
    pergate = 0.0;
    spillway_width = 0.0;
    basin_length = 0.0;
    sgr = 0.0;

    spill_side = (Location)-1;

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
        float *cap = (float *)calloc (1, sizeof(float));
        okay = rfile->readFloatOrNa(na, *cap);
        powerhouse_cap.append(*cap);
    }
    else if (token.compare("powerhouse_2_capacity", Qt::CaseInsensitive) == 0)
    {
        float *cap = (float *)calloc (1, sizeof(float));
        okay = rfile->readFloatOrNa(na, *cap);
        powerhouse_cap.append(*cap);
    }
    else if (token.compare("floor_elevation", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readFloatOrNa(na, floor_elev);
        if (okay) lower_elev = floor_elev;
    }
    else if (token.compare("forebay_elevation", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readFloatOrNa(na, forebay_elev);
    }
    else if (token.compare("tailrace_elevation", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readFloatOrNa(na, tailrace_elev);
    }
    else if (token.compare("bypass_elevation", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readFloatOrNa(na, bypass_elev);
    }
    else if (token.compare("forebay_depth", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readFloatOrNa(na, upper_depth);
    }
    else if (token.compare("full_pool_head", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readFloatOrNa(na, full_head);
    }
    else if (token.compare("collector", Qt::CaseInsensitive) == 0)
    {
        collector = 1;
    }
    else if (token.compare("spillway_width", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readFloatOrNa(na, spillway_width);
    }
    else if (token.compare("spill_side", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readString(na);
        if (na.compare("right", Qt::CaseInsensitive) == 0)
            spill_side = Right;
        else if (na.compare("left", Qt::CaseInsensitive) == 0)
            spill_side = Left;
        else
        {
            spill_side = FlowDivisions;
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
        okay = rfile->readFloatOrNa(na, gate_width);
    }
    else if (token.compare("basin_length", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readFloatOrNa(na, basin_length);
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
        basin = new_basin();
        rfile->readFloatOrNa(na, basin->min_volume);
        rfile->readFloatOrNa(na, basin->max_volume);
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
    spill_side = Left;

    return okay;
}

bool Dam::construct ()
{
    bool okay = true;
    error = 0;

    // base elevation
    lower_elev = floor_elev;
    upper_elev = lower_elev;

    // get widths from surrounding reaches
    tailrace_width = down->upper_width;
//    width = tailrace_width;
    if (up != NULL)
    {
        width = up->width > tailrace_width? up->width: tailrace_width;
    }
    else
    {
        width = down->width > tailrace_width? down->width: tailrace_width;
    }
    upper_width = width;
    lower_width = width;

    // get forebay depth and head from elevation, or vice versa
    if (forebay_elev == 0.0)
    {
        if (full_head == 0.0)
            full_head = 112.0;
        forebay_elev = floor_elev + full_head;
    }
    else
    {
        full_head = forebay_elev - floor_elev;
    }

    if (tailrace_elev == 0.0 && floor_elev > 0.0)
    {
        if (full_head == 0.0)
            full_head = 75.0;
        tailrace_elev = forebay_elev - full_head;
    }
    else
    {
        full_head = forebay_elev - tailrace_elev;
    }

    full_fb_depth = forebay_elev - floor_elev;
    upper_depth = full_fb_depth;
    lower_depth = tailrace_elev - floor_elev;

    // spillway width defaults if necessary
    if (ngates == 0 || gate_width == 0.0)
    {
        if (spillway_width == 0.0)
            spillway_width = 1320;
        if (gate_width == 0.0)
        {
            gate_width = spillway_width;
            ngates = 1;
            pergate = 1.0;
        }
        else
        {
            ngates = (int)(spillway_width / gate_width);
        }
    }

    if (spillway_width == 0.0)
        spillway_width = ngates * gate_width;

    if (tailrace_length < basin_length)
        tailrace_length = DAM_TAILRACE_DEFAULT;

    RiverSegment::construct();

//    error = findErrors();

    // Check values
    if (floor_elev < -50 ||
            forebay_elev <= 0.0 ||
            tailrace_elev < 0.0 ||
            bypass_elev > forebay_elev ||
            full_head < 0.0 ||
            full_fb_depth <= 0.0)
    {
        Log::instance()->add
                (Log::Error, QString("bad physical specifications at $1").arg(*name));
        error |= BadPhysics;
    }
    if (ngates * gate_width != spillway_width)
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
    for (int i = 0; i < powerhouse_cap.count(); i++)
    {
        QString string("powerhouse_");
        if (i > 0)
            string.append(QString("%1_").arg (QString::number(i+1)));
        string.append("capacity");
        rfile->writeString(indent + 1, string, QString::number(powerhouse_cap.at(i), 'f', 2));
    }
    rfile->writeString(indent + 1, "floor_elevation", QString::number(floor_elev, 'f', 2));
    rfile->writeString(indent + 1, "forebay_elevation", QString::number(forebay_elev, 'f', 2));
    rfile->writeString(indent + 1, "tailrace_elevation", QString::number(tailrace_elev, 'f', 2));
    if (bypass_elev > 0.0)
        rfile->writeString(indent + 1, "bypass_elevation", QString::number(bypass_elev, 'f', 2));
    rfile->writeString(indent + 1, "spillway_width", QString::number(spillway_width, 'f', 2));
    rfile->writeString(indent + 1, "spill_side", QString(spill_side? "left" : "right"));
    if (ngates > 0)
    {
        rfile->writeString(indent + 1, "pergate", QString::number(pergate, 'f', 2));
        rfile->writeString(indent + 1, "ngates", QString::number(ngates));
        rfile->writeString(indent + 1, "gate_width", QString::number(gate_width, 'f', 2));
    }
    rfile->writeString(indent + 1, "basin_length", QString::number(basin_length, 'f', 2));
    rfile->writeString(indent + 1, "sgr", QString::number(sgr, 'f', 2));
    if (abbrev != NULL && !abbrev->isEmpty())
        rfile->writeString(indent + 1,"abbrev", *abbrev);
    if (basin != NULL)
    {
        rfile->writeString(indent + 1, "storage_basin",
                           QString::number(basin->min_volume, 'f', 2),
                           QString::number(basin->max_volume, 'f', 2));
    }
    outputCourse (indent + 1, rfile);
    rfile->writeEnd(indent, "dam", *name);

    return okay;
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
