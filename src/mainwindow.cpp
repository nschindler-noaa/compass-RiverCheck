#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mapScene.h"
#include "damdetaildialog.h"
#include "reachdetaildialog.h"
#include "segmentinfo.h"

#include <QDir>
#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>
#include <QStringListModel>
#include <QPrintDialog>
#include <QPrinter>

MainWindow::MainWindow (QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMinimumSize(1000, 800);

    system = new RiverSystem (this);
    riv_desc = NULL;

    connect (ui->action_File_Open, SIGNAL(triggered()), SLOT(file_open()));
    connect (ui->action_File_Save, SIGNAL(triggered()), SLOT(file_save()));
    connect (ui->action_File_Save_As, SIGNAL(triggered()), SLOT(file_save_as()));
    connect (ui->action_File_Print, SIGNAL(triggered()), SLOT(file_print()));
    connect (ui->action_File_Exit, SIGNAL(triggered()), SLOT(file_exit()));

    connect (ui->actionShow_File_Header, SIGNAL(triggered()), SLOT(show_header()));

    connect (ui->action_Help_About, SIGNAL(triggered()), SLOT(help_about()));
    connect (ui->action_Help_About_Qt, SIGNAL(triggered()), SLOT(help_aboutQt()));

    connect (ui->actionShow_Map, SIGNAL (triggered()), SLOT (showMap()));
    connect (ui->actionShow_Current_Dam, SIGNAL(triggered()), SLOT(showDamPage()));
    connect (ui->actionShow_Current_Reach, SIGNAL(triggered()), SLOT(showReachPage()));

    spec_list = new QStringListEditWidget ("Species");
    ui->verticalLayout_info->insertWidget(0, spec_list);
    connect (spec_list, SIGNAL(dataChanged()), SLOT(riverDataChanged()));
    connect (spec_list, SIGNAL(itemAdded(QString)), system, SLOT(addSpecies(QString)));
    connect (spec_list, SIGNAL(itemRemoved(QString)), system, SLOT(deleteSpecies(QString)));
    connect (spec_list, SIGNAL(ItemChanged(QString,QString)), system, SLOT(changeSpeciesName(QString,QString)));

    stck_list = new QStringListEditWidget ("Stocks");
    ui->verticalLayout_info->insertWidget(0, stck_list);
    connect (stck_list, SIGNAL(dataChanged()), SLOT(riverDataChanged()));
    connect (stck_list, SIGNAL(itemAdded(QString)), system, SLOT(addStock(QString)));
    connect (stck_list, SIGNAL(itemRemoved(QString)), system, SLOT(deleteStock(QString)));
    connect (stck_list, SIGNAL(ItemChanged(QString,QString)), system, SLOT(changeStockName(QString,QString)));

    damDialog = new DamDetailDialog (this);
    damDialogDown = new SegmentInfo (SegmentInfo::Upper, this);
    damDialogUp = new SegmentInfo (SegmentInfo::Lower, this);
    ui->horizontalLayout_damPage->addWidget(damDialogDown);
    ui->horizontalLayout_damPage->addWidget(damDialog);
    ui->horizontalLayout_damPage->addWidget(damDialogUp);
    connect (damDialog, SIGNAL(dataChanged()), SLOT(riverDataChanged()));
    connect (damDialogDown, SIGNAL(gotoSegment(RiverSegment *)), SLOT(displaySegment(RiverSegment*)));
    connect (damDialogUp, SIGNAL(gotoSegment(RiverSegment*)), SLOT(displaySegment(RiverSegment*)));

    reachDialog = new ReachDetailDialog (this);
    reachDialogDown = new SegmentInfo (SegmentInfo::Upper, this);
    reachDialogUp = new SegmentInfo (SegmentInfo::Lower, this);
    reachDialogFork = new SegmentInfo (SegmentInfo::Lower, this);
    ui->horizontalLayout_reachPage->addWidget(reachDialogDown);
    ui->horizontalLayout_reachPage->addWidget(reachDialog);
    ui->horizontalLayout_reachPage->addWidget(reachDialogUp);
    ui->horizontalLayout_reachPage->addWidget(reachDialogFork);
    connect (reachDialog, SIGNAL(dataChanged()), SLOT(riverDataChanged()));
    connect (reachDialogDown, SIGNAL(gotoSegment(RiverSegment *)), SLOT(displaySegment(RiverSegment*)));
    connect (reachDialogUp, SIGNAL(gotoSegment(RiverSegment*)), SLOT(displaySegment(RiverSegment*)));
    connect (reachDialogFork, SIGNAL(gotoSegment(RiverSegment*)), SLOT(displaySegment(RiverSegment*)));

    file_open();
    showMap();
}

