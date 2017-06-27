#include "RiverFile.h"
#include "RiverPoint.h"
#include "RiverSegment.h"
#include "RiverSystem.h"
#include "RiverSite.h"
#include "Headwater.h"
#include "Reach.h"
#include "Dam.h"
#include "Log.h"

RiverSystem *riverSystem = NULL;

RiverSystem::RiverSystem(QObject *parent) :
    QObject(parent)
{
    setup ();
    riverSystem = this;
}

RiverSystem::RiverSystem(RiverFile *rivfile, QObject *parent) :
    QObject(parent)
{
    setup();
    riverSystem = this;
    parseDesc(rivfile);
}

void RiverSystem::setup ()
{
    rivers = new QList<River *>();
    species = new QList <Species *>();
    stocks = new QList <Stock *>();
    releaseSites = new QList <RiverSite *>();

    speciesNames = new QStringList();
    stockNames = new QStringList();
    riverNames = new QStringList();
    powerhouses = new QStringList();
    dams = new QStringList();
    reaches = new QStringList();
    headwaters = new QStringList();
    basins = new QStringList();
}

RiverSystem::~RiverSystem ()
{
    deleteAll ();
}

RiverSegment *RiverSystem::mouth()
{
    return rivers->at(0)->firstSegment();
}


void RiverSystem::deleteAll()
{
//    int i;
    while (rivers->count())
        delete rivers->takeLast();
    delete rivers;

    while (species->count())
        delete species->takeLast();
    delete species;

    while (stocks->count())
        delete stocks->takeLast();
    delete stocks;

    while (releaseSites->count())
        delete (releaseSites->takeLast());
    delete releaseSites;

    delete speciesNames;
    delete stockNames;
    delete powerhouses;
    delete dams;
    delete reaches;
    delete headwaters;
    delete basins;

}

bool RiverSystem::parseDesc(RiverFile *rfile)
{
    bool okay = true;
//    if (rfile->isReadable())
    {
        okay = rfile->open(QIODevice::ReadOnly);
        if (okay)
            okay = rfile->readHeader();
        if (okay)
            okay = parse (rfile);
        rfile->close();
    }
/*    else
        okay = false;*/
    if (riverNames->isEmpty())
        okay = false;

    return okay;
}

