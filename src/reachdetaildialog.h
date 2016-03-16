#ifndef REACHDETAILDIALOG_H
#define REACHDETAILDIALOG_H

#include <QtGui/QWidget>
#include <QtGui/QDialog>
#include <QtGui/QGraphicsScene>

#include "Reach.h"
#include "seeview.h"
#include "segmentViews.h"


namespace Ui {
class ReachDetailDialog;
}

class ReachDetailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReachDetailDialog(QWidget *parent = 0);
    ~ReachDetailDialog();

//    void addSegment (RiverSegment *seg);

private:
    Ui::ReachDetailDialog *ui; /**< The Qt Designer form */

    Reach *reach;          /**< Reference to Reach river segment */
    // given values
    float length;          /**< Length of the segment in feet (read-only) */
    float width;           /**< Average width of segment (editable) */
    float ave_depth;       /**< Average depth of segment (not shown) */
    float lower_elevation; /**< Elevation of down stream end of segment (editable) */
    float lower_depth;     /**< Depth of down stream end of segment (editable) */
    float lower_width;     /**< Width of down stream end of segment (read-only) */
    float upper_elevation; /**< Elevation of up stream end of segment (read-only) */
    float upper_depth;     /**< Depth of down stream end of segment (editable) */
    float slope;           /**< Slope of sides of segment (editable) */
    // derived values
    float slp_tan;         /**< Tangent of slope (calculated) */
    float lower_area;      /**< Area of down stream end of segment (read-only) */
    float bed_width;       /**< Width of stream bed of segment (read-only) */
    float upper_width;     /**< Width of up stream end of segment (read-only) */
    float upper_area;      /**< Area of up stream end of segment (read-only) */


    float up_offset;
    float down_offset;

    SeeView *topView;
    ReachTopViewItem *segUpTopView;
    ReachTopViewItem *segTopView;
    ReachTopViewItem *segDownTopView;
    QGraphicsRectItem *segUpDamTopView;
    QGraphicsRectItem *segDownDamTopView;

    SeeView *sideView;
    ReachSideViewItem *segUpSideView;
    ReachSideViewItem *segSideView;
    ReachSideViewItem *segDownSideView;
    QGraphicsRectItem *segUpDamSideView;
    QGraphicsRectItem *segDownDamSideView;

    SeeView *secViewUpper;
    ReachSectionItem *segSectionUpper;
    ReachSectionItem *segUpSectionLower;
    QGraphicsRectItem *segDamSectionLower;

    SeeView *secViewLower;
    ReachSectionItem *segSectionLower;
    ReachSectionItem *segDownSectionUpper;
    QGraphicsRectItem *segDamSectionUpper;

    void setData();
    void calcData();
    void construct (RiverSegment *seg);

    void setItems();
    void updateViews();
    QPen drawPen;

    qreal scaleFactor;
    bool canAddViews;

public slots:
    void setSegment (RiverSegment *seg);

    void changeLowerElev (double elev);
    void changeLowerDepth (double dep);
    void changeUpperDepth (double dep);
    void changeWidth (double wid);
    void changeSlope (double deg);

    void saveData();
    void resetData();

    void setScale (float sc);

signals:
    void dataChanged();
};


#endif // REACHDETAILDIALOG_H
