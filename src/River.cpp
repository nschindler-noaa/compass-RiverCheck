#include "River.h"
#include "RiverFile.h"
#include "RiverPoint.h"
#include "RiverSegment.h"
#include "RiverSite.h"
//#include "RiverSystem.h"
#include "Log.h"
#include "logdialog.h"

River::River (QObject *parent) :
    QObject (parent)
{
    name = new QString ("");
    segments = new QList <RiverSegment *>();
    flowMax = 0.0;
    flowMin = 0.0;
    slope = 0.0;
}

River::River (QString rname, QObject *parent) :
    QObject (parent)
{
    name = new QString (rname);
    segments = new QList <RiverSegment *>();
    flowMax = 0.0;
    flowMin = 0.0;
    slope = 0.0;
}

River::~River ()
{
    while (segments->count() > 0)
        delete segments->takeFirst();
    delete segments;

    delete name;
}

bool River::parse(RiverFile *rfile)
{
    bool okay = true, end = false;
    QString token (""), na("");
    float val;

    while (okay && !end)
    {
        token = rfile->popToken ();
        if (token.compare ("EOF", Qt::CaseInsensitive) == 0)
        {
            rfile->printMessage(EOF_MSG);
            end = true;
        }
        else if (token.compare ("river", Qt::CaseInsensitive) == 0)
        {
            rfile->pushToken(token);
        }
        else if (token.compare ("flow_max", Qt::CaseInsensitive) == 0)
        {
            okay = rfile->readFloatOrNa(na, val);
            if (okay)
                flowMax = val;
        }
        else if (token.compare ("flow_min", Qt::CaseInsensitive) == 0)
        {
            okay = rfile->readFloatOrNa(na, val);
            if (okay)
                flowMin = val;
        }
        else if (token.compare ("reach", Qt::CaseInsensitive) == 0)
        {
            Reach *rch;
            QString rchName ("");
            okay = rfile->readString (rchName);
            if (okay)
            {
                rch = new Reach (rchName, *name, this);
                segments->append(rch);
                reaches.append(rch);
                rch->flow_min = flowMin;
                rch->flow_max = flowMax;

                okay = rch->parse (rfile);
                emit addedReach(rch);
            }
        }
        else if (token.compare ("dam", Qt::CaseInsensitive) == 0)
        {
            Dam *dm;
            QString dmName ("");
            okay = rfile->readString (dmName);
            if (okay)
            {
                dm = new Dam (dmName, *name, this);
                segments->append(dm);
                dams.append(dm);
                dm->flow_min = flowMin;
                dm->flow_max = flowMax;

                okay = dm->parse (rfile);
                emit addedDam(dm);
            }
        }
        else if (token.compare ("headwater", Qt::CaseInsensitive) == 0)
        {
            Headwater *hwtr;
            QString hwName ("");
            okay = rfile->readString (hwName);
            if (okay)
            {
                hwtr = new Headwater (hwName, *name, this);
                segments->append(hwtr);
                hwtr->flow_min = flowMin;
                hwtr->flow_max = flowMax;

                okay = hwtr->parse (rfile);
                emit addedHeadwater(hwtr);
            }
        }
        else if (token.contains ("end"))
        {
            end = true;
            rfile->checkEnd ("river", *name);
        }
        else
        {
            rfile->handle_unknown_token (token);
            rfile->skipLine ();
        }
    }
    return okay;
}

bool River::construct()
{
    bool okay = true;
//    River *riv = nullptr;
    RiverSegment *cur_seg = nullptr;
    RiverSegment *down_seg = nullptr;
    QString curRiver ("");

    down_seg = (RiverSegment *) segments->at (0);
    curRiver = QString (*down_seg->riverName);

    // construct the river(s)
    if (segments->count() > 1)
    {
        for (int i = 1; okay && i < segments->count(); i++)
        {
            cur_seg = (RiverSegment *) segments->at(i);

            cur_seg->down = down_seg;
            down_seg->up = cur_seg;

            if (down_seg->top()->getLatitude() != cur_seg->bottom()->getLatitude() ||
                down_seg->top()->getLongitude() != cur_seg->bottom()->getLongitude())
            {
                Log::instance()->add(Log::Error, QString ("Upstream of %1 doesn't match downstream of %2").arg(
                                         *down_seg->name, *cur_seg->name));
//                cur_seg->errors.set(SegmentErrors::LatLonLower);
//                down_seg->errors.set(SegmentErrors::LatLonUpper);// |= LatLonUpper;
            }
            down_seg = cur_seg;
        }
    }
    else
    {
        cur_seg = down_seg;
    }
    // we have ended, but is it at a headwater? We don't care
    // because we don't do anything with headwaters.
/*    if (cur->type != RiverSegment::HeadwaterSegment)
    {
        QString hname (curRiver);
        hname.append(" Headwater");
        cur = new Headwater (hname, curRiver, this);
        cur->down = prev;
        prev->up = cur;
        cur->course.append(new RiverPoint (*prev->top()));

        segments->append (cur);
//        ((RiverSystem *)parent())->headwaters->append(hname);
        Log::instance()->add(Log::Debug, QString (
                  QString("adding headwater %1").arg(hname)));
    }*/

    // construct the reaches
    for (int i = 0; i < reaches.count(); i++)
    {
        Reach *rch = reaches.at (i);
        rch->construct();
    }
    // construct the dams (more complicated)
    for (int i = 0; i < dams.count(); i++)
    {
        Dam *dm = dams.at (i);
        dm->construct();
    }

    return okay;
}

