#include "qstringlisteditdialog.h"
#include "ui_qstringlisteditdialog.h"

#include <QtGui/QMessageBox>

QStringListEditDialog::QStringListEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QStringListEditDialog)
{
    ui->setupUi(this);
}

QStringListEditDialog::QStringListEditDialog(QString title, QStringList *sList, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QStringListEditDialog)
{
    ui->setupUi(this);
    title_ = QString(title);

    setWindowTitle (title_);
    setQStringList (sList);

    connect (ui->plainTextEdit, SIGNAL(textChanged()), SLOT(textChanged()));
    changed = false;
    saved = true;

    connect (ui->pushButton_save, SIGNAL(clicked()), SLOT(saveData()));
    connect (ui->pushButton_reset, SIGNAL(clicked()), SLOT(resetData()));
    connect (ui->pushButton_close, SIGNAL(clicked()), SLOT(close()));
}

QStringListEditDialog::~QStringListEditDialog()
{
    if (!saved)
    {
        QMessageBox msgBox ;
        msgBox.setText("The text has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        QPushButton *saveButton = msgBox.addButton(tr("Save"), QMessageBox::YesRole);
        QPushButton *discardButton = msgBox.addButton(tr("Discard"), QMessageBox::NoRole);

        msgBox.exec();

        if (msgBox.clickedButton() == (QAbstractButton *)saveButton)
        {
            saveData ();
        }
        else if (msgBox.clickedButton() == (QAbstractButton*)discardButton)
        {
            changed = false;
        }
    }

    if (changed)
        emit dataChanged();

    delete ui;
}

void QStringListEditDialog::setQStringList(QStringList *sList)
{
    strList = sList;
    resetData();
}

void QStringListEditDialog::textChanged()
{
    if (!changed)
    {
        QString changedTitle (QString ("* %1 *").arg(title_));
        setWindowTitle(changedTitle);
//        emit dataChanged ();
        changed = true;
        saved = false;
    }
}

void QStringListEditDialog::saveData()
{
    QString text (ui->plainTextEdit->toPlainText());
    QStringList slist (text.split('\n', QString::KeepEmptyParts));

    if (changed)
    {
        strList->clear();
        for (int i = 0; i < slist.count(); i++)
        {
            strList->append(slist.at(i));
        }
        setWindowTitle(title_);
        saved = true;
    //    emit dataChanged ();
    }
}

void QStringListEditDialog::resetData()
{
    QString text ("");

    if (changed)
    {
        for (int i = 0; i < strList->count(); i++)
        {
            text.append (strList->at(i));
            text.append ('\n');
        }
        ui->plainTextEdit->setPlainText(text);
        setWindowTitle(title_);
        changed = false;
        saved = true;
    }
}
