#include "qstringlisteditwidget.h"
#include "ui_qstringlisteditwidget.h"

#include <QtGui/QInputDialog>

QStringListEditWidget::QStringListEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QStringListEditWidget)
{
    ui->setupUi(this);
    setMinimumWidth(10);
    setMaximumWidth(200);
    strList = NULL;
}

QStringListEditWidget::QStringListEditWidget (QString title, QStringList *sList, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QStringListEditWidget)
{
    ui->setupUi(this);
    setMinimumWidth(10);
    setMaximumWidth(200);

    ui->label_Title->setText(title);
    setQStringList(sList);

    connect (ui->toolButton_add, SIGNAL(clicked()), SLOT(addListItem()));
    connect (ui->toolButton_remove, SIGNAL(clicked()), SLOT(removeListItem()));
    connect (ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
             SLOT(editListItem(QListWidgetItem*)));
}

QStringListEditWidget::~QStringListEditWidget()
{
    delete ui;
}

void QStringListEditWidget::setQStringList(QStringList *sList)
{
    while (ui->listWidget->count() > 0)
        ui->listWidget->takeItem(0);

    strList = sList;
    if (sList == NULL)
    {
        strList = new QStringList();
    }

    for (int i = 0; i < strList->count(); i++)
    {
        QListWidgetItem *sp = new QListWidgetItem(strList->at(i),
                    ui->listWidget);
        ui->listWidget->addItem(sp);
    }
    ui->listWidget->setAcceptDrops(true);
}

void QStringListEditWidget::addListItem ()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Add List Item"),
                                         tr(""), QLineEdit::Normal,
                                         QString(""), &ok);
    if (ok && !text.isEmpty())
    {
        QListWidgetItem *sp = new QListWidgetItem(text, ui->listWidget);
        ui->listWidget->addItem(sp);
        strList->append(text);
        emit itemAdded(text);
        emit dataChanged();
    }
}

void QStringListEditWidget::removeListItem ()
{
    int row = ui->listWidget->currentRow();
    if (row >= 0 && row < strList->count())
    {
        QListWidgetItem *sp = ui->listWidget->takeItem(row);
        strList->takeAt(row);
        emit itemRemoved(sp->text());
        emit dataChanged();
    }
}

void QStringListEditWidget::editListItem(QListWidgetItem *item)
{
    QString string (item->text());
    bool ok;
    QString text = QInputDialog::getText(this, tr("Edit List Item"),
                                         tr(""), QLineEdit::Normal,
                                         string, &ok);
    if (ok)
    {
        if (text.isEmpty())
        {
            removeListItem();
        }
        else
        {
            item->setText(text);
            emit ItemChanged(string, text);
        }
        emit dataChanged();
    }
}
