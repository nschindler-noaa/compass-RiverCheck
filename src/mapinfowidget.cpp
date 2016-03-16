#include "mapinfowidget.h"

#include <QtGui/QLayout>

mapInfoWidget::mapInfoWidget (QWidget *parent) :
    QWidget (parent)
{
    setup();
    setTitle ("");
    setData (0.0);
}

mapInfoWidget::mapInfoWidget (QString title, float value, QWidget *parent) :
    QWidget (parent)
{
    setup();
    setTitle (title);
    setData (value);
}

void mapInfoWidget::setup()
{
    name = new QLabel(this);
    valueBox = new QLineEdit(this);
    space = new QSpacerItem(0, 0, QSizePolicy::Preferred, QSizePolicy::Preferred);
    QLayout *lyout = this->layout();
    lyout->addWidget(name);
    lyout->addWidget((QWidget*)space);
    lyout->addWidget(valueBox);
}

void mapInfoWidget::setData(float value)
{
    valueBox->setText(QString::number(value, 'f', 4));
}

void mapInfoWidget::setTitle(QString title)
{
    name->setText(title);
}
