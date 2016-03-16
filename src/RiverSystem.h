#ifndef RIVERSYSTEM_H
#define RIVERSYSTEM_H

#include <QObject>
#include <QStringList>
//#include <QList>
#include "River.h"
#include "RiverSite.h"
#include "Species.h"

class River;
class Reach;

class RiverSystem : public QObject
{
    Q_OBJECT

public:
    RiverSystem (QObject *parent = 0);
    RiverSystem (RiverFile *rivfile, QObject *parent = 0);
    ~RiverSystem ();
    void setup ();
    void reset ();
    void deleteAll ();

    QList <River *> *rivers;
    QList <Species *> *species;
    QList <Stock *> *stocks;
    QList <RiverSite *> *releaseSites;

    QStringList *speciesNames;
    QStringList *stockNames;
    QStringList *riverNames;
    QStringList *powerhouses;
    QStringList *dams;
    QStringList *reaches;
    QStringList *headwaters;
    QStringList *basins;

    River *findRiver (QString name);
    RiverSegment *findSegment (QString name);
    RiverSegment *findSegment (RiverPoint *pt);
    Species *findSpecies (QString name);
    Stock *findStock (QString name);
    RiverSite *findReleaseSite (QString name);


signals:
    void constructed (bool okay);
//    void flows_computed (bool okay);
//    void temps_computed (bool okay);


public slots:
    bool parseDesc (RiverFile *rfile);
    bool parse (RiverFile *rfile);
    bool initialize ();
    bool construct ();
    void markRegulationPts ();
    RiverSegment *mouth();
    bool writeDesc (RiverFile *rfile);
    bool output (RiverFile *rfile);

    void addSpecies (QString name);
    void deleteSpecies (QString name);
    void changeSpeciesName (QString oldName, QString newName);
    void addStock (QString name);
    void deleteStock (QString name);
    void changeStockName (QString oldName, QString newName);

    void addDam (Dam *dam);
    void deleteDam (Dam *dam);
    void addReach (Reach *rch);
    void deleteReach (Reach *reach);
    void addHeadwater (Headwater *hwtr);
    void adjustReaches (Reach *downReach, Reach *upReach, QList<Reach *>reaches);

    void addSegment (RiverSegment *seg);
    void deleteSegment (QString name);
    void deleteSegment (RiverSegment *seg);

private:
};

//extern RiverSystem *riverSystem;

#endif // RIVERSYSTEM_H
