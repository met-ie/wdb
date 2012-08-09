## - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
## 
## wdb - weather and water data storage
##
## Copyright (C) 2007 met.no
##
##  Contact information:
##  Norwegian Meteorological Institute
##  Box 43 Blindern
##  0313 OSLO
##  NORWAY
##  E-mail: wdb@met.no
##
##  This is free software; you can redistribute it and/or modify
##  it under the terms of the GNU General Public License as published by
##  the Free Software Foundation; either version 2 of the License, or
##  (at your option) any later version.
##
## - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#!/bin/sh
#WDB_TMP_DIR=__WDB_BUILDDIR__/var/tmp
#mkdir -p $WDB_TMP_DIR
TEST_WRITE=./testWrite

#
# Copy across test data
# (clean up first)
#rm -f $GRIB_FILE
#rm -f $CHECK_FILE
#cp __WDB_SRCDIR__/test/install/callInterface/wciInstallTest.grib $GRIB_FILE
#cp __WDB_SRCDIR__/test/install/callInterface/wciInstallTest.grib $CHECK_FILE
#chmod 666 $WDB_TMP_DIR/*

# Check if we have write permission on destination directory/file:
#if ! touch $GRIB_FILE; then
#    echo Unable to create file: $GRIB_FILE
#    exit 1
#fi

#
# Generate Test Data
#
# DataProvider
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '2004-12-24 06:00:00+00'
$TEST_WRITE --dataprovider 'test wci 1' --placename 'test grid, rotated' --reftime '2004-12-24 06:00:00+00'
$TEST_WRITE --dataprovider 'test wci 2' --placename 'test grid, rotated' --reftime '2004-12-24 06:00:00+00'

# PlaceName
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '2004-12-25 06:00:00+00'
$TEST_WRITE --dataprovider 'test wci 0' --placename 'hirlam 10 grid' --reftime '2004-12-25 06:00:00+00'
$TEST_WRITE --dataprovider 'test wci 0' --placename 'hirlam 20 grid' --reftime '2004-12-25 06:00:00+00'
$TEST_WRITE --dataprovider 'test wci 4' --placename 'oslo' --reftime '2004-12-25 06:00:00+00' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
$TEST_WRITE --dataprovider 'test wci 6' --placename 'test point 1' --reftime '2004-12-25 06:00:00+00' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
$TEST_WRITE --dataprovider 'test wci 6' --placename 'test point 1' --reftime '2004-12-25 06:00:00+00' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
$TEST_WRITE --dataprovider 'test wci 7' --placename 'test point 1' --reftime '2004-12-25 06:00:00+00' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
$TEST_WRITE --value 1 --dataprovider 'test wci 7' --placename 'test point 15' --reftime '2010-12-24 12:00:00+00' --valueparameter='land area fraction'
$TEST_WRITE --value 2 --dataprovider 'test wci 7' --placename 'test point 15' --reftime '2011-12-24 12:00:00+00' --valueparameter='land area fraction'
$TEST_WRITE --value 3 --dataprovider 'test wci 7' --placename 'test point 16' --reftime '2011-12-24 12:00:00+00' --valueparameter='land area fraction'

