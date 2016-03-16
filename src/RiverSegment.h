#ifndef RIVERSEGMENT_H
#define RIVERSEGMENT_H

#include <QObject>
#include <QList>
#include <QString>
#include <QtGui/QGraphicsScene>

#include "RiverFile.h"
#include "RiverPoint.h"

#include "definitions.h"

class RiverSegment : public QObject
{
    Q_OBJECT
public:
    RiverSegment (QString rivName = QString(""), QObject *parent = 0);
    RiverSegment (const RiverSegment &rhs);
    ~RiverSegment ();

    void setup ();
    void clear ();        /**< initialize everything to 0.0 */
    void reset ();        /**< reset all calculated values */
    bool parseToken (QString token, RiverFile *infile);

    virtual bool parse (RiverFile *infile);
    virtual bool initialize ();
    virtual bool construct ();
    virtual bool output (int indent, RiverFile *rfile);
    bool outputCourse (int indent, RiverFile * rfile);

    QString *riverName;
    QString *name;
    QString *abbrev;

    QList<RiverPoint *> course; /**< List of river points that make up the river course.  */
    RiverPoint * top ();        /**< The point at the up stream end of the segment. */
    RiverPoint * bottom ();     /**< The point at the down stream end of the segment. */
    int currentPoint;           /**< Index of the current point. */
    RiverPoint * nextPointUp ();/**< Next point up stream. */
    RiverPoint * nextPointDn ();/**< Next point down stream. */
    float distance (RiverPoint * loc); /**< calculates the distance in miles
                                to the bottom (downriver) end of the segment */

//    QList<RiverSite *> tributaries;


    enum SegmentType {
        DamSegment,
        ReachSegment,
        HeadwaterSegment
    };
    SegmentType type;  /**< type of river segment. */

    bool regPoint;     /**< True if this is a flow regulation point. */
    float flow_max;    /**< Maximum flow. Can not exceed maximum flow of river. */
    float flow_min;    /**< Minimum flow. */

    float width;       /**< Average width in feet */
    float lower_width; /**< Width of the reach at the lower end in feet */
    float upper_width; /**< Width of the reach at the upper end in feet */
    float lower_depth; /**< Maximum depth at lower end of reach in feet */
    float upper_depth; /**< Maximum depth at upper end of reach in feet */
    float lower_elev;  /**< Height above sea level, or bottom of the river
                         *  at the lower end of reach in feet. */
    float upper_elev;  /**< Height above sea level, or bottom of the river
                         *  at the upper end of reach in feet (calculated). */
    float length;      /**< Length of segment in miles */
    float bed_width;      /**< Width of the riverbed for this reach in feet */

    RiverSegment *up;  /**< next segment up the same river.*/
    RiverSegment *fork;/**< next segment up for different river. */
    RiverSegment *down;/**< next segment down the (same) river. */

//    /** Division of river into separate flows. Also used for spill side location */
//    enum Location {
//        Right,         /**< Right side of the segment */
//        Left,          /**< Left side of the segment */
//        FlowDivisions, /**< Number of flow divisions */
//        Middle         /**< Currently not used */
//    };

    /* Errors that can occur in a segment or between segments. They are 'OR'ed together.
    enum SegError {
        LatLonUpper = 0x1,
        LatLonLower = 0x2,
        ElevUpper = 0x4,
        ElevLower = 0x8,
        SlopeIncorrect = 0x10,
        SpillwayWidth = 0x20
    };*/

    enum Impounded {
        NotImpounded,
        PartiallyImpounded,
        FullyImpounded
    };

    Impounded impound ();

    short error;  /**< flag that contains error masks. See /ref errors below for more information. */
    short findErrors ();

    QPen normalPen;
    QPen backgroundPen;

private:

signals:

public slots:
/*    QGraphicsScene * mapView();
    QGraphicsScene * sideView();
    QGraphicsScene * topView();
    QGraphicsScene * sectionA();
    QGraphicsScene * sectionB();
*/
};

/** Errors. (Tried enum, but caused trouble in compiling) */
#define LatLonUpper    (0x1)
#define LatLonLower    (0x2)
#define ElevUpper      (0x4)
#define ElevLower      (0x8)
#define DepthUpper     (0x10)
#define DepthLower     (0x20)
#define SlopeIncorrect (0x40)
#define SpillwayWidth  (0x80)
#define BadPhysics     (0x100)

#endif // RIVERSEGMENT_H
