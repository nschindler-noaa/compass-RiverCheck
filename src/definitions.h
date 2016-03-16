#ifndef DEFINITIONS_H
#define DEFINITIONS_H

/** This file includes various definitions that are used throughout COMPASS.
  */

#define DAYS_IN_SEASON       (366) /**< Number of days in year */
#define DAM_SLICES_PER_DAY     (2) /**< Number of time slices per day at a dam */
#define STEPS_PER_DAY   DAM_SLICES_PER_DAY /**< Same as DAM_SLICES_PER_DAY */
#define DAM_SLICES_IN_SEASON (732) /**< DAM_SLICES_PER_DAY * DAYS_IN_SEASON */

#define STEPS_IN_SEASON      (732) /**< Same as DAM_SLICES_IN_SEASON */

#define STEP_DAY(step)   ((int)(step / STEPS_PER_DAY))

/** Define (or undefine) REALTIME */
#undef REALTIME

/** Define (or undefine) ROUTE_TRACKING */
#define ROUTE_TRACKING

/** Division of river into separate flows. Also used for spill side location */
enum Location {
    Right,         /**< Right side of the segment */
    Left,          /**< Left side of the segment */
    FlowDivisions, /**< Number of flow divisions */
    Middle         /**< Currently not used */
};


#ifndef NULL
#define NULL ((void *)0.0)
#endif

// some math definitions
#ifndef M_PI
#define M_PI (3.1415926535897932384626433832795)
#endif
#define M_PI_180  ( 0.017453292519943295769236907685)
#define DEG_2_RAD   M_PI_180
#define M_180_PI  (57.295779513082320876798154814105)
#define RAD_2_DEG   M_180_PI

// scaling for segment views
#define WIDTH_SCALE (.20)
#define LENGTH_SCALE (.20)


#endif // DEFINITIONS_H
