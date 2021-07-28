#include "PowerHouse.h"

PowerHouse::PowerHouse()
{
    priority = 0;
    capacity = 0.0;
    flowMin = 0.0;
    side = Left;
}

PowerHouse::~PowerHouse()
{
    while(getNumPeriods() > 0)
    {
        Period *per = schedule.takeLast();
        per->~Period();
        delete per;
    }
}

short PowerHouse::getPriority() const
{
    return priority;
}

void PowerHouse::setPriority(short value)
{
    priority = value;
}

float PowerHouse::getCapacity() const
{
    return capacity;
}

void PowerHouse::setCapacity(float value)
{
    capacity = value;
}

float PowerHouse::getFlowMin() const
{
    return flowMin;
}

void PowerHouse::setFlowMin(float value)
{
    flowMin = value;
}

Location PowerHouse::getSide() const
{
    return side;
}

void PowerHouse::setSide(const Location &value)
{
    side = value;
}

QList<Period *> PowerHouse::getSchedule() const
{
    return schedule;
}

void PowerHouse::setSchedule(const QList<Period *> &value)
{
    schedule = value;
}

int PowerHouse::getNumPeriods()
{
    return schedule.count();
}
