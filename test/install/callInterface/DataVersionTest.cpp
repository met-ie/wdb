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
    Foundation, Inc., 51 Franklin Street, Fifth Floor1, Boston,
    MA  02110-1301, USA
*/


/**
 * @file
 * Implementation of Data Version WCI Install Tests
 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <DataVersionTest.h>

CPPUNIT_TEST_SUITE_REGISTRATION( DataVersionTest );

using namespace std;
using namespace pqxx;

DataVersionTest::DataVersionTest()
{
	// NOOP
}

DataVersionTest::~DataVersionTest()
{
	// NOOP
}

void DataVersionTest::setUp()
{
	//setUser("wcitestwriter");
	AbstractWciTestFixture::setUp();
}

void DataVersionTest::tearDown()
{
	AbstractWciTestFixture::tearDown();
	//resetUser();
}

void
DataVersionTest::testV1_01A_NoDataVersion()
{
	CPPUNIT_ASSERT_THROW(  t->exec( statementOid_( "'{}'" ) ), pqxx::data_exception );
}

void
DataVersionTest::testV1_01B_NoDataVersion()
{
    CPPUNIT_ASSERT_THROW(  t->exec( statementFloat_( "'{}'" ) ), pqxx::data_exception );
}

void
DataVersionTest::testV1_02A_OneDataVersion()
{
    result rO = t->exec( statementOid_( "ARRAY[1]") );
    CPPUNIT_ASSERT_EQUAL( result::size_type(2), rO.size() );
}

void
DataVersionTest::testV1_02B_OneDataVersion()
{
    result rF = t->exec( statementFloat_( "ARRAY[1]") );
    CPPUNIT_ASSERT_EQUAL( result::size_type(3), rF.size() );
}

void
DataVersionTest::testV1_03A_MultipleDataVersion()
{
    result rO = t->exec( statementOid_( "ARRAY[0, 2, 3]") );
    CPPUNIT_ASSERT_EQUAL( result::size_type(4), rO.size() );
}

void
DataVersionTest::testV1_03B_MultipleDataVersion()
{
    result rF = t->exec( statementFloat_( "ARRAY[0, 2, 3]") );
    CPPUNIT_ASSERT_EQUAL( result::size_type(7), rF.size() );
}

void
DataVersionTest::testV1_04A_MoreThan255DataVersion()
{
	//writeData(265);
    const int noProvidersQueried = 260;
    ostringstream ss;
    ss << "ARRAY[";
    for ( int i = 0; i < noProvidersQueried-1; i++ )
        ss << i << ", ";
    ss << " 259]";

    result rO = t->exec( statementOid_( ss.str() ) );
    CPPUNIT_ASSERT_EQUAL( result::size_type(7), rO.size() );
}

void
DataVersionTest::testV1_04B_MoreThan255DataVersion()
{
	//writeData(265);
    const int noProvidersQueried = 260;
    ostringstream ss;
    ss << "ARRAY[";
    for ( int i = 0; i < noProvidersQueried-1; i++ )
        ss << i << ", ";
    ss << " 259]";

    result rF = t->exec( statementFloat_( ss.str() ) );
    CPPUNIT_ASSERT_EQUAL( result::size_type(12), rF.size() );
}

void
DataVersionTest::testV1_05A_NullDataVersion()
{
    result rO = t->exec( statementOid_( "NULL") );
    CPPUNIT_ASSERT( ! rO.empty() );
    CPPUNIT_ASSERT_EQUAL( result::size_type(7), rO.size() );
}

void
DataVersionTest::testV1_05B_NullDataVersion()
{
    result rO = t->exec( statementFloat_( "NULL") );
    CPPUNIT_ASSERT( ! rO.empty() );
    CPPUNIT_ASSERT_EQUAL( result::size_type(12), rO.size() );
}

void
DataVersionTest::testV2_01A_PositiveInteger()
{
    result rO = t->exec( statementOid_( "ARRAY[1, 4]") );
    CPPUNIT_ASSERT_EQUAL( result::size_type(3), rO.size() );
}

void
DataVersionTest::testV2_01B_PositiveInteger()
{
    result rO = t->exec( statementFloat_( "ARRAY[1, 4]") );
    CPPUNIT_ASSERT_EQUAL( result::size_type(5), rO.size() );
}

void
DataVersionTest::testV2_02A_NegativeInteger()
{
    result rO = t->exec( statementOid_( "ARRAY[-1, -3]") );
    CPPUNIT_ASSERT_EQUAL( result::size_type(3), rO.size() );
}

void
DataVersionTest::testV2_02B_NegativeInteger()
{
    result rO = t->exec( statementFloat_( "ARRAY[-1, -3]") );
    CPPUNIT_ASSERT_EQUAL( result::size_type(5), rO.size() );
}

void
DataVersionTest::testV2_03A_NonInteger()
{
	CPPUNIT_ASSERT_THROW( t->exec( statementOid_( "ARRAY[0, 1, abc]") ), pqxx::sql_error );
}

void
DataVersionTest::testV2_03B_NonInteger()
{
	CPPUNIT_ASSERT_THROW( t->exec( statementFloat_( "ARRAY[0, 1, def]") ), pqxx::sql_error );
}

void
DataVersionTest::testV3_01A_AllExist()
{
    result rO = t->exec( statementOid_( "ARRAY[0, 1, 4, -3]") );
    CPPUNIT_ASSERT_EQUAL( result::size_type(6), rO.size() );
}

void
DataVersionTest::testV3_01B_AllExist()
{
    result rO = t->exec( statementFloat_( "ARRAY[0, 1, 4, -3]") );
    CPPUNIT_ASSERT_EQUAL( result::size_type(10), rO.size() );
}

void
DataVersionTest::testV3_02A_NoneExist()
{
    result rO = t->exec( statementOid_( "ARRAY[299, -350]") );
    CPPUNIT_ASSERT( rO.empty() );
}

void
DataVersionTest::testV3_02B_NoneExist()
{
    result rO = t->exec( statementOid_( "ARRAY[299, -350]") );
    CPPUNIT_ASSERT( rO.empty() );
}

void
DataVersionTest::testV3_03A_SomeExist()
{
    result rO = t->exec( statementOid_( "ARRAY[-350, 1, 4, 299]") );
    CPPUNIT_ASSERT_EQUAL( result::size_type(3), rO.size() );
}

void
DataVersionTest::testV3_03B_SomeExist()
{
    result rO = t->exec( statementFloat_( "ARRAY[-350, 1, 4, 299]") );
    CPPUNIT_ASSERT_EQUAL( result::size_type(5), rO.size() );
}

void
DataVersionTest::testV4_01A_DataVersionNoSize()
{
	CPPUNIT_ASSERT_THROW(  t->exec( statementOid_( "'{}'" ) ), pqxx::data_exception );
}

void
DataVersionTest::testV4_01B_DataVersionNoSize()
{
    CPPUNIT_ASSERT_THROW(  t->exec( statementFloat_( "'{}'" ) ), pqxx::data_exception );
}

void
DataVersionTest::testV4_02A_DataVersionSizeInt()
{
    result rO = t->exec( statementOid_( "ARRAY[2, 4, -1]") );
    CPPUNIT_ASSERT_EQUAL( result::size_type(3), rO.size() );
}

void
DataVersionTest::testV4_02B_DataVersionSizeInt()
{
	result rF = t->exec( statementFloat_( "ARRAY[2, 4, -1]") );
    CPPUNIT_ASSERT_EQUAL( result::size_type(5), rF.size() );
}

void
DataVersionTest::testV4_03A_DataVersionGtSizeInt()
{
	CPPUNIT_ASSERT_THROW(  t->exec( statementOid_( "ARRAY[2456263471]" ) ), pqxx::sql_error );
}

void
DataVersionTest::testV4_03B_DataVersionGtSizeInt()
{
    CPPUNIT_ASSERT_THROW(  t->exec( statementFloat_( "ARRAY[2456263471]" ) ), pqxx::sql_error );
}

void
DataVersionTest::testV5_01A_NoDuplicates()
{
    result rO = t->exec( statementOid_( "ARRAY[1, 2, 3]") );
    CPPUNIT_ASSERT_EQUAL( result::size_type(4), rO.size() );
}

void
DataVersionTest::testV5_01B_NoDuplicates()
{
    result rF = t->exec( statementFloat_( "ARRAY[1, 2, 3]") );
    CPPUNIT_ASSERT_EQUAL( result::size_type(7), rF.size() );
}

void
DataVersionTest::testV5_02A_OneDuplicate()
{
    result rO = t->exec( statementOid_( "ARRAY[1, 2, 3, 2]") );
    CPPUNIT_ASSERT_EQUAL( result::size_type(4), rO.size() );
}

void
DataVersionTest::testV5_02B_OneDuplicate()
{
	result rF = t->exec( statementFloat_( "ARRAY[1, 2, 3, 2]") );
    CPPUNIT_ASSERT_EQUAL( result::size_type(7), rF.size() );
}

void
DataVersionTest::testV5_03A_ManyDuplicates()
{
    result rO = t->exec( statementOid_( "ARRAY[0, 2, 2, 2, -1, 6, 6, 6, 6]") );
    CPPUNIT_ASSERT_EQUAL( result::size_type(5), rO.size() );
}

void
DataVersionTest::testV5_03B_ManyDuplicates()
{
    result rF = t->exec( statementFloat_( "ARRAY[0, 2, 2, 2, -1, 6, 6, 6, 6]") );
    CPPUNIT_ASSERT_EQUAL( result::size_type(8), rF.size() );
}

void DataVersionTest::testV6_01A_GetNewestNoEntries()
{
    result r = t->exec( statementOid_( "ARRAY[-1]", 3) );
    CPPUNIT_ASSERT( r.empty() );
}

void DataVersionTest::testV6_01B_GetNewestNoEntries()
{
    result r = t->exec( statementFloat_( "ARRAY[-1]", 3) );
    CPPUNIT_ASSERT( r.empty() );
}

void DataVersionTest::testV6_02A_GetNewestOneEntry()
{
    result r = t->exec( statementOid_( "ARRAY[-1]", 10) );
    CPPUNIT_ASSERT_EQUAL( result::size_type(1), r.size() );
}

void DataVersionTest::testV6_02B_GetNewestOneEntry()
{
    result r = t->exec( statementFloat_( "ARRAY[-1]", 10) );
    CPPUNIT_ASSERT_EQUAL( result::size_type(1), r.size() );
}

void DataVersionTest::testV6_03A_GetNewestSeveralEntries()
{
    result r = t->exec( statementOid_( "'{-1}'", 11) );
    CPPUNIT_ASSERT_EQUAL( result::size_type(1), r.size() );
    CPPUNIT_ASSERT_EQUAL(2, r[0]["dataversion"].as<int>());
}

void DataVersionTest::testV6_03B_GetNewestSeveralEntries()
{
    result r = t->exec( statementFloat_( "'{-1}'", 11) );
    CPPUNIT_ASSERT_EQUAL( result::size_type(1), r.size() );
    CPPUNIT_ASSERT_EQUAL(2, r[0]["dataversion"].as<int>());
}

void DataVersionTest::testV7_01A_PositiveVersionOutOfBounds()
{
    result r = t->exec( statementOid_( "'{2}'", 15) ); // dataversions in db should be 0 and 1.
    CPPUNIT_ASSERT(r.empty());
}

void DataVersionTest::testV7_01B_PositiveVersionOutOfBounds()
{
    result r = t->exec( statementFloat_( "'{2}'", 15) ); // dataversions in db should be 0 and 1.
    CPPUNIT_ASSERT(r.empty());
}

void DataVersionTest::testV7_02A_NegativeVersionOutOfBounds()
{
    result r = t->exec( statementOid_( "'{-3}'", 15) ); // negative dataversions in db should be -1 and -2.
    CPPUNIT_ASSERT(r.empty());
}


void DataVersionTest::testV7_02B_NegativeVersionOutOfBounds()
{
    result r = t->exec( statementFloat_( "'{-3}'", 15) ); // negative dataversions in db should be -1 and -2.
    CPPUNIT_ASSERT(r.empty());
}

namespace
{
	template<int Val>
	inline bool hasDataVersion(const row & t )
	{
		return t["dataversion"].as<int>() == Val;
	}
}

void DataVersionTest::testV8_01A_MixedPositiveAndNegativeVersion()
{
    result r = t->exec( statementOid_( "'{-2, 2}'", 16) );
    CPPUNIT_ASSERT_EQUAL( result::size_type(2), r.size() );

    CPPUNIT_ASSERT( find_if(r.begin(), r.end(), hasDataVersion<1>) != r.end() );
    CPPUNIT_ASSERT( find_if(r.begin(), r.end(), hasDataVersion<2>) != r.end() );
}

void DataVersionTest::testV8_01B_MixedPositiveAndNegativeVersion()
{
    result r = t->exec( statementFloat_( "'{-2, 2}'", 16) );
    CPPUNIT_ASSERT_EQUAL( result::size_type(2), r.size() );

    CPPUNIT_ASSERT( find_if(r.begin(), r.end(), hasDataVersion<1>) != r.end() );
    CPPUNIT_ASSERT( find_if(r.begin(), r.end(), hasDataVersion<2>) != r.end() );
}

void DataVersionTest::testV8_02A_MixedPositiveAndNegativeVersionOverlapping()
{
    result r = t->exec( statementOid_( "'{-2, 1}'", 16) );
    CPPUNIT_ASSERT_EQUAL( result::size_type(1), r.size() );
    CPPUNIT_ASSERT_EQUAL(1, r[0]["dataversion"].as<int>());
}

void DataVersionTest::testV8_02B_MixedPositiveAndNegativeVersionOverlapping()
{
    result r = t->exec( statementFloat_( "'{-2, 1}'", 16) );
    CPPUNIT_ASSERT_EQUAL( result::size_type(1), r.size() );
    CPPUNIT_ASSERT_EQUAL(1, r[0]["dataversion"].as<int>());
}


//
// Support Functions
//

string DataVersionTest::statementOid_( const string & dataVersion, int paramid ) const
{
    ostringstream st;
    st << "SELECT dataversion FROM wci.read( ARRAY['test wci 0'], NULL,"
       << "'2004-12-29 06:00:00+00', NULL, "
       << "ARRAY['" << specFromParamNumber_.find( paramid )->second << "'], "
       << "NULL, "
       << dataVersion << ", NULL::wci.returngid )";

    return st.str();
}

string DataVersionTest::statementFloat_( const string & dataVersion, int paramid ) const
{
    ostringstream st;
    st << "SELECT dataversion FROM wci.read( ARRAY['test wci 1', 'test wci 4'], "
	   << "'nearest test point 0', "
       << "'2004-12-29 06:00:00+00', NULL, "
       << "ARRAY['" << specFromParamNumber_.find( paramid )->second << "'], "
       << "NULL, "
       << dataVersion << ", NULL::wci.returnFloat )";

    return st.str();
}

string DataVersionTest::writeStatement_() const
{
	// Todo: Identify a correct OID and use that instead...
	ostringstream ret;
	ret << "SELECT wci.write( "<< 24944 << "::oid, "<< "'Test Grid, Rotated'::text, '2008-02-01 00:00:00'::timestamp,"
			<< "'2008-02-01 00:00:00'::timestamp, '2008-02-01 00:00:00'::timestamp, "
			<< "'air temperature', 'height above reference ellipsoid', "<< 0 << ", "<< 0
			<< " )";
	return ret.str();
}

void DataVersionTest::writeData(size_t noOfWrites)
{
    for ( size_t i  = 0; i < noOfWrites; ++ i )
		t->exec(writeStatement_());
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
    ret[ 15 ] = "max air temperature";
    ret[ 16 ] = "min air temperature";
    ret[ 32 ] = "altitude";
    ret[ 33 ] = "x wind";
    ret[ 34 ] = "y wind";
    ret[ 66 ] = "surface roughness length";

    return ret;
}

}

const map<int, string> DataVersionTest::specFromParamNumber_ = getSpecFromParamNumber();
