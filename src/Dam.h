#ifndef DAM_H
#define DAM_H

#include <QList>

#include "definitions.h"
#include "RiverSegment.h"
#include "PowerHouse.h"
#include "Period.h"
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
    QList<float> volume;      /**< Volume per day (DAYS_IN_SEASON) */
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

    Basin *getBasin() const;
    void setBasin(Basin *value);

    QList<PowerHouse *> getPowerhouses() const;
    void setPowerhouses(const QList<PowerHouse *> &value);
    int getNumPowerhouses ();

    float getTailrace_width() const;
    void setTailrace_width(float value);

    float getTailraceWidth() const;
    void setTailraceWidth(float value);

    float getTailraceLength() const;
    void setTailraceLength(float value);

    float getTailraceElev() const;
    void setTailraceElev(float value);

    float getForebayElev() const;
    void setForebayElev(float value);

    float getFullFbDepth() const;
    void setFullFbDepth(float value);

    float getFullHead() const;
    void setFullHead(float value);

    float getBypassElev() const;
    void setBypassElev(float value);

    float getFloorElev() const;
    void setFloorElev(float value);

    int getCollector() const;
    void setCollector(int value);

    int getNgates() const;
    void setNgates(int value);

    float getGateWidth() const;
    void setGateWidth(float value);

    float getPergate() const;
    void setPergate(float value);

    float getSpillwayWidth() const;
    void setSpillwayWidth(float value);

    float getStillingLength() const;
    void setStillingLength(float value);

    float getSgr() const;
    void setSgr(float value);

    Location getSpillSide() const;
    void setSpillSide(const Location &value);

    QList<RSW *> getSpillWeirs() const;
    void setSpillWeirs(const QList<RSW *> &value);
    int getNumSpillWeirs ();

private:
    /** Pointer to the storage basin info */
    Basin *storage;  /**< Storage basin pointer. If no basin, this is nullptr. */

    /* physical characteristics; some may be computed from others,
     * depending on which were found in the river description file.
     */
    QList<PowerHouse *> powerhouses;
//    QList <float> powerhouse_cap;

    float tailraceWidth; /**< Tailrace width (ft) - lower width */
    float tailraceLength;/**< Tailrace length in ft */
    float tailraceElev;  /**< Tailrace elevation (ft) */
//    float baseElev;
    float forebayElev;   /**< Forebay elevation (ft) */
    float fullFbDepth;   /**< Full pool forebay depth - upper depth */
    float fullHead;      /**< Full pool head */
    float bypassElev;    /**< Height of bypass */
    float floorElev;     /**< Dam base elevation (ft) */

    int collector;       /**< Whether or not this dam is a collector dam.
                           * (i.e. it has PIT tag detectors and a
                           * different kind of bypass system which can
                           * produce latent effects) */

    int ngates;          /**< Number of spill gates */
    float gateWidth;     /**< Width of each gate (ft) */
    float pergate;       /**< Max spill per gate */
    float spillwayWidth; /**< Spillway width */
    float stillingLength; /**< Stilling basin depth */
    float sgr;           /**< Specific gravity of roller */

    Location spillSide;  /**< Spillway location. */

    /* Removable spill weirs */
    QList<RSW *> spillWeirs;

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


