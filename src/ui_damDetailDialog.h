/********************************************************************************
** Form generated from reading UI file 'damDetailDialog.ui'
**
** Created: Fri May 17 16:17:24 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DAMDETAILDIALOG_H
#define UI_DAMDETAILDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DamDetailDialog
{
public:
    QGridLayout *gridLayout;
    QGraphicsView *graphicsView_a;
    QVBoxLayout *verticalLayout_traceElev;
    QSpacerItem *verticalSpacer_7;
    QLabel *label_tailrace;
    QLabel *label_traceElev;
    QDoubleSpinBox *doubleSpinBox_traceElev;
    QSpacerItem *verticalSpacer_8;
    QLabel *label_floor;
    QLabel *label_floorElev;
    QDoubleSpinBox *doubleSpinBox_floorElev;
    QGraphicsView *graphicsView_side;
    QGraphicsView *graphicsView_top;
    QLabel *label_topView;
    QLabel *label_secA;
    QVBoxLayout *verticalLayout_fbay_bypassElev;
    QLabel *label_forebay;
    QLabel *label_forebayElev;
    QDoubleSpinBox *doubleSpinBox_fbayElev;
    QSpacerItem *verticalSpacer_11;
    QLabel *label_bypass;
    QLabel *label_bypassElev;
    QDoubleSpinBox *doubleSpinBox_bypassElev;
    QSpacerItem *verticalSpacer_5;
    QLabel *label_sideView;
    QHBoxLayout *horizontalLayout_basinLength;
    QLabel *label_basinLength;
    QDoubleSpinBox *doubleSpinBox_basinLength;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_down;
    QVBoxLayout *verticalLayout_revert;
    QPushButton *pushButton_revert;
    QVBoxLayout *verticalLayout_up;
    QVBoxLayout *verticalLayout_save;
    QPushButton *pushButton_save;
    QVBoxLayout *verticalLayout_extra;
    QHBoxLayout *horizontalLayout_SGR;
    QLabel *label_SGR;
    QDoubleSpinBox *doubleSpinBox_SGR;
    QSpacerItem *horizontalSpacer_11;
    QHBoxLayout *horizontalLayout_PH1Cap;
    QLabel *label_Phouse1Cap;
    QDoubleSpinBox *doubleSpinBox_PH1Cap;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_PH2Cap;
    QLabel *label_Phouse2Cap;
    QDoubleSpinBox *doubleSpinBox_PH2Cap;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_spillwyWidth;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label_spillSide;
    QComboBox *comboBox_spillSide;
    QLabel *label_spillwyWidth;
    QDoubleSpinBox *doubleSpinBox_spillWidth;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_spillSide;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_spillGates;
    QSpinBox *spinBox_gateNum;
    QLabel *label_eachGateWidth;
    QDoubleSpinBox *doubleSpinBox_gateWidth;
    QLabel *label;
    QLabel *label_spillwyWidthValue;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *DamDetailDialog)
    {
        if (DamDetailDialog->objectName().isEmpty())
            DamDetailDialog->setObjectName(QString::fromUtf8("DamDetailDialog"));
        DamDetailDialog->resize(738, 566);
        gridLayout = new QGridLayout(DamDetailDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        graphicsView_a = new QGraphicsView(DamDetailDialog);
        graphicsView_a->setObjectName(QString::fromUtf8("graphicsView_a"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(2);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphicsView_a->sizePolicy().hasHeightForWidth());
        graphicsView_a->setSizePolicy(sizePolicy);
        graphicsView_a->setAcceptDrops(false);

        gridLayout->addWidget(graphicsView_a, 7, 5, 1, 1);

        verticalLayout_traceElev = new QVBoxLayout();
        verticalLayout_traceElev->setObjectName(QString::fromUtf8("verticalLayout_traceElev"));
        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_traceElev->addItem(verticalSpacer_7);

        label_tailrace = new QLabel(DamDetailDialog);
        label_tailrace->setObjectName(QString::fromUtf8("label_tailrace"));
        label_tailrace->setAlignment(Qt::AlignCenter);

        verticalLayout_traceElev->addWidget(label_tailrace);

        label_traceElev = new QLabel(DamDetailDialog);
        label_traceElev->setObjectName(QString::fromUtf8("label_traceElev"));
        label_traceElev->setAlignment(Qt::AlignCenter);

        verticalLayout_traceElev->addWidget(label_traceElev);

        doubleSpinBox_traceElev = new QDoubleSpinBox(DamDetailDialog);
        doubleSpinBox_traceElev->setObjectName(QString::fromUtf8("doubleSpinBox_traceElev"));
        doubleSpinBox_traceElev->setAlignment(Qt::AlignCenter);
        doubleSpinBox_traceElev->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_traceElev->setMinimum(-50);
        doubleSpinBox_traceElev->setMaximum(2000);

        verticalLayout_traceElev->addWidget(doubleSpinBox_traceElev);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_traceElev->addItem(verticalSpacer_8);

        label_floor = new QLabel(DamDetailDialog);
        label_floor->setObjectName(QString::fromUtf8("label_floor"));
        label_floor->setAlignment(Qt::AlignCenter);

        verticalLayout_traceElev->addWidget(label_floor);

        label_floorElev = new QLabel(DamDetailDialog);
        label_floorElev->setObjectName(QString::fromUtf8("label_floorElev"));
        label_floorElev->setAlignment(Qt::AlignCenter);

        verticalLayout_traceElev->addWidget(label_floorElev);

        doubleSpinBox_floorElev = new QDoubleSpinBox(DamDetailDialog);
        doubleSpinBox_floorElev->setObjectName(QString::fromUtf8("doubleSpinBox_floorElev"));
        doubleSpinBox_floorElev->setAlignment(Qt::AlignCenter);
        doubleSpinBox_floorElev->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_floorElev->setMinimum(-50);
        doubleSpinBox_floorElev->setMaximum(2000);

        verticalLayout_traceElev->addWidget(doubleSpinBox_floorElev);


        gridLayout->addLayout(verticalLayout_traceElev, 7, 4, 1, 1);

        graphicsView_side = new QGraphicsView(DamDetailDialog);
        graphicsView_side->setObjectName(QString::fromUtf8("graphicsView_side"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(2);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(graphicsView_side->sizePolicy().hasHeightForWidth());
        graphicsView_side->setSizePolicy(sizePolicy1);
        graphicsView_side->setAcceptDrops(false);

        gridLayout->addWidget(graphicsView_side, 7, 7, 1, 1);

        graphicsView_top = new QGraphicsView(DamDetailDialog);
        graphicsView_top->setObjectName(QString::fromUtf8("graphicsView_top"));
        sizePolicy1.setHeightForWidth(graphicsView_top->sizePolicy().hasHeightForWidth());
        graphicsView_top->setSizePolicy(sizePolicy1);
        graphicsView_top->setAcceptDrops(false);

        gridLayout->addWidget(graphicsView_top, 3, 7, 1, 1);

        label_topView = new QLabel(DamDetailDialog);
        label_topView->setObjectName(QString::fromUtf8("label_topView"));
        label_topView->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_topView, 4, 7, 1, 1);

        label_secA = new QLabel(DamDetailDialog);
        label_secA->setObjectName(QString::fromUtf8("label_secA"));
        label_secA->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_secA, 8, 5, 1, 1);

        verticalLayout_fbay_bypassElev = new QVBoxLayout();
        verticalLayout_fbay_bypassElev->setObjectName(QString::fromUtf8("verticalLayout_fbay_bypassElev"));
        label_forebay = new QLabel(DamDetailDialog);
        label_forebay->setObjectName(QString::fromUtf8("label_forebay"));
        label_forebay->setAlignment(Qt::AlignCenter);

        verticalLayout_fbay_bypassElev->addWidget(label_forebay);

        label_forebayElev = new QLabel(DamDetailDialog);
        label_forebayElev->setObjectName(QString::fromUtf8("label_forebayElev"));
        label_forebayElev->setAlignment(Qt::AlignCenter);

        verticalLayout_fbay_bypassElev->addWidget(label_forebayElev);

        doubleSpinBox_fbayElev = new QDoubleSpinBox(DamDetailDialog);
        doubleSpinBox_fbayElev->setObjectName(QString::fromUtf8("doubleSpinBox_fbayElev"));
        doubleSpinBox_fbayElev->setAlignment(Qt::AlignCenter);
        doubleSpinBox_fbayElev->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_fbayElev->setMinimum(0);
        doubleSpinBox_fbayElev->setMaximum(2000);

        verticalLayout_fbay_bypassElev->addWidget(doubleSpinBox_fbayElev);

        verticalSpacer_11 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_fbay_bypassElev->addItem(verticalSpacer_11);

        label_bypass = new QLabel(DamDetailDialog);
        label_bypass->setObjectName(QString::fromUtf8("label_bypass"));
        label_bypass->setAlignment(Qt::AlignCenter);

        verticalLayout_fbay_bypassElev->addWidget(label_bypass);

        label_bypassElev = new QLabel(DamDetailDialog);
        label_bypassElev->setObjectName(QString::fromUtf8("label_bypassElev"));
        label_bypassElev->setAlignment(Qt::AlignCenter);

        verticalLayout_fbay_bypassElev->addWidget(label_bypassElev);

        doubleSpinBox_bypassElev = new QDoubleSpinBox(DamDetailDialog);
        doubleSpinBox_bypassElev->setObjectName(QString::fromUtf8("doubleSpinBox_bypassElev"));
        doubleSpinBox_bypassElev->setAlignment(Qt::AlignCenter);
        doubleSpinBox_bypassElev->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_bypassElev->setMaximum(2000);

        verticalLayout_fbay_bypassElev->addWidget(doubleSpinBox_bypassElev);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_fbay_bypassElev->addItem(verticalSpacer_5);


        gridLayout->addLayout(verticalLayout_fbay_bypassElev, 7, 6, 1, 1);

        label_sideView = new QLabel(DamDetailDialog);
        label_sideView->setObjectName(QString::fromUtf8("label_sideView"));
        label_sideView->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_sideView, 8, 7, 1, 1);

        horizontalLayout_basinLength = new QHBoxLayout();
        horizontalLayout_basinLength->setObjectName(QString::fromUtf8("horizontalLayout_basinLength"));
        label_basinLength = new QLabel(DamDetailDialog);
        label_basinLength->setObjectName(QString::fromUtf8("label_basinLength"));

        horizontalLayout_basinLength->addWidget(label_basinLength);

        doubleSpinBox_basinLength = new QDoubleSpinBox(DamDetailDialog);
        doubleSpinBox_basinLength->setObjectName(QString::fromUtf8("doubleSpinBox_basinLength"));
        doubleSpinBox_basinLength->setAlignment(Qt::AlignCenter);
        doubleSpinBox_basinLength->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_basinLength->setMaximum(400);

        horizontalLayout_basinLength->addWidget(doubleSpinBox_basinLength);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_basinLength->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout_basinLength, 9, 7, 1, 1);

        verticalLayout_down = new QVBoxLayout();
        verticalLayout_down->setObjectName(QString::fromUtf8("verticalLayout_down"));

        gridLayout->addLayout(verticalLayout_down, 3, 0, 8, 1);

        verticalLayout_revert = new QVBoxLayout();
        verticalLayout_revert->setObjectName(QString::fromUtf8("verticalLayout_revert"));
        pushButton_revert = new QPushButton(DamDetailDialog);
        pushButton_revert->setObjectName(QString::fromUtf8("pushButton_revert"));

        verticalLayout_revert->addWidget(pushButton_revert);


        gridLayout->addLayout(verticalLayout_revert, 12, 0, 1, 1);

        verticalLayout_up = new QVBoxLayout();
        verticalLayout_up->setObjectName(QString::fromUtf8("verticalLayout_up"));

        gridLayout->addLayout(verticalLayout_up, 3, 8, 7, 1);

        verticalLayout_save = new QVBoxLayout();
        verticalLayout_save->setObjectName(QString::fromUtf8("verticalLayout_save"));
        pushButton_save = new QPushButton(DamDetailDialog);
        pushButton_save->setObjectName(QString::fromUtf8("pushButton_save"));

        verticalLayout_save->addWidget(pushButton_save);


        gridLayout->addLayout(verticalLayout_save, 12, 8, 1, 1);

        verticalLayout_extra = new QVBoxLayout();
        verticalLayout_extra->setObjectName(QString::fromUtf8("verticalLayout_extra"));
        horizontalLayout_SGR = new QHBoxLayout();
        horizontalLayout_SGR->setObjectName(QString::fromUtf8("horizontalLayout_SGR"));
        label_SGR = new QLabel(DamDetailDialog);
        label_SGR->setObjectName(QString::fromUtf8("label_SGR"));

        horizontalLayout_SGR->addWidget(label_SGR);

        doubleSpinBox_SGR = new QDoubleSpinBox(DamDetailDialog);
        doubleSpinBox_SGR->setObjectName(QString::fromUtf8("doubleSpinBox_SGR"));
        doubleSpinBox_SGR->setButtonSymbols(QAbstractSpinBox::NoButtons);

        horizontalLayout_SGR->addWidget(doubleSpinBox_SGR);

        horizontalSpacer_11 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_SGR->addItem(horizontalSpacer_11);


        verticalLayout_extra->addLayout(horizontalLayout_SGR);

        horizontalLayout_PH1Cap = new QHBoxLayout();
        horizontalLayout_PH1Cap->setObjectName(QString::fromUtf8("horizontalLayout_PH1Cap"));
        label_Phouse1Cap = new QLabel(DamDetailDialog);
        label_Phouse1Cap->setObjectName(QString::fromUtf8("label_Phouse1Cap"));

        horizontalLayout_PH1Cap->addWidget(label_Phouse1Cap);

        doubleSpinBox_PH1Cap = new QDoubleSpinBox(DamDetailDialog);
        doubleSpinBox_PH1Cap->setObjectName(QString::fromUtf8("doubleSpinBox_PH1Cap"));
        doubleSpinBox_PH1Cap->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_PH1Cap->setMaximum(2000);

        horizontalLayout_PH1Cap->addWidget(doubleSpinBox_PH1Cap);

        horizontalSpacer_6 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_PH1Cap->addItem(horizontalSpacer_6);


        verticalLayout_extra->addLayout(horizontalLayout_PH1Cap);

        horizontalLayout_PH2Cap = new QHBoxLayout();
        horizontalLayout_PH2Cap->setObjectName(QString::fromUtf8("horizontalLayout_PH2Cap"));
        label_Phouse2Cap = new QLabel(DamDetailDialog);
        label_Phouse2Cap->setObjectName(QString::fromUtf8("label_Phouse2Cap"));

        horizontalLayout_PH2Cap->addWidget(label_Phouse2Cap);

        doubleSpinBox_PH2Cap = new QDoubleSpinBox(DamDetailDialog);
        doubleSpinBox_PH2Cap->setObjectName(QString::fromUtf8("doubleSpinBox_PH2Cap"));
        doubleSpinBox_PH2Cap->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_PH2Cap->setMaximum(2000);

        horizontalLayout_PH2Cap->addWidget(doubleSpinBox_PH2Cap);

        horizontalSpacer_4 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_PH2Cap->addItem(horizontalSpacer_4);


        verticalLayout_extra->addLayout(horizontalLayout_PH2Cap);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_extra->addItem(verticalSpacer);

        horizontalLayout_spillwyWidth = new QHBoxLayout();
        horizontalLayout_spillwyWidth->setObjectName(QString::fromUtf8("horizontalLayout_spillwyWidth"));
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_spillwyWidth->addItem(horizontalSpacer_9);

        label_spillSide = new QLabel(DamDetailDialog);
        label_spillSide->setObjectName(QString::fromUtf8("label_spillSide"));

        horizontalLayout_spillwyWidth->addWidget(label_spillSide);

        comboBox_spillSide = new QComboBox(DamDetailDialog);
        comboBox_spillSide->setObjectName(QString::fromUtf8("comboBox_spillSide"));
        comboBox_spillSide->setEditable(true);
        comboBox_spillSide->setMaxVisibleItems(2);
        comboBox_spillSide->setMaxCount(2);

        horizontalLayout_spillwyWidth->addWidget(comboBox_spillSide);

        label_spillwyWidth = new QLabel(DamDetailDialog);
        label_spillwyWidth->setObjectName(QString::fromUtf8("label_spillwyWidth"));

        horizontalLayout_spillwyWidth->addWidget(label_spillwyWidth);

        doubleSpinBox_spillWidth = new QDoubleSpinBox(DamDetailDialog);
        doubleSpinBox_spillWidth->setObjectName(QString::fromUtf8("doubleSpinBox_spillWidth"));
        doubleSpinBox_spillWidth->setAlignment(Qt::AlignCenter);
        doubleSpinBox_spillWidth->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_spillWidth->setMaximum(2000);

        horizontalLayout_spillwyWidth->addWidget(doubleSpinBox_spillWidth);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_spillwyWidth->addItem(horizontalSpacer_5);


        verticalLayout_extra->addLayout(horizontalLayout_spillwyWidth);

        horizontalLayout_spillSide = new QHBoxLayout();
        horizontalLayout_spillSide->setObjectName(QString::fromUtf8("horizontalLayout_spillSide"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_spillSide->addItem(horizontalSpacer_7);

        label_spillGates = new QLabel(DamDetailDialog);
        label_spillGates->setObjectName(QString::fromUtf8("label_spillGates"));
        label_spillGates->setAlignment(Qt::AlignCenter);

        horizontalLayout_spillSide->addWidget(label_spillGates);

        spinBox_gateNum = new QSpinBox(DamDetailDialog);
        spinBox_gateNum->setObjectName(QString::fromUtf8("spinBox_gateNum"));
        spinBox_gateNum->setLayoutDirection(Qt::LeftToRight);
        spinBox_gateNum->setFrame(true);
        spinBox_gateNum->setAlignment(Qt::AlignCenter);
        spinBox_gateNum->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        spinBox_gateNum->setMaximum(50);

        horizontalLayout_spillSide->addWidget(spinBox_gateNum);

        label_eachGateWidth = new QLabel(DamDetailDialog);
        label_eachGateWidth->setObjectName(QString::fromUtf8("label_eachGateWidth"));
        label_eachGateWidth->setAlignment(Qt::AlignCenter);

        horizontalLayout_spillSide->addWidget(label_eachGateWidth);

        doubleSpinBox_gateWidth = new QDoubleSpinBox(DamDetailDialog);
        doubleSpinBox_gateWidth->setObjectName(QString::fromUtf8("doubleSpinBox_gateWidth"));
        doubleSpinBox_gateWidth->setAlignment(Qt::AlignCenter);
        doubleSpinBox_gateWidth->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_gateWidth->setMaximum(99.99);

        horizontalLayout_spillSide->addWidget(doubleSpinBox_gateWidth);

        label = new QLabel(DamDetailDialog);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_spillSide->addWidget(label);

        label_spillwyWidthValue = new QLabel(DamDetailDialog);
        label_spillwyWidthValue->setObjectName(QString::fromUtf8("label_spillwyWidthValue"));
        label_spillwyWidthValue->setFrameShape(QFrame::StyledPanel);

        horizontalLayout_spillSide->addWidget(label_spillwyWidthValue);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_spillSide->addItem(horizontalSpacer);


        verticalLayout_extra->addLayout(horizontalLayout_spillSide);


        gridLayout->addLayout(verticalLayout_extra, 3, 4, 1, 3);


        retranslateUi(DamDetailDialog);

        comboBox_spillSide->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(DamDetailDialog);
    } // setupUi

    void retranslateUi(QDialog *DamDetailDialog)
    {
        DamDetailDialog->setWindowTitle(QApplication::translate("DamDetailDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label_tailrace->setText(QApplication::translate("DamDetailDialog", "Tailrace", 0, QApplication::UnicodeUTF8));
        label_traceElev->setText(QApplication::translate("DamDetailDialog", "Elev", 0, QApplication::UnicodeUTF8));
        doubleSpinBox_traceElev->setSuffix(QApplication::translate("DamDetailDialog", " ft.", 0, QApplication::UnicodeUTF8));
        label_floor->setText(QApplication::translate("DamDetailDialog", "Floor", 0, QApplication::UnicodeUTF8));
        label_floorElev->setText(QApplication::translate("DamDetailDialog", "Elev", 0, QApplication::UnicodeUTF8));
        doubleSpinBox_floorElev->setSuffix(QApplication::translate("DamDetailDialog", " ft.", 0, QApplication::UnicodeUTF8));
        label_topView->setText(QApplication::translate("DamDetailDialog", "Top View", 0, QApplication::UnicodeUTF8));
        label_secA->setText(QApplication::translate("DamDetailDialog", "Downstream Section", 0, QApplication::UnicodeUTF8));
        label_forebay->setText(QApplication::translate("DamDetailDialog", "Forebay", 0, QApplication::UnicodeUTF8));
        label_forebayElev->setText(QApplication::translate("DamDetailDialog", "Elev", 0, QApplication::UnicodeUTF8));
        doubleSpinBox_fbayElev->setSuffix(QApplication::translate("DamDetailDialog", " ft.", 0, QApplication::UnicodeUTF8));
        label_bypass->setText(QApplication::translate("DamDetailDialog", "Bypass", 0, QApplication::UnicodeUTF8));
        label_bypassElev->setText(QApplication::translate("DamDetailDialog", "Elev", 0, QApplication::UnicodeUTF8));
        doubleSpinBox_bypassElev->setSuffix(QApplication::translate("DamDetailDialog", " ft.", 0, QApplication::UnicodeUTF8));
        label_sideView->setText(QApplication::translate("DamDetailDialog", "Side View", 0, QApplication::UnicodeUTF8));
        label_basinLength->setText(QApplication::translate("DamDetailDialog", "Basin Length", 0, QApplication::UnicodeUTF8));
        doubleSpinBox_basinLength->setSuffix(QApplication::translate("DamDetailDialog", " ft.", 0, QApplication::UnicodeUTF8));
        pushButton_revert->setText(QApplication::translate("DamDetailDialog", "Revert", 0, QApplication::UnicodeUTF8));
        pushButton_save->setText(QApplication::translate("DamDetailDialog", "Save", 0, QApplication::UnicodeUTF8));
        label_SGR->setText(QApplication::translate("DamDetailDialog", "SGR", 0, QApplication::UnicodeUTF8));
        label_Phouse1Cap->setText(QApplication::translate("DamDetailDialog", "PowerHouse 1 cap.", 0, QApplication::UnicodeUTF8));
        doubleSpinBox_PH1Cap->setSuffix(QString());
        label_Phouse2Cap->setText(QApplication::translate("DamDetailDialog", "PowerHouse 2 cap.", 0, QApplication::UnicodeUTF8));
        doubleSpinBox_PH2Cap->setSuffix(QString());
        label_spillSide->setText(QApplication::translate("DamDetailDialog", "Spill Side ", 0, QApplication::UnicodeUTF8));
        label_spillwyWidth->setText(QApplication::translate("DamDetailDialog", "Spillway Width", 0, QApplication::UnicodeUTF8));
        doubleSpinBox_spillWidth->setSuffix(QApplication::translate("DamDetailDialog", " ft.", 0, QApplication::UnicodeUTF8));
        label_spillGates->setText(QApplication::translate("DamDetailDialog", "Spill gates", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        spinBox_gateNum->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        label_eachGateWidth->setText(QApplication::translate("DamDetailDialog", "* Each gate", 0, QApplication::UnicodeUTF8));
        doubleSpinBox_gateWidth->setSuffix(QApplication::translate("DamDetailDialog", " ft.", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DamDetailDialog", "=", 0, QApplication::UnicodeUTF8));
        label_spillwyWidthValue->setText(QApplication::translate("DamDetailDialog", "value", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DamDetailDialog: public Ui_DamDetailDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DAMDETAILDIALOG_H
