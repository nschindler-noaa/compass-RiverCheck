/********************************************************************************
** Form generated from reading UI file 'reachDetailDialog.ui'
**
** Created: Fri May 17 09:46:32 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REACHDETAILDIALOG_H
#define UI_REACHDETAILDIALOG_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QDialog>
#include <QDoubleSpinBox>
#include <QGraphicsView>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ReachDetailDialog
{
public:
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QGraphicsView *graphicsView_down_section;
    QGraphicsView *graphicsView_up_section;
    QVBoxLayout *verticalLayout_6;
    QSpacerItem *verticalSpacer_7;
    QLabel *label_lower_3;
    QLabel *label_lowerDepth;
    QDoubleSpinBox *doubleSpinBox_lowerDepth;
    QSpacerItem *verticalSpacer_8;
    QLabel *label_lower_4;
    QLabel *label_lowerArea;
    QLabel *label_lowerAreaValue;
    QVBoxLayout *verticalLayout_5;
    QSpacerItem *verticalSpacer_9;
    QLabel *label_upper_3;
    QLabel *label_upperDepth;
    QDoubleSpinBox *doubleSpinBox_upperDepth;
    QSpacerItem *verticalSpacer_10;
    QLabel *label_upper_4;
    QLabel *label_upperArea;
    QLabel *label_upperAreaValue;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_slope;
    QDoubleSpinBox *doubleSpinBox_slope;
    QSpacerItem *horizontalSpacer;
    QLabel *label_up_secB;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_10;
    QLabel *label_bed_width;
    QDoubleSpinBox *doubleSpinBox_bed_width;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_down_secA;
    QLabel *label_down_side;
    QGraphicsView *graphicsView_down_side;
    QLabel *label_down_top;
    QVBoxLayout *verticalLayout_lowerElev;
    QSpacerItem *verticalSpacer_4;
    QLabel *label_lower_2;
    QLabel *label_lowerElev;
    QDoubleSpinBox *doubleSpinBox_lowerElev;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer_6;
    QLabel *label_upper_2;
    QLabel *label_upperElev;
    QDoubleSpinBox *doubleSpinBox_upperElev;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label_length;
    QLabel *label_lengthValue;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_up_top;
    QLabel *label_up_side;
    QGraphicsView *graphicsView_up_side;
    QVBoxLayout *verticalLayout_width;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_lower_1;
    QLabel *label_lowerWidth;
    QDoubleSpinBox *doubleSpinBox_lowerWidth;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_11;
    QLabel *label_upper_1;
    QLabel *label_upperWidth;
    QDoubleSpinBox *doubleSpinBox_upperWidth;
    QSpacerItem *verticalSpacer_12;
    QGraphicsView *graphicsView_down_top;
    QGraphicsView *graphicsView_up_top;
    QLabel *label;
    QPushButton *pushButton_revert;
    QPushButton *pushButton_save;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_width;
    QDoubleSpinBox *doubleSpinBox_width;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QDialog *ReachDetailDialog)
    {
        if (ReachDetailDialog->objectName().isEmpty())
            ReachDetailDialog->setObjectName(QString::fromUtf8("ReachDetailDialog"));
        ReachDetailDialog->resize(706, 636);
        gridLayout = new QGridLayout(ReachDetailDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        graphicsView_down_section = new QGraphicsView(ReachDetailDialog);
        graphicsView_down_section->setObjectName(QString::fromUtf8("graphicsView_down_section"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(graphicsView_down_section->sizePolicy().hasHeightForWidth());
        graphicsView_down_section->setSizePolicy(sizePolicy);
        graphicsView_down_section->setMinimumSize(QSize(150, 60));

        gridLayout_2->addWidget(graphicsView_down_section, 12, 1, 1, 1);

        graphicsView_up_section = new QGraphicsView(ReachDetailDialog);
        graphicsView_up_section->setObjectName(QString::fromUtf8("graphicsView_up_section"));
        sizePolicy.setHeightForWidth(graphicsView_up_section->sizePolicy().hasHeightForWidth());
        graphicsView_up_section->setSizePolicy(sizePolicy);
        graphicsView_up_section->setMinimumSize(QSize(150, 60));

        gridLayout_2->addWidget(graphicsView_up_section, 12, 2, 1, 1);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_7);

        label_lower_3 = new QLabel(ReachDetailDialog);
        label_lower_3->setObjectName(QString::fromUtf8("label_lower_3"));
        label_lower_3->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(label_lower_3);

        label_lowerDepth = new QLabel(ReachDetailDialog);
        label_lowerDepth->setObjectName(QString::fromUtf8("label_lowerDepth"));
        label_lowerDepth->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(label_lowerDepth);

        doubleSpinBox_lowerDepth = new QDoubleSpinBox(ReachDetailDialog);
        doubleSpinBox_lowerDepth->setObjectName(QString::fromUtf8("doubleSpinBox_lowerDepth"));
        doubleSpinBox_lowerDepth->setAlignment(Qt::AlignCenter);
        doubleSpinBox_lowerDepth->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_lowerDepth->setMaximum(500);

        verticalLayout_6->addWidget(doubleSpinBox_lowerDepth);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_8);

        label_lower_4 = new QLabel(ReachDetailDialog);
        label_lower_4->setObjectName(QString::fromUtf8("label_lower_4"));
        label_lower_4->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(label_lower_4);

        label_lowerArea = new QLabel(ReachDetailDialog);
        label_lowerArea->setObjectName(QString::fromUtf8("label_lowerArea"));
        label_lowerArea->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(label_lowerArea);

        label_lowerAreaValue = new QLabel(ReachDetailDialog);
        label_lowerAreaValue->setObjectName(QString::fromUtf8("label_lowerAreaValue"));
        label_lowerAreaValue->setFrameShape(QFrame::StyledPanel);
        label_lowerAreaValue->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(label_lowerAreaValue);


        gridLayout_2->addLayout(verticalLayout_6, 12, 0, 1, 1);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_9);

        label_upper_3 = new QLabel(ReachDetailDialog);
        label_upper_3->setObjectName(QString::fromUtf8("label_upper_3"));
        label_upper_3->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_upper_3);

        label_upperDepth = new QLabel(ReachDetailDialog);
        label_upperDepth->setObjectName(QString::fromUtf8("label_upperDepth"));
        label_upperDepth->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_upperDepth);

        doubleSpinBox_upperDepth = new QDoubleSpinBox(ReachDetailDialog);
        doubleSpinBox_upperDepth->setObjectName(QString::fromUtf8("doubleSpinBox_upperDepth"));
        doubleSpinBox_upperDepth->setAlignment(Qt::AlignCenter);
        doubleSpinBox_upperDepth->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_upperDepth->setMaximum(500);

        verticalLayout_5->addWidget(doubleSpinBox_upperDepth);

        verticalSpacer_10 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_10);

        label_upper_4 = new QLabel(ReachDetailDialog);
        label_upper_4->setObjectName(QString::fromUtf8("label_upper_4"));
        label_upper_4->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_upper_4);

        label_upperArea = new QLabel(ReachDetailDialog);
        label_upperArea->setObjectName(QString::fromUtf8("label_upperArea"));
        label_upperArea->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_upperArea);

        label_upperAreaValue = new QLabel(ReachDetailDialog);
        label_upperAreaValue->setObjectName(QString::fromUtf8("label_upperAreaValue"));
        label_upperAreaValue->setFrameShape(QFrame::StyledPanel);
        label_upperAreaValue->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_upperAreaValue);


        gridLayout_2->addLayout(verticalLayout_5, 12, 3, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);

        label_slope = new QLabel(ReachDetailDialog);
        label_slope->setObjectName(QString::fromUtf8("label_slope"));

        horizontalLayout_4->addWidget(label_slope);

        doubleSpinBox_slope = new QDoubleSpinBox(ReachDetailDialog);
        doubleSpinBox_slope->setObjectName(QString::fromUtf8("doubleSpinBox_slope"));
        doubleSpinBox_slope->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_slope->setMaximum(90);

        horizontalLayout_4->addWidget(doubleSpinBox_slope);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);


        gridLayout_2->addLayout(horizontalLayout_4, 13, 2, 1, 1);

        label_up_secB = new QLabel(ReachDetailDialog);
        label_up_secB->setObjectName(QString::fromUtf8("label_up_secB"));
        label_up_secB->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_up_secB, 14, 2, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_10);

        label_bed_width = new QLabel(ReachDetailDialog);
        label_bed_width->setObjectName(QString::fromUtf8("label_bed_width"));

        horizontalLayout_2->addWidget(label_bed_width);

        doubleSpinBox_bed_width = new QDoubleSpinBox(ReachDetailDialog);
        doubleSpinBox_bed_width->setObjectName(QString::fromUtf8("doubleSpinBox_bed_width"));
        doubleSpinBox_bed_width->setAlignment(Qt::AlignCenter);
        doubleSpinBox_bed_width->setReadOnly(true);
        doubleSpinBox_bed_width->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_bed_width->setMaximum(8000);

        horizontalLayout_2->addWidget(doubleSpinBox_bed_width);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        gridLayout_2->addLayout(horizontalLayout_2, 13, 1, 1, 1);

        label_down_secA = new QLabel(ReachDetailDialog);
        label_down_secA->setObjectName(QString::fromUtf8("label_down_secA"));
        label_down_secA->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_down_secA, 14, 1, 1, 1);

        label_down_side = new QLabel(ReachDetailDialog);
        label_down_side->setObjectName(QString::fromUtf8("label_down_side"));
        label_down_side->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_down_side, 11, 1, 1, 1);

        graphicsView_down_side = new QGraphicsView(ReachDetailDialog);
        graphicsView_down_side->setObjectName(QString::fromUtf8("graphicsView_down_side"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(2);
        sizePolicy1.setHeightForWidth(graphicsView_down_side->sizePolicy().hasHeightForWidth());
        graphicsView_down_side->setSizePolicy(sizePolicy1);
        graphicsView_down_side->setMinimumSize(QSize(0, 60));

        gridLayout_2->addWidget(graphicsView_down_side, 10, 1, 1, 1);

        label_down_top = new QLabel(ReachDetailDialog);
        label_down_top->setObjectName(QString::fromUtf8("label_down_top"));
        label_down_top->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_down_top, 9, 1, 1, 1);

        verticalLayout_lowerElev = new QVBoxLayout();
        verticalLayout_lowerElev->setContentsMargins(1, 1, 1, 1);
        verticalLayout_lowerElev->setObjectName(QString::fromUtf8("verticalLayout_lowerElev"));
        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_lowerElev->addItem(verticalSpacer_4);

        label_lower_2 = new QLabel(ReachDetailDialog);
        label_lower_2->setObjectName(QString::fromUtf8("label_lower_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_lower_2->sizePolicy().hasHeightForWidth());
        label_lower_2->setSizePolicy(sizePolicy2);
        label_lower_2->setAlignment(Qt::AlignCenter);

        verticalLayout_lowerElev->addWidget(label_lower_2);

        label_lowerElev = new QLabel(ReachDetailDialog);
        label_lowerElev->setObjectName(QString::fromUtf8("label_lowerElev"));
        sizePolicy2.setHeightForWidth(label_lowerElev->sizePolicy().hasHeightForWidth());
        label_lowerElev->setSizePolicy(sizePolicy2);
        label_lowerElev->setAlignment(Qt::AlignCenter);

        verticalLayout_lowerElev->addWidget(label_lowerElev);

        doubleSpinBox_lowerElev = new QDoubleSpinBox(ReachDetailDialog);
        doubleSpinBox_lowerElev->setObjectName(QString::fromUtf8("doubleSpinBox_lowerElev"));
        doubleSpinBox_lowerElev->setAlignment(Qt::AlignCenter);
        doubleSpinBox_lowerElev->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_lowerElev->setMinimum(-100);
        doubleSpinBox_lowerElev->setMaximum(5000);

        verticalLayout_lowerElev->addWidget(doubleSpinBox_lowerElev);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_lowerElev->addItem(verticalSpacer_3);


        gridLayout_2->addLayout(verticalLayout_lowerElev, 10, 0, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setSizeConstraint(QLayout::SetNoConstraint);
        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_6);

        label_upper_2 = new QLabel(ReachDetailDialog);
        label_upper_2->setObjectName(QString::fromUtf8("label_upper_2"));
        sizePolicy2.setHeightForWidth(label_upper_2->sizePolicy().hasHeightForWidth());
        label_upper_2->setSizePolicy(sizePolicy2);
        label_upper_2->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label_upper_2);

        label_upperElev = new QLabel(ReachDetailDialog);
        label_upperElev->setObjectName(QString::fromUtf8("label_upperElev"));
        sizePolicy2.setHeightForWidth(label_upperElev->sizePolicy().hasHeightForWidth());
        label_upperElev->setSizePolicy(sizePolicy2);
        label_upperElev->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label_upperElev);

        doubleSpinBox_upperElev = new QDoubleSpinBox(ReachDetailDialog);
        doubleSpinBox_upperElev->setObjectName(QString::fromUtf8("doubleSpinBox_upperElev"));
        doubleSpinBox_upperElev->setAlignment(Qt::AlignCenter);
        doubleSpinBox_upperElev->setReadOnly(true);
        doubleSpinBox_upperElev->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_upperElev->setMinimum(-50);
        doubleSpinBox_upperElev->setMaximum(7000);

        verticalLayout_4->addWidget(doubleSpinBox_upperElev);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_5);


        gridLayout_2->addLayout(verticalLayout_4, 10, 3, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_8);

        label_length = new QLabel(ReachDetailDialog);
        label_length->setObjectName(QString::fromUtf8("label_length"));

        horizontalLayout->addWidget(label_length);

        label_lengthValue = new QLabel(ReachDetailDialog);
        label_lengthValue->setObjectName(QString::fromUtf8("label_lengthValue"));
        label_lengthValue->setFrameShape(QFrame::StyledPanel);
        label_lengthValue->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_lengthValue);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        gridLayout_2->addLayout(horizontalLayout, 0, 1, 1, 2);

        label_up_top = new QLabel(ReachDetailDialog);
        label_up_top->setObjectName(QString::fromUtf8("label_up_top"));
        label_up_top->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_up_top, 9, 2, 1, 1);

        label_up_side = new QLabel(ReachDetailDialog);
        label_up_side->setObjectName(QString::fromUtf8("label_up_side"));
        label_up_side->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_up_side, 11, 2, 1, 1);

        graphicsView_up_side = new QGraphicsView(ReachDetailDialog);
        graphicsView_up_side->setObjectName(QString::fromUtf8("graphicsView_up_side"));
        sizePolicy1.setHeightForWidth(graphicsView_up_side->sizePolicy().hasHeightForWidth());
        graphicsView_up_side->setSizePolicy(sizePolicy1);
        graphicsView_up_side->setMinimumSize(QSize(0, 60));

        gridLayout_2->addWidget(graphicsView_up_side, 10, 2, 1, 1);

        verticalLayout_width = new QVBoxLayout();
        verticalLayout_width->setObjectName(QString::fromUtf8("verticalLayout_width"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_width->addItem(verticalSpacer_2);

        label_lower_1 = new QLabel(ReachDetailDialog);
        label_lower_1->setObjectName(QString::fromUtf8("label_lower_1"));
        label_lower_1->setAlignment(Qt::AlignCenter);

        verticalLayout_width->addWidget(label_lower_1);

        label_lowerWidth = new QLabel(ReachDetailDialog);
        label_lowerWidth->setObjectName(QString::fromUtf8("label_lowerWidth"));
        label_lowerWidth->setAlignment(Qt::AlignCenter);

        verticalLayout_width->addWidget(label_lowerWidth);

        doubleSpinBox_lowerWidth = new QDoubleSpinBox(ReachDetailDialog);
        doubleSpinBox_lowerWidth->setObjectName(QString::fromUtf8("doubleSpinBox_lowerWidth"));
        doubleSpinBox_lowerWidth->setAlignment(Qt::AlignCenter);
        doubleSpinBox_lowerWidth->setReadOnly(true);
        doubleSpinBox_lowerWidth->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_lowerWidth->setMaximum(10000);

        verticalLayout_width->addWidget(doubleSpinBox_lowerWidth);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_width->addItem(verticalSpacer);


        gridLayout_2->addLayout(verticalLayout_width, 8, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer_11 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_11);

        label_upper_1 = new QLabel(ReachDetailDialog);
        label_upper_1->setObjectName(QString::fromUtf8("label_upper_1"));
        label_upper_1->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_upper_1);

        label_upperWidth = new QLabel(ReachDetailDialog);
        label_upperWidth->setObjectName(QString::fromUtf8("label_upperWidth"));
        label_upperWidth->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_upperWidth);

        doubleSpinBox_upperWidth = new QDoubleSpinBox(ReachDetailDialog);
        doubleSpinBox_upperWidth->setObjectName(QString::fromUtf8("doubleSpinBox_upperWidth"));
        doubleSpinBox_upperWidth->setAlignment(Qt::AlignCenter);
        doubleSpinBox_upperWidth->setReadOnly(true);
        doubleSpinBox_upperWidth->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_upperWidth->setMaximum(8000);

        verticalLayout_2->addWidget(doubleSpinBox_upperWidth);

        verticalSpacer_12 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_12);


        gridLayout_2->addLayout(verticalLayout_2, 8, 3, 1, 1);

        graphicsView_down_top = new QGraphicsView(ReachDetailDialog);
        graphicsView_down_top->setObjectName(QString::fromUtf8("graphicsView_down_top"));
        sizePolicy.setHeightForWidth(graphicsView_down_top->sizePolicy().hasHeightForWidth());
        graphicsView_down_top->setSizePolicy(sizePolicy);
        graphicsView_down_top->setMinimumSize(QSize(100, 150));

        gridLayout_2->addWidget(graphicsView_down_top, 8, 1, 1, 1);

        graphicsView_up_top = new QGraphicsView(ReachDetailDialog);
        graphicsView_up_top->setObjectName(QString::fromUtf8("graphicsView_up_top"));
        sizePolicy.setHeightForWidth(graphicsView_up_top->sizePolicy().hasHeightForWidth());
        graphicsView_up_top->setSizePolicy(sizePolicy);
        graphicsView_up_top->setMinimumSize(QSize(100, 150));

        gridLayout_2->addWidget(graphicsView_up_top, 8, 2, 1, 1);

        label = new QLabel(ReachDetailDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label, 15, 1, 1, 2);

        pushButton_revert = new QPushButton(ReachDetailDialog);
        pushButton_revert->setObjectName(QString::fromUtf8("pushButton_revert"));

        gridLayout_2->addWidget(pushButton_revert, 15, 0, 1, 1);

        pushButton_save = new QPushButton(ReachDetailDialog);
        pushButton_save->setObjectName(QString::fromUtf8("pushButton_save"));

        gridLayout_2->addWidget(pushButton_save, 15, 3, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        label_width = new QLabel(ReachDetailDialog);
        label_width->setObjectName(QString::fromUtf8("label_width"));

        horizontalLayout_5->addWidget(label_width);

        doubleSpinBox_width = new QDoubleSpinBox(ReachDetailDialog);
        doubleSpinBox_width->setObjectName(QString::fromUtf8("doubleSpinBox_width"));
        doubleSpinBox_width->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_width->setMaximum(9000);
        doubleSpinBox_width->setSingleStep(1);

        horizontalLayout_5->addWidget(doubleSpinBox_width);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);


        gridLayout_2->addLayout(horizontalLayout_5, 5, 1, 1, 2);


        gridLayout->addLayout(gridLayout_2, 6, 2, 1, 2);


        retranslateUi(ReachDetailDialog);

        QMetaObject::connectSlotsByName(ReachDetailDialog);
    } // setupUi

    void retranslateUi(QDialog *ReachDetailDialog)
    {
        ReachDetailDialog->setWindowTitle(QApplication::translate("ReachDetailDialog", "Dialog", 0));
        label_lower_3->setText(QApplication::translate("ReachDetailDialog", "Lower", 0));
        label_lowerDepth->setText(QApplication::translate("ReachDetailDialog", "Depth", 0));
        doubleSpinBox_lowerDepth->setSuffix(QApplication::translate("ReachDetailDialog", " ft.", 0));
        label_lower_4->setText(QApplication::translate("ReachDetailDialog", "Lower", 0));
        label_lowerArea->setText(QApplication::translate("ReachDetailDialog", "Area", 0));
        label_lowerAreaValue->setText(QApplication::translate("ReachDetailDialog", "TextLabel", 0));
        label_upper_3->setText(QApplication::translate("ReachDetailDialog", "Upper", 0));
        label_upperDepth->setText(QApplication::translate("ReachDetailDialog", "Depth", 0));
        doubleSpinBox_upperDepth->setSuffix(QApplication::translate("ReachDetailDialog", " ft.", 0));
        label_upper_4->setText(QApplication::translate("ReachDetailDialog", "Upper", 0));
        label_upperArea->setText(QApplication::translate("ReachDetailDialog", "Area", 0));
        label_upperAreaValue->setText(QApplication::translate("ReachDetailDialog", "TextLabel", 0));
        label_slope->setText(QApplication::translate("ReachDetailDialog", "Slope of sides", 0));
        doubleSpinBox_slope->setSuffix(QApplication::translate("ReachDetailDialog", " deg.", 0));
        label_up_secB->setText(QApplication::translate("ReachDetailDialog", "Upstream Section", 0));
        label_bed_width->setText(QApplication::translate("ReachDetailDialog", "Bed Width", 0));
        doubleSpinBox_bed_width->setSuffix(QApplication::translate("ReachDetailDialog", " ft.", 0));
        label_down_secA->setText(QApplication::translate("ReachDetailDialog", "Downstream Section", 0));
        label_down_side->setText(QApplication::translate("ReachDetailDialog", "Downstream Side View", 0));
        label_down_top->setText(QApplication::translate("ReachDetailDialog", "Downstream Top View", 0));
        label_lower_2->setText(QApplication::translate("ReachDetailDialog", "Lower", 0));
        label_lowerElev->setText(QApplication::translate("ReachDetailDialog", "Elev", 0));
        doubleSpinBox_lowerElev->setSuffix(QApplication::translate("ReachDetailDialog", " ft.", 0));
        label_upper_2->setText(QApplication::translate("ReachDetailDialog", "Upper", 0));
        label_upperElev->setText(QApplication::translate("ReachDetailDialog", "Elev", 0));
        doubleSpinBox_upperElev->setSuffix(QApplication::translate("ReachDetailDialog", " ft.", 0));
        label_length->setText(QApplication::translate("ReachDetailDialog", "Length", 0));
        label_lengthValue->setText(QApplication::translate("ReachDetailDialog", "ft.", 0));
        label_up_top->setText(QApplication::translate("ReachDetailDialog", "Upstream Top View", 0));
        label_up_side->setText(QApplication::translate("ReachDetailDialog", "Upstream Side View", 0));
        label_lower_1->setText(QApplication::translate("ReachDetailDialog", "Lower", 0));
        label_lowerWidth->setText(QApplication::translate("ReachDetailDialog", "Width", 0));
        doubleSpinBox_lowerWidth->setSuffix(QApplication::translate("ReachDetailDialog", " ft.", 0));
        label_upper_1->setText(QApplication::translate("ReachDetailDialog", "Upper", 0));
        label_upperWidth->setText(QApplication::translate("ReachDetailDialog", "Width", 0));
        doubleSpinBox_upperWidth->setSuffix(QApplication::translate("ReachDetailDialog", " ft.", 0));
        label->setText(QApplication::translate("ReachDetailDialog", "Note: Length and width are scaled by 1/10.", 0));
        pushButton_revert->setText(QApplication::translate("ReachDetailDialog", "Revert", 0));
        pushButton_save->setText(QApplication::translate("ReachDetailDialog", "Save", 0));
        label_width->setText(QApplication::translate("ReachDetailDialog", "Ave Width", 0));
        doubleSpinBox_width->setSuffix(QApplication::translate("ReachDetailDialog", " ft.", 0));
    } // retranslateUi

};

namespace Ui {
    class ReachDetailDialog: public Ui_ReachDetailDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REACHDETAILDIALOG_H
