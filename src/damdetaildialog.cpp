#include "damdetaildialog.h"
#include "ui_damDetailDialog.h"
#include "Dam.h"
#include "Reach.h"

DamDetailDialog::DamDetailDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DamDetailDialog)
{
    ui->setupUi(this);

    segInfoUp = new SegmentInfo(SegmentInfo::Upper, this);
    segInfoUp->hideName();
    segInfoUp->hideButton();
    segInfoUp->hideFrame();
    ui->verticalLayout_up->addWidget(segInfoUp);
    segInfoDown = new SegmentInfo (SegmentInfo::Lower, this);
    segInfoDown->hideName();
    segInfoDown->hideButton();
    segInfoDown->hideFrame();
    ui->verticalLayout_down->addWidget(segInfoDown);

    ui->comboBox_spillSide->addItem ("Right");
    ui->comboBox_spillSide->addItem ("Left");
    ui->comboBox_spillSide->setCurrentIndex (0);
    connect (ui->doubleSpinBox_basinLength, SIGNAL(valueChanged(double)), SLOT(changeBasinLength(double)));
    connect (ui->spinBox_gateNum, SIGNAL(valueChanged(int)), SLOT(changeGateNumber(int)));
    connect (ui->doubleSpinBox_gateWidth, SIGNAL(valueChanged(double)), SLOT(changeGateWidth(double)));
    connect (ui->doubleSpinBox_bypassElev, SIGNAL(valueChanged(double)), SLOT(changeBypassElev(double)));
    connect (ui->doubleSpinBox_fbayElev, SIGNAL(valueChanged(double)), SLOT(changeFBayElev(double)));
    connect (ui->doubleSpinBox_floorElev, SIGNAL(valueChanged(double)), SLOT(changeFloorElev(double)));
    connect (ui->doubleSpinBox_spillWidth, SIGNAL(valueChanged(double)), SLOT(changeSpillWidth(double)));
    connect (ui->doubleSpinBox_traceElev, SIGNAL(valueChanged(double)), SLOT(changeTailRaceElev(double)));
    connect (ui->doubleSpinBox_SGR, SIGNAL(valueChanged(double)), SLOT(changeSGR(double)));
    connect (ui->comboBox_spillSide, SIGNAL(currentIndexChanged(QString)), SLOT(changeSpillSide(QString)));

    connect (ui->pushButton_save, SIGNAL(clicked()), SLOT(saveData()));
    connect (ui->pushButton_revert, SIGNAL(clicked()), SLOT(resetData()));

    dam = nullptr;

    topView = new SeeView (this);
    connect (topView, SIGNAL(scaleChanged(float)), SLOT(setScale(float)));
    segTopView = new DamTopViewItem (nullptr);
    segUpTopView = new ReachTopViewItem (segTopView);
    segDownTopView = new ReachTopViewItem (segTopView);
    topView->addItem(segTopView);
//    topView->addItem(segUpTopView);
//    topView->addItem(segDownTopView);
    ui->graphicsView_top->setScene(topView);

    sideView = new SeeView (this);
    connect (sideView, SIGNAL(scaleChanged(float)), SLOT(setScale(float)));
    segSideView = new DamSideViewItem (nullptr);
    segUpSideView = new ReachSideViewItem(segSideView);
    segDownSideView = new ReachSideViewItem (segSideView);
    sideView->addItem(segSideView);
/*    sideView->addItem(segUpSideView);
    sideView->addItem(segDownSideView);*/
    ui->graphicsView_side->setScene(sideView);

    sectionView = new SeeView (this);
    connect (sectionView, SIGNAL(scaleChanged(float)), SLOT(setScale(float)));
    segSectionView = new DamSectionItem (nullptr);
    segUpSectionView = new ReachSectionItem (segSectionView);
    segDownSectionView = new ReachSectionItem (segSectionView);
    sectionView->addItem(segSectionView);
/*    sectionView->addItem(segUpSectionView);
    sectionView->addItem(segDownSectionView);*/
    ui->graphicsView_a->setScene(sectionView);

    backgroundPen = QPen(Qt::darkGray, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    spillPen = QPen(Qt::blue, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    scaleFactor = 1.0;
}

DamDetailDialog::~DamDetailDialog()
{
    delete segTopView;
    delete segSideView;
    delete segSectionView;

    delete ui;
}


void DamDetailDialog::setSegment(RiverSegment *seg)
{
    dam = (Dam *)seg;

    segInfoUp->addSegment(seg);
    segInfoDown->addSegment(seg);

    setData ();
    calcData();
    updateViews();
}

void DamDetailDialog::setData()
{
    if (dam != nullptr)
    {
        floor_elev = dam->getFloorElev();//dam->floorElev;
        tailrace_elev = dam->getTailraceElev();//dam->tailraceElev;
        tailrace_length = 1000.0;//dam->basin_length * 2.0;
        forebay_elev = dam->getForebayElev();// dam->forebayElev;
        bypass_elev = dam->getBypassElev();// dam->bypassElev;
        basin_length = dam->getStillingLength();// dam->stillingLength;
        gate_num = dam->getNgates();// dam->ngates;
        gate_width = dam->getGateWidth();// dam->gateWidth;
        gate_flow = dam->getPergate();// dam->pergate;
        spill_width = dam->getSpillwayWidth();// dam->spillwayWidth;
        spill_side = dam->getSpillSide();// dam->spillSide;
        SGR = dam->getSgr();// dam->sgr;

        ui->doubleSpinBox_SGR->setValue(SGR);
        if (dam->getNumPowerhouses() > 0)
            ui->doubleSpinBox_PH1Cap->setValue(dam->getPowerhouses().at(0)->getCapacity());// powerhouse_cap.at(0));
        else
            ui->doubleSpinBox_PH1Cap->setValue(0.0);
        if (dam->getNumPowerhouses() > 1)
            ui->doubleSpinBox_PH2Cap->setValue(dam->getPowerhouses().at(1)->getCapacity());// powerhouse_cap.at(1));
        else
            ui->doubleSpinBox_PH2Cap->setValue(0.0);
        ui->doubleSpinBox_basinLength->setValue(basin_length);
        ui->doubleSpinBox_bypassElev->setValue(bypass_elev);
        ui->doubleSpinBox_fbayElev->setValue(forebay_elev);
        ui->doubleSpinBox_floorElev->setValue(floor_elev);
        ui->doubleSpinBox_traceElev->setValue(tailrace_elev);
        ui->spinBox_gateNum->setValue(gate_num);
        ui->doubleSpinBox_gateWidth->setValue(gate_width);
        ui->doubleSpinBox_spillWidth->setValue(spill_width);
        ui->comboBox_spillSide->setCurrentIndex (spill_side);
    }
}

void DamDetailDialog::calcData()
{
    ui->doubleSpinBox_spillWidValue->setValue(gate_num * gate_width);
//    ui->label_spillwyWidthValue->setText (QString::number(
//                         (gate_num * gate_width), 'f', 2));

    upper_depth = forebay_elev - floor_elev;
}

void DamDetailDialog::setItems()
{
    Reach *upReach;
    Reach *downReach;

    float dam_length = 20.0;
    float up_offset = dam_length / scaleFactor + 2.0;
    float down_offset = (tailrace_length / 10.0) / scaleFactor + 2.0;

    if (dam != nullptr)
    {
        upReach = (Reach *)dam->up;
        downReach = (Reach *)dam->down;

        segTopView->setValues(dam_length / scaleFactor,
                              (dam->lowerWidth / 10.0) / scaleFactor,
                              basin_length / 10.0 / scaleFactor,
                              tailrace_length / 10.0 / scaleFactor,
                              gate_num,
                              (gate_width / 10.0) / scaleFactor,
                              spill_side,
                              0.0);
        ui->graphicsView_top->setSceneRect(-100.0,
                                           -400.0 / scaleFactor,
                                           200.0,
                                           800.0 / scaleFactor);

        segSideView->setValues(dam_length / scaleFactor,
                               forebay_elev / scaleFactor,
                               tailrace_elev / scaleFactor,
                               (basin_length / 10.0) / scaleFactor,
                               tailrace_length / 10.0 / scaleFactor,
                               bypass_elev / scaleFactor,
                               floor_elev / scaleFactor,
                               0.0);
        ui->graphicsView_side->setSceneRect(-40.0,
                                            -forebay_elev / scaleFactor, //(floor_elev / scaleFactor - 10.0),
                                            80.0,
                                            upper_depth / scaleFactor);//-(upper_depth / scaleFactor + 20.0));

        segSectionView->setValues((dam->lowerWidth / 10.0) / scaleFactor,
                                  (forebay_elev - floor_elev) / scaleFactor,
                                  gate_num,
                                  (gate_width / 10.0) / scaleFactor,
                                  spill_side,
                                  tailrace_elev / scaleFactor,
                                  bypass_elev / scaleFactor,
                                  floor_elev / scaleFactor);
        ui->graphicsView_a->setSceneRect(-400.0 / scaleFactor,
                                         -forebay_elev / scaleFactor, //(floor_elev / scaleFactor - 10.0),
                                         800.0 / scaleFactor,
                                         upper_depth / scaleFactor);//-(upper_depth / scaleFactor + 20.0));
        if (upReach != nullptr)
        {
            float upReachLength = upReach->length * 528.0;
            segUpTopView->setValues(upReachLength / scaleFactor,
                                    upReach->upperWidth / 10.0 / scaleFactor,
                                    upReach->lowerWidth / 10.0 / scaleFactor,
                                    upReach->bedWidth / 10.0 / scaleFactor,
                                    up_offset);
            segUpSideView->setValues(upReachLength / scaleFactor,
                                     upReach->upperElev / scaleFactor,
                                     upReach->lowerElev / scaleFactor,
                                     upReach->upperDepth / scaleFactor,
                                     upReach->lowerDepth / scaleFactor,
                                     up_offset);
            segUpSectionView->setValues(upReach->lowerWidth / 10.0 / scaleFactor,
                                        upReach->lowerDepth / scaleFactor,
                                        upReach->bedWidth / 10.0 / scaleFactor,
                                        upReach->lowerElev / scaleFactor);
        }
        else
        {
            segUpTopView->setValues(0,0,0,0,0);
            segUpSideView->setValues(0,0,0,0,0,0);
            segUpSectionView->setValues(0,0,0,0);
        }

        if (downReach != nullptr)
        {
            float downReachLength = downReach->length * 5280.0 / 10.0;
            segDownTopView->setValues(downReachLength / scaleFactor,
                                      downReach->upperWidth / 10.0 / scaleFactor,
                                      downReach->lowerWidth / 10.0 / scaleFactor,
                                      downReach->bedWidth / 10.0 / scaleFactor,
                                      -(downReachLength / scaleFactor + down_offset));
            segDownSideView->setValues(downReachLength / scaleFactor,
                                       downReach->upperElev / scaleFactor,
                                       downReach->lowerElev / scaleFactor,
                                       downReach->upperDepth / scaleFactor,
                                       downReach->lowerDepth / scaleFactor,
                                       -(downReachLength / scaleFactor + down_offset));
            segDownSectionView->setValues(downReach->upperWidth / 10.0 / scaleFactor,
                                          downReach->upperDepth / scaleFactor,
                                          downReach->bedWidth / 10.0 / scaleFactor,
                                          downReach->upperElev / scaleFactor);
        }
        else
        {
            segDownTopView->setValues(0,0,0,0,0);
            segDownSideView->setValues(0,0,0,0,0,0);
            segDownSectionView->setValues(0,0,0,0);
        }
    }
}

void DamDetailDialog::updateViews()
{
    topView->removeItem(segTopView);
/*    topView->removeItem(segUpTopView);
    topView->removeItem(segDownTopView);*/

    sideView->removeItem(segSideView);
/*    sideView->removeItem(segUpSideView);
    sideView->removeItem(segDownSideView);*/

    sectionView->removeItem(segSectionView);
/*    sectionView->removeItem(segUpSectionView);
    sectionView->removeItem(segDownSectionView);*/

    topView->update();
    sideView->update();
    sectionView->update();

    setItems();
    calcData();

    topView->addItem(segTopView);
/*    topView->addItem(segUpTopView);
    topView->addItem(segDownTopView);*/

    sideView->addItem(segSideView);
/*    sideView->addItem(segUpSideView);
    sideView->addItem(segDownSideView);*/

    sectionView->addItem(segSectionView);
/*    sectionView->addItem(segUpSectionView);
    sectionView->addItem(segDownSectionView);*/

    ui->graphicsView_top->setSceneRect(-100, -400, 200, 800);


/*    if (dam != nullptr)
    {
        ui->graphicsView_top->setScene(topView());
        ui->graphicsView_side->setScene(sideView());
        ui->graphicsView_a->setScene(sectionA());
    }*/
}
/*
SeeView * DamDetailDialog::topView()
{
    float width = dam->width;
    if (dam->up != nullptr && width < dam->up->width)
        width = dam->up->width;
    if (width < dam->down->upper_width)
        width = dam->down->upper_width;

    if (top != nullptr)
        delete top;
    top = new SeeView(this);
    connect (top, SIGNAL(scaleChanged(int)), SLOT(scale(int)));

    top->addPath(drawDamTop_back(), backgroundPen);
//    top->addPath(drawSegTop (dam->down));
//    top->addPath(drawSegTop (dam->up));

    top->addPath(drawDamTop_spill(), spillPen);

    top->setSceneRect(-ui->doubleSpinBox_basinLength->value()-10, -width/2.0 -10, ui->doubleSpinBox_basinLength->value()*2.0, width + 20);

    return top;
}

SeeView * DamDetailDialog::sideView()
{
    if (side != nullptr)
        delete side;
    side = new SeeView(this);
    connect (side, SIGNAL(scaleChanged(int)), SLOT(scale(int)));
    side->addPath(drawDamSide_back(), backgroundPen);
//    side->addPath(drawSegSide (dam->down));
//    side->addPath(drawSegSide (dam->up));

    side->addPath(drawDamSide_spill(), spillPen);

    side->setSceneRect(-ui->doubleSpinBox_basinLength->value()-10, -dam->floor_elev +40, ui->doubleSpinBox_basinLength->value()*2.0, -dam->forebay_elev-dam->upper_depth -40);

    return side;
}

SeeView * DamDetailDialog::sectionA()
{
//    float width = dam->width;
    if (dam->up != nullptr && width < dam->up->width)
        width = dam->up->width;
    if (width < dam->down->upper_width)
        width = dam->down->upper_width;

    if (secA != nullptr)
        delete secA;
    secA = new SeeView(this);
    connect (secA, SIGNAL(scaleChanged(int)), SLOT(scale(int)));
    secA->addPath(drawDamSecA_back(), backgroundPen);
//    secA->addPath(drawSegSecA (dam->down));
//    secA->addPath(drawSegSecA (dam->up));

    secA->addPath(drawDamSecA_spill(), spillPen);

    secA->setSceneRect(-width/2.0 -10, -dam->floor_elev + 40, width + 20, -dam->forebay_elev-dam->upper_depth - 40);

    return secA;
}
*/
void DamDetailDialog::changeBasinLength(double len)
{
    basin_length = len;
    tailrace_length = basin_length * 2.0;
    updateViews();
}

void DamDetailDialog::changeBypassElev(double elev)
{
    bypass_elev = elev;
    updateViews();
}

void DamDetailDialog::changeFBayElev(double elev)
{
    forebay_elev = elev;
    updateViews();
}

void DamDetailDialog::changeFloorElev(double elev)
{
    floor_elev = elev;
    updateViews();
}

void DamDetailDialog::changeGateNumber(int num)
{
    gate_num = num;
    calcData();
    updateViews();
}

void DamDetailDialog::changeGateWidth(double wid)
{
    gate_width = wid;
    calcData();
    updateViews();
}

void DamDetailDialog::changeSpillWidth(double wid)
{
    spill_width = wid;
    updateViews();
}

void DamDetailDialog::changeSpillSide(QString loc)
{
    if (loc.compare("Right") == 0)
        spill_side = Right;
    else if (loc.compare("Left") == 0)
        spill_side = Left;
    updateViews();
}

void DamDetailDialog::changeTailRaceElev(double elev)
{
    tailrace_elev = elev;
    updateViews();
}

void DamDetailDialog::changeSGR(double sgr)
{
    SGR = sgr;
    updateViews();
}

void DamDetailDialog::saveData()
{
    dam->setSgr(SGR);
    if (dam->getNumPowerhouses() > 0)
        dam->getPowerhouses().at(0)->setCapacity(ui->doubleSpinBox_PH1Cap->value());
//        dam->powerhouse_cap[0] = ui->doubleSpinBox_PH1Cap->value();
    if (dam->getNumPowerhouses() > 1)
        dam->getPowerhouses().at(1)->setCapacity(ui->doubleSpinBox_PH2Cap->value());
//        dam->powerhouse_cap[1] = ui->doubleSpinBox_PH2Cap->value();
    dam->setStillingLength(basin_length);// stillingLength = basin_length;
    dam->setBypassElev(bypass_elev);// bypassElev = bypass_elev;
    dam->setForebayElev(forebay_elev);// forebayElev = forebay_elev;
    dam->setFloorElev(floor_elev);// floorElev = floor_elev;
    dam->setTailraceElev(tailrace_elev);// tailraceElev = tailrace_elev;
    dam->setNgates(gate_num);// ngates = gate_num;
    dam->setGateWidth(gate_width);// gateWidth = gate_width;
    dam->setSpillwayWidth(spill_width);// spillwayWidth = spill_width;
    dam->setSpillSide(spill_side);// spillSide = spill_side;
    dam->construct();
    if (dam->up != nullptr)
        construct (dam->up);
    if (dam->down != nullptr)
        construct (dam->down);

    emit dataChanged();
}

void DamDetailDialog::construct(RiverSegment *seg)
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

void DamDetailDialog::resetData()
{
    setData();
    updateViews();
}

/*
QPainterPath DamDetailDialog::drawDamTop_back()
{
    QPainterPath damtop;
    float startPtY = -(dam->width / 2.0);
    double segwidth2, segupwidth2, seglength;

    damtop.moveTo(0.0, startPtY);
    damtop.addRect(0, -startPtY, 20.0, -dam->width);
    damtop.setFillRule(Qt::WindingFill);

    // draw down seg
    if (dam->down != nullptr)
    {
        segwidth2 = dam->down->width / 2.0;
        segupwidth2 = dam->down->upper_width / 2.0;
        seglength = dam->down->length * 5280.0;
        {
            QPainterPath downseg (QPointF(-20, -segupwidth2));
            downseg.lineTo(-seglength-20, -segwidth2);
            downseg.lineTo(-seglength-20, segwidth2);
            downseg.lineTo(-20, segupwidth2);
            downseg.lineTo(-20, -segupwidth2);
            damtop.addPath(downseg);
        }
    }

    // draw up seg
    if (dam->up != nullptr)
    {
        segwidth2 = dam->up->width / 2.0;
        segupwidth2 = dam->up->upper_width / 2.0;
        seglength = dam->up->length * 5280.0;
        {
            QPainterPath upseg (QPointF(20, -segwidth2));
            upseg.lineTo(seglength+20, -segupwidth2);
            upseg.lineTo(seglength+20, segupwidth2);
            upseg.lineTo(20, segwidth2);
            upseg.lineTo(20, -segwidth2);
            damtop.addPath(upseg);
        }
    }
    return damtop;
}

QPainterPath DamDetailDialog::drawDamTop_spill()
{
    QPainterPath damtop;
    float startPtY = -(dam->width / 2.0);
    double gatewidth = ui->doubleSpinBox_gateWidth->value();

    switch (ui->comboBox_spillSide->currentIndex())
    {
    case 0:
    {
        startPtY += dam->width - ui->doubleSpinBox_spillWidth->value();
        break;
    }
    case 1:
    default:
        break;
    }
    for (int i = 0; i < ui->spinBox_gateNum->value(); i++)
    {
        damtop.addRect(0, -startPtY - 2, 20, -gatewidth + 4);
        startPtY += gatewidth;
    }

    return damtop;
}

QPainterPath DamDetailDialog::drawDamSide_back()
{
    QPainterPath damside;
    double floor = ui->doubleSpinBox_floorElev->value();
    double forebay = ui->doubleSpinBox_fbayElev->value();
    double tailrace = ui->doubleSpinBox_traceElev->value();
    double segdowndepth, segupdepth, seglength;

    damside.addRect(0, -floor, 20, floor - forebay);
    damside.addRect(-20, -floor, 20, floor - tailrace);

    // draw down seg
    if (dam->down != nullptr)
    {
        segdowndepth = dam->down->lower_depth;
        segupdepth = dam->down->upper_depth;
        seglength = dam->down->length * 5280.0;
        {
            QPainterPath downseg (QPointF(-seglength-20, -dam->down->lower_elev));
            downseg.lineTo(-seglength-20, -dam->down->lower_elev - segdowndepth);
            downseg.lineTo(-20, -dam->down->upper_elev - segupdepth);
            downseg.lineTo(-20, -dam->down->upper_elev);
            downseg.lineTo(-seglength-20, -dam->down->lower_elev);
            damside.addPath(downseg);
        }
    }
    // draw up seg
    if (dam->up != nullptr)
    {
        segdowndepth = dam->up->lower_depth;
        segupdepth = dam->up->upper_depth;
        seglength = dam->up->length * 5280.0;
        {
            QPainterPath upseg (QPointF(20, -dam->up->lower_elev));
            upseg.lineTo(seglength, -dam->up->upper_elev);
            upseg.lineTo(seglength, -dam->up->upper_elev - segupdepth);
            upseg.lineTo(20, -dam->up->lower_elev - segdowndepth);
            upseg.lineTo(20, -dam->up->lower_elev);
            damside.addPath(upseg);
        }
    }
    return damside;
}

QPainterPath DamDetailDialog::drawDamSide_spill()
{
    QPainterPath damside;
    double bypass = ui->doubleSpinBox_bypassElev->value();
    double basinlength = ui->doubleSpinBox_basinLength->value();

    damside.addRect(10, -bypass, 10, -10);
    damside.addRect(-basinlength, -ui->doubleSpinBox_floorElev->value(), basinlength, -10);

    return damside;
}

QPainterPath DamDetailDialog::drawDamSecA_back()
{
    QPainterPath damsecA;
    double startPtX = -(dam->down->width) / 2.0;
    double startPtY = ui->doubleSpinBox_floorElev->value();
    double segdepth, segbedwidth2, segwidth2;

    damsecA.addRect(startPtX, -startPtY, dam->down->width, -(ui->doubleSpinBox_fbayElev->value() - ui->doubleSpinBox_floorElev->value()));
    startPtY = ui->doubleSpinBox_traceElev->value();
    damsecA.addRect(startPtX, -startPtY, dam->down->width, -dam->down->upper_depth);

    // draw down seg
    if (dam->down != nullptr)
    {
        segdepth = dam->down->upper_depth;
        segbedwidth2 = dam->down->bed_width / 2.0;
        segwidth2 = dam->down->upper_width / 2.0;
        {
            QPainterPath downseg (QPointF(-segwidth2, -dam->down->upper_elev - segdepth));
            downseg.lineTo(segwidth2, -dam->down->upper_elev - segdepth);
            downseg.lineTo(segbedwidth2, -dam->down->upper_elev);
            downseg.lineTo(-segbedwidth2, -dam->down->upper_elev);
            downseg.lineTo(-segwidth2, -dam->down->upper_elev - segdepth);
            damsecA.addPath(downseg);
        }
    }
    // draw up seg
    if (dam->up != nullptr)
    {
        segdepth = dam->up->lower_depth;
        segbedwidth2 = dam->up->bed_width / 2.0;
        segwidth2 = dam->up->width / 2.0;
        {
            QPainterPath upseg (QPointF(-segwidth2, -dam->up->lower_elev - segdepth));
            upseg.lineTo(segwidth2, -dam->up->lower_elev - segdepth);
            upseg.lineTo(segbedwidth2, -dam->up->lower_elev);
            upseg.lineTo(-segbedwidth2, -dam->up->lower_elev);
            upseg.lineTo(-segwidth2, -dam->up->lower_elev - segdepth);
            damsecA.addPath(upseg);
        }
    }
    return damsecA;
}

QPainterPath DamDetailDialog::drawDamSecA_spill()
{
    QPainterPath damsecA;
    float startPtX = -(dam->width / 2.0);
    double gatewidth = ui->doubleSpinBox_gateWidth->value();
    double traceElev = ui->doubleSpinBox_traceElev->value();
    double spillheight = ui->doubleSpinBox_fbayElev->value() - traceElev;

    switch (ui->comboBox_spillSide->currentIndex())
    {
    case 0: // Right
        damsecA.addRect(0, -ui->doubleSpinBox_bypassElev->value(), -startPtX, -10);
        break;
    case 1: // Left
        damsecA.addRect(startPtX, -ui->doubleSpinBox_bypassElev->value(), -startPtX, -10);
        startPtX = dam->width - ui->doubleSpinBox_spillWidth->value();
        break;
    default:
        break;
    }
    for (int i = 0; i < ui->spinBox_gateNum->value(); i++)
    {
        damsecA.addRect(startPtX + 2, -ui->doubleSpinBox_traceElev->value(), gatewidth - 4, -spillheight);
        startPtX += gatewidth;
    }

    return damsecA;
}

QPainterPath DamDetailDialog::drawSegTop(RiverSegment *seg)
{
    QPainterPath segtop;
    float startPtX = 20.0;
    float startPtY = -(seg->width / 2.0);

    switch (seg->type)
    {
    case RiverSegment::DamSegment:
        segtop.addPath(drawDamTop_back());
        break;
    case RiverSegment::ReachSegment:
    {
        break;
    }
    case RiverSegment::HeadwaterSegment:
    default:
        break;
    }

    return segtop;
}

QPainterPath DamDetailDialog::drawSegSide(RiverSegment *seg)
{
    QPainterPath segside;

    switch (seg->type)
    {
    case RiverSegment::DamSegment:
        segside.addPath(drawDamSide_back());
        break;
    case RiverSegment::ReachSegment:
    {

        break;
    }
    case RiverSegment::HeadwaterSegment:
    default:
        break;
    }

    return segside;
}

QPainterPath DamDetailDialog::drawSegSecA(RiverSegment *seg)
{
    QPainterPath segsecA;

    switch (seg->type)
    {
    case RiverSegment::DamSegment:
        segsecA.addPath(drawDamSecA_back());
        break;
    case RiverSegment::ReachSegment:
    {
        break;
    }
    case RiverSegment::HeadwaterSegment:
    default:
        break;
    }

    return segsecA;
}*/

void DamDetailDialog::setScale(float sc)
{
    if (sc > 0.0)
        scaleFactor += 0.5;//scaleFactor;
    else
        scaleFactor -= 0.5;//*= 0.5;

    if (scaleFactor < 1.0)
        scaleFactor = 1.0;

    updateViews();
}
