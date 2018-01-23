#ifndef DAMDETAILDIALOG_H
#define DAMDETAILDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QGraphicsScene>

#include "Dam.h"
#include "seeview.h"
#include "segmentViews.h"
#include "segmentinfo.h"

namespace Ui {
class DamDetailDialog;
}

class DamDetailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DamDetailDialog(QWidget *parent = 0);
    ~DamDetailDialog();

private:
    Ui::DamDetailDialog *ui;
    Dam *dam;

    // editable values
    float floor_elev;
    float tailrace_elev;
    float tailrace_length;
    float forebay_elev;
    float bypass_elev;
    float basin_length;
    int gate_num;
    float gate_width;
    float gate_flow;
    float spill_width;
    Location spill_side;
    float SGR;
    // derived values
    float lower_elev;
    float lower_depth;
    float lower_width;
    float upper_elev;
    float upper_depth;
    float upper_width;

    QPen backgroundPen;
    QPen spillPen;

    SeeView *topView;
    DamTopViewItem *segTopView;
    ReachTopViewItem *segUpTopView;
    ReachTopViewItem *segDownTopView;

    SeeView *sideView;
    DamSideViewItem *segSideView;
    ReachSideViewItem *segUpSideView;
    ReachSideViewItem *segDownSideView;

    SeeView *sectionView;
    DamSectionItem *segSectionView;
    ReachSectionItem *segUpSectionView;
    ReachSectionItem *segDownSectionView;

    SegmentInfo *segInfoUp;
    SegmentInfo *segInfoDown;

    void setData ();
    void calcData ();
    void construct (RiverSegment *seg);

    void setItems ();
    void updateViews();

    float scaleFactor;

public slots:
    void setSegment (RiverSegment *seg);

    void changeBasinLength (double len);
    void changeGateNumber (int num);
    void changeGateWidth (double wid);
    void changeBypassElev (double elev);
    void changeFBayElev (double elev);
    void changeFloorElev (double elev);
    void changeSpillWidth (double wid);
    void changeSpillSide (QString loc);
    void changeTailRaceElev (double elev);
    void changeSGR (double sgr);

    void saveData();
    void resetData();

    void setScale (float sc);

signals:
    void dataChanged();
};


#endif // DAMDETAILDIALOG_H
