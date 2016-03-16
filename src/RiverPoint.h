#ifndef RIVERPOINT_H
#define RIVERPOINT_H

#include <QString>

#include "RiverFile.h"

#define GREAT_CIRCLE

class dms
{
public:
    dms ();
    dms (QString str);
    dms (int d, int m, int s, QString dir);
    dms (QString d, QString m, QString s, QString dir);
    dms (float val);
    dms (const dms &rhs);
    void setup ();
    ~dms ();

    bool equals (const dms rhs);

    int deg;
    int min;
    int sec;
    float degrees;
    QString *direction;
    short sign;
    QString line;

    float value ();
    void setText ();
    QString text ();
    float setValue (float val);
    float setValue (int degs, int mins, int secs, QString dir);
    float setValue (QString degs, QString mins, QString secs, QString dir);

private:
    double gc_dist (double y0, double x0, double y1, double x1);
};

/*

class RiverPoint
{
public:
    explicit RiverPoint(QObject *parent = 0);
    RiverPoint (const RiverPoint &other);

    const float lat () {return latitude;}
    const float lon () {return longitude;}
    const float width () {return wide;}

    float setLon (int d, int m, int s);
    float setLat (int d, int m, int s);
    float setLon (const float x);
    float setLat (const float x);
    float setWidth (const float w);

private:
    float latitude;
    float longitude;
    float wide;
};
*/
class RiverPoint
{
public:
    RiverPoint ();
    RiverPoint(const RiverPoint &other);
    ~RiverPoint ();
    void clear ();
    void initialize ();

    dms *latitude;
    dms *longitude;
    float width;
    bool readLatLon (QString *line);
    float setLongitude (float ln);
    float setLongitude (int d, int m, int s, QString dir);
    float setLongitude (QString deg, QString min, QString sec, QString dir);
    void setLonDir (QString ew);
    float setLatitude (float lt);
    float setLatitude (int d, int m, int s, QString dir);
    float setLatitude (QString deg, QString min, QString sec, QString dir);
    void setLatDir (QString ns);
    float setWidth (float wd);
    void reset ();

    bool equals (const RiverPoint rhs);
    bool operator == (const RiverPoint rhs);
    bool operator != (const RiverPoint rhs);

    double calcDistance (RiverPoint *pt);

    QString text ();
    bool output (int indent, RiverFile *rfile);
};



#endif // RIVERPOINT_H
