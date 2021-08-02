#include "Reach.h"
#include "Dam.h"
#include "Log.h"
#include "definitions.h"
#include <cmath>

float Ufree = 0.045;		/* kfs x10-1*/

Reach::Reach (QString rname, QString rivName, QObject *parent) :
    RiverSegment (rivName, parent)
{
    name = new QString (rname);
    type = RiverSegment::ReachSegment;
    abbrev = nullptr;

    clear ();
}

void Reach::reset()
{
    RiverSegment::reset();
    length = 0.0;
    volume = 0.0;
    surface_area = 0.0;
    ave_depth = 0.0;
    bedWidth = 0.0;

}

void Reach::clear ()
{
    RiverSegment::clear();
    reset();
    slope = 40.0;

//    water_tt = 0.0;

}
/*
float Reach::computeVolume (float elev_chng, float upper_d, float lower_d, float wd, float slp_tan)
{
    float vol = 0.0;

    if (upper_d == lower_d)
    {
        vol = (wd - slp_tan * (lower_d + elev_chng)) * (lower_d - elev_chng);
    }
    else if (elev_chng == 0.0)
    {
        vol = wd * (upper_d + lower_d)/2.0 - slp_tan/3.0
                * ((upper_d + lower_d) * (upper_d + lower_d)/2.0 + upper_d * lower_d);
    }
    else
    {
        float vol_init = (1 / (lower_d - upper_d)) * (lower_d - elev_chng)
                * (lower_d - elev_chng) * (wd/2.0 - slp_tan * (lower_d/6.0 + upper_d/2.0 + elev_chng/3.0 ));
        float vol_exss = 0;
        if (elev_chng >= upper_d)
            vol_exss = 0.0;
        else
        {
            vol_exss = (1 / (lower_d - upper_d)) * (upper_d - elev_chng)
                * (upper_d - elev_chng) * (wd/2.0 - slp_tan * (lower_d/2.0 + upper_d/6.0 + elev_chng/3.0 ));
        }
        vol = vol_init - vol_exss;
    }
    return vol;
}

float Reach::computeVelocity(float elev_chng, float upper_d, float lower_d, float avg_fl)
{
    float vel = 0.0;

    if (-(elev_chng) < upper_d)
    {
        if (volume != 0)
            vel = avg_fl / volume;
    }
    else
    {
        vel = (avg_fl == 0)? 0.0
                                  : 1.0 / (volume /
               avg_fl + (1 - lower_d + elev_chng) / (lower_d - upper_d))
                                    / (Ufree * 1.0);
    }
    return vel;
}

float Reach::computeWTT(int firstDay, int lastDay)
{
    float avg_vel = 0.0;
    int i = 0;

    // convert to time steps
    int firstStep = firstDay * STEPS_PER_DAY;
    int lastStep = lastDay * STEPS_PER_DAY;

    for (i = firstStep; i <= lastStep && i < STEPS_IN_SEASON; ++i)
        avg_vel += velocity[i];
    avg_vel /= (i-firstStep + 1);

    return waterTravelTime (avg_vel);
}

float Reach::waterTravelTime (float avg_vel)
{
    float wtt = 0.0;*/

    /* return average water particle travel time through this seg in days */
/*    wtt = (length / avg_vel) / STEPS_PER_DAY;

    return wtt;
}*/

bool Reach::parse (RiverFile *rfile)
{
    bool okay = true, end = false;
    QString token ("");

    while (okay && !end)
    {
        token = rfile->popToken ();
        if (token.compare ("eof", Qt::CaseInsensitive) == 0)
        {
            rfile->printEOF("Reach data.");
            okay = false;
        }
        else if (token.compare("end", Qt::CaseInsensitive) == 0)
        {
            okay = rfile->checkEnd("reach", *name);
            end = true;
        }
        else
        {
            okay = parseToken (token, rfile);
        }
    }

    return okay;
}

