#include "segmentinfo.h"
#include "ui_segmentinfo.h"
#include "Reach.h"

SegmentInfo::SegmentInfo(Side loc, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SegmentInfo)
{
    ui->setupUi(this);
    setup(loc);
    segment = NULL;
    connect (ui->pushButton_goto, SIGNAL(clicked()), SLOT(gotoClicked()));
}

SegmentInfo::SegmentInfo (Side loc, RiverSegment *seg, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SegmentInfo)
{
    ui->setupUi(this);
    setup(loc);
    addSegment(seg);
}

SegmentInfo::~SegmentInfo()
{
    delete ui;
}

void SegmentInfo::setup(Side loc)
{
    side = loc;
    switch (loc)
    {
    case Upper:
    {
        ui->label_dir_width->setText("Upper");
        ui->label_dir_area->setText("Upper");
        ui->label_dir_elev->setText("Upper");
        ui->label_dir_depth->setText("Upper");
        break;
    }
    case Lower:
    {
        ui->label_dir_width->setText("Lower");
        ui->label_dir_area->setText("Lower");
        ui->label_dir_elev->setText("Lower");
        ui->label_dir_depth->setText("Lower");
        break;
    }
    default:
        break;
    }
}

void SegmentInfo::addSegment(RiverSegment *seg)
{
    double area;
    segment = seg;
    if (segment != NULL)
    {
        ui->textEdit_name->setText(*seg->name);
        switch (side)
        {
        case Upper:
            ui->lineEdit_width->setText(QString::number(seg->upperWidth, 'f', 2));
            ui->lineEdit_elev->setText(QString::number(seg->upperElev, 'f', 2));
            ui->lineEdit_depth->setText(QString::number(seg->upperDepth, 'f', 2));
            if (segment->type == RiverSegment::DamSegment)
            {
                ui->label_areaValue->hide();
                ui->label_dir_area->hide();
                ui->label_area->hide();
            }
            else
            {
                Reach *rch = (Reach *)segment;
                area = (rch->upperWidth - (rch->upperWidth - rch->bedWidth)/2.0) * rch->upperDepth;
                ui->label_areaValue->setText(QString::number(area, 'f', 2));
                ui->label_areaValue->show();
                ui->label_dir_area->show();
                ui->label_area->show();
            }
            break;
        case Lower:
            ui->lineEdit_width->setText(QString::number(seg->lowerWidth, 'f', 2));
            ui->lineEdit_elev->setText(QString::number(seg->lowerElev, 'f', 2));
            ui->lineEdit_depth->setText(QString::number(seg->lowerDepth, 'f', 2));
            if (segment->type == RiverSegment::DamSegment)
            {

                ui->label_areaValue->hide();
                ui->label_dir_area->hide();
                ui->label_area->hide();
            }
            else
            {
                Reach *rch = (Reach *)segment;
                area = (rch->lowerWidth - (rch->lowerWidth - rch->bedWidth)/2.0) * rch->lowerDepth;
                ui->label_areaValue->setText(QString::number(area, 'f', 2));
                ui->label_areaValue->show();
                ui->label_dir_area->show();
                ui->label_area->show();
            }
            break;
        default:
            break;
        }
    }
}

void SegmentInfo::gotoClicked()
{
    emit gotoSegment(segment);
}

void SegmentInfo::hideName(bool flag)
{
    ui->textEdit_name->setVisible(!flag);
}

void SegmentInfo::hideButton(bool flag)
{
    ui->pushButton_goto->setVisible(!flag);
}

/*
UpperSegmentInfo::UpperSegmentInfo(QWidget *parent) :
    SegmentInfo(parent)
{
//    connect (ui->pushButton_goto, SIGNAL(clicked()), SIGNAL(gotoSegment(segment)));
}

UpperSegmentInfo::UpperSegmentInfo(RiverSegment *seg, QWidget *parent) :
    SegmentInfo(parent)
{
    ui->label_dir_width->setText("Upper");
    ui->label_dir_elev->setText("Upper");
    ui->label_dir_depth->setText("Upper");
//    connect (ui->pushButton_goto, SIGNAL(clicked()), SIGNAL(gotoSegment(RiverSegment*)));
//    addSegment(seg);
}

UpperSegmentInfo::~UpperSegmentInfo()
{
}

void UpperSegmentInfo::addSegment(RiverSegment *seg)
{
    segment = seg;
    if (segment != NULL)
    {
        ui->textEdit_name->setText(*seg->name);
    }
}

LowerSegmentInfo::LowerSegmentInfo(QWidget *parent) :
    SegmentInfo(parent)
{
//    connect (ui->pushButton_goto, SIGNAL(clicked()), SIGNAL(gotoSegment(RiverSegment*)));
}

LowerSegmentInfo::LowerSegmentInfo(RiverSegment *seg, QWidget *parent) :
    SegmentInfo(parent)
{
    ui->label_dir_width->setText("Lower");
    ui->label_dir_elev->setText("Lower");
    ui->label_dir_depth->setText("Lower");
    addSegment(seg);
//    connect (ui->pushButton_goto, SIGNAL(clicked()), SIGNAL(gotoSegment(RiverSegment*)));
//    addSegment(seg);
}

LowerSegmentInfo::~LowerSegmentInfo()
{
}

void LowerSegmentInfo::addSegment(RiverSegment *seg)
{
    segment = seg;
    if (segment != NULL)
    {
        ui->textEdit_name->setText(*seg->name);
    }
}
*/
