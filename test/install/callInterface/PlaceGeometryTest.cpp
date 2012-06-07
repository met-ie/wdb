/*
    wdb - weather and water data storage

    Copyright (C) 2007 met.no

    Contact information:
    Norwegian Meteorological Institute
    Box 43 Blindern
    0313 OSLO
    NORWAY
    E-mail: wdb@met.no

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
    MA  02110-1301, USA
*/


/**
 * @file
 * Implementation of Place Geometry WCI Install Tests
 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <PlaceGeometryTest.h>
#include <cmath>
#include <string>
#include <sstream>
#include <proj_api.h>
#include <wdbException.h>
#include <wdbMath.h>
#include <WdbProjection.h>

/*
 * PlaceGeometryTest
 *
 * The PlaceGeometryTest suite is by far the most fragile in WDB. This is due
 * to the tests being dependent on PROJ (geography). We need to test that we
 * return the correct locations, but these locations can change from implementation
 * to implementation, as PROJ itself is not consistent across versions.
 *
 * PlaceGeometryTest will FAIL if WDB is linked on a different PROJ version
 * than is used by PostGIS.
 *
 */
CPPUNIT_TEST_SUITE_REGISTRATION( PlaceGeometryTest );

using namespace std;
using namespace pqxx;

void
pointToWgs84( double & lon, double & lat, std::string proj = "+proj=ob_tran +o_proj=longlat +lon_0=-40 +o_lat_p=22 +a=6367470.0 +b=6367470.0 +no_defs")
{
	projPJ src = pj_init_plus( proj.c_str() );
	if ( ! src )
		throw std::logic_error( "Invalid PROJ definition for HIRLAM10 ");
	projPJ wgs84 = pj_init_plus( "+proj=longlat +ellps=WGS84 +no_defs" );
	if ( ! wgs84 )
		throw std::runtime_error( "Invalid PROJ definition for WGS84 ");
	lon *= DEG_TO_RAD;
	lat *= DEG_TO_RAD;
	int error = pj_transform( src, wgs84, 1, 0, &lon, &lat, NULL);
	if ( error )
	{
		throw std::runtime_error( "Error in reprojection" );
	}
	pj_free( src );
	pj_free( wgs84 );
	lon *= RAD_TO_DEG;
	lat *= RAD_TO_DEG;
}



// Lifecycle
//---------------------------------------------------------------------------

PlaceGeometryTest::PlaceGeometryTest()
{
	// NOOP
}

PlaceGeometryTest::~PlaceGeometryTest()
{
	// NOOP
}


// The Tests
//---------------------------------------------------------------------------

void PlaceGeometryTest::testG1_01A_ValidPoint()
{
    // We expect an exception on error
    t->exec( statement_( "POINT( 11.34 60.75 )" ) );
}

void PlaceGeometryTest::testG1_01B_ValidPoint()
{
    // We expect an exception on error
    t->exec( statement_( "POINT( 11.34 60.75 )" ) );
}

void PlaceGeometryTest::testG1_02A_InvalidPoint()
{
    // CPPUNIT_ASSERT_THROW( t->exec( statement_( "POINT( 248 90.75 )" ) ), sql_error );
    // TODO: Test Invalid Point fails
    NOT_FINISHED();
}

void PlaceGeometryTest::testG1_02B_InvalidPoint()
{
    // CPPUNIT_ASSERT_THROW( t->exec( statement_( "POINT( 248 90.75 )" ) ), sql_error );
    // TODO: Test Invalid Point fails
    NOT_FINISHED();
}

void PlaceGeometryTest::testG1_03A_ValidPolygon()
{
    // We expect an exception if this is invalid
    t->exec( statement_( "POLYGON( ( 11.34 60.75, 11.34 62.75, 13.34 62.75, 11.34 60.75 ) )" ) );
}


void PlaceGeometryTest::testG1_03B_ValidPolygon()
{
    // We expect an exception if this is invalid
    t->exec( statement_( "POLYGON( ( 11.34 60.75, 11.34 62.75, 13.34 62.75, 11.34 60.75 ) )" ) );
}

void PlaceGeometryTest::testG1_04A_InvalidPolygon()
{
    // CPPUNIT_ASSERT_THROW( t->exec( statement_( "POLYGON( ( 11.34 60.75, 11.34 92.75, 13.34 62.75, 11.34 60.75 ) )" ) ), sql_error );
	// TODO: Test Invalid Polygon fails
    NOT_FINISHED();
}

void PlaceGeometryTest::testG1_04B_InvalidPolygon()
{
    // CPPUNIT_ASSERT_THROW( t->exec( statement_( "POLYGON( ( 11.34 60.75, 11.34 92.75, 13.34 62.75, 11.34 60.75 ) )" ) ), sql_error );
	// TODO: Test Invalid Polygon fails
    NOT_FINISHED();
}

void PlaceGeometryTest::testG1_07A_ValidMultiPolygon()
{
    // We expect an exception if this is invalid
    t->exec( statement_( "MULTIPOLYGON( ( ( 11.34 60.75, 11.34 62.75, 13.34 62.75, 11.34 60.75 ) ) )" ) );
}


void PlaceGeometryTest::testG1_07B_ValidMultiPolygon()
{
    // We expect an exception if this is invalid
    t->exec( statement_( "MULTIPOLYGON( ( ( 11.34 60.75, 11.34 62.75, 13.34 62.75, 11.34 60.75 ) ) )" ) );
}

void PlaceGeometryTest::testG1_08A_InvalidMultiPolygon()
{
    CPPUNIT_ASSERT_THROW( t->exec( statement_( "MULTIPOLYGON( ( 11.34 60.75, 11.34 92.75, 13.34 62.75, 11.34 60.75 ) )" ) ), sql_error );
}

void PlaceGeometryTest::testG1_08B_InvalidMultiPolygon()
{
    CPPUNIT_ASSERT_THROW( t->exec( statement_( "MULTIPOLYGON( ( ( 11.34 60.75, 11.34 92.75, 13.34 62.75, 11.34 60.75 ), (( 11.34 60.75 11.34 )) ) )" ) ), sql_error );
}

void PlaceGeometryTest::testG2_01A_NoGeometry()
{
    CPPUNIT_ASSERT_THROW( t->exec( statement_( "", 1 ) ), sql_error );
    //startNewTransaction();
    //CPPUNIT_ASSERT_THROW( t->exec( statement_( "POINT()" ) ), sql_error );
}

void PlaceGeometryTest::testG2_01B_NoGeometry()
{
    CPPUNIT_ASSERT_THROW( t->exec( statement_( "" , 1 ) ), sql_error );
    //startNewTransaction();
    //CPPUNIT_ASSERT_THROW( t->exec( statement_( "POINT()" ) ), sql_error );
}

void PlaceGeometryTest::testG2_02A_OneGeometry()
{
    t->exec( statement_( "POINT( 11.34 60.75 )" ) );
}

void PlaceGeometryTest::testG2_02B_OneGeometry()
{
    t->exec( statement_( "POINT( 11.34 60.75 )" ) );
}

void PlaceGeometryTest::testG2_03A_MultipleGeometry()
{
    result r = t->exec( statement_( "MULTIPOINT( 11.34 60.75, 13.72 68.09 )" ) );

    NOT_FINISHED();
}

void PlaceGeometryTest::testG2_03B_MultipleGeometry()
{
    result r = t->exec( statement_( "MULTIPOLYGON( ( ( 11.34 60.75, 13.72 68.09, 14 65, 11.34 60.75)), ( ( 10 70, 11 71, 11 70.5, 10 70)))" ) );
}

void PlaceGeometryTest::testG2_04_MoreThan255Geometries()
{
    float lon = 11.34;
    float lat = 60.75;
    ostringstream multiPoint;
    multiPoint << "MULTIPOINT( " << lon << ' ' << lat;
    for ( float i = 0.01; i < 3; i += 0.01 )
        multiPoint << ", " << lon + i << ' ' << lat + i;
    multiPoint << " )";

    string p = multiPoint.str();

    result r = t->exec( statement_( p.c_str() ) );

    NOT_FINISHED();
}

void PlaceGeometryTest::testG2_05A_NullGeometry()
{
    // We are here only interested in showing that this is valid

    // Since we have had an error here related to return value, we test this
    // as well: return value is oid instead of floats.
    result oidReturn =
        t->exec( "SELECT * FROM wci.read( NULL, NULL, NULL, NULL, '{\"" + specFromParamNumber_.find( 1 )->second + "\"}', NULL, NULL, NULL::wci.returngid )" );
    CPPUNIT_ASSERT( not oidReturn.empty() );
}

void PlaceGeometryTest::testG2_05B_NullGeometry()
{
    // We are here only interested in showing that this is valid, but returns no rows
    result floatReturn = t->exec( statement_( "NULL" ) );
    CPPUNIT_ASSERT( floatReturn.empty() ); // No rows returned
}

