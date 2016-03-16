#ifndef HEADWATER_H
#define HEADWATER_H

#include "RiverSegment.h"

class Headwater : public RiverSegment
{
public:
    Headwater (QString hname, QString rivName = QString (""), QObject *parent = 0);

    void clear ();

    bool parse (RiverFile *infile);
    bool parseToken (QString token, RiverFile *infile);
    bool initialize();
    bool output (int indent, RiverFile *rfile);

    bool read_flows;     /**< true if flow values are read from a data file. */
    bool regulated;          /**< Whether this is a regulated or unregulated headwater */
    float flow_coefficient;   /**< For unregulated flow */

    float elev_change[DAYS_IN_SEASON]; /**< Delta from max */
/*    GasDistribution *gas_out; *< Output gas distribution */
/*    float *initial_gas;       *< Only defined if there is an initial gas
                               * vector which supercedes any in-river gas */

/*    float turbidity[STEPS_IN_SEASON]; *< Turbidity at each model
                                                            *time step */
/*    int turbidity_flag;       *< 1 if input_turb = "0N" (reading turbidity),
                                                            * 0 if "Off" (propogate from above)*/

    float flow_mean;          /**< Mean flow at this headwater */

    void calculateFlow ();
    void fillRegulated ();   /**< fills headwaters that are regulated and labels them as such. */
    void fillUnRegulated (); /**< fills headwaters not filled in previous - fillRegulated must be called first. */
    void calculateFlowInputs ();
    void calculateFlows ();
    void calculateTemp ();
    void calculateTempInputs ();
    void calculateTemps ();

public slots:
    void mapView();
    void sideView();
    void topView();
    void sectionA();
    void sectionB();

};

#endif // HEADWATER_H