# Polygon Placenames
$TEST_WRITE --dataprovider 'test wci 0' --placename 'hirlam 10 grid' --reftime '2004-12-25 06:00:00+00' --valueparameter 'dew point temperature' -P164,161=2 -P165,160=2 -P165,161=2 -P165,162=2 -P166,159=2 -P166,160=2 -P166,161=2 -P166,162=2 -P166,163=2 -P167,158=2 -P167,159=2 -P167,160=2 -P167,161=2 -P167,162=2 -P167,163=2 -P167,164=2 -P168,159=2 -P168,160=2 -P168,161=2 -P168,162=2 -P168,163=2 -P169,160=2 -P169,161=2 -P169,162=2 -P170,161=2
$TEST_WRITE --dataprovider 'test wci 6' --placename 'test point 9'  --reftime '2004-12-25 06:00:00+00' --valueparameter 'dew point temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' --value 2
$TEST_WRITE --dataprovider 'test wci 6' --placename 'test point 10' --reftime '2004-12-25 06:00:00+00' --valueparameter 'dew point temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' --value 2
$TEST_WRITE --dataprovider 'test wci 6' --placename 'test point 11' --reftime '2004-12-25 06:00:00+00' --valueparameter 'dew point temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' --value 2
$TEST_WRITE --dataprovider 'test wci 6' --placename 'test point 12' --reftime '2004-12-25 06:00:00+00' --valueparameter 'dew point temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' --value 2
$TEST_WRITE --dataprovider 'test wci 6' --placename 'test point 13' --reftime '2004-12-25 06:00:00+00' --valueparameter 'dew point temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' --value 2
$TEST_WRITE --dataprovider 'test wci 6' --placename 'test point 14' --reftime '2004-12-25 06:00:00+00' --valueparameter 'dew point temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' --value 2
$TEST_WRITE --dataprovider 'test wci 0' --placename 'hirlam 10 grid' --reftime '2004-12-25 06:00:00+00' --valueparameter 'max air temperature' -P164,161=2 -P165,160=2 -P165,161=2 -P165,162=2 -P166,159=2 -P166,160=2 -P166,161=2 -P166,162=2 -P166,163=2 -P167,158=2 -P167,159=2 -P167,160=2 -P167,161=2 -P167,162=2 -P167,163=2 -P167,164=2 -P168,159=2 -P168,160=2 -P168,161=2 -P168,162=2 -P168,163=2 -P169,160=2 -P169,161=2 -P169,162=2 -P170,161=2 
$TEST_WRITE --dataprovider 'test wci 6' --placename 'test point 9'  --reftime '2004-12-25 06:00:00+00' --valueparameter 'min air temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' --value 2 
$TEST_WRITE --dataprovider 'test wci 6' --placename 'test point 10' --reftime '2004-12-25 06:00:00+00' --valueparameter 'min air temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' --value 2 
$TEST_WRITE --dataprovider 'test wci 6' --placename 'test point 11' --reftime '2004-12-25 06:00:00+00' --valueparameter 'min air temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' --value 2
$TEST_WRITE --dataprovider 'test wci 6' --placename 'test point 12' --reftime '2004-12-25 06:00:00+00' --valueparameter 'min air temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' --value 2
$TEST_WRITE --dataprovider 'test wci 6' --placename 'test point 13' --reftime '2004-12-25 06:00:00+00' --valueparameter 'min air temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' --value 2
$TEST_WRITE --dataprovider 'test wci 6' --placename 'test point 14' --reftime '2004-12-25 06:00:00+00' --valueparameter 'min air temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' --value 2