MainWindow::~MainWindow ()
{
    if (dataChanged)
    {
        saveChanges();
    }
    if (system != NULL)
        delete system;
    system = NULL;
    if (riv_desc != NULL)
        delete riv_desc;
    riv_desc = NULL;
    delete ui;
}

bool MainWindow::saveChanges()
{
    bool saved = true;
    QMessageBox msgBox ;
    msgBox.setText("The river description has been modified.");
    msgBox.setInformativeText("Do you want to save your changes?");
    QPushButton *newButton = msgBox.addButton(tr("Save as New"), QMessageBox::ActionRole);
    QPushButton *saveButton = msgBox.addButton(tr("Save"), QMessageBox::YesRole);
    QPushButton *discardButton = msgBox.addButton(tr("Discard"), QMessageBox::NoRole);

    msgBox.exec();

    if (msgBox.clickedButton() == (QAbstractButton *)newButton)
    {
        file_save_as ();
    }
    else if (msgBox.clickedButton() == (QAbstractButton *)saveButton)
    {
        file_save ();
    }
    else if (msgBox.clickedButton() == (QAbstractButton *)discardButton)
    {
       file_revert();
       saved = false ;
    }
    return saved;
}

void MainWindow::file_open ()
{
    QString filename = QFileDialog::getOpenFileName
            (this, OPEN_FILE, QDir::current().path(), FILE_FILTER);
    riv_desc = new RiverFile (filename, this);
    connect (riv_desc, SIGNAL(dataChanged()), SLOT(riverDataChanged()));

    openFile();
    currentDam = NULL;
    currentReach = NULL;
}

void MainWindow::file_save ()
{
    saveFile ();
}

void MainWindow::file_save_as ()
{
    // Dialog to get new file name
    QString newfile = QFileDialog::getSaveFileName
            (this, SAVE_FILE, QDir::current().path(), FILE_FILTER);

    saveFileAs(newfile);
}

void MainWindow::file_revert()
{
    if (riv_desc != NULL)
    {
        riv_desc->close();
        openFile();
    }
}

void MainWindow::show_header()
{
    riv_desc->editHeader();
}

void MainWindow::file_print ()
{
    if (dataChanged)
        saveChanges();
    printFile();
}

void MainWindow::file_exit ()
{
    close();
}

void MainWindow::help_about ()
{
    QString about ("");
    about.append(QString("This application is used to examine and edit river description files (.desc) "));
    about.append(QString("for the COMPASS application. \n\nIt is programmed in C++ with Qt.\n\n"));
    about.append(QString("Version number:\t%1\n").arg(metadata::version()));
    about.append(QString("Release date:\t\t%1\n").arg(metadata::versionDate()));
    about.append(QString("Programmed by:\t%1\n\n").arg(metadata::modifier()));
    about.append(QString("Application created by %1 on %2\n").arg(
                     metadata::creator(), metadata::createdDate()));
//      QMessageBox::about(this, "River Description File checker", "Programmed by Neal Schindler");
    QMessageBox::about(this, metadata::name(), about);//"Programmed by Neal Schindler");
}

void MainWindow::help_aboutQt ()
{
    QMessageBox::aboutQt(this, QString("About Qt used for %1.").arg(metadata::name()));//River Description File checker.");
}

void MainWindow::openFile ()
{
    bool okay = true;
    showMap();

    if (riv_desc != NULL)
    {
        if (system != NULL)
            delete system;
        system = NULL;

        system = new RiverSystem (this);
        system->initialize();
        okay = system->parseDesc(riv_desc);
        if (okay)
        {
            system->construct();
            displaySystem();

            ui->RiverSystemName->setText(QString ("%1 %2").arg (system->riverNames->at(0), "River Basin"));
        }
        else
        {
            int ret = QMessageBox::warning(this, tr("River Description File"),
                tr("The parsing routine ran into a problem with the file on line %1.\n"
                   "Do you want to open a different file?").arg(QString::number(riv_desc->line)),
                QMessageBox::Ok | QMessageBox::Cancel);
            if (ret == QMessageBox::Ok)
                file_open();

        }
    }
    // find any errors
    for (int i = 0; i < system->rivers->count(); i++)
        for (int j = 0; j < system->rivers->at (i)->segments->count(); j++)
            system->rivers->at(i)->segments->at(j)->findErrors();

    riverDataSaved();
}

