#include "Species.h"

Species::Species (QString nm)
{
    if (nm.isEmpty ())
        name = new QString ("Generic");
    else
        name = new QString(nm);


}

Species::~Species ()
{
    delete name;
}

bool Species::output(int indent, RiverFile *rfile)
{
    bool okay = true;

    rfile->writeString(indent, "species", *name);

    return okay;
}