# PlaceGeos
# G1-G4, G7, G8, G17, G31 Test
$TEST_WRITE --dataprovider 'test wci 0' --placename 'hirlam 10 grid' --reftime '2004-12-26 06:00:00+00' --valueparameter 'air pressure'
# G5 Test
$TEST_WRITE --dataprovider 'test wci 0' --placename 'hirlam 10 grid' --reftime '2004-12-26 06:00:00+00' --valueparameter 'tendency of surface air pressure' -P 168,156=2
# G6 Test
$TEST_WRITE --dataprovider 'test wci 0' --placename 'hirlam 20 grid' --reftime '2004-12-26 06:00:00+00' --valueparameter 'snowfall amount' -P280,135=2 -P90,42=3 -P233,17=4 -P233,377=5 -P232,374=6
# G9 Test
$TEST_WRITE --dataprovider 'test wci 0' --placename 'hirlam 10 grid' --reftime '2004-12-26 06:00:00+00' --valueparameter 'air temperature' -P164,161=2 -P165,160=2 -P165,161=2 -P165,162=2 -P166,159=2 -P166,160=2 -P166,161=2 -P166,162=2 -P166,163=2 -P167,158=2 -P167,159=2 -P167,160=2 -P167,161=2 -P167,162=2 -P167,163=2 -P167,164=2 -P168,159=2 -P168,160=2 -P168,161=2 -P168,162=2 -P168,163=2 -P169,160=2 -P169,161=2 -P169,162=2 -P170,161=2
# G11 Test
$TEST_WRITE --dataprovider 'test wci 0' --placename 'hirlam 10 grid' --reftime '2004-12-26 06:00:00+00' --valueparameter 'max air temperature' -P164,161=2 -P165,160=2 -P165,161=2 -P165,162=2 -P166,159=2 -P166,160=2 -P166,161=2 -P166,162=2 -P166,163=2 -P167,158=2 -P167,159=2 -P167,160=2 -P167,161=2 -P167,162=2 -P167,163=2 -P167,164=2 -P168,159=2 -P168,160=2 -P168,161=2 -P168,162=2 -P168,163=2 -P169,160=2 -P169,161=2 -P169,162=2 -P170,161=2 -P161,164=3 -P161,165=3 -P162,163=3 -P162,164=3 -P162,165=3 -P162,166=3 -P163,162=3 -P163,163=3 -P163,164=3 -P163,165=3 -P163,166=3 -P163,167=3 -P164,162=3 -P164,163=3 -P164,164=3 -P164,165=3 -P164,166=3 -P164,167=3 -P165,163=3 -P165,164=3 -P165,165=3 -P165,166=3 -P166,164=3 -P166,165=3
# G12 Test
$TEST_WRITE --dataprovider 'test wci 0' --placename 'hirlam 10 grid' --reftime '2004-12-26 06:00:00+00' --valueparameter 'convective precipitation amount' -P164,161=2 -P165,160=2 -P165,161=2 -P165,162=2 -P166,159=2 -P166,160=2 -P166,161=2 -P166,162=2 -P166,163=2 -P167,158=2 -P167,159=2 -P167,160=2 -P167,161=2 -P167,162=2 -P167,163=1 -P167,164=2 -P168,159=2 -P168,160=2 -P168,161=2 -P168,162=2 -P168,163=2 -P169,160=2 -P169,161=2 -P169,162=2 -P170,161=2 -P161,164=3 -P161,165=3 -P162,163=3 -P162,164=3 -P162,165=3 -P162,166=3 -P163,162=3 -P163,163=3 -P163,164=3 -P163,165=3 -P163,166=3 -P163,167=3 -P164,162=3 -P164,163=3 -P164,164=3 -P164,165=3 -P164,166=3 -P164,167=3 -P165,163=3 -P165,164=3 -P165,165=3 -P165,166=3 -P166,164=3 -P166,165=3
$TEST_WRITE --dataprovider 'test wci 0' --placename 'hirlam 10 grid' --reftime '2004-12-26 06:00:00+00' --valueparameter 'convective snowfall amount' -P164,161=2 -P165,160=2 -P165,161=2 -P165,162=2 -P166,159=2 -P166,160=2 -P166,161=2 -P166,162=2 -P166,163=2 -P167,158=2 -P167,159=2 -P167,160=2 -P167,161=2 -P167,162=2 -P167,163=1 -P167,164=2 -P168,159=2 -P168,160=2 -P168,161=2 -P168,162=2 -P168,163=2 -P169,160=2 -P169,162=2 -P170,161=2 -P161,164=3 -P161,165=3 -P162,163=3 -P162,164=3 -P162,165=3 -P162,166=3 -P163,162=3 -P163,163=3 -P163,164=3 -P163,165=3 -P163,166=3 -P163,167=3 -P164,162=3 -P164,163=3 -P164,164=3 -P164,165=3 -P164,166=3 -P164,167=3 -P165,163=3 -P165,164=3 -P165,165=3 -P165,166=3 -P166,164=3 -P166,165=3
# G20 Test
$TEST_WRITE --dataprovider 'test wci 0' --placename 'hirlam 10 grid' --reftime '2004-12-26 06:00:00+00' --valueparameter 'min air temperature'  -P150,0=2
# G21 Test
$TEST_WRITE --dataprovider 'test wci 0' --placename 'hirlam 10 grid' --reftime '2004-12-26 06:00:00+00' --valueparameter 'altitude'  -P150,0=2
# G22 Test
$TEST_WRITE --dataprovider 'test wci 0' --placename 'hirlam 10 grid' --reftime '2004-12-26 06:00:00+00' --valueparameter 'x wind' -P 150,0=2 -P 150,1=2 -P 151,0=2 -P 151,1=2
# G23, G24 Test
$TEST_WRITE --dataprovider 'test wci 0' --placename 'hirlam 10 grid' --reftime '2004-12-26 06:00:00+00' --valueparameter 'y wind' -P 175,0=2 -P 175,1=2 -P 176,0=3 -P 176,1=3
# Undefined points G20-5 G21-5 G22-5 G23-5
$TEST_WRITE --dataprovider 'test wci 0' --placename 'hirlam 10 grid' --reftime '2004-12-26 06:00:00+00' --valueparameter 'dew point temperature' -P 175,0=2 -P 175,1=NaN -P 176,0=3 -P 176,1=3
# G25 Test
$TEST_WRITE --dataprovider 'test wci 6' --placename 'test point 1' --reftime '2004-12-26 06:00:00+00' --valueparameter 'air temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
$TEST_WRITE --dataprovider 'test wci 7' --placename 'test point 2' --reftime '2004-12-26 06:00:00+00' --valueparameter 'air temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
$TEST_WRITE --dataprovider 'test wci 6' --placename 'test point 3' --reftime '2004-12-26 06:00:00+00' --valueparameter 'air temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
$TEST_WRITE --dataprovider 'test wci 6' --placename 'test point 4' --reftime '2004-12-26 06:00:00+00' --valueparameter 'air temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
$TEST_WRITE --dataprovider 'test wci 6' --placename 'test point 5' --reftime '2004-12-26 06:00:00+00' --valueparameter 'air temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
$TEST_WRITE --dataprovider 'test wci 6' --placename 'test point 6' --reftime '2004-12-26 06:00:00+00' --valueparameter 'air temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
$TEST_WRITE --dataprovider 'test wci 6' --placename 'test point 7' --reftime '2004-12-26 06:00:00+00' --valueparameter 'air temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
# G30 Test
$TEST_WRITE --dataprovider 'test wci 0' --placename 'hirlam 10 grid' --reftime '2004-12-26 06:00:00+00' --valueparameter 'surface roughness length' --initCoord
# G101 Test
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test utm grid' --reftime '2004-12-26 06:00:00+00' --valueparameter 'cloud area fraction'
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test utm grid' --reftime '2004-12-26 06:00:00+00' --valueparameter 'land area fraction'
$TEST_WRITE --dataprovider 'test wci 0' --placename 'global grid' --reftime '2004-12-26 06:00:00+00' --valueparameter 'land area fraction'
# G102 Test
$TEST_WRITE --dataprovider 'test wci 6' --placename 'test point 8' --reftime '2004-12-26 06:00:00+00' --valueparameter 'snowfall amount' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-13 06:00:00+00' 
$TEST_WRITE --dataprovider 'test wci 6' --placename 'test point 9' --reftime '2004-12-26 06:00:00+00' --valueparameter 'air temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-13 06:00:00+00' 
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '2004-12-24 06:00:00+00'