bool RiverSystem::parse(RiverFile *rfile)
{
    bool okay = true, end = false;
    QString token (""), na("");
    float val;
    QString currentRiver("");
    int currentRivInd = 0;

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
            River *river;
            okay = rfile->readString (currentRiver);
            if (okay)
            {
                if (riverNames->contains(currentRiver))
                {
                    river = findRiver (currentRiver);
                }
                else
                {
                    river = new River (currentRiver, this);
                    riverNames->append(currentRiver);
                    rivers->append(river);
                    connect (river, SIGNAL(addedDam(Dam*)), SLOT(addDam(Dam*)));
                    connect (river, SIGNAL(addedReach(Reach*)), SLOT(addReach(Reach*)));
                    connect (river, SIGNAL(addedHeadwater(Headwater*)), SLOT(addHeadwater(Headwater*)));
//                    Log::instance()->add(Log::Error, "No reach by this name");
  //                  Log::instance()->add(Log::Error, reachName);
                }
                okay = river->parse (rfile);
            }
        }
        else if (token.compare ("flow_max", Qt::CaseInsensitive) == 0)
        {
            if (rivers->count() > 0)
            {
                okay = rfile->readFloatOrNa(na, val);
                rivers->at(currentRivInd - 1)->flowMax = val;
            }
            else
            {
                Log::instance()->add(Log::Error, "Trying to read value for flow max with no river defined.");
            }
        }
        else if (token.compare ("flow_min", Qt::CaseInsensitive) == 0)
        {
            if (rivers->count() > 0)
            {
                okay = rfile->readFloatOrNa(na, val);
                rivers->at(currentRivInd - 1)->flowMin = val;
            }
            else
            {
                Log::instance()->add(Log::Error, "Trying to read value for flow min with no river defined.");
            }
        }
        else if (token.compare ("reach", Qt::CaseInsensitive) == 0)
        {
            Reach *reach;
            QString reachName ("");
            okay = rfile->readString (reachName);
            if (okay)
            {
                if (reaches->contains(reachName))
                {
                    reach = (Reach *)findSegment(reachName);
                }
                else
                {
                    reach = new Reach (reachName);
//                    Log::instance()->add(Log::Error, "No reach by this name");
  //                  Log::instance()->add(Log::Error, reachName);
                }
                okay = reach->parse (rfile);
            }
        }
        else if (token.compare ("dam", Qt::CaseInsensitive) == 0)
        {
            QString damName ("");
            okay = rfile->readString (damName);
            if (okay)
            {
                Dam *dam;
                if (dams->contains(damName))
                {
                    dam = (Dam *)findSegment(damName);
                }
                else
                {
                    dam = new Dam (damName);
//                    Log::instance()->add(Log::Error, "No dam by this name");
  //                  Log::instance()->add(Log::Error, damName);
                }
                okay = dam->parse (rfile);
            }
        }
        else if (token.compare ("headwater", Qt::CaseInsensitive) == 0)
        {
            Headwater *hwtr;
            QString hwName ("");
            okay = rfile->readString (hwName);
            if (okay)
            {
                if (headwaters->contains(hwName))
                {
                    hwtr = (Headwater *)findSegment(hwName);
                }
                else
                {
                    hwtr = new Headwater (hwName);
 //                   Log::instance()->add(Log::Error, "No headwater by this name");
   //                 Log::instance()->add(Log::Error, hwName);
                }
                okay = hwtr->parse (rfile);
            }
        }
        else if (token.compare ("release_site", Qt::CaseInsensitive) == 0)
        {
            okay = rfile->readString(token);
            if (okay)
            {
                RiverSite *rsite = new RiverSite("release_site", token);
                okay = rsite->parse (rfile);
                releaseSites->append(rsite);
/*            rsite->segment = findSegment(rsite->location);
            rsite->distance = rsite->segment->distance(rsite->location);*/
            }
        }
        else if (token.compare ("species", Qt::CaseInsensitive) == 0)
        {
            okay = rfile->readString(token);
            if (okay)
            {
                Species * spc = new Species (token);
                species->append(spc);
                speciesNames->append(token);
            }
        }
        else if (token.compare ("stock", Qt::CaseInsensitive) == 0)
        {
            okay = rfile->readString(token);
            if (okay)
            {
                Stock *stk = new Stock (token);
                stocks->append(stk);
                stockNames->append(token);
            }
        }
        else if (token.contains ("end"))
        {
//            rfile->skipLine ();
            end = true;
            rfile->checkEnd ("", currentRiver);
        }
        else
        {
            rfile->handle_unknown_token (token);
            rfile->skipLine ();
        }
    }
    return okay;
}

bool RiverSystem::construct()
{
    bool done = false;
    River *cur_riv = NULL;
    River *down_riv = NULL;
    RiverSegment *cur_seg = NULL;
    RiverSegment *down_seg = NULL;
    QString curRiver ("");

    for (int i = 0; !done && i < rivers->count(); i++)
    {
        cur_riv = (River *)rivers->at(i);
        cur_riv->construct();
    }
    for (int i = 1; i < rivers->count(); i++)
    {
        cur_seg = NULL;
        down_seg = NULL;
        done = false;
        cur_riv = (River *)rivers->at(i);
        cur_seg = (RiverSegment *)cur_riv->segments->at(0);
        for (int j = 0; !done && j < rivers->count(); j++)
        {
            if (j != i)
            {
                down_riv = (River *)rivers->at(j);
                down_seg = down_riv->findSegment(cur_seg->bottom());
                if (down_seg != NULL && down_seg->type == RiverSegment::ReachSegment)
                {
                    cur_seg->down = down_seg;
                    down_seg->fork = cur_seg;
                    done = true;
                }
            }
        }
        if (!done)
        {
            Log::instance()->add(Log::Error, QString("could not find connection to %1").arg(
                                     *cur_riv->name));
            break;
        }
    }

    emit constructed(done);
    return done;
}

