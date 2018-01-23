/********************************************************************************
** Form generated from reading UI file 'qstringlisteditwidget.ui'
**
** Created: Fri Mar 29 11:27:31 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QSTRINGLISTEDITWIDGET_H
#define UI_QSTRINGLISTEDITWIDGET_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QListWidget>
#include <QSpacerItem>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_QStringListEditWidget
{
public:
    QAction *actionAddItem;
    QAction *actionRemoveItem;
    QVBoxLayout *verticalLayout;
    QLabel *label_Title;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout;
    QToolButton *toolButton_add;
    QSpacerItem *horizontalSpacer;
    QToolButton *toolButton_remove;

    void setupUi(QWidget *QStringListEditWidget)
    {
        if (QStringListEditWidget->objectName().isEmpty())
            QStringListEditWidget->setObjectName(QString::fromUtf8("QStringListEditWidget"));
        QStringListEditWidget->resize(262, 335);
        actionAddItem = new QAction(QStringListEditWidget);
        actionAddItem->setObjectName(QString::fromUtf8("actionAddItem"));
        actionRemoveItem = new QAction(QStringListEditWidget);
        actionRemoveItem->setObjectName(QString::fromUtf8("actionRemoveItem"));
        verticalLayout = new QVBoxLayout(QStringListEditWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_Title = new QLabel(QStringListEditWidget);
        label_Title->setObjectName(QString::fromUtf8("label_Title"));
        label_Title->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_Title);

        listWidget = new QListWidget(QStringListEditWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout->addWidget(listWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        toolButton_add = new QToolButton(QStringListEditWidget);
        toolButton_add->setObjectName(QString::fromUtf8("toolButton_add"));

        horizontalLayout->addWidget(toolButton_add);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        toolButton_remove = new QToolButton(QStringListEditWidget);
        toolButton_remove->setObjectName(QString::fromUtf8("toolButton_remove"));

        horizontalLayout->addWidget(toolButton_remove);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(QStringListEditWidget);

        QMetaObject::connectSlotsByName(QStringListEditWidget);
    } // setupUi

    void retranslateUi(QWidget *QStringListEditWidget)
    {
        QStringListEditWidget->setWindowTitle(QApplication::translate("QStringListEditWidget", "Form", 0));
        actionAddItem->setText(QApplication::translate("QStringListEditWidget", "addItem", 0));
#ifndef QT_NO_TOOLTIP
        actionAddItem->setToolTip(QApplication::translate("QStringListEditWidget", "Add item to list", 0));
#endif // QT_NO_TOOLTIP
        actionRemoveItem->setText(QApplication::translate("QStringListEditWidget", "removeItem", 0));
#ifndef QT_NO_TOOLTIP
        actionRemoveItem->setToolTip(QApplication::translate("QStringListEditWidget", "Remove Item from list", 0));
#endif // QT_NO_TOOLTIP
        label_Title->setText(QApplication::translate("QStringListEditWidget", "Title", 0));
        toolButton_add->setText(QApplication::translate("QStringListEditWidget", "+", 0));
        toolButton_remove->setText(QApplication::translate("QStringListEditWidget", "--", 0));
    } // retranslateUi

};

namespace Ui {
    class QStringListEditWidget: public Ui_QStringListEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QSTRINGLISTEDITWIDGET_H
