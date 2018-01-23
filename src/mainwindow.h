#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

#include "RiverFile.h"
#include "RiverSystem.h"
#include "mapScene.h"
#include "qstringlisteditwidget.h"
#include "damdetaildialog.h"
#include "reachdetaildialog.h"
#include "segmentinfo.h"
#include "metadata.h"

#define OPEN_FILE tr("Open river description file.")
#define SAVE_FILE tr("Save river description file.")
#define FILE_FILTER tr("River Description Files (*.desc)")

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
    void openFile ();
    void saveFile ();
    void saveFileAs (QString filename = QString(""));
    void printFile ();
//    void exit ();

//    void helpAbout ();



private:
    Ui::MainWindow *ui;

    RiverFile *riv_desc;
    RiverSystem *system;
    bool dataChanged;
    bool saveChanges();

    mapScene *map;

    QStringListEditWidget *spec_list;
    QStringListEditWidget *stck_list;

    SegmentInfo *damDialogDown;
    SegmentInfo *damDialogUp;
    DamDetailDialog *damDialog;
    Dam *currentDam;
    SegmentInfo *reachDialogDown;
    SegmentInfo *reachDialogUp;
    SegmentInfo *reachDialogFork;
    ReachDetailDialog *reachDialog;
    Reach *currentReach;

private slots:
    void displaySystem ();
    void displaySegment (RiverSegment *seg);

    void showMap ();
    void showDamPage ();
    void showDam (Dam *dam);
    void showReachPage ();
    void showReach (Reach *reach);

    void file_open ();
    void file_save ();
    void file_save_as ();
    void file_revert ();
    void file_print ();
    void file_exit ();

    void show_header ();

    void help_about ();
    void help_aboutQt ();

public slots:
    void riverDataChanged (RiverSegment *seg = 0);
    void riverDataSaved ();

};

#endif // MAINWINDOW_H
