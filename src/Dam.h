#ifndef DAM_H
#define DAM_H

#include <QList>

#include "definitions.h"
#include "RiverSegment.h"
#include "PowerHouse.h"
#include "RSW.h"
#include "mapDam.h"


#define DAM_TAILRACE_DEFAULT  100.0

/** \struct basin
 * \brief A structure to represent a storage basin associated with a dam.
 */
struct basin
{
public:
    float min_volume;         /**< Minimum allowable volume */
    float max_volume;         /**< Maximum allowable volume */
};
typedef struct basin Basin;
Basin * new_basin ();
void delete_basin (Basin *bsn);


/** \class Dam
 * \brief Dam-specific segment data (i.e. the dam parameters) */
class Dam : public RiverSegment
{
public:

    Dam (QString dname, QString rivName = QString (""), QObject *parent = 0);
    Dam (const Dam &rhs);
    ~Dam ();
    void clear ();
    void reset ();
    bool parse (RiverFile *infile);
    bool parseToken (QString token, RiverFile *infile);
    bool initialize ();
    bool construct ();
    bool output(int indent, RiverFile *rfile);

    /** Pointer to the storage basin info */
    Basin *basin;      /**< Storage basin pointer. If no basin, this is NULL. */

    /* physical characteristics; some may be computed from others,
     * depending on which were found in the river description file.
     */
//    QList<PowerHouse *> powerhouses;
    QList <float> powerhouse_cap;

    float tailrace_width; /**< Tailrace width (ft) - lower width */
    float tailrace_length;/**< Tailrace length in ft */
//    float base_elev;
    float forebay_elev;   /**< Forebay elevation (ft) */
    float tailrace_elev;  /**< Tailrace elevation (ft) */
    float full_head;      /**< Full pool head */
    float full_fb_depth;  /**< Full pool forebay depth - upper depth */
    float bypass_elev;    /**< Height of bypass */
    float floor_elev;     /**< Dam base elevation (ft) */

    int collector;        /**< Whether or not this dam is a collector dam.
                           * (i.e. it has PIT tag detectors and a
                           * different kind of bypass system which can
                           * produce latent effects) */

    int ngates;           /**< Number of spill gates */
    float gate_width;     /**< Width of each gate (ft) */
    float pergate;        /**< Max spill per gate */
    float spillway_width; /**< Spillway width */
    float basin_length;   /**< Stilling basin depth */
    float sgr;            /**< Specific gravity of roller */

    Location spill_side;  /**< Spillway location. */

    /* Removable spill weirs */
    QList <RSW *> spill_weirs;

public slots:
//    mapDam * mapView();
//    QGraphicsScene * sideView();
//    QGraphicsScene * topView();
//    QGraphicsScene * sectionA();
//    QGraphicsScene * sectionB();

signals:
    void dataChanged();
    void displayDetail (RiverSegment *seg);
};

#endif // DAM_H


