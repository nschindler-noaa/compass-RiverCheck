#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <QStringList>
#include "RiverSegment.h"
#include "Species.h"




/** /class Transport
 *  /brief Transport operation parameters
 *   This is used to transport fish from a dam to a river segment downriver.
 *   A transport is part of the dam structure.
 */

class Transport
{
public:
    Transport();
    ~Transport();


    Species *getHighFlowSpecies() const;
    void setHighFlowSpecies(Species *value);

    RiverSegment *getSourceSegment() const;
    void setSourceSegment(RiverSegment *value);

    RiverSegment *getTargetSegment() const;
    void setTargetSegment(RiverSegment *value);


    float getRate() const;
    void setRate(float value);

    float getHighFlow() const;
    void setHighFlow(float value);

    float getHighFlowPassedPct() const;
    void setHighFlowPassedPct(float value);

    int getNumberLowDays() const;
    void setNumberLowDays(int value);

    int getEndCount() const;
    void setEndCount(int value);

    int getEndDate() const;
    void setEndDate(int value);

    int getRestartCount() const;
    void setRestartCount(int value);

    int getRestartDate() const;
    void setRestartDate(int value);

    QList<bool> getTransportActive() const;
    void setTransportActive(const QList<bool> &value);

    bool getRestartByDate() const;
    void setRestartByDate(bool value);

    int getMaxNumRestarts() const;
    void setMaxNumRestarts(int value);

    int getStartCount() const;
    void setStartCount(int value);

    int getStartDate() const;
    void setStartDate(int value);

    bool getStartByDate() const;
    void setStartByDate(bool value);

private:
    bool startByDate;        /**< Bool: start trans by date or count */
    int startDate;           /**< For transport start by date */
    int startCount;          /**< For transport start by count */
    int maxNumRestarts;         /**< Max restarts; -1 for infinite */
    bool restartByDate;      /**< Bool: restart trns by date or count*/
    QList<bool> transportActive;	/**< Bool array for transport activity by day */
    int restartDate;         /**< For transport restart by date */
    int restartCount;        /**< For transport restart by count */
    int endDate;             /**< Hard date for transport end */
    int endCount;            /**< Low count for transport end */
    int numberLowDays;         /**< Number of consecutive low count
                                *  days required to end transport */
    float highFlowPassedPct;    /**< Percentage passage of hfl_spec
                                *  for full transport */
    float highFlow;            /**< High flow val for partial transport*/
    Species *highFlowSpecies; /**< Species to return to river during high flow */

    float rate;               /**< Rate of transport 100-500 mi per day */

    RiverSegment *sourceSegment; /**< Dam transported from */
    RiverSegment *targetSegment; /**< Release point */

};

#endif // TRANSPORT_H
