#include "reachdetaildialog.h"
#include "ui_reachDetailDialog.h"

#include "segmentViews.h"

ReachDetailDialog::ReachDetailDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReachDetailDialog)
{
    ui->setupUi(this);
    connect (ui->doubleSpinBox_lowerElev, SIGNAL(valueChanged(double)), SLOT(changeLowerElev(double)));
    connect (ui->doubleSpinBox_lowerDepth, SIGNAL(valueChanged(double)), SLOT(changeLowerDepth(double)));
    connect (ui->doubleSpinBox_lowerWidth, SIGNAL(valueChanged(double)), SLOT(changeWidth(double)));
    connect (ui->doubleSpinBox_slope, SIGNAL(valueChanged(double)), SLOT(changeSlope(double)));
    connect (ui->doubleSpinBox_upperDepth, SIGNAL(valueChanged(double)), SLOT(changeUpperDepth(double)));

    connect (ui->pushButton_save, SIGNAL(clicked()), SLOT(saveData()));
    connect (ui->pushButton_revert, SIGNAL(clicked()), SLOT(resetData()));

    reach = NULL;

    topView = new SeeView (this);
    connect (topView, SIGNAL(scaleChanged(float)), SLOT(setScale(float)));
//    topViewDown = new SeeView (this);
//    connect (topViewDown, SIGNAL(scaleChanged(float)), SLOT(setScale(float)));
    segTopView = new ReachTopViewItem (NULL) ;
    segUpTopView = new ReachTopViewItem (segTopView);
    segDownTopView = new ReachTopViewItem (segTopView);
    segUpDamTopView = new QGraphicsRectItem (segTopView);
    segDownDamTopView = new QGraphicsRectItem (segTopView);
    topView->addItem(segTopView);
/*    topView->addItem(segUpTopView);
    topView->addItem(segDownTopView);
    topView->addItem(segUpDamTopView);
    topView->addItem(segDownDamTopView);*/
//    topViewDown->addItem(segTopView);
//    topViewDown->addItem(segDownTopView);
    ui->graphicsView_up_top->setScene(topView);
    ui->graphicsView_down_top->setScene(topView);//topViewDown);

    sideView = new SeeView (this);
    connect (sideView, SIGNAL(scaleChanged(float)), SLOT(setScale(float)));
//    sideViewDown = new SeeView (this);
//    connect (sideViewDown, SIGNAL(scaleChanged(float)), SLOT(setScale(float)));
    segSideView = new ReachSideViewItem (NULL);
    segUpSideView = new ReachSideViewItem (segSideView);
    segDownSideView = new ReachSideViewItem (segSideView);
    segUpDamSideView = new QGraphicsRectItem (segSideView);
    segDownDamSideView = new QGraphicsRectItem (segSideView);
    sideView->addItem(segSideView);
/*    sideView->addItem(segUpSideView);
//    sideViewDown->addItem(segSideView);
    sideView->addItem(segDownSideView);
    sideView->addItem(segUpDamSideView);
    sideView->addItem(segDownDamSideView);*/
    ui->graphicsView_up_side->setScene(sideView);
    ui->graphicsView_down_side->setScene(sideView);

    secViewUpper = new SeeView (this);
    connect (secViewUpper, SIGNAL(scaleChanged(float)), SLOT(setScale(float)));
    segSectionUpper = new ReachSectionItem (NULL);
    segUpSectionLower = new ReachSectionItem (segSectionUpper);
    segDamSectionLower = new QGraphicsRectItem (segSectionUpper);
    secViewUpper->addItem(segSectionUpper);
/*    secViewUpper->addItem(segUpSectionLower);
    secViewUpper->addItem(segDamSectionLower);*/
    ui->graphicsView_up_section->setScene(secViewUpper);

    secViewLower = new SeeView (this);
    connect (secViewLower, SIGNAL(scaleChanged(float)), SLOT(setScale(float)));
    segSectionLower = new ReachSectionItem (NULL);
    segDownSectionUpper = new ReachSectionItem (segSectionLower);
    segDamSectionUpper = new QGraphicsRectItem (segSectionLower);
    secViewLower->addItem(segSectionLower);
/*    secViewLower->addItem(segDownSectionUpper);
    secViewLower->addItem(segDamSectionUpper);*/
    ui->graphicsView_down_section->setScene(secViewLower);

    drawPen = QPen(Qt::darkGray, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    segUpDamTopView->setPen(drawPen);
    segDownDamTopView->setPen(drawPen);
    segUpDamSideView->setPen(drawPen);
    segDownDamSideView->setPen(drawPen);
    segDamSectionUpper->setPen(drawPen);
    segDamSectionLower->setPen(drawPen);

    scaleFactor = 1.0;
    canAddViews = false;
}

ReachDetailDialog::~ReachDetailDialog()
{
    delete ui;
}

void ReachDetailDialog::setSegment(RiverSegment *seg)
{
    reach = (Reach *)seg;
    canAddViews = false;
    if (reach != NULL)
    {
        setData();
        updateViews();
    }
}

void ReachDetailDialog::setData()
{
    float uprArea = 0.0;
    float lwrArea = 0.0;

    if (reach != NULL)
    {
        length = reach->length * 528.0;
        width = reach->width;
        ave_depth = reach->ave_depth;
        lower_elevation = reach->lower_elev;
        lower_depth = reach->lower_depth;
        lower_width = reach->lower_width;
        upper_elevation = reach->upper_elev;
        upper_depth = reach->upper_depth;
        upper_width = reach->upper_width;
        bed_width = reach->bed_width;
        slope = reach->slope;
        ui->doubleSpinBox_width->setValue(reach->width);
        ui->doubleSpinBox_slope->setValue(reach->slope);
        ui->doubleSpinBox_lowerElev->setValue(reach->lower_elev);
        ui->doubleSpinBox_lowerDepth->setValue(reach->lower_depth);
        ui->doubleSpinBox_upperElev->setValue(reach->upper_elev);
        ui->doubleSpinBox_upperDepth->setValue(reach->upper_depth);
        ui->label_lengthValue->setText(QString("%1 mi.").arg(QString::number(reach->length, 'f', 2)));
        calcData();
    }
}

void ReachDetailDialog::calcData()
{
    ave_depth = (lower_depth + upper_depth) / 2.0;
//    ui->doubleSpinBox_width->setValue(ave_depth);

    slp_tan = tan(slope * DEG_2_RAD);
    bed_width = lower_width - 2.0 * (slp_tan * lower_depth);
    ui->doubleSpinBox_lowerWidth->setValue(lower_width);

    width = bed_width + 2.0 * (slp_tan * ave_depth);
    ui->doubleSpinBox_bed_width->setValue (bed_width);

    upper_width = bed_width + 2.0 * (slp_tan * upper_depth);
    ui->doubleSpinBox_upperWidth->setValue(upper_width);

    lower_area = lower_depth * ((lower_width - bed_width)/2.0 + bed_width);
    ui->label_lowerAreaValue->setText(QString::number(lower_area, 'f', 2));

    upper_area = upper_depth * ((upper_width - bed_width)/2.0 + bed_width);
    ui->label_upperAreaValue->setText(QString::number(upper_area, 'f', 2));

    canAddViews = true;
}

void ReachDetailDialog::setItems()
{
    Reach *upReach;
    Reach *downReach;

    up_offset = 2.0;
    down_offset = 2.0;

    if (reach != NULL && canAddViews)
    {
        upReach = (Reach *)(reach->up);
        downReach = (Reach *)(reach->down);
        segTopView->setValues (length / scaleFactor,
                               (upper_width / 10.0) / scaleFactor,
                               (lower_width / 10.0) / scaleFactor,
                               (bed_width / 10.0) / scaleFactor,
                               0.0);
        ui->graphicsView_up_top->setSceneRect((length / scaleFactor) - 40.0,
                                              -300.0 / scaleFactor,
                                              80.0,
                                              600.0 / scaleFactor);
        ui->graphicsView_down_top->setSceneRect(-40.0,
                                                -300.0 / scaleFactor,
                                                80.0,
                                                600.0 / scaleFactor);

        segSideView->setValues(length / scaleFactor,
                               upper_elevation / scaleFactor,
                               lower_elevation / scaleFactor,
                               upper_depth / scaleFactor,
                               lower_depth / scaleFactor,
                               0.0);
        ui->graphicsView_up_side->setSceneRect((length / scaleFactor) - 40.0,
                                 -(upper_elevation - 20.0) / scaleFactor,
                                 80.0,
                                 -(upper_depth + 20.0) / scaleFactor);
        ui->graphicsView_down_side->setSceneRect(-40.0,
                                   -(lower_elevation - 20.0) / scaleFactor,
                                   80.0,
                                   -(lower_depth + 20.0) / scaleFactor);

        segSectionUpper->setValues((upper_width / 10.0) / scaleFactor,
                                   upper_depth / scaleFactor,
                                   (bed_width / 10.0) / scaleFactor,
                                   (upper_elevation) / scaleFactor);
        ui->graphicsView_up_section->setSceneRect(((-upper_width/2.0) / 10.0) / scaleFactor,
                                   -(upper_elevation - 20.0) / scaleFactor,
                                   (upper_width / 10.0) / scaleFactor,
                                   -(upper_depth + 40.0) / scaleFactor);

        segSectionLower->setValues((lower_width / 10.0) / scaleFactor,
                                   lower_depth / scaleFactor,
                                   (bed_width / 10.0) / scaleFactor,
                                   lower_elevation / scaleFactor);
        ui->graphicsView_down_section->setSceneRect(((-lower_width/2.0) / 10.0) / scaleFactor,
                                   -(lower_elevation - 20.0) / scaleFactor,
                                   (lower_width / 10.0) / scaleFactor,
                                   -(lower_depth + 40.0) / scaleFactor);

        if (upReach != NULL &&
                upReach->type == RiverSegment::DamSegment)
        {
            up_offset = 6.0;
            segUpDamTopView->setRect(length / scaleFactor + 2.0,
                             -(upReach->upper_width / 10.0 + 2.0) / 2.0 / scaleFactor,
                             2.0,
                             (upReach->upper_width / 10.0 + 4.0) / scaleFactor);
            segUpDamSideView->setRect(length / scaleFactor + 2.0,
                                    -(upReach->upper_elev - 2.0) / scaleFactor,
                                    2.0,
                                    -(upReach->upper_depth + 4.0) / scaleFactor);
            segDamSectionLower->setRect(-(upReach->lower_width / 10.0 / 2.0) / scaleFactor,
                                        -(upReach->lower_elev / scaleFactor),
                                        (upReach->lower_width / 10.0 / scaleFactor),
                                        -(upReach->upper_depth / scaleFactor));
            upReach= (Reach *)(reach->up->up);
        }
        else
        {
            segUpDamTopView->setRect(0,0,0,0);
            segUpDamSideView->setRect(0,0,0,0);
            segDamSectionLower->setRect(0,0,0,0);
        }

        if (upReach == NULL)
        {
            segUpTopView->setValues(0, 0, 0, 0, 0);
            segUpSideView->setValues(0, 0, 0, 0, 0, 0);
            segUpSectionLower->setValues(0, 0, 0, 0);
        }
        else
        {
            float upReachLength = upReach->length * 528.0;
            segUpTopView->setValues (upReachLength / scaleFactor,
                                     upReach->upper_width / 10.0 / scaleFactor,
                                     upReach->lower_width / 10.0 / scaleFactor,
                                     upReach->bed_width / 10.0 / scaleFactor,
                                     length / scaleFactor + up_offset);
            segUpSideView->setValues(upReachLength / scaleFactor,
                                     upReach->upper_elev / scaleFactor,
                                     upReach->lower_elev / scaleFactor,
                                     upReach->upper_depth / scaleFactor,
                                     upReach->lower_depth / scaleFactor,
                                     length / scaleFactor + up_offset);
            segUpSectionLower->setValues(upReach->lower_width / 10.0 / scaleFactor,
                                         upReach->lower_depth / scaleFactor,
                                         upReach->bed_width / 10.0 / scaleFactor,
                                         upReach->lower_elev / scaleFactor);
        }

        if (downReach != NULL &&
                downReach->type == RiverSegment::DamSegment)
        {
            down_offset = 6.0;
            segDownDamTopView->setRect(-4.0,
                             -(downReach->lower_width / 10.0 / 2.0 + 2.0) / scaleFactor,
                             2.0,
                             (downReach->lower_width / 10.0 + 4.0) / scaleFactor);
            segDownDamSideView->setRect(-4.0,
                                    -(downReach->lower_elev - 2.0) / scaleFactor,
                                    2.0,
                                    -(downReach->upper_depth + 4.0) / scaleFactor);
            segDamSectionUpper->setRect(-(downReach->lower_width / 10.0 / 2.0) / scaleFactor,
                                        -(downReach->lower_elev / scaleFactor),
                                        (downReach->lower_width / 10.0 / scaleFactor),
                                        -(downReach->upper_depth / scaleFactor));
            downReach= (Reach *)(reach->down->down);
        }
        else
        {
            segDownDamTopView->setRect(0,0,0,0);
            segDownDamSideView->setRect(0,0,0,0);
            segDamSectionUpper->setRect(0,0,0,0);
        }

        if (downReach == NULL)
        {
            segDownTopView->setValues(0, 0, 0, 0, 0);
            segDownSideView->setValues(0, 0, 0, 0, 0, 0);
            segDownSectionUpper->setValues(0, 0, 0, 0);
        }
        else
        {
            float downReachLength = downReach->length * 528.0;
            segDownTopView->setValues(downReachLength / scaleFactor,
                                      downReach->upper_width / 10.0 / scaleFactor,
                                      downReach->lower_width / 10.0 / scaleFactor,
                                      downReach->bed_width / 10.0 / scaleFactor,
                                      -downReachLength / scaleFactor - down_offset);
            segDownSideView->setValues(downReachLength / scaleFactor,
                                       downReach->upper_elev / scaleFactor,
                                       downReach->lower_elev / scaleFactor,
                                       downReach->upper_depth / scaleFactor,
                                       downReach->lower_depth / scaleFactor,
                                       -downReachLength / scaleFactor - down_offset);
            segDownSectionUpper->setValues(downReach->upper_width / 10.0 / scaleFactor,
                                           downReach->upper_depth / scaleFactor,
                                           downReach->bed_width / 10.0 / scaleFactor,
                                           downReach->upper_elev / scaleFactor);
        }
    }
}

void ReachDetailDialog::changeLowerElev(double elev)
{
    lower_elevation = elev;
//    if (canAddViews)
    {
        calcData();
        updateViews();
    }
}

void ReachDetailDialog::changeLowerDepth(double dep)
{
    lower_depth = dep;
//    if (canAddViews)
    {
        calcData();
        updateViews();
    }
}

void ReachDetailDialog::changeUpperDepth(double dep)
{
    upper_depth = dep;
//    if (canAddViews)
    {
        calcData();
        updateViews();
    }
}

void ReachDetailDialog::changeWidth(double wid)
{
    lower_width = wid;
//    if (canAddViews)
    {
        calcData();
        updateViews();
    }
}

void ReachDetailDialog::changeSlope(double deg)
{
    slope = deg;
    slp_tan = tan(slope * DEG_2_RAD);
//    if (canAddViews)
    {
        calcData();
        updateViews();
    }
}

void ReachDetailDialog::updateViews()
{
    topView->removeItem(segTopView);
/*    topView->removeItem(segDownTopView);
    topView->removeItem(segUpTopView);
    topView->removeItem(segUpDamTopView);
    topView->removeItem(segDownDamTopView);*/
    topView->update();

    sideView->removeItem(segSideView);
/*    sideView->removeItem(segUpSideView);
    sideView->removeItem(segDownSideView);
    sideView->removeItem(segUpDamSideView);
    sideView->removeItem(segDownDamSideView);*/
    sideView->update();

    secViewUpper->removeItem(segSectionUpper);
/*    secViewUpper->removeItem(segUpSectionLower);
    secViewUpper->removeItem(segDamSectionLower);*/
    secViewUpper->update();

    secViewLower->removeItem(segSectionLower);
/*    secViewLower->removeItem(segDownSectionUpper);
    secViewLower->removeItem(segDamSectionUpper);*/
    secViewLower->update();

    setItems();

    topView->addItem(segTopView);
/*    topView->addItem(segUpTopView);
    topView->addItem(segDownTopView);
    topView->addItem(segUpDamTopView);
    topView->addItem(segDownDamTopView);*/
    topView->update();

    sideView->addItem(segSideView);
/*    sideView->addItem(segUpSideView);
    sideView->addItem(segDownSideView);
    sideView->addItem(segUpDamSideView);
    sideView->addItem(segDownDamSideView);*/
    sideView->update();

    secViewUpper->addItem(segSectionUpper);
/*    secViewUpper->addItem(segUpSectionLower);
    secViewUpper->addItem(segDamSectionLower);*/
    secViewUpper->update();

    secViewLower->addItem(segSectionLower);
/*    secViewLower->addItem(segDownSectionUpper);
    secViewLower->addItem(segDamSectionUpper);*/
    secViewLower->update();
}

void ReachDetailDialog::saveData()
{
    reach->width = width;
    reach->ave_depth = ave_depth;
    reach->lower_elev = lower_elevation;
    reach->lower_depth = lower_depth;
    reach->lower_width = lower_width;
    reach->slope = slope;
    reach->upper_elev = upper_elevation;
    reach->upper_depth = upper_depth;
    reach->upper_width = upper_width;
    reach->bed_width = bed_width;
    reach->construct();
    if (reach->up != NULL)
        construct(reach->up);
    if (reach->down != NULL)
        construct(reach->down);
    emit dataChanged();
}

void ReachDetailDialog::construct(RiverSegment *seg)
{
    Dam *dm; Reach *rch;

    switch (seg->type)
    {
    case RiverSegment::DamSegment:
        dm = (Dam *) seg;
        dm->construct();
        break;
    case RiverSegment::ReachSegment:
        rch = (Reach *)seg;
        rch->construct();
        break;
    case RiverSegment::HeadwaterSegment:
    default:
        seg->construct();
        break;
    }
}

void ReachDetailDialog::resetData()
{
    canAddViews = false;
    setData();
    updateViews();
}

void ReachDetailDialog::setScale(float sc)
{
    qreal halfFactor = scaleFactor * 0.5;
    if (sc > 0.0)
        scaleFactor += 0.5;
    else
        scaleFactor -= 0.5;//halfFactor * 0.5;

    if (scaleFactor < 1.0)
        scaleFactor = 1.0;

    updateViews();
}

