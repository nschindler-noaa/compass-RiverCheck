#include "Transport.h"

Transport::Transport()
{

}

float Transport::getRate() const
{
    return rate;
}

void Transport::setRate(float value)
{
    rate = value;
}

float Transport::getHighFlow() const
{
    return highFlow;
}

void Transport::setHighFlow(float value)
{
    highFlow = value;
}

float Transport::getHighFlowPassedPct() const
{
    return highFlowPassedPct;
}

void Transport::setHighFlowPassedPct(float value)
{
    highFlowPassedPct = value;
}

void Transport::setTargetSegment(RiverSegment *value)
{
    targetSegment = value;
}

void Transport::setSourceSegment(RiverSegment *value)
{
    sourceSegment = value;
}

void Transport::setHighFlowSpecies(Species *value)
{
    highFlowSpecies = value;
}

int Transport::getNumberLowDays() const
{
    return numberLowDays;
}

void Transport::setNumberLowDays(int value)
{
    numberLowDays = value;
}

int Transport::getEndCount() const
{
    return endCount;
}

void Transport::setEndCount(int value)
{
    endCount = value;
}

int Transport::getEndDate() const
{
    return endDate;
}

void Transport::setEndDate(int value)
{
    endDate = value;
}

int Transport::getRestartCount() const
{
    return restartCount;
}

void Transport::setRestartCount(int value)
{
    restartCount = value;
}

int Transport::getRestartDate() const
{
    return restartDate;
}

void Transport::setRestartDate(int value)
{
    restartDate = value;
}

QList<bool> Transport::getTransportActive() const
{
    return transportActive;
}

void Transport::setTransportActive(const QList<bool> &value)
{
    transportActive = value;
}

bool Transport::getRestartByDate() const
{
    return restartByDate;
}

void Transport::setRestartByDate(bool value)
{
    restartByDate = value;
}

int Transport::getMaxNumRestarts() const
{
    return maxNumRestarts;
}

void Transport::setMaxNumRestarts(int value)
{
    maxNumRestarts = value;
}

int Transport::getStartCount() const
{
    return startCount;
}

void Transport::setStartCount(int value)
{
    startCount = value;
}

int Transport::getStartDate() const
{
    return startDate;
}

void Transport::setStartDate(int value)
{
    startDate = value;
}

bool Transport::getStartByDate() const
{
    return startByDate;
}

void Transport::setStartByDate(bool value)
{
    startByDate = value;
}

Species *Transport::getHighFlowSpecies() const
{
    return highFlowSpecies;
}

RiverSegment *Transport::getSourceSegment() const
{
    return sourceSegment;
}

RiverSegment *Transport::getTargetSegment() const
{
    return targetSegment;
}
