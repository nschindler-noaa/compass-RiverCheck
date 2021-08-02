#=======================================#

COMPASS River Description File Checker
Version 1.3.0b

#=======================================#

Programmer: Neal Schindler
Date: 2017-09-01

This is programmed with Qt 5.12 using dynamic libraries
and should therefore compile on many platforms,
including Mac OSX, MS Windows, and Linux

Tested on Windows 10 and Linux

History:

2021-08-01
Version 1.3.0b
1. Tweaked views for better visibility..

2019-04-17
Version 1.2.6b
1. Moved to Qt 5.12 on Windows 10.

2018-10-30
Version 1.2.5b
1. Moved to Qt 5.11 on Windows 10.

2017-01-23
Version 1.2.4b
1. Added getter/setter functions to encapsulate data.

2016-12-09
Version 1.2.3b changes
1. Made changes to .pro file to build under Qt 5.7

2016-02-25
Version 1.2.3b Changes
1. Rebuilt with 5.7 libraries.

2016-02-25
Version 1.2.2b Changes
1. Calculate RiverSegment before Reach.
2. Fixed the reach width calculations.
3. Calculate Reaches before Dams (to get better width numbers).
4. Added a check for duplicate lat/lon points.

2014-09-10
Version 1.2b Changes
1. Changed how width is read from data file. Now reads in as lower_width
   rather than width (average width).

2013-05-21
First release.

If any problems, notify me at
neal.schindler(at)noaa.gov

This program is property of NOAA, DOC