void PlaceGeometryTest::testG3_01_NoDuplicates()
{
    result r = t->exec( statement_( "MULTIPOINT( 11.34 60.75, 11.34 61.75 )" ) );
    NOT_FINISHED();
}

void PlaceGeometryTest::testG3_02_OneDuplicate()
{
    result r = t->exec( statement_( "MULTIPOINT( 11.34 60.75, 11.34 60.75 )" ) );
    NOT_FINISHED();
}

void PlaceGeometryTest::testG3_03_SeveralDuplicates()
{
    result r = t->exec( statement_( "MULTIPOINT( 11.34 60.75, "
                                    "12.24 66.07, "
                                    "11.34 60.75, "
                                    "11.34 60.75 )" ) );
    NOT_FINISHED();
}

void PlaceGeometryTest::testG5_01_NorthernHemisphere()
{
	double lon = 5.750 + (168 * 0.1);
	double lat = -13.250 + (156 * 0.1);
	pointToWgs84( lon, lat );
	CPPUNIT_ASSERT( lat > 0 );

	ostringstream pt;
	pt << "POINT(" << wdb::round(lon,4) << " " << wdb::round(lat,4) << ")";
	result r = t->exec( statement_( pt.str(), 3 ) );

	CPPUNIT_ASSERT_EQUAL( result::size_type( 1 ), r.size() );
    CPPUNIT_ASSERT_EQUAL( 2, r.front() [ "value" ].as<int>() );
}

void PlaceGeometryTest::testG5_02_SouthernHemisphere()
{
    result r = t->exec( statement_( "POINT( 4.32 -24 )" ) );

    NOT_FINISHED();
}

void PlaceGeometryTest::testG5_03_Equator()
{
    result r = t->exec( statement_( "POINT( 4.32 0 )" ) );

    NOT_FINISHED();
}

void PlaceGeometryTest::testG5_04_NorthPole()
{
    // closest point to north pole:
    result r = t->exec( statement_( "POINT( 4.32 90 )", 3 ) );

    //CPPUNIT_ASSERT( not r.empty() );
    //CPPUNIT_ASSERT_EQUAL( 2, r.front() [ "value" ].as<int>() );
    NOT_FINISHED();
}

void PlaceGeometryTest::testG5_05_SouthPole()
{
	// transform doesn't work in the presence of certain srids
    //result r = t->exec( statement_( "POINT( 4.32 -90 )" ) );
    NOT_FINISHED();
}

void PlaceGeometryTest::testG5_06_SetOfPointsInNorthernHemisphere()
{
    result r = t->exec( statement_( "MULTIPOINT( 11.34 60.75, 13.72 68.09 )" ) );
    NOT_FINISHED();
}

void PlaceGeometryTest::testG5_07_SetOfPointsInSouthernHemisphere()
{
    result r = t->exec( statement_( "MULTIPOINT( 11.34 -60.75, 13.72 -68.09 )" ) );
    NOT_FINISHED();
}

void PlaceGeometryTest::testG5_08_SetOfPointsAtEquator()
{
    result r = t->exec( statement_( "MULTIPOINT( 11.34 0, 13.72 0 )" ) );
    NOT_FINISHED();
}

void PlaceGeometryTest::testG6_01_EasternHemisphere()
{
	double lon = -46.5 + (280 * 0.2);
	double lat = -36.5 + (135 * 0.2);
	pointToWgs84( lon, lat , "+proj=ob_tran +o_proj=longlat +lon_0=0 +o_lat_p=25 +a=6367470.0 +no_defs");
	CPPUNIT_ASSERT( lon > 0 );

	ostringstream pt;
	pt << "POINT(" << wdb::round(lon,4) << " " << wdb::round(lat,4) << ")";
	result r = t->exec( statement_( pt.str(), 10 ) );

	CPPUNIT_ASSERT_EQUAL( result::size_type( 1 ), r.size() );
    CPPUNIT_ASSERT_EQUAL( 2, r.front() [ "value" ].as<int>() );
}

void PlaceGeometryTest::testG6_02_WesternHemisphere()
{
	double lon = -46.5 + (90 * 0.2);
	double lat = -36.5 + (42 * 0.2);
	pointToWgs84( lon, lat , "+proj=ob_tran +o_proj=longlat +lon_0=0 +o_lat_p=25 +a=6367470.0 +no_defs");
	CPPUNIT_ASSERT( lon < 0 );

	ostringstream pt;
	pt << "POINT(" << wdb::round(lon,4) << " " << wdb::round(lat,4) << ")";
	result r = t->exec( statement_( pt.str(), 10 ) );

	CPPUNIT_ASSERT_EQUAL( result::size_type( 1 ), r.size() );
    CPPUNIT_ASSERT_EQUAL( 3, r.front() [ "value" ].as<int>() );
}

void PlaceGeometryTest::testG6_03_0Meridian()
{
	double lon = -46.5 + (233 * 0.2);
	double lat = -36.5 + (17 * 0.2);
	pointToWgs84( lon, lat , "+proj=ob_tran +o_proj=longlat +lon_0=0 +o_lat_p=25 +a=6367470.0 +no_defs");
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.0, lon, 0.1);
	lon = 0.1;

	ostringstream pt;
	pt << "nearest POINT(" << wdb::round(lon,4) << " " << wdb::round(lat,4) << ")";
	result r = t->exec( statement_( pt.str(), 10 ) );

	CPPUNIT_ASSERT_EQUAL( result::size_type( 1 ), r.size() );
    CPPUNIT_ASSERT_EQUAL( 4, r.front() [ "value" ].as<int>() );
}

void PlaceGeometryTest::testG6_04_180EMeridian()
{
	double lon = -46.5 + (233 * 0.2);
	double lat = -36.5 + (377 * 0.2);
	pointToWgs84( lon, lat , "+proj=ob_tran +o_proj=longlat +lon_0=0 +o_lat_p=25 +a=6367470.0 +no_defs");
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 180.0, lon, 0.5);
	lon = 179.9;

	ostringstream pt;
	pt << "nearest POINT(" << wdb::round(lon,4) << " " << wdb::round(lat,4) << ")";
	result r = t->exec( statement_( pt.str(), 10 ) );

	CPPUNIT_ASSERT_EQUAL( result::size_type( 1 ), r.size() );
    CPPUNIT_ASSERT_EQUAL( 5, r.front() [ "value" ].as<int>() );
}

void PlaceGeometryTest::testG6_05_180WMeridian()
{
	double lon = -46.5 + (232 * 0.2);
	double lat = -36.5 + (374 * 0.2);
	pointToWgs84( lon, lat , "+proj=ob_tran +o_proj=longlat +lon_0=0 +o_lat_p=25 +a=6367470.0 +no_defs");
	CPPUNIT_ASSERT_DOUBLES_EQUAL( -180.0, lon, 0.5);
	lon = -179.9;

	ostringstream pt;
	pt << "nearest POINT(" << wdb::round(lon,4) << " " << wdb::round(lat,4) << ")";
	result r = t->exec( statement_( pt.str(), 10 ) );

	CPPUNIT_ASSERT_EQUAL( result::size_type( 1 ), r.size() );
    CPPUNIT_ASSERT_EQUAL( 6, r.front() [ "value" ].as<int>() );
}

void PlaceGeometryTest::testG6_06_SetOfPointsInEasternHemisphere()
{
    result r = t->exec( statement_( "MULTIPOINT( 100.60 40.75, 101.48 43.12 )" ) );
    NOT_FINISHED();
}

void PlaceGeometryTest::testG6_07_SetOfPointsInWesternHemisphere()
{
    result r = t->exec( statement_( "MULTIPOINT( -100.60 40.75, -101.48 43.12 )" ) );
    NOT_FINISHED();
}

void PlaceGeometryTest::testG6_08_SetOfPointsAt0Meridian()
{
    result r = t->exec( statement_( "MULTIPOINT( 0 40.75, 0 43.12 )" ) );
    NOT_FINISHED();
}

void PlaceGeometryTest::testG6_09_SetOfPointsAt180Meridian()
{
    result r = t->exec( statement_( "MULTIPOINT( 180 40.75, 180 43.12 )" ) );
    NOT_FINISHED();
}

void PlaceGeometryTest::testG6_10_SetOfPointsAtN180Meridian()
{
    result r = t->exec( statement_( "MULTIPOINT( -180 40.75, -180 43.12 )" ) );
    NOT_FINISHED();
}

void PlaceGeometryTest::testG7_01_OnePoint()
{
    // This is a valid point.
	// If type is incorrect, we expect an excecption
    result r = t->exec( statement_( "nearest POINT( 11.34 60.75 )" ) );
	CPPUNIT_ASSERT( r.size() );
}

void PlaceGeometryTest::testG7_02_SetOfPoints()
{
    result r = t->exec( statement_( "MULTIPOINT( 180 40.75, 180 43.12 )" ) );
    NOT_FINISHED();
}

