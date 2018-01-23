#include "Period.h"

Period::Period()
{
    init();
}

Period::Period(Period *rhs)
{
    init();
    copy(rhs);
}

Period::~Period()
{
    init();
}

Period *Period::copy (Period *rhs)
{
    setStartDay(rhs->getStartDay());
    setEndDay(rhs->getEndDay());
    setValue(rhs->getValue());
    setOn(rhs->isOn());
    return this;
}

void Period::init()
{
    startDay = 0;
    endDay = DAYS_IN_SEASON - 1;
    value = 0.0;
    on = false;
}

int Period::getStartDay() const
{
    return startDay;
}

void Period::setStartDay(int value)
{
    startDay = value;
}

int Period::getEndDay() const
{
    return endDay;
}

void Period::setEndDay(int value)
{
    if (value >= DAYS_IN_SEASON)
        value = DAYS_IN_SEASON - 1;
    endDay = value;
}

float Period::getValue() const
{
    return value;
}

void Period::setValue(float value)
{
    value = value;
}

bool Period::isOn() const
{
    return on;
}

void Period::setOn(bool value)
{
    on = value;
}

