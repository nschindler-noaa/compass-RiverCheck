#ifndef STOCK_H
#define STOCK_H
/** \file stock.h
 *  \brief Defines the data structure for stocks (groups of fish from a common
 *         release point with similar characteristics).
 */
#include <QString>

#include "definitions.h"
#include "RiverFile.h"

/**
 * \struct stock
 * The general design is that there are a number of custom stocks,
 * designated in the river description file, the data for which are
 * gathered in the global stock_info struct below.  in addition, each
 * species contains one Stock object, which is "generic" data for that
 * species.

 * The key usage is that each release keeps a handle to one Stock
 * object, either one of the custom globals or the generic from the
 * appropriate species for that release.
 *
 * equation []'s and float []'s are dimensioned by number of
 * \ref reach_classes. */



/** Default values for Stock. These disable as many features as possible
 * and when an input file is written out, only values that differ from
 * these defaults are written out. Thus, old parameters that are
 * generally disabled are hidden. */

class Stock
{
public:
    Stock(QString name = QString (""));
    ~Stock();
    QString  *name;      /**< Name of the stock */

    bool output (int indent, RiverFile *rfile);
};

#endif // STOCK_H
