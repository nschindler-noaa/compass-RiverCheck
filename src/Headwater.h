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

    void calculateFlow ();
    void fillRegulated ();   /**< fills headwaters that are regulated and labels them as such. */
    void fillUnRegulated (); /**< fills headwaters not filled in previous - fillRegulated must be called first. */
    void calculateFlowInputs ();
    void calculateFlows ();
    void calculateTemp ();
    void calculateTempInputs ();
    void calculateTemps ();

    bool getReadFlows() const;
    void setReadFlows(bool value);

    bool getRegulated() const;
    void setRegulated(bool value);

    float getFlowCoefficient() const;
    void setFlowCoefficient(float value);

    float getFlowMean() const;
    void setFlowMean(float value);

    float getElevChange (int index) const;
    void setElevChange (int index, float value);

public slots:
    void mapView();
    void sideView();
    void topView();
    void sectionA();
    void sectionB();

private:
    bool readFlows;     /**< true if flow values are read from a data file. */
    bool regulated;     /**< Whether this is a regulated or unregulated headwater.
                         *  a regulated headwater is above a regulation point
                         *  with not intervening forks.  */
    float flowCoefficient;   /**< Flow coefficient for unregulated flow. */

    float elevChange[DAYS_IN_SEASON]; /**< Delta from max */
/*    GasDistribution *gas_out; *< Output gas distribution */
/*    float *initial_gas;       *< Only defined if there is an initial gas
                               * vector which supercedes any in-river gas */

/*    float turbidity[STEPS_IN_SEASON]; *< Turbidity at each model
                                                            *time step */
/*    bool turbidity_flag;       *< 1 if input_turb = "0N" (reading turbidity),
                                                            * 0 if "Off" (propogate from above)*/

    float flowMean;          /**< Mean flow at this headwater */

};

#endif // HEADWATER_H
