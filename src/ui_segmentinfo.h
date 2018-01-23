/********************************************************************************
** Form generated from reading UI file 'segmentinfo.ui'
**
** Created: Fri Mar 29 11:28:58 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEGMENTINFO_H
#define UI_SEGMENTINFO_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QFrame>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpacerItem>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_SegmentInfo
{
public:
    QVBoxLayout *verticalLayout_5;
    QFrame *frame;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pushButton_goto;
    QTextEdit *textEdit_name;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_dir_width;
    QLabel *label_2;
    QLineEdit *lineEdit_width;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_dir_elev;
    QLabel *label_4;
    QLineEdit *lineEdit_elev;
    QSpacerItem *verticalSpacer_4;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_5;
    QLabel *label_dir_depth;
    QLabel *label_6;
    QLineEdit *lineEdit_depth;
    QSpacerItem *verticalSpacer_6;
    QVBoxLayout *verticalLayout_6;
    QSpacerItem *verticalSpacer_8;
    QLabel *label_dir_area;
    QLabel *label_area;
    QLabel *label_areaValue;
    QSpacerItem *verticalSpacer_7;

    void setupUi(QWidget *SegmentInfo)
    {
        if (SegmentInfo->objectName().isEmpty())
            SegmentInfo->setObjectName(QString::fromUtf8("SegmentInfo"));
        SegmentInfo->resize(100, 600);
        SegmentInfo->setMaximumSize(QSize(100, 2000));
        verticalLayout_5 = new QVBoxLayout(SegmentInfo);
        verticalLayout_5->setSpacing(1);
        verticalLayout_5->setContentsMargins(3, 3, 3, 3);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        frame = new QFrame(SegmentInfo);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        verticalLayout_4 = new QVBoxLayout(frame);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        pushButton_goto = new QPushButton(frame);
        pushButton_goto->setObjectName(QString::fromUtf8("pushButton_goto"));

        verticalLayout_4->addWidget(pushButton_goto);

        textEdit_name = new QTextEdit(frame);
        textEdit_name->setObjectName(QString::fromUtf8("textEdit_name"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textEdit_name->sizePolicy().hasHeightForWidth());
        textEdit_name->setSizePolicy(sizePolicy);
        textEdit_name->setMinimumSize(QSize(20, 20));
        textEdit_name->setMaximumSize(QSize(16777213, 50));
        textEdit_name->setAcceptDrops(false);
        textEdit_name->setFrameShape(QFrame::Box);
        textEdit_name->setFrameShadow(QFrame::Plain);
        textEdit_name->setReadOnly(true);
        textEdit_name->setTabStopWidth(20);
        textEdit_name->setTextInteractionFlags(Qt::NoTextInteraction);

        verticalLayout_4->addWidget(textEdit_name);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        label_dir_width = new QLabel(frame);
        label_dir_width->setObjectName(QString::fromUtf8("label_dir_width"));
        label_dir_width->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_dir_width);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_2);

        lineEdit_width = new QLineEdit(frame);
        lineEdit_width->setObjectName(QString::fromUtf8("lineEdit_width"));
        lineEdit_width->setReadOnly(true);

        verticalLayout->addWidget(lineEdit_width);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        verticalLayout_4->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        label_dir_elev = new QLabel(frame);
        label_dir_elev->setObjectName(QString::fromUtf8("label_dir_elev"));
        label_dir_elev->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_dir_elev);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_4);

        lineEdit_elev = new QLineEdit(frame);
        lineEdit_elev->setObjectName(QString::fromUtf8("lineEdit_elev"));
        lineEdit_elev->setReadOnly(true);

        verticalLayout_2->addWidget(lineEdit_elev);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_4);


        verticalLayout_4->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_5);

        label_dir_depth = new QLabel(frame);
        label_dir_depth->setObjectName(QString::fromUtf8("label_dir_depth"));
        label_dir_depth->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_dir_depth);

        label_6 = new QLabel(frame);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_6);

        lineEdit_depth = new QLineEdit(frame);
        lineEdit_depth->setObjectName(QString::fromUtf8("lineEdit_depth"));
        lineEdit_depth->setReadOnly(true);

        verticalLayout_3->addWidget(lineEdit_depth);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_6);


        verticalLayout_4->addLayout(verticalLayout_3);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_8);

        label_dir_area = new QLabel(frame);
        label_dir_area->setObjectName(QString::fromUtf8("label_dir_area"));
        label_dir_area->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(label_dir_area);

        label_area = new QLabel(frame);
        label_area->setObjectName(QString::fromUtf8("label_area"));
        label_area->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(label_area);

        label_areaValue = new QLabel(frame);
        label_areaValue->setObjectName(QString::fromUtf8("label_areaValue"));
        label_areaValue->setFrameShape(QFrame::StyledPanel);
        label_areaValue->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(label_areaValue);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_7);


        verticalLayout_4->addLayout(verticalLayout_6);


        verticalLayout_5->addWidget(frame);


        retranslateUi(SegmentInfo);

        QMetaObject::connectSlotsByName(SegmentInfo);
    } // setupUi

    void retranslateUi(QWidget *SegmentInfo)
    {
        SegmentInfo->setWindowTitle(QApplication::translate("SegmentInfo", "Form", 0));
        pushButton_goto->setText(QApplication::translate("SegmentInfo", "Go to", 0));
        label_dir_width->setText(QApplication::translate("SegmentInfo", "Upper", 0));
        label_2->setText(QApplication::translate("SegmentInfo", "Width", 0));
        lineEdit_width->setText(QApplication::translate("SegmentInfo", "ft.", 0));
        label_dir_elev->setText(QApplication::translate("SegmentInfo", "Upper", 0));
        label_4->setText(QApplication::translate("SegmentInfo", "Elevation", 0));
        label_dir_depth->setText(QApplication::translate("SegmentInfo", "Upper", 0));
        label_6->setText(QApplication::translate("SegmentInfo", "Depth", 0));
        label_dir_area->setText(QApplication::translate("SegmentInfo", "Upper", 0));
        label_area->setText(QApplication::translate("SegmentInfo", "Area", 0));
        label_areaValue->setText(QApplication::translate("SegmentInfo", "ft.", 0));
    } // retranslateUi

};

namespace Ui {
    class SegmentInfo: public Ui_SegmentInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEGMENTINFO_H