void MainWindow::saveFile ()
{
    system->writeDesc (riv_desc);
    riverDataSaved();
}

void MainWindow::saveFileAs (QString filename)
{
    RiverFile *newfile;
    if (!filename.isEmpty() && filename != riv_desc->fileName())
    {
        riv_desc->close();
        newfile = new RiverFile (filename, this);
        newfile->copyHeader(riv_desc);
        delete riv_desc;
        riv_desc = newfile;
    }
    saveFile();
}

void MainWindow::printFile ()
{
    QPrinter printer;
    QPrintDialog printDialog (&printer, this);
    int result = printDialog.exec();
    if (result == QDialog::Accepted)
    {
        // print the file
        ;

    }
}


void MainWindow::displaySystem ()
{
    spec_list->setQStringList(system->speciesNames);
    stck_list->setQStringList(system->stockNames);

    map = new mapScene (system, ui->mapView);
    connect (map, SIGNAL(showDetail(RiverSegment *)), SLOT(displaySegment(RiverSegment *)));
    connect (map, SIGNAL(deleteSegment(RiverSegment *)), system, SLOT(deleteSegment(RiverSegment *)));

    ui->mapView->setScene(map);
    ui->mapView->setSceneRect(map->boundingRect());
}

void MainWindow::showMap()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::displaySegment(RiverSegment *seg)
{
    switch (seg->type)
    {
    case RiverSegment::DamSegment:
    {
        Dam *dam = (Dam *)seg;
        currentDam = dam;
        showDamPage ();
        break;
    }
    case RiverSegment::ReachSegment:
    {
        Reach *reach = (Reach *)seg;
        currentReach = reach;
        showReachPage ();
        break;
    }
    case RiverSegment::HeadwaterSegment:
    default:
        showMap();
        break;
    }
}

void MainWindow::showDamPage()
{
    if (currentDam == NULL)
    {
        if (system->dams->count() > 0)
            currentDam = (Dam *)(system->findSegment(system->dams->at(0)));
    }

    if (currentDam == NULL)
    {
        showMap();
    }
    else
    {
        ui->DamName->setText(*currentDam->name);
        damDialog->setSegment(currentDam);
        damDialogDown->addSegment(currentDam->down);
        if (currentDam->up == NULL)
            damDialogUp->hide();
        else
        {
            damDialogUp->addSegment(currentDam->up);
            damDialogUp->show();
        }
        ui->stackedWidget->setCurrentIndex(1);
    }
}

void MainWindow::showDam(Dam *dam)
{
    currentDam = dam;
    showDamPage();
}

void MainWindow::showReachPage()
{
    if (currentReach == NULL)
    {
        if (system->reaches->count() > 0)
            currentReach = (Reach *)(system->findSegment(system->reaches->at(0)));
    }

    if (currentReach == NULL)
    {
        showMap();
    }
    else
    {
        ui->ReachName->setText(*currentReach->name);
        reachDialog->setSegment(currentReach);
        if (currentReach->down == NULL)
            reachDialogDown->hide();
        else
        {
            reachDialogDown->addSegment(currentReach->down);
            reachDialogDown->show();
        }
        if (currentReach->up == NULL)
            reachDialogUp->hide();
        else
        {
            reachDialogUp->addSegment(currentReach->up);
            reachDialogUp->show();
        }
        if (currentReach->fork == NULL)
            reachDialogFork->hide();
        else
        {
            reachDialogFork->addSegment(currentReach->fork);
            reachDialogFork->show();
        }
        ui->stackedWidget->setCurrentIndex(2);
    }
}

void MainWindow::showReach(Reach *reach)
{
    currentReach = reach;
    showReachPage ();
}

void MainWindow::riverDataChanged (RiverSegment *seg)
{
    dataChanged = true;
    setWindowTitle(QString ("River check: * %1 *").arg(
                       riv_desc->fileName()));

}


void MainWindow::riverDataSaved ()
{
    dataChanged = false;
    setWindowTitle(QString ("River check: %1").arg(
                       riv_desc->fileName()));
}