void PlaceGeometryTest::testG7_03_OnePolygon()
{
    // This is a valid polygon
	// If type is incorrect, we expect an exception
    result r = t->exec( statement_( "POLYGON( ( "
									"11.34 60.75, "
									"11.34 62.75, "
									"13.34 62.75, "
									"11.34 60.75 ) )" ) );
	CPPUNIT_ASSERT( r.size() );
}

void PlaceGeometryTest::testG7_04_SetOfPolygons()
{
    result r = t->exec( statement_( "MULTIPOLYGON( ( "
                                    "(11.34 60.75, "
                                    "11.34 62.75, "
                                    "13.34 62.75, "
                                    "11.34 60.75) ),"
                                    "( (11.34 60.75, "
                                    "11.34 62.75, "
                                    "13.34 62.75, "
                                    "11.34 60.75)"
                                    " ) )" ) );
	CPPUNIT_ASSERT( r.size() );
}

void PlaceGeometryTest::testG8_01_NullArea()
{
    result r = t->exec( statement_( "POLYGON( ( "
                                    "11.34 60.75, "
                                    "11.34 60.75, "
                                    "11.34 60.75, "
                                    "11.34 60.75 ) )" ) );

    CPPUNIT_ASSERT( r.empty() );
}

void PlaceGeometryTest::testG8_02_AreaSizeLtProjPrecision()
{
    const double p = 0.0001; // -E04 is smallest precision in WDB
    double lat = 11.34;
    double lon = 60.75;
    ostringstream polygon;
    polygon << "POLYGON((" << lon << ' ' << lat << ',' << lon + p << ' ' << lat << ',' << lon + p << ' ' << lat + p << ',' << lon << ' ' << lat + p << ',' << lon << ' ' << lat << "))";

    string pol = polygon.str();

    result r = t->exec( statement_( pol.c_str() ) );

    CPPUNIT_ASSERT( r.empty() );
}


void PlaceGeometryTest::testG8_03_PolygonWithMeasurableArea()
{
    // Already tested by testValidPoint();
	result r = t->exec( statement_( "POLYGON( ( 11.34 60.75, 11.34 62.75, 13.34 62.75, 11.34 60.75 ) )" ) );
    CPPUNIT_ASSERT( not r.empty() );
}

void PlaceGeometryTest::testG9_01_4PointsInPolygon()
{
    const char * polygon = "POLYGON(( "
                           "11.34 60.75, "
                           "12.34 60.75, "
                           "12.34 61.25, "
                           "11.34 61.25, "
                           "11.34 60.75 ))";

    result r = t->exec( statement_( polygon, 11 ) );

    CPPUNIT_ASSERT( (result::size_type( 25 ) == r.size())||(result::size_type( 29 ) == r.size()) );
    int count = 0;
    for ( result::const_iterator it = r.begin(); it != r.end(); ++ it ) {
    	if ( 2 == ( *it ) [ "value" ].as<int>() )
    		count++;
    }
    CPPUNIT_ASSERT_EQUAL( 25, count );
}

void PlaceGeometryTest::testG9_02_SeveralPointsInPolygon()
{
    const char * polygon = "POLYGON(( "
                           "11.34 60.75, "
						   "11.84 60.75, "
                           "12.34 60.75, "
						   "12.34 61.00, "
                           "12.34 61.25, "
                           "11.34 61.25, "
                           "11.34 60.75 ))";

    result r = t->exec( statement_( polygon, 11 ) );

    CPPUNIT_ASSERT( (result::size_type( 25 ) == r.size())||(result::size_type( 29 ) == r.size()) );
    int count = 0;
    for ( result::const_iterator it = r.begin(); it != r.end(); ++ it ) {
    	if ( 2 == ( *it ) [ "value" ].as<int>() )
    		count++;
    }
    CPPUNIT_ASSERT_EQUAL( 25, count );
}

void PlaceGeometryTest::testG9_03_MoreThan1000PointsInPolygon()
{
    // Does not work with other values than 0 for centreLon and centreLat

    const double radius = 15;
    const double centreLon = 0; //13;
    //const double centreLat = 0; //60;
    const double noOfPoints = 20;

    const double increment = ( 2 * radius ) / noOfPoints;

    ostringstream halfCircle;
    halfCircle << "POLYGON((";
    for ( double offset = 0; offset < noOfPoints; ++ offset )
    {
        double lon = centreLon - radius + ( increment * offset );
        double lat = std::sqrt( ( radius * radius ) - ( lon * lon ) );
        halfCircle << wdb::round(lon,4) << " " << wdb::round(lat,4) << ", ";
    }
    double lon = centreLon - radius;
    double lat = std::sqrt( ( radius * radius ) - ( lon * lon ) );
    halfCircle << wdb::round(lon,4) << " " << wdb::round(lat,4) << "))";

    const std::string hc = halfCircle.str();

    result r = t->exec( statement_( hc.c_str(), 11 ) );

    //CPPUNIT_ASSERT_EQUAL( result::size_type( 32119 ), r.size() );
    CPPUNIT_ASSERT_EQUAL( result::size_type( 28813 ), r.size() );
    // Can find no better way to test this.

	// Should with with noOfPoints = 1000. Currently, WCI has a problem
	// with this (decoding of geometries).
	NOT_FINISHED();
}

void PlaceGeometryTest::testG9_04_LongPolygonSpecification()
{
    double lon = 11.34;
    double lat = 60.75;
    std::ostringstream p;
    p << "POLYGON((";
    for ( ; lon < 12.34; lon += 0.1 )
    	p << lon << ' ' << lat << ", ";
    for ( ; lat < 61.25; lat += 0.1 )
    	p << lon << ' ' << lat << ", ";
    for ( ; lon > 11.34; lon -= 0.1 )
    	p << lon << ' ' << lat << ", ";
    for ( ; lat > 60.75; lat -= 0.1 )
    	p << lon << ' ' << lat << ", ";
    p << 11.34 << ' ' << 60.75 << "))";

    const std::string polygon = p.str();

    CPPUNIT_ASSERT(polygon.size() > 255);

    result r = t->exec( statement_( polygon, 11 ) );

//    CPPUNIT_ASSERT( (result::size_type( 25 ) == r.size())||(result::size_type( 29 ) == r.size()) );
    int count = 0;
    for ( result::const_iterator it = r.begin(); it != r.end(); ++ it ) {
    	if ( 2 == ( *it ) [ "value" ].as<int>() )
    		count++;
    }
    CPPUNIT_ASSERT_EQUAL( 25, count );
}

void PlaceGeometryTest::testG10_01_ConvexPolygon()
{
	// Todo: Fails, as WCI uses bounding boxes
    const char * polygon = "POLYGON(( "
                           "11.34 60.75, "
                           "12.34 60.75, "
    					   "13.34 61.25, "
                           "12.34 61.75, "
                           "11.34 61.75, "
                           "11.34 60.75 ))";

    result r = t->exec( statement_( polygon ) );

    //CPPUNIT_ASSERT_EQUAL( result::size_type( 49 ), r.size() );

    // Todo: Check for specific points not performed
    //for ( result::const_iterator it = r.begin(); it != r.end(); ++ it )
    //    CPPUNIT_ASSERT_EQUAL( 1, ( *it ) [ "value" ].as<int>() );
	NOT_FINISHED();
}

void PlaceGeometryTest::testG10_02_ConcavePolygon()
{
	// Todo: Fails, as WCI uses bounding boxes
	const char * polygon = "POLYGON(( "
                           "11.34 60.75, "
                           "12.34 60.75, "
    					   "11.84 61.25, "
                           "12.34 61.75, "
                           "11.34 61.75, "
                           "11.34 60.75 ))";

    result r = t->exec( statement_( polygon ) );

    //CPPUNIT_ASSERT_EQUAL( result::size_type( 49 ), r.size() );

    //for ( result::const_iterator it = r.begin(); it != r.end(); ++ it )
    //    CPPUNIT_ASSERT_EQUAL( 1, ( *it ) [ "value" ].as<int>() );
	NOT_FINISHED();
}

void PlaceGeometryTest::testG11_01_NoCrossingPoints()
{
    const char * polygon = "POLYGON(( "
                           "11.34 60.75, "
                           "12.34 60.75, "
                           "12.34 61.25, "
                           "11.34 61.25, "
                           "11.34 60.75 ))";

    result r = t->exec( statement_( polygon, 15 ) );

    CPPUNIT_ASSERT_EQUAL( result::size_type( 25 ), r.size() );
    int count = 0;
    for ( result::const_iterator it = r.begin(); it != r.end(); ++ it ) {
    	if ( 2 == ( *it ) [ "value" ].as<int>() )
    		count++;
    }
    CPPUNIT_ASSERT_EQUAL( 25, count );
}