bool River::initialize()
{
    bool okay = true;
    if (slope == 0.0)
        slope = DEFAULT_SLOPE;

    // dams need to be constructed first (more complicated)
    for (int i = 0; i < dams.count(); i++)
    {
        Dam *dm = dams.at (i);
        dm->initialize();
    }
    for (int i = 0; i < reaches.count(); i++)
    {
        Reach *rch = reaches.at (i);
        rch->initialize();
    }

    return okay;
}

RiverSegment * River::findSegment(QString name)
{
    RiverSegment *seg = nullptr;
    for (int i = 0; i < segments->count(); i++)
    {
        seg = (RiverSegment *)segments->at (i);
        if (seg->name->compare(name) == 0)
            break;
    }
    return seg;
}

RiverSegment * River::findSegment(RiverPoint *pt)
{
    RiverSegment *seg = nullptr;
    bool found = false;
    for (int i = 0; !found && i < segments->count(); i++)
    {
        seg = (RiverSegment *)segments->at (i);
        for (int j = 0; !found && j < seg->course.count(); j++)
            if (seg->course.at (j)->equals(*pt))
                found = true;
    }
    if (!found)
        seg = nullptr;

    return seg;
}

/** Sets all dams to be regulation points */
void River::markRegulationPts()
{
    for (int i = 0; i < segments->count(); i++)\
    {
        RiverSegment *seg = segments->at(i);
        if (seg->type == RiverSegment::DamSegment)
            seg->regPoint = true;
    }
}

bool River::output (int indent, RiverFile *rfile)
{
    bool okay = true;
    int i = 0;
    // first output name, flow_max, and flow_min
    rfile->writeString(indent, "river", *name);
    rfile->writeString(indent+1, "flow_max", QString::number(flowMax, 'f', 2));
    rfile->writeString(indent+1, "flow_min", QString::number(flowMin, 'f', 3));

    // output segments in order
    for (i = 0; i < segments->count(); i++)
    {
        rfile->writeNewline();
        RiverSegment *seg = segments->at(i);
        switch (seg->type)
        {
        case (RiverSegment::DamSegment):
            okay = (static_cast<Dam *>(seg))->output (indent+1, rfile);
            break;
        case (RiverSegment::ReachSegment):
            okay = (static_cast<Reach *>(seg))->output (indent+1, rfile);
            break;
        case (RiverSegment::HeadwaterSegment):
            okay = (static_cast<Headwater *>(seg))->output (indent+1, rfile);
            break;
        default:
            Log::instance()->add(Log::Error, QString("During output, segment type %1 not recognized.")
                                 .arg (QString::number(seg->type)));
        }

    }
    rfile->writeEnd(indent, "", *name);

    return okay;
}

bool River::deleteSegment(RiverSegment *seg)
{
    bool okay = true;
    int ind = 0;
    RiverSegment *found_seg;
    ind = segments->indexOf(seg);//= findSegment(*seg->name);
    if (ind >= 0) //found_seg == seg)
    {
        found_seg = segments->takeAt(ind);
        if (seg->down != nullptr)
            seg->down->up = seg->up;
        if (seg->up != nullptr)
            seg->up->down = seg->down;

        switch (seg->type)
        {
        case RiverSegment::DamSegment:
        {
            Dam *dam = static_cast<Dam *>(seg);
            ind = dams.indexOf(dam);
            if (ind >= 0)
                dams.takeAt(ind);
            delete dam;
            break;
        }
        case RiverSegment::ReachSegment:
        {
            Reach *reach = static_cast<Reach *>(seg);
            ind = reaches.indexOf(reach);
            if (ind >= 0)
                reaches.takeAt(ind);
            delete reach;
            break;
        }
        case RiverSegment::HeadwaterSegment:
        {
            Headwater *hwater = static_cast<Headwater *>(seg);
            delete hwater;
            break;
        }
        default:
            delete seg;
        }
    }
    else
    {
        Log::instance()->add(Log::Error, QString("Could not find segment %1 to delete.").arg
                             (*seg->name));
    }

    return okay;
}

