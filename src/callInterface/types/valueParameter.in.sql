-- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
-- 
-- wdb - weather and water data storage
--
-- Copyright (C) 2007 met.no
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

CREATE OR REPLACE FUNCTION __WCI_SCHEMA__.normalizeParameter( param TEXT )
RETURNS text
AS '__WDB_LIBDIR__/__WCI_LIB__', 'normalizeWciParameter'
LANGUAGE C IMMUTABLE STRICT;


-- Replace function wci_int.getparametername(wci_int.gridvalue);
CREATE OR REPLACE FUNCTION __WCI_SCHEMA__.getParameterName( data __WCI_SCHEMA__.gridvalue_v )
RETURNS text AS
$BODY$
DECLARE
	ret text;
BEGIN
	ret := data.valueparametername;
	RETURN ret;
END;
$BODY$
LANGUAGE 'plpgsql' IMMUTABLE STRICT;


CREATE OR REPLACE FUNCTION __WCI_SCHEMA__.assertUnitIsPhenomenon( unit text, physicalphenomenon_ text )
RETURNS void AS
$BODY$
DECLARE
	pp text; --selected physicalphenomenon from table
BEGIN
	SELECT physicalphenomenon INTO pp FROM __WCI_SCHEMA__.unit_v WHERE unitname = unit;

	IF pp != physicalphenomenon_ THEN
		RAISE EXCEPTION '% is not a % (it is a %)', unit,  physicalphenomenon_, pp;
	END IF;
END;
$BODY$
LANGUAGE 'plpgsql' STRICT STABLE;


CREATE OR REPLACE FUNCTION
__WCI_SCHEMA__.getValueParameterId(
        parameter text
)
RETURNS integer AS
$BODY$
DECLARE
        session __WCI_SCHEMA__.sessionData_v;
        ret integer;
BEGIN
	session := __WCI_SCHEMA__.getsessiondata();

	SELECT parameterid INTO ret
	FROM __WCI_SCHEMA__.parameter_mv
	WHERE
		parametername = parameter AND
		parameternamespaceid = session.parameterNameSpaceId;
	
	IF NOT FOUND THEN
		RAISE EXCEPTION 'Failed to identify valueparameter ( % ) in namespace ( % )', parameter, session.parameterNameSpaceId;
	END IF;

	RETURN ret;
END;
$BODY$
LANGUAGE 'plpgsql';
