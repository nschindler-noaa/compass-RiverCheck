#ifndef POWERHOUSE_H
#define POWERHOUSE_H

//#include "CompassFile.h"
#include "RiverFile.h"
#include "Period.h"
#include "definitions.h"

#include <QString>

class PowerHouse
{
public:
    PowerHouse();
    ~PowerHouse();

    void allocate (int slicesInSeason);

    bool parse (RiverFile *infile);
    bool parseToken (QString token, RiverFile *infile);

    QString *getName() const;
    void setName(QString *value);

    int getNumber() const;
    void setNumber(int value);

    short getPriority() const;
    void setPriority(short value);

    float getThreshold() const;
    void setThreshold(float value);

    float getCapacity() const;
    void setCapacity(float value);

    QList<float> getFlowFraction() const;
    void setFlowFraction(const QList<float> &value);

    float getFlowFractionValue (int index);
    void setFlowFractionValue (int index, float value);

    float getFlowMin () const;
    void setFlowMin (float min);

    QList<Period *> getSchedule() const;
    void setSchedule(const QList<Period *> &value);
    int getNumPeriods ();

    Location getSide() const;
    void setSide(const Location &value);

private:
    short priority;    /**< Ranking of powerhouse. The highest priority is
                         *  0 followed by increasing positive numbers. */
    float capacity;    /**< Capacity in KCFS of this powerhouse. */
    float flowMin;    /**< Minimum flow to turn this powerhouse on. */
    Location side;     /**< Location of powerhouse. */
    QList<Period *> schedule; /**< List of time periods with the amount
                         * of flow for this powerhouse. */
};

#endif // POWERHOUSE_H
