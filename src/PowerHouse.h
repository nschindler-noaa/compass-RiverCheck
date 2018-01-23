#ifndef POWERHOUSE_H
#define POWERHOUSE_H

#include <QList>
#include "definitions.h"
#include "Period.h"

class PowerHouse
{
public:
    PowerHouse();
    ~PowerHouse();

    short getPriority() const;
    void setPriority(short value);

    float getCapacity() const;
    void setCapacity(float value);

    float getFlow_min() const;
    void setFlow_min(float value);

    Location getSide() const;
    void setSide(const Location &value);

    QList<Period *> getSchedule() const;
    void setSchedule(const QList<Period *> &value);
    int getNumPeriods ();

private:
    short priority;    /**< Ranking of powerhouse. The highest priority is
                         *  0 followed by increasing positive numbers. */
    float capacity;    /**< Capacity in KCFS of this powerhouse. */
    float flow_min;    /**< Minimum flow to turn this powerhouse on. */
    Location side;     /**< Location of powerhouse. */
    QList<Period *> schedule; /**< List of time periods with the amount
                         * of flow for this powerhouse. */
};

#endif // POWERHOUSE_H