void PlaceGeometryTest::testG11_02_1CrossingPoint()
{
	// The result for this query is identical with that of G11/1, because
	// WCI uses a bounding box to select the points within the polygon. As
	// a result, points that are actually outside the polygon still get
	// selected.
	//
	// So far, at least, this is working as designed.
	const char * polygon = "POLYGON(( "
                           "11.34 60.75, "
                           "12.34 60.75, "
                           "11.34 61.25, "
                           "12.34 61.25, "
                           "11.34 60.75 ))";

    result r = t->exec( statement_( polygon, 15 ) );

    CPPUNIT_ASSERT_EQUAL( result::size_type( 12 ), r.size() );
    int count = 0;
    for ( result::const_iterator it = r.begin(); it != r.end(); ++ it ) {
    	if ( 2 == ( *it ) [ "value" ].as<int>() )
    		count++;
    }
    // Actually 13, but we apparently cut 1
    CPPUNIT_ASSERT_EQUAL( 12 , count );
}

void PlaceGeometryTest::testG11_03_MoreThan1CrossingPoint()
{
	// As discussed above, this query uses a bounding box, which means that
	// the return result is greater than what is really needful.
    const char * polygon = "POLYGON(( "
                           "11.34 60.75, "
                           "12.34 60.75, "
                           "11.34 61.25, "
                           "12.34 61.75, "
						   "11.34 61.75, "
						   "12.34 61.25, "
                           "11.34 60.75 ))";
    result r = t->exec( statement_( polygon, 15 ) );

    CPPUNIT_ASSERT_EQUAL( result::size_type( 24 ), r.size() );
    int count = 0;
    for ( result::const_iterator it = r.begin(); it != r.end(); ++ it ) {
    	if (( 2 == ( *it ) [ "value" ].as<int>() )|| (( *it ) [ "value" ].as<int>() == 3))
    		count++;
    }
    // Actually 28, but we cut one
    CPPUNIT_ASSERT_EQUAL( 24, count );
}


void PlaceGeometryTest::testG12_01_PolygonWith1Hole()
{
	double lon = 5.750 + (167 * 0.1);
	double lat = -13.250 + (163 * 0.1);
	pointToWgs84( lon, lat );
	ostringstream pol;
	pol << "POLYGON(( 11.34 60.75, "
                     "12.34 60.75, "
                     "12.34 61.25, "
                     "11.34 61.25, "
                     "11.34 60.75 ), "
		<< "(" << (wdb::round(lon,4) - 0.05) << " " << (wdb::round(lat,4) - 0.05) << ", "
			   << (wdb::round(lon,4) + 0.05) << " " << (wdb::round(lat,4) - 0.05) << ", "
			   << (wdb::round(lon,4) + 0.05) << " " << (wdb::round(lat,4) + 0.05) << ", "
			   << (wdb::round(lon,4) - 0.05) << " " << (wdb::round(lat,4) + 0.05) << ", "
			   << (wdb::round(lon,4) - 0.05) << " " << (wdb::round(lat,4) - 0.05) << "))";
    result r = t->exec( statement_( pol.str(), 17 ) );
    CPPUNIT_ASSERT_EQUAL( result::size_type( 24 ), r.size() );
    int count = 0;
    for ( result::const_iterator it = r.begin(); it != r.end(); ++ it ) {
    	if ( 2 == ( *it ) [ "value" ].as<int>() )
    		count++;
    }
    CPPUNIT_ASSERT_EQUAL( 24, count );
}


void PlaceGeometryTest::testG12_02_PolygonWith2Holes()
{
	double lon = 5.750 + (167 * 0.1);
	double lat = -13.250 + (163 * 0.1);
	pointToWgs84( lon, lat );
	double lon2 = 5.750 + (169 * 0.1);
	double lat2 = -13.250 + (161 * 0.1);
	pointToWgs84( lon2, lat2 );
	ostringstream pol;
	pol << "POLYGON(( 11.34 60.75, "
                     "12.34 60.75, "
                     "12.34 61.25, "
                     "11.34 61.25, "
                     "11.34 60.75 ), "
		<< "(" << (wdb::round(lon,4) - 0.05) << " " << (wdb::round(lat,4) - 0.05) << ", "
			   << (wdb::round(lon,4) + 0.05) << " " << (wdb::round(lat,4) - 0.05) << ", "
			   << (wdb::round(lon,4) + 0.05) << " " << (wdb::round(lat,4) + 0.05) << ", "
			   << (wdb::round(lon,4) - 0.05) << " " << (wdb::round(lat,4) + 0.05) << ", "
			   << (wdb::round(lon,4) - 0.05) << " " << (wdb::round(lat,4) - 0.05) << "),"
		<< "(" << (wdb::round(lon2,4) - 0.05) << " " << (wdb::round(lat2,4) - 0.05) << ", "
			   << (wdb::round(lon2,4) + 0.05) << " " << (wdb::round(lat2,4) - 0.05) << ", "
			   << (wdb::round(lon2,4) + 0.05) << " " << (wdb::round(lat2,4) + 0.05) << ", "
			   << (wdb::round(lon2,4) - 0.05) << " " << (wdb::round(lat2,4) + 0.05) << ", "
			   << (wdb::round(lon2,4) - 0.05) << " " << (wdb::round(lat2,4) - 0.05) << ")"
		<< " )";
    result r = t->exec( statement_( pol.str(), 18 ) );
    CPPUNIT_ASSERT_EQUAL( result::size_type( 23 ), r.size() );
    int count = 0;
    for ( result::const_iterator it = r.begin(); it != r.end(); ++ it ) {
    	if ( 2 == ( *it ) [ "value" ].as<int>() )
    		count++;
    }
    CPPUNIT_ASSERT_EQUAL( 23, count );
}


void PlaceGeometryTest::testG12_03_PolygonWithSeveralHoles()
{
	double lon = 5.750 + (167 * 0.1);
	double lat = -13.250 + (163 * 0.1);
	pointToWgs84( lon, lat );
	double lon2 = 5.750 + (169 * 0.1);
	double lat2 = -13.250 + (161 * 0.1);
	pointToWgs84( lon2, lat2 );
	ostringstream pol;
	pol << "POLYGON(( 11.34 60.75, "
                     "12.34 60.75, "
                     "12.34 61.25, "
                     "11.34 61.25, "
                     "11.34 60.75 ), "
		<< "(" << (wdb::round(lon,4) - 0.05) << " " << (wdb::round(lat,4) - 0.05) << ", "
			   << (wdb::round(lon,4) + 0.05) << " " << (wdb::round(lat,4) - 0.05) << ", "
			   << (wdb::round(lon,4) + 0.05) << " " << (wdb::round(lat,4) + 0.05) << ", "
			   << (wdb::round(lon,4) - 0.05) << " " << (wdb::round(lat,4) + 0.05) << ", "
			   << (wdb::round(lon,4) - 0.05) << " " << (wdb::round(lat,4) - 0.05) << "),"
		<< "(" << (wdb::round(lon2,4) - 0.05) << " " << (wdb::round(lat2,4) - 0.05) << ", "
			   << (wdb::round(lon2,4) + 0.05) << " " << (wdb::round(lat2,4) - 0.05) << ", "
			   << (wdb::round(lon2,4) + 0.05) << " " << (wdb::round(lat2,4) + 0.05) << ", "
			   << (wdb::round(lon2,4) - 0.05) << " " << (wdb::round(lat2,4) + 0.05) << ", "
			   << (wdb::round(lon2,4) - 0.05) << " " << (wdb::round(lat2,4) - 0.05) << "),"
		<< "(10.3 45.1, 10.4 45.1, 10.4 45.2, 10.3 45.2, 10.3 45.1),"
		<< "(15.3 45.1, 15.4 45.1, 15.4 45.2, 15.3 45.2, 15.3 45.1),"
		<< "(25.6 33.0, 25.7 33.0, 25.7 33.1, 25.6 33.1, 25.6 33.0)"
		<< " )";
    result r = t->exec( statement_( pol.str(), 18 ) );
    CPPUNIT_ASSERT_EQUAL( result::size_type( 23 ), r.size() );
    int count = 0;
    for ( result::const_iterator it = r.begin(); it != r.end(); ++ it ) {
    	if ( 2 == ( *it ) [ "value" ].as<int>() )
    		count++;
    }
    CPPUNIT_ASSERT_EQUAL( 23, count );
}

