#ifndef POWERHOUSE_H
#define POWERHOUSE_H

#include "CompassFile.h"
#include "Period.h"
#include "definitions.h"

class PowerHouse
{
public:
    PowerHouse();
    ~PowerHouse();

    void allocate (int slicesInSeason);

    bool parse (CompassFile *infile);
    bool parseToken (QString token, CompassFile *infile);

    QString *getName() const;
    void setName(QString *value);

    int getNumber() const;
    void setNumber(int value);

    int getPriority() const;
    void setPriority(int value);

    float getThreshold() const;
    void setThreshold(float value);

    float getCapacity() const;
    void setCapacity(float value);

    QList<float> getFlowFraction() const;
    void setFlowFraction(const QList<float> &value);

    float getFlowFractionValue (int index);
    void setFlowFractionValue (int index, float value);

    QList<Period *> getSchedule() const;
    void setSchedule(const QList<Period *> &value);
    int getNumPeriods ();

    Location getSide() const;
    void setSide(const Location &value);

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