bool RiverSystem::initialize()
{
    bool okay = true;
    River * riv = NULL;

    for (int i = 0; i < rivers->count(); i++)
    {
        riv = (River *)rivers->at(i);
        okay = riv->initialize();
    }

    return okay;
}

River * RiverSystem::findRiver(QString name)
{
    River *riv = NULL;
    for (int i = 0; i < rivers->count(); i++)
    {
        riv = (River *)rivers->at (i);
        if (riv->name->compare(name) == 0)
            break;
    }
    return riv;
}

RiverSegment * RiverSystem::findSegment(QString name)
{
    River *riv = NULL;
    RiverSegment *seg = NULL;
    for (int i = 0; i < rivers->count(); i++)
    {
        riv = (River *)rivers->at (i);
        seg = riv->findSegment(name);
        if (seg != NULL)
            break;
    }
    return seg;
}

RiverSegment * RiverSystem::findSegment(RiverPoint *pt)
{
    River *riv = NULL;
    RiverSegment *seg = NULL;
    for (int i = 0; i < rivers->count(); i++)
    {
        riv = (River *)rivers->at (i);
        seg = riv->findSegment(pt);
        if (seg != NULL)
            break;
    }
    return seg;
}

Species * RiverSystem::findSpecies(QString name)
{
    Species *spec = NULL;
    for (int i = 0; i < species->count(); i++)
    {
        spec = (Species *)species->at (i);
        if (spec->name->compare(name) == 0)
            break;
    }
    return spec;
}

Stock * RiverSystem::findStock(QString name)
{
    Stock *st = NULL;
    for (int i = 0; i < stocks->count(); i++)
    {
        st = (Stock *)stocks->at (i);
        if (st->name->compare(name) == 0)
            break;
    }
    return st;
}


RiverSite * RiverSystem::findReleaseSite(QString name)
{
    RiverSite *site = NULL;
    for (int i = 0; i < releaseSites->count(); i++)
    {
        site = (RiverSite *)releaseSites->at (i);
        if (site->name->compare(name) == 0)
            break;
    }
    return site;
}

void RiverSystem::markRegulationPts()
{
    for (int i = 0; i < dams->count(); i++)\
    {
        QString damname = (QString)dams->at (i);
        Dam *dam = static_cast <Dam *> (findSegment(damname));
        dam->regPoint = true;
    }
}

bool RiverSystem::writeDesc(RiverFile *rfile)
{
    bool okay = true;

//    if (rfile->isWritable())
    {
        okay = rfile->open(QIODevice::WriteOnly);
        rfile->writeHeader();
        output (rfile);
        rfile->close();
    }
    /*else
        okay = false;*/

    return okay;
}

bool RiverSystem::output (RiverFile *rfile)
{
    bool okay = true;
    int i = 0;
    // output all species
    for (i = 0; i < species->count(); i++)
    {
        okay = species->at (i)->output (0, rfile);
    }
    rfile->writeNewline();

    // output all stocks
    for (i = 0; i < stocks->count(); i++)
    {
        okay = stocks->at (i)->output (0, rfile);
    }
    rfile->writeNewline();

    // output all release sites
    for (i = 0; i < releaseSites->count(); i++)
    {
        okay = releaseSites->at (i)->output (0, rfile);
        rfile->writeNewline();
    }

    // output rivers in order, this includes all river segments
    for (i = 0; i < rivers->count(); i++)
    {
        okay = rivers->at (i)->output (0, rfile);
        rfile->writeNewline();
    }

    // end of description

    return okay;
}

void RiverSystem::addSpecies(QString name)
{
    species->append(new Species (name));
}
void RiverSystem::deleteSpecies(QString name)
{
    int index = 0;
    for (; index < species->count(); index++)
    {
        if (species->at(index)->name->compare(name) == 0)
        {
            Species * sp = (Species *)species->takeAt(index);
            delete sp;
        }
    }
}
void RiverSystem::changeSpeciesName(QString oldName, QString newName)
{
    if (!oldName.isEmpty() && !newName.isEmpty())
    {
        QString *nm = findSpecies(oldName)->name;
        nm->clear();
        nm->append(newName);
    }
}

