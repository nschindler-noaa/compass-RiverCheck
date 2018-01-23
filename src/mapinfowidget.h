#ifndef MAPINFOWIDGET_H
#define MAPINFOWIDGET_H

#include <QWidget>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QSpacerItem>

class mapInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit mapInfoWidget(QWidget *parent = 0);
    mapInfoWidget (QString title, float value = 0.0, QWidget *parent = 0);
    
    void setup();

signals:
    void dataChanged (float value);
    
public slots:
    void setData (float value);
    void setTitle (QString title);

protected:
    QLabel *name;
    QLineEdit *valueBox;
    QSpacerItem *space;
    
};

#endif // MAPINFOWIDGET_H
