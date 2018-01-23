#ifndef SEGMENTINFO_H
#define SEGMENTINFO_H
#include "RiverSegment.h"

#include <QWidget>

namespace Ui {
class SegmentInfo;
}

class SegmentInfo : public QWidget
{
    Q_OBJECT
    
public:
    enum Side {
        Upper,
        Lower
    };

    explicit SegmentInfo(Side loc, QWidget *parent = 0);
    SegmentInfo (Side loc, RiverSegment *seg, QWidget *parent = 0);
    ~SegmentInfo();
    
    Ui::SegmentInfo *ui;

    RiverSegment *segment;

public slots:
    void addSegment (RiverSegment *seg);
    void gotoClicked();
    void hideName (bool flag = true);
    void hideButton (bool flag = true);

signals:
    void gotoSegment (RiverSegment *seg);

protected:
    void setup(Side loc);
    Side side;
};
/*
class UpperSegmentInfo : public SegmentInfo
{
    Q_OBJECT

public:
    explicit UpperSegmentInfo (QWidget *parent = 0);
    UpperSegmentInfo (RiverSegment *seg, QWidget *parent = 0);
    ~UpperSegmentInfo();

public slots:
    void addSegment (RiverSegment *seg);

};

class LowerSegmentInfo : public SegmentInfo
{
    Q_OBJECT

public:
    explicit LowerSegmentInfo (QWidget *parent = 0);
    LowerSegmentInfo (RiverSegment *seg, QWidget *parent = 0);
    ~LowerSegmentInfo();

public slots:
    void addSegment (RiverSegment *seg);

};*/

#endif // SEGMENTINFO_H
