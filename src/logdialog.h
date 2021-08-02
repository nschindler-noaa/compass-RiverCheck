#ifndef LOGDIALOG_H
#define LOGDIALOG_H

#include "Log.h"

#include <QDialog>

namespace Ui {
class LogDialog;
}

class LogDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LogDialog(Log *loginst, QWidget *parent = nullptr);
    ~LogDialog() override;

protected:
    void display(QString text);

private:
    Ui::LogDialog *ui;

    Log *log;

};

#endif // LOGDIALOG_H