# Test Polygon
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, wgs84' --reftime '2010-12-24 06:00:00+00'
$TEST_WRITE --dataprovider 'test wci 0' --placename 'proff grid' --reftime '2010-12-25 06:00:00+00'

# PlaceGeometryTest::testPointAndPlaceName
$TEST_WRITE --dataprovider 'test wci 0' --placename 'hirlam 20 grid' --reftime '2004-12-26 06:00:00+00' --valueparameter 'geopotential'
$TEST_WRITE --dataprovider 'test wci 0' --placename 'hirlam 10 grid' --reftime '2004-12-26 06:00:00+00' --valueparameter 'geopotential'



# Fix wci.write. Cannot write gridded data to floatvalue table


# ReferenceTime
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '2007-01-11 06:00:00+00' --validtimefrom '2007-01-11 06:00:00+00' --validtimeto '2007-01-12 06:00:00+00'
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '2007-01-12 06:00:00+00' --validtimefrom '2007-01-12 06:00:00+00' --validtimeto '2007-01-13 06:00:00+00'
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '2007-01-13 06:00:00+00' --validtimefrom '2007-01-13 06:00:00+00' --validtimeto '2007-01-14 06:00:00+00'

# ValidTime
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '2007-02-11 06:00:00+00' --validtimefrom '2007-02-11 06:00:00+00' --validtimeto '2007-02-11 18:00:00+00'
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '2007-02-12 06:00:00+00' --validtimefrom '2007-02-12 06:00:00+00' --validtimeto '2007-02-12 06:00:00+00'
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '2007-02-13 06:00:00+00' --validtimefrom '2007-02-13 06:00:00+00' --validtimeto '2007-02-13 18:00:00+00'
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '2007-12-24 06:00:00+00' --validtimefrom '2007-12-24 06:00:00+00' --validtimeto '2007-12-24 12:00:00+00'

# Parameter
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '2004-12-27 06:00:00+00' --valueparameter 'air pressure'
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '2004-12-27 06:00:00+00' --valueparameter 'tendency of surface air pressure'
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '2004-12-27 06:00:00+00' --valueparameter 'air temperature'
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '2004-12-27 06:00:00+00' --valueparameter 'max air temperature'
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '2004-12-27 06:00:00+00' --valueparameter 'min air temperature'
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '2004-12-27 06:00:00+00' --valueparameter 'altitude'
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '2004-12-27 06:00:00+00' --valueparameter 'x wind'
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '2004-12-27 06:00:00+00' --valueparameter 'y wind'

