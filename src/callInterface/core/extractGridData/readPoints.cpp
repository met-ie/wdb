/*
 wdb

 Copyright (C) 2009 met.no

 Contact information:
 Norwegian Meteorological Institute
 Box 43 Blindern
 0313 OSLO
 NORWAY
 E-mail: mail@met.no

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

#include "readPoints.h"
#include "AllPointsReader.h"
#include "SinglePointReader.h"
#include "PolygonReader.h"
#include <geos.h>
#include <boost/shared_ptr.hpp>
#include <map>

extern "C"
{
#include <postgres.h>

struct GridPointDataListIterator * readPoints(
		const struct PlaceSpecification * ps, GEOSGeom location,
		enum InterpolationType interpolation, FileId dataId)
{
	GridPointDataListIterator * ret = NULL;
	try
	{
		if ( location == 0 )
		{
			AllPointsReader reader(* ps);
			struct GridPointDataList * list = reader.read(dataId);
			ret = GridPointDataListIteratorNew(list);
		}
		else
		{
			int geometryType = GEOSGeomTypeId(location);
			if (geometryType == geos::GEOS_POINT)
			{
				SinglePointReader reader(* ps);
				GridPointDataList * list = reader.read(location, interpolation, dataId);
				ret = GridPointDataListIteratorNew(list);
			}
			else if (geometryType == geos::GEOS_POLYGON)
			{
				PolygonReader reader(* ps);
				GridPointDataList * list = reader.read(location, interpolation, dataId);
				ret = GridPointDataListIteratorNew(list);
			}
			else
				throw std::runtime_error("This geometry type is not supported");
		}
	}
	catch (std::exception & e)
	{
		if ( ret )
			GridPointDataListDelete(ret->list);
		if ( location )
			GEOSGeom_destroy(location);
		ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED), errmsg(e.what())));
	}
	catch (...)
	{
		// This should never happen, but just in case...
		if ( ret )
			GridPointDataListDelete(ret->list);
		if ( location )
			GEOSGeom_destroy(location);
		ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED), "Unknown error when fetching point data. Please tell someone about this"));
	}

	if ( location )
		GEOSGeom_destroy(location);
	return ret;
}

}