void RiverSystem::addStock(QString name)
{
    stocks->append(new Stock (name));
}
void RiverSystem::deleteStock(QString name)
{
    int index = 0;
    for (; index < stocks->count(); index++)
    {
        if (stocks->at(index)->name->compare(name) == 0)
        {
            Stock *stk = (Stock *)stocks->takeAt(index);
            delete stk;
        }
    }
}
void RiverSystem::changeStockName(QString oldName, QString newName)
{
    if (!oldName.isEmpty() && !newName.isEmpty())
    {
        QString *nm = findStock(oldName)->name;
        nm->clear();
        nm->append(newName);
    }
}

void RiverSystem::addSegment (RiverSegment *seg)
{
    switch (seg->type)
    {
    case RiverSegment::DamSegment:
    {
        Dam *dam = (Dam *)seg;
        addDam(dam);
        break;
    }
    case RiverSegment::ReachSegment:
    {
        Reach *rch = (Reach *)seg;
        addReach(rch);
        break;
    }
    case RiverSegment::HeadwaterSegment:
    {
        Headwater *hwtr = (Headwater *)seg;
        addHeadwater(hwtr);
        break;
    }
    default:
        break;
    }
}

void RiverSystem::deleteSegment(QString name)
{
    RiverSegment *seg = findSegment(name);
    deleteSegment(seg);
}

void RiverSystem::deleteSegment(RiverSegment *seg)
{
    switch (seg->type)
    {
    case RiverSegment::DamSegment:
    {
        Dam *dam = (Dam *)seg;
        deleteDam (dam);
        break;
    }
    case RiverSegment::ReachSegment:
    {
        Reach *reach = (Reach *)seg;
        deleteReach (reach);
        break;
    }
    case RiverSegment::HeadwaterSegment:
    default:
        break;
    }
}

void RiverSystem::addDam(Dam *dam)
{
    int i, num = dam->getNumPowerhouses();
    dams->append(*dam->name);
    for (i = 0; i < num; i++)
        powerhouses->append(QString ("%1_PH%2").arg(
                                *dam->name, QString::number(i+1)));
}

void RiverSystem::deleteDam(Dam *dam)
{
    int ind;
    River *river = findRiver(*dam->riverName);

    Reach *seg_down = (Reach *)(dam->down);
    Reach *seg_up = (Reach *)(dam->up);

    ind = dams->indexOf(*dam->name);
    if (ind >= 0)
        dams->takeAt(ind);
    for (int i = 0; i < dam->getNumPowerhouses(); i++)
    {
        QString ph_name (*dam->name);
        ph_name.append(QString("_%1").arg(QString::number(i + 1)));
        ind = powerhouses->indexOf(ph_name);
        if (ind >= 0)
            powerhouses->takeAt(ind);
    }

    if (river == NULL)
        Log::instance()->add(Log::Error, QString("Could not find river %1").arg
                             (*dam->riverName));
    else if (seg_up != NULL)
    {
        // get list of impounded reaches to adjust depths, slopes, and widths
        QList <Reach *> impounded_reaches;
        impounded_reaches.append(seg_up);
        while (seg_up->up != NULL &&
               seg_up->up->type == RiverSegment::ReachSegment &&
               seg_up->up->getImpound() != RiverSegment::NotImpounded)
        {
            seg_up = (Reach *)seg_up->up;
            impounded_reaches.append(seg_up);
        }
        if (seg_up->getImpound() == RiverSegment::NotImpounded)
            adjustReaches (seg_down, seg_up, impounded_reaches);
        else
            adjustReaches (seg_down, seg_down, impounded_reaches);

/*        for (int i = impounded_reaches.count()-1; i >= 0; i--)
        {
            seg_up = impounded_reaches.takeAt(i);
            if (seg_up->type == RiverSegment::ReachSegment)
            {
                if (seg_up->up == NULL)
                {
                    seg_up->upper_depth = 15;
                    seg_up->upper_elev = seg_up->lower_elev;
                    seg_up->slope = river->slope;
                    seg_up->tan_slope = tan(seg_up->slope);
                    seg_up->width = seg_up->bed_width + (2 *seg_up->tan_slope);
                }
                else
                {
                    seg_up->upper_depth = seg_up->up->lower_depth;
                    seg_up->upper_elev = seg_up->up->lower_elev;
                }

                if (seg_up->up->type == RiverSegment::ReachSegment)
                {
                    Reach * seg_up_up = (Reach *)(seg_up->up);
                    seg_up->slope = seg_up_up->slope;
                    seg_up->tan_slope = tan(seg_up->slope);
                    seg_up->width = seg_up->bed_width + (2 * (seg_up->tan_slope * seg_up->lower_depth));
                }
                else
                {
                    seg_up->slope = river->slope;
                    seg_up->tan_slope = tan(seg_up->slope);
                    seg_up->width = seg_up->bed_width + (2 * (seg_up->tan_slope * seg_up->lower_depth));
                }
                seg_up->calculateGeometries();
            }
        }
        if (seg_down->upper_elev != seg_up->lower_elev)
            seg_down->upper_elev = seg_up->lower_elev;
        if (seg_up->lower_depth != seg_down->upper_depth)
            seg_up->lower_depth = seg_down->upper_depth;
*/
        river->deleteSegment(dam);
    }
    else if (seg_down != NULL)
    {
        seg_down->upper_elev = seg_down->lower_elev;
        river->deleteSegment(dam);
    }
}