# Level
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '2004-12-28 06:00:00+00' --levelparameter 'height above ground' --levelfrom 0 --levelto 0
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '2004-12-28 06:00:00+00' --levelparameter 'height above ground' --levelfrom 5 --levelto 10
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '2004-12-28 06:00:00+00' --levelparameter 'height above reference ellipsoid' --levelfrom 10 --levelto 10

# DataVersion
# V1-V5 Test
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '2004-12-29 06:00:00+00' --valueparameter 'air pressure' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '2004-12-29 06:00:00+00' --valueparameter 'air pressure' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00'
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '2004-12-29 06:00:00+00' --valueparameter 'air pressure' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00'
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '2004-12-29 06:00:00+00' --valueparameter 'air pressure' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00'
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '2004-12-29 06:00:00+00' --valueparameter 'air pressure' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00'
$TEST_WRITE --dataprovider 'test wci 0' --placename 'hirlam 10 grid' --reftime '2004-12-29 06:00:00+00' --valueparameter 'air pressure' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
$TEST_WRITE --dataprovider 'test wci 0' --placename 'hirlam 10 grid' --reftime '2004-12-29 06:00:00+00' --valueparameter 'air pressure' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
$TEST_WRITE --dataprovider 'test wci 1' --placename 'test grid, rotated' --reftime '2004-12-29 06:00:00+00' --valueparameter 'air pressure' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
$TEST_WRITE --dataprovider 'test wci 1' --placename 'test grid, rotated' --reftime '2004-12-29 06:00:00+00' --valueparameter 'air pressure' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00'
$TEST_WRITE --dataprovider 'test wci 1' --placename 'test grid, rotated' --reftime '2004-12-29 06:00:00+00' --valueparameter 'air pressure' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00'
$TEST_WRITE --dataprovider 'test wci 1' --placename 'test grid, rotated' --reftime '2004-12-29 06:00:00+00' --valueparameter 'air pressure' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00'
$TEST_WRITE --dataprovider 'test wci 1' --placename 'test grid, rotated' --reftime '2004-12-29 06:00:00+00' --valueparameter 'air pressure' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00'
$TEST_WRITE --dataprovider 'test wci 1' --placename 'hirlam 20 grid' --reftime '2004-12-29 06:00:00+00' --valueparameter 'air pressure' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
$TEST_WRITE --dataprovider 'test wci 1' --placename 'hirlam 20 grid' --reftime '2004-12-29 06:00:00+00' --valueparameter 'air pressure' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2004-12-29 06:00:00+00' --valueparameter 'air pressure' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2004-12-29 06:00:00+00' --valueparameter 'air pressure' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2004-12-29 06:00:00+00' --valueparameter 'air pressure' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2004-12-29 06:00:00+00' --valueparameter 'air pressure' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2004-12-29 06:00:00+00' --valueparameter 'air pressure' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
# V6
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '2004-12-29 06:00:00+00' --valueparameter 'snowfall amount' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '2004-12-29 06:00:00+00' --valueparameter 'air temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '2004-12-29 06:00:00+00' --valueparameter 'air temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00'
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '2004-12-29 06:00:00+00' --valueparameter 'air temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2004-12-29 06:00:00+00' --valueparameter 'snowfall amount' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2004-12-29 06:00:00+00' --valueparameter 'air temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2004-12-29 06:00:00+00' --valueparameter 'air temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2004-12-29 06:00:00+00' --valueparameter 'air temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
# V7
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '2004-12-29 06:00:00+00' --valueparameter 'max air temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '2004-12-29 06:00:00+00' --valueparameter 'max air temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
$TEST_WRITE --dataprovider 'test wci 4' --placename 'oslo' --reftime '2004-12-29 06:00:00+00' --valueparameter 'max air temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
$TEST_WRITE --dataprovider 'test wci 4' --placename 'oslo' --reftime '2004-12-29 06:00:00+00' --valueparameter 'max air temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
# V8
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '2004-12-29 06:00:00+00' --valueparameter 'min air temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '2004-12-29 06:00:00+00' --valueparameter 'min air temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '2004-12-29 06:00:00+00' --valueparameter 'min air temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2004-12-29 06:00:00+00' --valueparameter 'min air temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2004-12-29 06:00:00+00' --valueparameter 'min air temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00' 
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2004-12-29 06:00:00+00' --valueparameter 'min air temperature' --validtimefrom '2005-01-11 06:00:00+00' --validtimeto '2005-01-12 06:00:00+00'
# TransactionCorrectnessTest 
$TEST_WRITE --dataprovider 'test wci 0' --placename 'test grid, rotated' --reftime '1975-04-21 06:00:00+00' --validtimefrom='1975-04-21 06:00:00+00' --validtimeto='1975-04-21 06:00:00+00' --levelparameter 'height above ground' --levelfrom 0 --levelto 0

