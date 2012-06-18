-- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
-- 
-- wdb - weather and water data storage
--
-- Copyright (C) 2012 met.no
--
--  Contact information:
--  Norwegian Meteorological Institute
--  Box 43 Blindern
--  0313 OSLO
--  NORWAY
--  E-mail: wdb@met.no
--
--  This is free software; you can redistribute it and/or modify
--  it under the terms of the GNU General Public License as published by
--  the Free Software Foundation; either version 2 of the License, or
--  (at your option) any later version.
--
-- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
--
-- This function calculates the prognosis hour of the database, given a
-- reference timestamp and validtime
-- 
SET SESSION client_min_messages TO 'warning';

CREATE OR REPLACE FUNCTION
wci.prognosishour( reftime timestamp with time zone,
				   validtime timestamp with time zone )
RETURNS double precision AS
$BODY$
SELECT extract(hour from ($2 - $1)) + (extract(day from ($2 - $1)) * 24); 
$BODY$
LANGUAGE 'sql' IMMUTABLE strict;
