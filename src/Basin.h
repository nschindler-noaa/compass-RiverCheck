#ifndef BASIN_H
#define BASIN_H

#include "definitions.h"

/** \class basin
 * \brief A structure to represent a storage basin associated with a dam.
 */
class Basin
{
public:
    Basin();

    float min_volume;         /**< Minimum allowable volume */
    float max_volume;         /**< Maximum allowable volume */

};

#endif // BASIN_H
