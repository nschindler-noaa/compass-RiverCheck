#ifndef POWERHOUSE_H
#define POWERHOUSE_H

#include "definitions.h"

class PowerHouse
{
public:
    PowerHouse(int num = 0);

    int number;
    float capacity;    /**< Capacity in KCFS of this powerhouse. */
    float flow_min;    /**< Minimum flow to turn this powerhouse on. */
    Location side;     /**< Location of powerhouse. */
    short priority;    /**< Ranking of powerhouse. The best priority is
                         *  0 followed by increasing positive numbers. */
};

#endif // POWERHOUSE_H
