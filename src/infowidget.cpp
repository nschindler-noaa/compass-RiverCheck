#include "infowidget.h"

infoFloatWidget::infoFloatWidget(QWidget *parent) :
    QWidget(parent)
{
    setup();

    setLabel(QString(""));
    setData(0.0);
}

infoFloatWidget::infoFloatWidget (QString label, float data, QWidget *parent) :
    QWidget(parent)
{
    setup();

    setLabel(label);
    setData(data);
}

void infoFloatWidget::setup()
{
    lout.addWidget(&title);
    lout.addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    lout.addWidget(&edit);

    setLayout(&lout);
}

void infoFloatWidget::setLabel(QString label)
{
    title.setText(label);
}

void infoFloatWidget::setData(float data)
{
    dat = data;
    edit.clear();
    edit.setText(QString::number(dat, 'f', 2));
}

float infoFloatWidget::data()
{
    float ret = 0.0;
    bool okay = true;

    ret = edit.text().toFloat(&okay);
    if (okay)
        dat = ret;
    else
        ret = 0.0;
    return ret;
}
