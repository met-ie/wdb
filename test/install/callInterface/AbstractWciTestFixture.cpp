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
 * Implementation of Abstract WCI Test Fixture
 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "AbstractWciTestFixture.h"


AbstractWciTestFixture::AbstractWciTestFixture()
	: currentUser_( defaultUser_ )
{
	// NOOP
}

AbstractWciTestFixture::~AbstractWciTestFixture()
{
	// NOOP
}


void AbstractWciTestFixture::startNewTransaction()
{
    AbstractWdbTestFixture::startNewTransaction();
    t->exec( "SELECT wci.begin('" + currentUser_ + "', 999, 999, 0 )" );
    t->exec( "SET TIME ZONE 'UTC';" );
}

void AbstractWciTestFixture::endTransaction()
{
    if ( t )
    {
        try
        {
            t->exec( "SELECT wci.end();" );
        }
        catch ( std::logic_error & )
        {
            // Transaction was aborted - calling wci.end() could not be done.
        }
    }
    AbstractWdbTestFixture::endTransaction();
}

const char * AbstractWciTestFixture::defaultParameter = "air pressure";

const std::string AbstractWciTestFixture::defaultUser_ = "wcitest";