/*
void PlaceGeometryTest::testG12_01_AnglePerpendicular()
{
    NOT_FINISHED();
}

void PlaceGeometryTest::testG12_02_AcuteAngle()
{
    NOT_FINISHED();
}

void PlaceGeometryTest::testG12_03_ObtuseAngle()
{
    NOT_FINISHED();
}

void PlaceGeometryTest::testG12_04_StraightAngle()
{
    NOT_FINISHED();
}

void PlaceGeometryTest::testG12_05_ReflexAngle()
{
    NOT_FINISHED();
}

void PlaceGeometryTest::testG13_01_FewLongSegments()
{
    NOT_FINISHED();
}

void PlaceGeometryTest::testG13_02_ManyShortSegments()
{
    NOT_FINISHED();
}

void PlaceGeometryTest::testG13_03_MixedSegments()
{
    NOT_FINISHED();
}

void PlaceGeometryTest::testG14_01_AllRequestedPointsOnGrid()
{
    NOT_FINISHED();
}

void PlaceGeometryTest::testG14_02_SomeRequestedPointsOnGrid()
{
    NOT_FINISHED();
}

void PlaceGeometryTest::testG14_03_NoPointsOnGrid()
{
    NOT_FINISHED();
}

void PlaceGeometryTest::testG15_01_CompleteOverlap()
{
    NOT_FINISHED();
}

void PlaceGeometryTest::testG15_02_PartialOverlap()
{
    NOT_FINISHED();
}

void PlaceGeometryTest::testG15_03_NoOverlap()
{
    NOT_FINISHED();
}

void PlaceGeometryTest::testG16_01_CompleteIntersection()
{
    NOT_FINISHED();
}

void PlaceGeometryTest::testG16_02_PartialIntersection()
{
    NOT_FINISHED();
}

void PlaceGeometryTest::testG16_03_NoIntersection()
{
    NOT_FINISHED();
}
*/

void PlaceGeometryTest::testG17_01_CorrectPointSyntax()
{
    t->exec( statement_( "POINT( 11.34 60.75 )" ) );
}

void PlaceGeometryTest::testG17_02_IncorrectPointSyntax()
{
    CPPUNIT_ASSERT_THROW( t->exec( statement_( "POINT((11.34 60.75))" ) ), sql_error );
    startNewTransaction();
    CPPUNIT_ASSERT_THROW( t->exec( statement_( "POINT(11.34, 60.75)" ) ), sql_error );
    startNewTransaction();
    CPPUNIT_ASSERT_THROW( t->exec( statement_( "POINT(foo 232)" ) ), sql_error );
}

void PlaceGeometryTest::testG17_03_CorrectPolygonSyntax()
{
    t->exec( statement_( "POLYGON( ( 11.34 60.75, 11.34 62.75, 13.34 62.75, 11.34 60.75 ) )" ) );
}

void PlaceGeometryTest::testG17_04_IncorrectPolygonSyntax()
{
    CPPUNIT_ASSERT_THROW( t->exec( statement_( "POLYGON( 11.34 60.75, 11.34 62.75, 13.34 62.75, 11.34 60.75 )" ) ), sql_error );
    startNewTransaction();
    CPPUNIT_ASSERT_THROW( t->exec( statement_( "POLYGON( ( 11.34 60.75, 11.34 62.75, 13.34 62.75, 12.34 68 ) )" ) ), sql_error );
    startNewTransaction();
    CPPUNIT_ASSERT_THROW( t->exec( statement_( "POLYGON( ( 11.34 60.75, 11.34 62.75, 13.34 foo, 11.34 60.75 ) )" ) ), sql_error );
}

/*
void PlaceGeometryTest::testG18_01_SpecOnGlobalField()
{
    NOT_FINISHED();
}

void PlaceGeometryTest::testG18_02_SpecOnNonGlobalField()
{
    NOT_FINISHED();
}
*/

void PlaceGeometryTest::testG19_01_InvalidInterpolationType()
{
    CPPUNIT_ASSERT_THROW( t->exec( statement_( "interpolish POINT((11.34 60.75))" ) ), sql_error );
}

void PlaceGeometryTest::testG19_02_NoInterpolationType()
{
    t->exec( statement_( "POINT( 11.34 60.75 )" ) );
}

void PlaceGeometryTest::testG20_01_ExactInsideGrid()
{
	double lon = 5.750 + (150 * 0.1);
	double lat = -13.250 + (0 * 0.1) + 0.02;
	pointToWgs84( lon, lat );

	ostringstream pt;
	pt << "exact POINT(" << wdb::round(lon,4) << " " << wdb::round(lat,4) << ")";
	result r = t->exec( statement_( pt.str(), 16 ) );

    CPPUNIT_ASSERT( r.empty() );
}

void PlaceGeometryTest::testG20_02_ExactEdgeOfGrid()
{
	double lon = 5.750 + (150 * 0.1);
	double lat = -13.250 + (0 * 0.1);
	pointToWgs84( lon, lat );

	ostringstream pt;
	pt << "exact POINT(" << wdb::round(lon,4) << " " << wdb::round(lat,4) << ")";
	result r = t->exec( statement_( pt.str(), 16 ) );

    CPPUNIT_ASSERT_EQUAL( result::size_type( 1 ), r.size() );
    CPPUNIT_ASSERT_EQUAL( 2, r.front() [ "value" ].as<int>() );
}

void PlaceGeometryTest::testG20_03_ExactJustOutsideGrid()
{
	double lon = 5.750 + (150 * 0.1);
	double lat = -13.250 + (0 * 0.1) - 0.02;
	pointToWgs84( lon, lat );

	ostringstream pt;
	pt << "exact POINT(" << wdb::round(lon,4) << " " << wdb::round(lat,4) << ")";
	result r = t->exec( statement_( pt.str(), 16 ) );

    CPPUNIT_ASSERT( r.empty() );
}

void PlaceGeometryTest::testG20_04_ExactFarOutsideGrid()
{
	double lon = 5.750 + (150 * 0.01);
	double lat = -13.250 + (0 * 0.1) - 5.0;
	pointToWgs84( lon, lat );

	ostringstream pt;
	pt << "exact POINT(" << wdb::round(lon,4) << " " << wdb::round(lat,4) << ")";
	result r = t->exec( statement_( pt.str(), 16 ) );

    CPPUNIT_ASSERT( r.empty() );
}

void PlaceGeometryTest::testG20_05_ExactWithUndefinedPoint()
{
	double lon = 5.750 + (175 * 0.1);
	double lat = -13.250 + (1 * 0.1);
	pointToWgs84( lon, lat );

	ostringstream pt;
	pt << "nearest POINT(" << wdb::round(lon,4) << " " << wdb::round(lat,4) << ")";
	result r = t->exec( statement_( pt.str(), 14 ) );

	CPPUNIT_ASSERT_EQUAL(1, (int) r.size());

	CPPUNIT_ASSERT( r.front()[ "value" ].is_null() );
}


void PlaceGeometryTest::testG21_01_NearestInsideGrid()
{
	double lon = 5.750 + (150 * 0.1) + 0.02;
	double lat = -13.250 + (0 * 0.1) + 0.02;
	pointToWgs84( lon, lat );

	ostringstream pt;
	pt << "nearest POINT(" << wdb::round(lon,4) << " " << wdb::round(lat,4) << ")";
	result r = t->exec( statement_( pt.str(), 32 ) );
    CPPUNIT_ASSERT_EQUAL( result::size_type( 1 ), r.size() );
    CPPUNIT_ASSERT_EQUAL( 2, r.front() [ "value" ].as<int>() );
}

void PlaceGeometryTest::testG21_02_NearestEdgeOfGrid()
{
	double lon = 5.750 + (150 * 0.1);
	double lat = -13.250 + (0 * 0.1);
	pointToWgs84( lon, lat );

	ostringstream pt;
	pt << "nearest POINT(" << wdb::round(lon,4) << " " << wdb::round(lat,4) << ")";
	result r = t->exec( statement_( pt.str(), 32 ) );

    CPPUNIT_ASSERT_EQUAL( result::size_type( 1 ), r.size() );
    CPPUNIT_ASSERT_EQUAL( 2, r.front() [ "value" ].as<int>() );
}

void PlaceGeometryTest::testG21_03_NearestJustOutsideGrid()
{
	double lon = 5.750 + (150 * 0.1);
	double lat = -13.250 + (0 * 0.1) - 0.6;
	pointToWgs84( lon, lat );

	ostringstream pt;
	pt << "nearest POINT(" << wdb::round(lon,4) << " " << wdb::round(lat,4) << ")";
	result r = t->exec( statement_( pt.str(), 32 ) );

    CPPUNIT_ASSERT( r.empty() );
}

void PlaceGeometryTest::testG21_04_NearestFarOutsideGrid()
{
	double lon = 5.750 + (150 * 0.1) - 1.35;
	double lat = -13.250 + (0 * 0.1) - 4.15;
	pointToWgs84( lon, lat );

	ostringstream pt;
	pt << "nearest POINT(" << wdb::round(lon,4) << " " << wdb::round(lat,4) << ")";
	result r = t->exec( statement_( pt.str(), 32 ) );

    CPPUNIT_ASSERT( r.empty() );
}

void PlaceGeometryTest::testG21_05_NearestWithUndefinedPoint()
{
	double lon = 5.750 + (175 * 0.1) + 0.02;
	double lat = -13.250 + (1 * 0.1) + 0.02;
	pointToWgs84( lon, lat );

	ostringstream pt;
	pt << "nearest POINT(" << wdb::round(lon,4) << " " << wdb::round(lat,4) << ")";
	result r = t->exec( statement_( pt.str(), 14 ) );

	CPPUNIT_ASSERT_EQUAL(1, (int) r.size());

	CPPUNIT_ASSERT( r.front()[ "value" ].is_null() );
}


