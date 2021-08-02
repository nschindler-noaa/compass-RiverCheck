#include "logdialog.h"
#include "ui_logdialog.h"

LogDialog::LogDialog(Log *loginst, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogDialog)
{
    ui->setupUi(this);
    log = loginst;
}

LogDialog::~LogDialog()
{
    delete ui;
}

void LogDialog::display(QString text)
{
    text.append('\n');
    ui->plainTextEdit->appendPlainText(text);
}
