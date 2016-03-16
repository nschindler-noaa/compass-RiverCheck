#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QLineEdit>
#include <QtGui/QHBoxLayout>


class infoFloatWidget : public QWidget
{
    Q_OBJECT
public:
    explicit infoFloatWidget (QWidget *parent = 0);
    infoFloatWidget (QString label, float data, QWidget *parent = 0);
    
signals:
    void dataChanged (float);
    
public slots:
    void setLabel (QString label);
    void setData (float data);
    float data ();

protected:
    QHBoxLayout lout;
    QLabel title;
    QLineEdit edit;

    void setup();

    float dat;
};

#endif // INFOWIDGET_H
