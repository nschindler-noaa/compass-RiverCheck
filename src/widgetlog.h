#ifndef WIDGETLOG_H
#define WIDGETLOG_H

#include <QString>
#include <QWidget>

#include "Log.h"

namespace Ui {
class WidgetLog;
}

class WidgetLog : public QWidget, Log
{
    Q_OBJECT

public:
    explicit WidgetLog(QWidget *parent = nullptr);
    ~WidgetLog();

protected:
    void display(QString txt) override;

private:
    Ui::WidgetLog *ui;
};

#endif // WIDGETLOG_H
