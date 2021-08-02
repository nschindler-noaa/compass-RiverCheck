#ifndef SEGMENTERRORS_H
#define SEGMENTERRORS_H

#include <QStringList>


class SegmentErrors
{
public:
    SegmentErrors();

    enum Error {
        LatLonUpper = 0,
        LatLonLower,
        ElevUpper,
        ElevLower,
        DepthUpper,
        DepthLower,
        SlopeIncorrect,
        SpillwayWidth,
        BadPhysics,
        NumErrors
    };

    void reset();
    int count() {return errorList.isEmpty()? 0: errorList.count();}
    void set(Error type);
    bool get(Error type) {return errorTrue[type];}
    QStringList getList() {return errorList;}

private:
    QList<bool> errorTrue;
    QStringList errorList;
};

#endif // SEGMENTERRORS_H