# Surround Interpolation
# G01 Test
$TEST_WRITE --dataprovider 'test wci 0' --placename 'hirlam 10 grid' --reftime '2004-12-26 12:00:00+00' --valueparameter 'x wind' -P 150,0=2 -P 150,1=2 -P 151,0=2 -P 151,1=2
$TEST_WRITE --dataprovider 'test wci 0' --placename 'hirlam 10 grid' --reftime '2004-12-26 12:00:00+00' --valueparameter 'y wind' -P 119,99=2 -P 119,100=2 -P 119,101=2 -P 119,102=2 -P 120,99=2 -P 120,100=2 -P 120,101=2 -P 120,102=2 -P 121,99=2 -P 121,100=2 -P 121,101=2 -P 121,102=2 -P 122,99=2 -P 122,100=2 -P 122,101=2 -P 122,102=2

#wciOutputTest
$TEST_WRITE  --reftime '2008-04-21 06:00:00+00' -P0,0=NaN

# Aggregate Test
# A01
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2005-01-01 06:00:00+00' --valueparameter 'air temperature' --validtimefrom '2005-01-01 06:00:00+00' --validtimeto '2005-01-01 06:00:00+00' --value="2" 
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2005-01-01 06:00:00+00' --valueparameter 'air temperature' --validtimefrom '2005-01-01 06:00:00+00' --validtimeto '2005-01-01 07:00:00+00' --value="1"
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2005-01-01 06:00:00+00' --valueparameter 'air temperature' --validtimefrom '2005-01-01 06:00:00+00' --validtimeto '2005-01-01 08:00:00+00' --value="3"
# A01
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2005-01-01 06:00:00+00' --valueparameter 'snowfall amount' --validtimefrom '2005-01-01 06:00:00+00' --validtimeto '2005-01-01 06:00:00+00' --value="2.7" 
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2005-01-01 06:00:00+00' --valueparameter 'snowfall amount' --validtimefrom '2005-01-01 06:00:00+00' --validtimeto '2005-01-01 07:00:00+00' --value="1.1"
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2005-01-01 06:00:00+00' --valueparameter 'snowfall amount' --validtimefrom '2005-01-01 06:00:00+00' --validtimeto '2005-01-01 08:00:00+00' --value="4.9"
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2005-01-01 06:00:00+00' --valueparameter 'snowfall amount' --validtimefrom '2005-01-01 06:00:00+00' --validtimeto '2005-01-01 09:00:00+00' --value="3.1"
# A02_01
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2005-01-01 06:00:00+00' --valueparameter 'air pressure' --validtimefrom '2005-01-01 06:00:00+00' --validtimeto '2005-01-01 06:00:00+00' --value="1" 
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2005-01-01 06:00:00+00' --valueparameter 'air pressure' --validtimefrom '2005-01-01 06:00:00+00' --validtimeto '2005-01-01 07:00:00+00' --value="3"
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2005-01-01 06:00:00+00' --valueparameter 'air pressure' --validtimefrom '2005-01-01 06:00:00+00' --validtimeto '2005-01-01 08:00:00+00' --value="2"
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2005-01-01 06:00:00+00' --valueparameter 'air pressure' --validtimefrom '2005-01-01 06:00:00+00' --validtimeto '2005-01-01 09:00:00+00' --value="4"
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2005-01-01 06:00:00+00' --valueparameter 'air pressure' --validtimefrom '2005-01-01 06:00:00+00' --validtimeto '2005-01-01 10:00:00+00' --value="3"
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2005-01-01 06:00:00+00' --valueparameter 'air pressure' --validtimefrom '2005-01-01 06:00:00+00' --validtimeto '2005-01-01 11:00:00+00' --value="5"
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2005-01-01 06:00:00+00' --valueparameter 'air pressure' --validtimefrom '2005-01-01 06:00:00+00' --validtimeto '2005-01-01 12:00:00+00' --value="3"
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2005-01-01 06:00:00+00' --valueparameter 'air pressure' --validtimefrom '2005-01-01 06:00:00+00' --validtimeto '2005-01-01 13:00:00+00' --value="6"
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2005-01-01 06:00:00+00' --valueparameter 'air pressure' --validtimefrom '2005-01-01 06:00:00+00' --validtimeto '2005-01-01 14:00:00+00' --value="4"
# A02_2
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2005-01-01 06:00:00+00' --valueparameter 'max air temperature' --validtimefrom '2005-01-01 06:00:00+00' --validtimeto '2005-01-01 06:00:00+00' --value="1" 
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2005-01-01 06:00:00+00' --valueparameter 'max air temperature' --validtimefrom '2005-01-01 06:00:00+00' --validtimeto '2005-01-01 07:00:00+00' --value="3"
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2005-01-01 06:00:00+00' --valueparameter 'max air temperature' --validtimefrom '2005-01-01 06:00:00+00' --validtimeto '2005-01-01 08:00:00+00' --value="2"
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2005-01-01 06:00:00+00' --valueparameter 'max air temperature' --validtimefrom '2005-01-01 06:00:00+00' --validtimeto '2005-01-01 09:00:00+00' --value="2"
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2005-01-01 06:00:00+00' --valueparameter 'max air temperature' --validtimefrom '2005-01-01 06:00:00+00' --validtimeto '2005-01-01 10:00:00+00' --value="7"
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2005-01-01 06:00:00+00' --valueparameter 'max air temperature' --validtimefrom '2005-01-01 06:00:00+00' --validtimeto '2005-01-01 11:00:00+00' --value="5"
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2005-01-01 06:00:00+00' --valueparameter 'max air temperature' --validtimefrom '2005-01-01 06:00:00+00' --validtimeto '2005-01-01 12:00:00+00' --value="2"
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2005-01-01 06:00:00+00' --valueparameter 'max air temperature' --validtimefrom '2005-01-01 06:00:00+00' --validtimeto '2005-01-01 13:00:00+00' --value="6"
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2005-01-01 06:00:00+00' --valueparameter 'max air temperature' --validtimefrom '2005-01-01 06:00:00+00' --validtimeto '2005-01-01 14:00:00+00' --value="4"
# A02_3
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2005-01-01 06:00:00+00' --valueparameter 'min air temperature' --validtimefrom '2005-01-01 06:00:00+00' --validtimeto '2005-01-01 06:00:00+00' --value="1" 
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2005-01-01 06:00:00+00' --valueparameter 'min air temperature' --validtimefrom '2005-01-01 06:00:00+00' --validtimeto '2005-01-01 07:00:00+00' --value="3"
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2005-01-01 06:00:00+00' --valueparameter 'min air temperature' --validtimefrom '2005-01-01 06:00:00+00' --validtimeto '2005-01-01 08:00:00+00' --value="2"
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2005-01-01 06:00:00+00' --valueparameter 'min air temperature' --validtimefrom '2005-01-01 06:00:00+00' --validtimeto '2005-01-01 09:00:00+00' --value="4"
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2005-01-01 06:00:00+00' --valueparameter 'min air temperature' --validtimefrom '2005-01-01 06:00:00+00' --validtimeto '2005-01-01 10:00:00+00' --value="7"
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2005-01-01 06:00:00+00' --valueparameter 'min air temperature' --validtimefrom '2005-01-01 06:00:00+00' --validtimeto '2005-01-01 11:00:00+00' --value="6"
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2005-01-01 06:00:00+00' --valueparameter 'min air temperature' --validtimefrom '2005-01-01 06:00:00+00' --validtimeto '2005-01-01 12:00:00+00' --value="6"
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2005-01-01 06:00:00+00' --valueparameter 'min air temperature' --validtimefrom '2005-01-01 06:00:00+00' --validtimeto '2005-01-01 13:00:00+00' --value="6"
$TEST_WRITE --dataprovider 'test wci 4' --placename 'test point 0' --reftime '2005-01-01 06:00:00+00' --valueparameter 'min air temperature' --validtimefrom '2005-01-01 06:00:00+00' --validtimeto '2005-01-01 14:00:00+00' --value="5"



# Exit
echo -e "# Generated test data..."