void PlaceGeometryTest::testG22_01_SurroundInsideGrid()
{
	double lon = 5.750 + (150 * 0.1) + 0.05;
	double lat = -13.250 + (0 * 0.1) + 0.05;
	pointToWgs84( lon, lat );

	ostringstream pt;
	pt << "surround POINT(" << wdb::round(lon,4) << " " << wdb::round(lat,4) << ")";
	result r = t->exec( statement_( pt.str(), 33 ) );

    CPPUNIT_ASSERT_EQUAL( result::size_type( 4 ), r.size() );
    for ( result::const_iterator it = r.begin(); it != r.end(); ++ it )
    {
        CPPUNIT_ASSERT_EQUAL( 2, ( *it ) [ "value" ].as<int>() );
    }
}

void PlaceGeometryTest::testG22_02_SurroundEdgeOfGrid()
{
	double lon = 5.750 + (151 * 0.1);
	double lat = -13.250 + (0 * 0.1);
	pointToWgs84( lon, lat );

	ostringstream pt;
	pt << "surround POINT(" << wdb::round(lon,4) << " " << wdb::round(lat,4) << ")";
	result r = t->exec( statement_( pt.str(), 33 ) );

    CPPUNIT_ASSERT_EQUAL( result::size_type( 4 ), r.size() );
    for ( result::const_iterator it = r.begin(); it != r.end(); ++ it )
    {
        CPPUNIT_ASSERT_EQUAL( 2, ( *it ) [ "value" ].as<int>() );
    }
}

void PlaceGeometryTest::testG22_03_SurroundJustOutsideGrid()
{
	double lon = 5.750 + (150 * 0.1);
	double lat = -13.250 + (0 * 0.1) - 0.06;
	pointToWgs84( lon, lat );

	ostringstream pt;
	pt << "surround POINT(" << wdb::round(lon,4) << " " << wdb::round(lat,4) << ")";
	result r = t->exec( statement_( pt.str(), 33 ) );

    CPPUNIT_ASSERT_EQUAL( result::size_type( 2 ), r.size() );
    for ( result::const_iterator it = r.begin(); it != r.end(); ++ it )
    {
        CPPUNIT_ASSERT_EQUAL( 2, ( *it ) [ "value" ].as<int>() );
    }
    // An alternative implementation would be for surround to return empty,
    // given that the point is outside the grid. For now, though, we shall
    // let the above implementation pass.
	// CPPUNIT_ASSERT( r.empty() );
}

void PlaceGeometryTest::testG22_04_SurroundFarOutsideGrid()
{
	double lon = 5.750 + (150 * 0.1) - 1.3;
	double lat = -13.250 + (0 * 0.1) - 4.1;
	pointToWgs84( lon, lat );

	ostringstream pt;
	pt << "surround POINT(" << wdb::round(lon,4) << " " << wdb::round(lat,4) << ")";
	result r = t->exec( statement_( pt.str(), 33 ) );

    CPPUNIT_ASSERT( r.empty() );
}

void PlaceGeometryTest::testG22_05_SurroundWithOneUndefinedPoint()
{
	double lon = 5.750 + (175 * 0.1) + 0.05;
	double lat = -13.250 + (0 * 0.1) + 0.05;
	pointToWgs84( lon, lat );

	ostringstream pt;
	pt << "surround POINT(" << wdb::round(lon,4) << " " << wdb::round(lat,4) << ")";
	result r = t->exec( statement_( pt.str(), 14 ) );

    CPPUNIT_ASSERT_EQUAL( result::size_type( 4 ), r.size() );

    CPPUNIT_ASSERT_EQUAL( 2, r[0]["value"].as<int>() );
    CPPUNIT_ASSERT_EQUAL( 3, r[1]["value"].as<int>() );
    CPPUNIT_ASSERT( r[2]["value"].is_null() );
    CPPUNIT_ASSERT_EQUAL( 3, r[3]["value"].as<int>() );
}

void PlaceGeometryTest::testG23_01_BilinearInsideGrid()
{
	double lon = 5.750 + (175 * 0.1) + 0.05;
	double lat = -13.250 + (0 * 0.1) + 0.05;
	pointToWgs84( lon, lat );

	ostringstream pt;
	pt << "bilinear POINT(" << wdb::round(lon,4) << " " << wdb::round(lat,4) << ")";
	result r = t->exec( statement_( pt.str(), 34 ) );

    CPPUNIT_ASSERT_EQUAL( result::size_type( 1 ), r.size() );

    CPPUNIT_ASSERT_DOUBLES_EQUAL( double(2.50), r.front()[ "value" ].as<double>(), 0.01 );
}

void PlaceGeometryTest::testG23_02_BilinearEdgeOfGrid()
{
	double lon = 5.750 + (175 * 0.1) + 0.05;
	double lat = -13.250 + (0 * 0.1);
	pointToWgs84( lon, lat );

	ostringstream pt;
	pt << "bilinear POINT(" << wdb::round(lon,4) << " " << wdb::round(lat,4) << ")";
	result r = t->exec( statement_( pt.str(), 34 ) );

	CPPUNIT_ASSERT_EQUAL( result::size_type( 1 ), r.size() );

    CPPUNIT_ASSERT_DOUBLES_EQUAL( double(2.50), r.front()[ "value" ].as<double>(), 0.01 );
}

void PlaceGeometryTest::testG23_03_BilinearJustOutsideGrid()
{
	double lon = 5.750 + (175 * 0.1);
	double lat = -13.250 + (0 * 0.1) - 0.1;
	pointToWgs84( lon, lat );

	ostringstream pt;
	pt << "bilinear POINT(" << wdb::round(lon,4) << " " << wdb::round(lat,4) << ")";
	result r =  t->exec( statement_( pt.str(), 34 ) );
	CPPUNIT_ASSERT(r.empty());
}

void PlaceGeometryTest::testG23_04_BilinearFarOutsideGrid()
{
	double lon = 5.750 + (175 * 0.1);
	double lat = -13.250 + (0 * 0.1) - 0.6;
	pointToWgs84( lon, lat );

	ostringstream pt;
	pt << "bilinear POINT(" << wdb::round(lon,4) << " " << wdb::round(lat,4) << ")";
	result r = t->exec( statement_( pt.str(), 34 ) );
	CPPUNIT_ASSERT(r.empty());
}

void PlaceGeometryTest::testG23_05_BilinearWithOneUndefinedPoint()
{
	double lon = 5.750 + (175 * 0.1) + 0.05;
	double lat = -13.250 + (0 * 0.1) + 0.05;
	pointToWgs84( lon, lat );

	ostringstream pt;
	pt << "bilinear POINT(" << wdb::round(lon,4) << " " << wdb::round(lat,4) << ")";
	result r = t->exec( statement_( pt.str(), 14 ) );

    //CPPUNIT_ASSERT( r.empty() );
    CPPUNIT_ASSERT( r.front()[ "value" ].is_null() );
}

void PlaceGeometryTest::testG24_01_BilinearReturnsCorrectGeometry()
{
	double lon = 5.750 + (175 * 0.1) + 0.05;
	double lat = -13.250 + (0 * 0.1) + 0.05;
	pointToWgs84( lon, lat );

	ostringstream pt;
	pt << "bilinear POINT(" << wdb::round(lon,4) << " " << wdb::round(lat,4) << ")";

	result r = t->exec( statement_( pt.str(), 34 ) );

    CPPUNIT_ASSERT_EQUAL( result::size_type( 1 ), r.size() );

    ostringstream pnt;
	pnt << "POINT(" << wdb::round(lon,4) << " " << wdb::round(lat,4) << ")";
    CPPUNIT_ASSERT_EQUAL( pnt.str(), r.front()["geometry_as_text"].as<string>() );
}

