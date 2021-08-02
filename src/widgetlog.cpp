#include "widgetlog.h"
#include "ui_widgetlog.h"

#include "Log.h"

WidgetLog::WidgetLog(QWidget *parent) :
    QWidget(parent), Log(DEFAULT_LOGNAME, parent),
    ui(new Ui::WidgetLog)
{
    ui->setupUi(this);
}

WidgetLog::~WidgetLog()
{
    delete ui;
}

void WidgetLog::display(QString txt)
{
    ui->plainTextEdit->appendPlainText(txt);
}
