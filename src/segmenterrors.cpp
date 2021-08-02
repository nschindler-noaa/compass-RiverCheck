#include "segmenterrors.h"

SegmentErrors::SegmentErrors()
{
    for (int i = 0; i < NumErrors; i++)
        errorTrue.append(false);
}

void SegmentErrors::reset()
{
    for (int i = 0; i < NumErrors; i++)
        errorTrue[i] = false;
}

void SegmentErrors::set(Error type)
{
    switch (type)
    {
    case LatLonUpper:
        if (errorTrue[LatLonUpper] == false) {
            errorList.append("Upper longitude/latitude mismatch.");
            errorTrue[LatLonUpper] = true;
        }
        break;
    case LatLonLower:
        if (errorTrue[LatLonLower] == false) {
            errorList.append("Lower longitude/latitude mismatch.");
            errorTrue[LatLonLower] = true;
        }
        break;
    case ElevUpper:
        if (errorTrue[ElevUpper] == false) {
            errorList.append("Upper elevation mismatch.");
            errorTrue[ElevUpper] = true;
        }
        break;
    case ElevLower:
        if (errorTrue[ElevLower] == false) {
            errorList.append("Lower elevation mismatch.");
            errorTrue[ElevLower] = true;
        }
        break;
    case DepthUpper:
        if (errorTrue[DepthUpper] == false) {
            errorList.append("Upper depth mismatch.");
            errorTrue[DepthUpper] = true;
        }
        break;
    case DepthLower:
        if (errorTrue[DepthLower] == false) {
            errorList.append("Lower depth mismatch.");
            errorTrue[DepthLower] = true;
        }
        break;
    case SlopeIncorrect:
        if (errorTrue[SlopeIncorrect] == false) {
            errorList.append("Incorrect slope.");
            errorTrue[SlopeIncorrect] = true;
        }
        break;
    case SpillwayWidth:
        if (errorTrue[SpillwayWidth] == false) {
            errorList.append("Spillway width and number and size of spillways do not match.");
            errorTrue[SpillwayWidth] = true;
        }
        break;
    case BadPhysics:
        if (errorTrue[BadPhysics] == false) {
            errorList.append("Dam construction includes bad physical specifications.");
            errorTrue[BadPhysics] = true;
        }
        break;
    default:
        break;
    }
}