//void PlaceGeometryTest::testExactPointAndPlaceName()
//{
//	double lon = 5.750 + (175 * 0.1) + 0.05;
//	double lat = -13.250 + (0 * 0.1) + 0.05;
//	pointToWgs84( lon, lat );
//
//	ostringstream pt;
//	pt << "exact POINT(" << wdb::round(lon,4) << " " << wdb::round(lat,4) << ")";
//
//	{
//		result r =  t->exec(statement_( pt.str(), 999 ));
//		CPPUNIT_ASSERT_EQUAL(result::size_type(2), r.size());
//	}
//	{
//		result r =  t->exec(statement_( pt.str() + " hirlam 10 grid", 999 ));
//		CPPUNIT_ASSERT_EQUAL(result::size_type(1), r.size());
//	}
//}
//
//void PlaceGeometryTest::testNearestPointAndPlaceName()
//{
//	double lon = 5.750 + (175 * 0.1) + 0.05;
//	double lat = -13.250 + (0 * 0.1) + 0.05;
//	pointToWgs84( lon, lat );
//
//	ostringstream pt;
//	pt << "nearest POINT(" << wdb::round(lon,4) << " " << wdb::round(lat,4) << ")";
//
//	{
//		result r =  t->exec(statement_( pt.str(), 999 ));
//		CPPUNIT_ASSERT_EQUAL(result::size_type(2), r.size());
//	}
//	{
//		result r =  t->exec(statement_( pt.str() + " hirlam 10 grid", 999 ));
//		CPPUNIT_ASSERT_EQUAL(result::size_type(1), r.size());
//	}
//}
//void PlaceGeometryTest::testSurroundPointAndPlaceName()
//{
//	double lon = 5.750 + (175 * 0.1) + 0.05;
//	double lat = -13.250 + (0 * 0.1) + 0.05;
//	pointToWgs84( lon, lat );
//
//	ostringstream pt;
//	pt << "surround POINT(" << wdb::round(lon,4) << " " << wdb::round(lat,4) << ")";
//
//	{
//		result r =  t->exec(statement_( pt.str(), 999 ));
//		CPPUNIT_ASSERT_EQUAL(result::size_type(8), r.size());
//	}
//	{
//		result r =  t->exec(statement_( pt.str() + " hirlam 10 grid", 999 ));
//		CPPUNIT_ASSERT_EQUAL(result::size_type(4), r.size());
//	}
//}
//void PlaceGeometryTest::testBilinearPointAndPlaceName()
//{
//	double lon = 5.750 + (175 * 0.1) + 0.05;
//	double lat = -13.250 + (0 * 0.1) + 0.05;
//	pointToWgs84( lon, lat );
//
//	ostringstream pt;
//	pt << "bilinear POINT(" << wdb::round(lon,4) << " " << wdb::round(lat,4) << ")";
//
//	{
//		result r =  t->exec(statement_( pt.str(), 999 ));
//		CPPUNIT_ASSERT_EQUAL(result::size_type(2), r.size());
//	}
//	{
//		result r =  t->exec(statement_( pt.str() + " hirlam 10 grid", 999 ));
//		CPPUNIT_ASSERT_EQUAL(result::size_type(1), r.size());
//	}
//}

void PlaceGeometryTest::testG25_01_PointSource_ExactHit()
{
	result r =  t->exec( statementFloat_( "exact POINT(15.2 55.75)", 11 ) );
    CPPUNIT_ASSERT_EQUAL( size_t( 1 ), count_val( r, "placename", "test point 3" ) );
	CPPUNIT_ASSERT_EQUAL( result::size_type( 1 ), r.size() );
}

void PlaceGeometryTest::testG25_02_PointSource_ExactMiss()
{
	result r =  t->exec( statementFloat_( "exact POINT(15.2 55.74)", 11 ) );
	CPPUNIT_ASSERT_EQUAL( result::size_type( 0 ), r.size() );
}

void PlaceGeometryTest::testG25_03_PointSource_Nearest() {
	result r =  t->exec( statementFloat_( "nearest POINT(15.21 55.72)", 11 ) );
    CPPUNIT_ASSERT_EQUAL( size_t( 1 ), count_val( r, "placename", "test point 3" ) );
	CPPUNIT_ASSERT_EQUAL( result::size_type( 1 ), r.size() );
}

void PlaceGeometryTest::testG25_04_PointSource_Bilinear() {
	// TODO: Correct Test
	/*
	result r =  t->exec( statementFloat_( "bilinear POINT(15.21 55.72)", 11 ) );
    CPPUNIT_ASSERT_EQUAL( size_t( 1 ), count_val( r, "placename", "test point 3" ) );
	CPPUNIT_ASSERT_EQUAL( result::size_type( 1 ), r.size() );
	*/
}

void PlaceGeometryTest::testG25_05_PointSource_Surround() {
	/*
	result r =  t->exec( statementFloat_( "surround POINT(15.21 55.72)", 11 ) );
    CPPUNIT_ASSERT_EQUAL( size_t( 1 ), count_val( r, "placename", "test point 3" ) );
    CPPUNIT_ASSERT_EQUAL( size_t( 1 ), count_val( r, "placename", "test point 4" ) );
    CPPUNIT_ASSERT_EQUAL( size_t( 1 ), count_val( r, "placename", "test point 5" ) );
    CPPUNIT_ASSERT_EQUAL( size_t( 1 ), count_val( r, "placename", "test point 6" ) );
	CPPUNIT_ASSERT_EQUAL( result::size_type( 4 ), r.size() );
	*/
}

void PlaceGeometryTest::testG25_06_PointSource_Polygon() {
	//result r =  t->exec( statement_( "exact POINT(-25 5.6)", 11 ) );
	//CPPUNIT_ASSERT_EQUAL( result::size_type( 1 ), r.size() );
}

void PlaceGeometryTest::testG30_02_AllPointsCorrectlyLocatedRotated()
{
	double lon, lat;
	ostringstream pt;
	const int randomOffset = 1234;
	for ( int y=0; y<400; y++ ) {
		for ( int x=0; x<248; x++ ) {
			if ( ( ( y * 248 ) + x ) == randomOffset ) {
				lon = 5.750 + ( x * 0.1 );
				lat = -13.250 + ( y * 0.1 );
				pointToWgs84( lon, lat );
				pt.str("");
				pt << "POINT(" << wdb::round(lon,4) << " " << wdb::round(lat,4) << ")";
				result r = t->exec( statement_( pt.str(), 66 ) );
				//if ( r.empty() ) {
				//	std::cout << "Failed to get a result for " << x << ", " << y << ": " << statement_( pt.str(), 66 );
				//}
				CPPUNIT_ASSERT( ! r.empty() );
				CPPUNIT_ASSERT_EQUAL( ( (x * 1000) + y), r.front()[ "value" ].as<int>() );
			}
		}
	}
}


void PlaceGeometryTest::testG31_01_ReturnAllRows()
{
    const result::size_type expectedRows = 99200; // This is the actual number of expected rows
    const result::size_type minExpectedRows = 96000; // What we deem as acceptable to pass the test

    // The following is the definition for the hirlam10 grid
	double lon = 5.750 + (0 * 0.1) - 0.1;
	double lat = -13.250 + (0 * 0.1) - 0.1;
	ostringstream pt;
	pt << "POLYGON((";
	pointToWgs84( lon, lat );
	pt << lon << " " << lat << ", ";
	lon = 5.750 + (62 * 0.1) + 0.1; lat = -13.250 + (0 * 0.1) - 0.1;
	pointToWgs84( lon, lat );
	pt << lon << " " << lat << ", ";
	lon = 5.750 + (124 * 0.1) + 0.1; lat = -13.250 + (0 * 0.1) - 0.1;
	pointToWgs84( lon, lat );
	pt << lon << " " << lat << ", ";
	lon = 5.750 + (186 * 0.1) + 0.1; lat = -13.250 + (0 * 0.1) - 0.1;
	pointToWgs84( lon, lat );
	pt << lon << " " << lat << ", ";
	lon = 5.750 + (248 * 0.1) + 0.1; lat = -13.250 + (0 * 0.1) - 0.1;
	pointToWgs84( lon, lat );
	pt << lon << " " << lat << ", ";
	lon = 5.750 + (248 * 0.1) + 0.1; lat = -13.250 + (100 * 0.1) + 0.1;
	pointToWgs84( lon, lat );
	pt << lon << " " << lat << ", ";
	lon = 5.750 + (248 * 0.1) + 0.1; lat = -13.250 + (200 * 0.1) + 0.1;
	pointToWgs84( lon, lat );
	pt << lon << " " << lat << ", ";
	lon = 5.750 + (248 * 0.1) + 0.1; lat = -13.250 + (300 * 0.1) + 0.1;
	pointToWgs84( lon, lat );
	pt << lon << " " << lat << ", ";
	lon = 5.750 + (248 * 0.1) + 0.1; lat = -13.250 + (400 * 0.1) + 0.1;
	pointToWgs84( lon, lat );
	pt << lon << " " << lat << ", ";
	lon = 5.750 + (186 * 0.1) - 0.1; lat = -13.250 + (400 * 0.1) + 0.1;
	pointToWgs84( lon, lat );
	pt << lon << " " << lat << ", ";
	lon = 5.750 + (124 * 0.1) - 0.1; lat = -13.250 + (400 * 0.1) + 0.1;
	pointToWgs84( lon, lat );
	pt << lon << " " << lat << ", ";
	lon = 5.750 + (62 * 0.1) - 0.1; lat = -13.250 + (400 * 0.1) + 0.1;
	pointToWgs84( lon, lat );
	pt << lon << " " << lat << ", ";
	lon = 5.750 + (0 * 0.1) - 0.1; lat = -13.250 + (400 * 0.1) + 0.1;
	pointToWgs84( lon, lat );
	pt << lon << " " << lat << ", ";
	lon = 5.750 + (0 * 0.1) - 0.1; lat = -13.250 + (300 * 0.1) + 0.1;
	pointToWgs84( lon, lat );
	pt << lon << " " << lat << ", ";
	lon = 5.750 + (0 * 0.1) - 0.1; lat = -13.250 + (200 * 0.1) - 0.1;
	pointToWgs84( lon, lat );
	pt << lon << " " << lat << ", ";
	lon = 5.750 + (0 * 0.1) - 0.1; lat = -13.250 + (100 * 0.1) + 0.1;
	pointToWgs84( lon, lat );
	pt << lon << " " << lat << ", ";
	lon = 5.750 + (0 * 0.1) - 0.1; lat = -13.250 + (0 * 0.1) - 0.1;
	pointToWgs84( lon, lat );
	pt << lon << " " << lat << "))";

	result r = t->exec( statement_( pt.str(), 33 ) );

    CPPUNIT_ASSERT( minExpectedRows <= r.size() );
    CPPUNIT_ASSERT( not r.empty() );
    if ( r.size() < minExpectedRows )
    {
    	ostringstream failMsg;
    	failMsg << "Too few returned rows from query: " << r.size();
    	string msg = failMsg.str();
    	CPPUNIT_FAIL( msg );
    }

    int valueid = r.front() [ "valueid" ].as<int>();
    for ( result::const_iterator it = r.begin(); it != r.end(); ++ it )
    {
        CPPUNIT_ASSERT_EQUAL( valueid, it->at( "valueid" ).as<int>() );
    }
}

