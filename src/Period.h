#ifndef PERIOD_H
#define PERIOD_H

#include "definitions.h"

class Period
{
public:
    Period();
    Period(Period *rhs);
    ~Period();

    Period *copy (Period *rhs);
    void init();

    int getStartDay() const;
    void setStartDay(int value);

    int getEndDay() const;
    void setEndDay(int value);

    float getValue() const;
    void setValue(float value);

    bool isOn() const;
    void setOn(bool value);


private:
    int startDay;
    int endDay;
    float value;
    bool on;
};

#endif // PERIOD_H
