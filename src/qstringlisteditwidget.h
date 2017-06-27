#ifndef QSTRINGLISTEDITWIDGET_H
#define QSTRINGLISTEDITWIDGET_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class QStringListEditWidget;
}

class QStringListEditWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit QStringListEditWidget(QWidget *parent = 0);
    QStringListEditWidget(QString title, QStringList *strList = 0, QWidget *parent = 0);
    ~QStringListEditWidget();
    
private:
    Ui::QStringListEditWidget *ui;
    bool changed;

public slots:
    void setQStringList (QStringList *sList);
    void addListItem ();
    void removeListItem ();
    void editListItem (QListWidgetItem *item);

signals:
    void itemAdded (QString item);
    void itemRemoved (QString item);
    void ItemChanged (QString oldItem, QString newItem);
    void dataChanged();

protected:
    QStringList *strList;

};

#endif // QSTRINGLISTEDITWIDGET_H