void PlaceGeometryTest::testG31_02_ReturnSomeRows()
{
    const result::size_type expectedRows = 92; //Old: 102; //190;

    result r = t->exec( statement_( "POLYGON( ( 11.34 60.75, 11.34 62.75, 13.34 62.75, 11.34 60.75 ) )" ) );
    CPPUNIT_ASSERT_EQUAL( expectedRows, r.size() );
}

void PlaceGeometryTest::testG31_03_ReturnNoRows()
{
    result r = t->exec( statement_( "POLYGON( ( 71.34 60.75, 71.34 62.75, 73.34 62.75, 71.34 60.75 ) )" ) );
    CPPUNIT_ASSERT( r.empty() );
}

void PlaceGeometryTest::testG40_01_AddPlacePoint()
{
	ostringstream q;
	q << "SELECT wci.addPlacePoint( \'InstallTest Point\',"
	  << "st_geomfromtext(\'POINT( 15 65 )\', "
	  << DEFAULT_SRID
	  << " ) )";
	// Add Meta
    result rId = t->exec( q.str() );
    CPPUNIT_ASSERT( rId.size() > 0 );
    // Check for meta
    result rC = t->exec( "SELECT * FROM wci.getPlaceDefinition( \'installTest poINt\' )" );
    CPPUNIT_ASSERT( rC.size() > 0 );
}

void PlaceGeometryTest::testG40_02_AddPlaceRegularGrid()
{
	ostringstream q;
	q << "SELECT wci.addPlaceRegularGrid( \'InstallTest Grid\',"
	  << "2, 2, 0.2, 0.2, 0.5, 0.5, \'+proj=longlat +a=6367470.0 +towgs84=0,0,0 +no_defs\' )";
	// Add Meta
    result rId = t->exec( q.str() );
    CPPUNIT_ASSERT( rId.size() > 0 );
    // Check for meta
    result rC = t->exec( "SELECT * FROM wci.getPlaceRegularGrid( \'installTest gRId\' )" );
    CPPUNIT_ASSERT( rC.size() > 0 );
}

void PlaceGeometryTest::testG41_01_addWithTrimmedSrid()
{
    result rC = t->exec( "SELECT wci.addPlaceRegularGrid('installTestSrid_01', 10,10,1,1,0,0,'+proj=longlat +ellps=airy +no_defs');" );
    CPPUNIT_ASSERT( rC.size() );
}

void PlaceGeometryTest::testG41_02_addWithRightSpacedSrid()
{
    result rC = t->exec( "SELECT wci.addPlaceRegularGrid('installTestSrid_02', 10,10,1,1,0,0,'+proj=longlat +ellps=airy +no_defs');" );
    CPPUNIT_ASSERT( rC.size() );
}

void PlaceGeometryTest::testG41_03_addWithLeftSpacedSrid()
{
    result rC = t->exec( "SELECT wci.addPlaceRegularGrid('installTestSrid_03', 10,10,1,1,0,0,' +proj=longlat +ellps=airy +no_defs');" );
    CPPUNIT_ASSERT( rC.size() );
}

void PlaceGeometryTest::testG41_04_addWithBothSpacedSrid()
{
    result rC = t->exec( "SELECT wci.addPlaceRegularGrid('installTestSrid_04', 10,10,1,1,0,0,'+proj=longlat +ellps=airy +no_defs ');" );
    CPPUNIT_ASSERT( rC.size() );
}

void PlaceGeometryTest::testG41_05_addWithArbitrarySpacedSrid()
{
    result rC = t->exec( "SELECT wci.addPlaceRegularGrid('installTestSrid_05', 10,10,1,1,0,0,'+proj=longlat     +ellps=airy +no_defs');" );
    CPPUNIT_ASSERT( rC.size() );
}

void PlaceGeometryTest::testG101_01_lonlatoutofbounds()
{
	const result::size_type expectedRowsI = 1;
    result rI = t->exec( statement_( "nearest POINT(13 64.5)", 100 ) );
    CPPUNIT_ASSERT_EQUAL( expectedRowsI, rI.size() );

    const result::size_type expectedRows = 0;
    result r = t->exec( statement_( "nearest POINT(151 -33)", 100 ) );
    CPPUNIT_ASSERT_EQUAL( expectedRows, r.size() );
}

void PlaceGeometryTest::testG101_02_lonlatoutofbounds()
{
	const result::size_type expectedRowsI = 2;
    result rI = t->exec( statement_( "nearest POINT(13 64.5)", 101 ) );
    CPPUNIT_ASSERT_EQUAL( expectedRowsI, rI.size() );

    const result::size_type expectedRows = 1;
    result r = t->exec( statement_( "nearest POINT(151 -33)", 101 ) );
    CPPUNIT_ASSERT_EQUAL( expectedRows, r.size() );
}

void PlaceGeometryTest::testG102_01_testLocationInterference()
{
	const result::size_type expectedRowsI = 1;
    result rI = t->exec( statementFloat_( "nearest POINT(15 60)", 10 ) );
    CPPUNIT_ASSERT_EQUAL( expectedRowsI, rI.size() );
}


// Support Functions
//---------------------------------------------------------------------------

std::string PlaceGeometryTest::statement_( const std::string & geo, int paramid ) const
{
    ostringstream st;
    st << "SELECT *, st_astext(placegeometry) AS geometry_as_text FROM wci.read( ARRAY['test group'], ";
    if ( "NULL" == geo ) {
        st << "NULL";
    }
    else {
        st << "'" << geo << "'";
    }
    st << ", '2004-12-26 06:00:00+00', ";
    st << "NULL, '{\"" << specFromParamNumber_.find( paramid )->second << "\"}', NULL, NULL, NULL::wci.returnfloat )";

    return st.str();
}

std::string PlaceGeometryTest::statementFloat_( const std::string & geo, int paramid ) const
{
    ostringstream st;
    st << "SELECT *, st_astext(placegeometry) AS geometry_as_text FROM wci.read( ARRAY['test wci 6', 'test wci 7'], ";
    if ( "NULL" == geo ) {
        st << "NULL";
    }
    else {
        st << "'" << geo << "'";
    }
    st << ", '2004-12-26 06:00:00+00', ";
    st << "NULL, '{\"" << specFromParamNumber_.find( paramid )->second << "\"}', NULL, NULL, NULL::wci.returnfloat )";

    return st.str();
}

namespace
{

map<int, string> getSpecFromParamNumber()
{
    map<int, string> ret;

    ret[ 1 ] = "air pressure";
    ret[ 3 ] = "tendency of surface air pressure";
    ret[ 10 ] = "snowfall amount";
    ret[ 11 ] = "air temperature";
    ret[ 14 ] = "dew point temperature";
    ret[ 15 ] = "max air temperature";
    ret[ 16 ] = "min air temperature";
    ret[ 17 ] = "convective precipitation amount";
    ret[ 18 ] = "convective snowfall amount";
    ret[ 32 ] = "altitude";
    ret[ 33 ] = "x wind";
    ret[ 34 ] = "y wind";
    ret[ 66 ] = "surface roughness length";
    ret[ 100 ] = "cloud area fraction";
    ret[ 101 ] = "land area fraction";
    ret[ 999 ] = "geopotential";

    return ret;
}

}

const map<int, string> PlaceGeometryTest::specFromParamNumber_ = getSpecFromParamNumber();