bool Reach::parseToken (QString token, RiverFile *rfile)
{
    bool okay = true;
    QString na("");

    if (token.compare ("upper_depth", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readFloatOrNa (na, upperDepth);
    }
    else if (token.compare("lower_depth", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readFloatOrNa(na, lowerDepth);
    }
    else if (token.compare("depth", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readFloatOrNa(na, lowerDepth);
        if (okay) upperDepth = lowerDepth;
    }
    else if (token.compare ("slope", Qt::CaseInsensitive) == 0)
    {
        okay = rfile->readFloatOrNa (na, slope);
    }
    else if (token.compare("abbrev", Qt::CaseInsensitive) == 0)
    {
        abbrev = new QString("");
        okay = rfile->readString(*abbrev);
    }
    else
    {
        okay = RiverSegment::parseToken (token, rfile);
    }

    return okay;
}

bool Reach::initialize()
{
    bool okay = true;


    return okay;
}

bool Reach::construct()
{
    bool okay = true;
    error = 0;
    errors.reset();

    RiverSegment::construct();
    okay = calculateGeometries();

//    error = findErrors();

    if (slope < 0.0 || slope > 90.0)
        errors.set(SegmentErrors::SlopeIncorrect);// |= SlopeIncorrect;

    // create map path

    // create views


    return okay;
}

bool Reach::calculateGeometries()
{
    bool okay = true;

    tan_slope = tan(slope * DEG_2_RAD);

    // set upper elevation if not read from file
    if (upperElev == 0.0)
    {
//        if (upper_depth == lower_depth)
        {
            if (up != nullptr)
            {
//                upper_elev = up->lower_elev;
                if (up->type == RiverSegment::ReachSegment)
                {
                    Reach *rch = (Reach *)up;
                    upperElev = rch->lowerElev;
                }
                else if (up->type == RiverSegment::DamSegment)
                {
                    Dam * dm = (Dam *)up;
                    upperElev = dm->getFloorElev();
                }
                else if (up->type == RiverSegment::HeadwaterSegment)
                {
                    Headwater *hd = (Headwater *)up;
                    upperElev = hd->lowerElev;
                }
            }
            else
            {
                upperElev = lowerElev;
            }
        }
/*        else
        {
            upper_elev = lower_elev + lower_depth - upper_depth;
        }*/
    }

    // calculate the length of this reach -- now in RiverSegment
    //length = distance (top());

    // calculate average depth
    ave_depth = (lowerDepth + upperDepth) / 2.0;// lower_depth - (lower_depth - upper_depth) / 2.0;

    // calculate width of river bed for this reach and any missing values
    if (width != 0)
    {
        bedWidth = width - (2 * (ave_depth * tan_slope));
        lowerWidth = bedWidth + (2 * (lowerDepth * tan_slope));
        upperWidth = bedWidth + (2 * (upperDepth * tan_slope));
    }
    else if (lowerWidth != 0)
    {
        bedWidth = lowerWidth - (2 * (lowerDepth * tan_slope));
        upperWidth = bedWidth + (2 * (upperDepth * tan_slope));
        width = (lowerWidth + upperWidth) / 2.0;
    }
    else if (upperWidth != 0)
    {
        bedWidth = upperWidth - (2 * (upperDepth * tan_slope));
        lowerWidth = bedWidth + (2 * (lowerDepth * tan_slope));
        width = (lowerWidth + upperWidth) / 2.0;
    }
    else
    {
        lowerWidth = 100;
        bedWidth = lowerWidth - (2 * (lowerDepth * tan_slope));
        upperWidth = bedWidth + (2 * (upperDepth * tan_slope));
        width = (lowerWidth + upperWidth) / 2.0;
    }

    // calculate volume first by calculating cross section area
    if (upperDepth == lowerDepth)
    {
        volume = (width - tan_slope * lowerDepth) * (lowerDepth);
    }
    else
    {
        volume = ((1.0 / (lowerDepth - upperDepth)) * lowerDepth * lowerDepth
            * (width / 2.0 - tan_slope * ((2.0 * lowerDepth) / 3.0 )));
    }
    volume *= length;

    surface_area = volume / ave_depth;

    return okay;
}

bool Reach::output(int indent, RiverFile *rfile)
{
    bool okay = true;

    rfile->writeString(indent, "reach", *name);
    rfile->writeString(indent + 1, "width", QString::number(width, 'f', 2));
    rfile->writeString(indent + 1, "lower_depth", QString::number(lowerDepth, 'f', 2));
    rfile->writeString(indent + 1, "upper_depth", QString::number(upperDepth, 'f', 2));
    if (slope != 40.0)
        rfile->writeString(indent + 1, "slope", QString::number(slope, 'f', 2));
    rfile->writeString(indent + 1, "lower_elev", QString::number(lowerElev, 'f', 2));
    if (abbrev != nullptr && !abbrev->isEmpty())
        rfile->writeString(indent + 1,"abbrev", *abbrev);
    outputCourse (indent + 1, rfile);
    rfile->writeEnd(indent, "reach", *name);

    return okay;
}

