#ifndef RSW_H
#define RSW_H

#include "definitions.h"

class RSW
{
public:
    RSW(int num = 0);

    int number;
    float capacity;    /**< Maximum flow  in KCFS (partitioned from overall spill)
                           * through this RSW (setting this to 0 essentially
                           * turns it off) */
    Location side;     /**< Location of rsw. */
    short priority;    /**< Ranking of rsw. The best priority is
                         *  0 followed by increasing positive numbers. */
};

#endif // RSW_H
