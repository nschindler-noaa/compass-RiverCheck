#=======================================#

COMPASS River Description File Checker
Version 1.2.3

#=======================================#

Programmer: Neal Schindler
Date: 2016-02-25

This is programmed with Qt 5.7 using static libraries
and should therefore be compilable
on many platforms. Mac OSX, MS Windows, and Linux

Tested on Windows 7 and Linux

History:

2016-12-09
Version 1.2.3 changes
1. Made changes to .pro file to build under Qt 5.7

2016-02-25
Version 1.2.2 Changes
1. Calculate RiverSegment before Reach.
2. Fixed the reach width calculations.
3. Calculate Reaches before Dams (to get better width numbers).
4. Added a check for duplicate lat/lon points.

2014-09-10
Version 1.2 Changes
1. Changed how width is read from data file. Now reads in as lower_width
   rather than width (average width).

2013-05-21
First release.

If any problems, notify me at
neal.schindler(at)noaa.gov

This program is property of NOAA, DOC
