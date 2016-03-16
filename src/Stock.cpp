#include "Stock.h"

Stock::Stock(QString nm)
{
    if (nm.isEmpty())
        name = new QString ("Generic");
    else
        name = new QString (nm);
}

Stock::~Stock ()
{
    delete name;
}

bool Stock::output(int indent, RiverFile *rfile)
{
    bool okay = true;

    rfile->writeString(indent, "stock", *name);

    return okay;
}
