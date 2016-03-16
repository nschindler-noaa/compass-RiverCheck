#ifndef QSTRINGLISTEDITDIALOG_H
#define QSTRINGLISTEDITDIALOG_H

#include <QtGui/QDialog>
#include <QStringList>

namespace Ui {
class QStringListEditDialog;
}

class QStringListEditDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit QStringListEditDialog(QWidget *parent = 0);
    QStringListEditDialog (QString title, QStringList *sList, QWidget *parent = 0);
    ~QStringListEditDialog();
    
signals:
    void dataChanged();

public slots:
    void textChanged ();
    void saveData();
    void resetData();

private:
    Ui::QStringListEditDialog *ui;
    QString title_;
    bool changed;
    bool saved;

protected:
    QStringList *strList;
    void setQStringList (QStringList *sList);

};

#endif // QSTRINGLISTEDITDIALOG_H
