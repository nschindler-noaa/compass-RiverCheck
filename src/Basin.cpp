#include "Basin.h"
#include "definitions.h"

Basin::Basin()
{
    minVolume = 0;
    maxVolume = 100;
    for (int i = 0; i < DAYS_IN_SEASON; i++)
        volume.append(0.0);
}

Basin::~Basin()
{
    volume.clear();
}


float Basin::getMinVolume() const
{
    return minVolume;
}

void Basin::setMinVolume(float value)
{
    minVolume = value;
}

float Basin::getMaxVolume() const
{
    return maxVolume;
}

void Basin::setMaxVolume(float value)
{
    maxVolume = value;
}

float Basin::getVolume(int index) const
{
    return volume[index];
}

void Basin::setVolume(int index, const float &value)
{
    volume[index] = value;
}
