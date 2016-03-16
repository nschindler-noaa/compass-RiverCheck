#ifndef REACH_H
#define REACH_H

#include "RiverSegment.h"
#include "mapReach.h"

#define DEPTH_PADDING   0.95


/** Reach/reservoir-specific parameters. A reach is a segment of
 *  the actual river (where water flows). */
class Reach : public RiverSegment
{
    Q_OBJECT
public:
    Reach (QString rname, QString rivName = QString (""), QObject *parent = 0);

    bool parse (RiverFile *infile);
    bool parseToken (QString token, RiverFile *infile);
    bool initialize ();
    bool construct ();
    bool output(int indent, RiverFile *rfile);

    float volume;         /**< Volume at maximum reservoir level in feet^3 */
//    float velocity;       /**< Speed of the water at max reservoir level */
    float surface_area;   /**< Average area in feet^2 */
    float ave_depth;      /**< Average maximum depth in feet */
    float slope;          /**< Angle of sides, from vertical; in degrees */
    double tan_slope;     /**< tangent of slope angle */
//    float water_tt;       /**< particle travel time; computed */

    void reset ();        /**< reset all calculated values */
    void clear ();        /**< initialize everything to 0.0 */
    bool calculateGeometries (); /**< Calculates all values not given.
                            * Do after all segments are connected. */
//    bool calculateWater (); /**< Calculates vol, vel, and travel time for max
//                            * level of reach. Do after geometries calculated.  */
//    float computeVolume (float elev_chng, float upper_d, float lower_d, float wd, float slp_tan);
//    float computeVelocity (float elev_chng, float upper_d, float lower_d, float avg_fl);
//    float computeWTT (int startDay, int stopDay);


private:
//    float waterTravelTime (float avg_vel);
public slots:
//    mapReach * mapView();
//    QGraphicsScene * sideView();
//    QGraphicsScene * topView();
//    QGraphicsScene * sectionA();
//    QGraphicsScene * sectionB();

};

#endif // REACH_H
