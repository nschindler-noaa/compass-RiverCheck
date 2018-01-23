/********************************************************************************
** Form generated from reading UI file 'qstringlisteditdialog.ui'
**
** Created: Fri Mar 29 11:26:45 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QSTRINGLISTEDITDIALOG_H
#define UI_QSTRINGLISTEDITDIALOG_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QDialog>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QSpacerItem>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QStringListEditDialog
{
public:
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *plainTextEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_reset;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_save;
    QPushButton *pushButton_close;

    void setupUi(QDialog *QStringListEditDialog)
    {
        if (QStringListEditDialog->objectName().isEmpty())
            QStringListEditDialog->setObjectName(QString::fromUtf8("QStringListEditDialog"));
        QStringListEditDialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(QStringListEditDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        plainTextEdit = new QPlainTextEdit(QStringListEditDialog);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));

        verticalLayout->addWidget(plainTextEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_reset = new QPushButton(QStringListEditDialog);
        pushButton_reset->setObjectName(QString::fromUtf8("pushButton_reset"));

        horizontalLayout->addWidget(pushButton_reset);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_save = new QPushButton(QStringListEditDialog);
        pushButton_save->setObjectName(QString::fromUtf8("pushButton_save"));

        horizontalLayout->addWidget(pushButton_save);

        pushButton_close = new QPushButton(QStringListEditDialog);
        pushButton_close->setObjectName(QString::fromUtf8("pushButton_close"));

        horizontalLayout->addWidget(pushButton_close);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(QStringListEditDialog);

        QMetaObject::connectSlotsByName(QStringListEditDialog);
    } // setupUi

    void retranslateUi(QDialog *QStringListEditDialog)
    {
        QStringListEditDialog->setWindowTitle(QApplication::translate("QStringListEditDialog", "Dialog", 0));
        pushButton_reset->setText(QApplication::translate("QStringListEditDialog", "Reset", 0));
        pushButton_save->setText(QApplication::translate("QStringListEditDialog", "Save", 0));
        pushButton_close->setText(QApplication::translate("QStringListEditDialog", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class QStringListEditDialog: public Ui_QStringListEditDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QSTRINGLISTEDITDIALOG_H