void RiverSystem::adjustReaches(Reach *downReach, Reach *upReach, QList<Reach *> reaches)
{
    Reach *reach = (Reach *)reaches.takeLast();
    float bd_width = upReach->bed_width;
    reach->slope = DEFAULT_SLOPE;
    reach->tan_slope = tan(reach->slope * DEG_2_RAD);
    if (upReach == downReach)
    {
        if (reach->up != NULL &&
                reach->up->lower_depth < upReach->upper_depth)
            reach->lower_depth = reach->upper_depth = reach->up->lower_depth;
        else
            reach->lower_depth = reach->upper_depth = upReach->upper_depth;
    }
    else
    {
        reach->lower_depth = reach->upper_depth = upReach->lower_depth;
    }
    reach->width = bd_width + 2.0 * reach->upper_depth;
    reach->calculateGeometries();

    while (reaches.count() > 0)
    {
        reach = (Reach *)reaches.takeLast();
        upReach = (Reach *)reach->up;
        reach->width = upReach->width;
        reach->slope = upReach->slope;
        reach->lower_depth = reach->upper_depth = upReach->lower_depth;
        reach->calculateGeometries();
    }

//    reach->width = downReach->upper_width;
    reach->lower_depth = downReach->upper_depth;
    reach->calculateGeometries();

    if (downReach->upper_elev != reach->lower_elev)
        downReach->upper_elev  = reach->lower_elev;
}

void RiverSystem::addReach(Reach *rch)
{
    reaches->append(*rch->name);
}

void RiverSystem::deleteReach (Reach *reach)
{
    int ind = 0;

    River *river = findRiver(*reach->riverName);
    bool del = false;

    ind = reaches->indexOf(*reach->name);
    if (ind >= 0)
        reaches->takeAt(ind);

    if (reach->up != NULL && reach->down != NULL)
    {
        if (reach->up->bottom() == reach->down->top())
            del = true;
    }
    else if (reach->down == NULL)
        del = true;
    else if (reach->up == NULL && reach->down->type != RiverSegment::DamSegment)
        del = true;
    else
        del = false;

    if (del)
        river->deleteSegment(reach);
    else
        Log::instance()->add(Log::Error,
                     QString("Cannot delete segment %1.").arg(
                     *reach->name));
}

void RiverSystem::addHeadwater(Headwater *hwtr)
{
    headwaters->append(*hwtr->name);
}

