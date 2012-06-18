-- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
-- 
-- wdb - weather and water data storage
--
-- Copyright (C) 2007-2009 met.no
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
SET SESSION client_min_messages TO 'warning';


CREATE TABLE __WDB_SCHEMA__.valuetype (
	valuetype				integer NOT NULL,
	valuetypename			character varying(80) NOT NULL,
    valuetypedescription	character varying(255) NOT NULL
);

ALTER TABLE ONLY __WDB_SCHEMA__.valuetype
    ADD CONSTRAINT valuetype_pkey PRIMARY KEY (valuetype);

REVOKE ALL ON __WDB_SCHEMA__.valuetype FROM public;
GRANT ALL ON __WDB_SCHEMA__.valuetype TO wdb_admin;


CREATE TABLE __WDB_SCHEMA__.qualityconfidencecode (
    confidencecode				integer NOT NULL,
    confidencecodedescription	character varying(255) NOT NULL
);

ALTER TABLE ONLY __WDB_SCHEMA__.qualityconfidencecode
    ADD CONSTRAINT confidencecode_pkey PRIMARY KEY (confidencecode);

REVOKE ALL ON __WDB_SCHEMA__.qualityconfidencecode FROM public;
GRANT ALL ON __WDB_SCHEMA__.qualityconfidencecode TO wdb_admin;

INSERT INTO __WDB_SCHEMA__.qualityconfidencecode VALUES ( 0, 'not defined' );


--
-- Name: FloatValue Group 
--
CREATE TABLE __WDB_SCHEMA__.floatvaluegroup (
    valuegroupid				serial NOT NULL,
    dataproviderid 				bigint NOT NULL,
    placeid						bigint NOT NULL,
    validtimefrom				interval NOT NULL,
    validtimeto					interval NOT NULL,
    validtimeindeterminatecode	integer NOT NULL,
    valueparameterid			integer NOT NULL,
    levelparameterid			integer NOT NULL,
    levelfrom					real NOT NULL,
    levelto						real NOT NULL,
    levelindeterminatecode		integer NOT NULL,
    dataversion					integer NOT NULL
);

REVOKE ALL ON __WDB_SCHEMA__.floatvaluegroup FROM public;
GRANT ALL ON __WDB_SCHEMA__.floatvaluegroup TO wdb_admin;
GRANT SELECT, DELETE ON __WDB_SCHEMA__.floatvaluegroup TO wdb_clean;


--
-- Name: FloatValue Detail
--
CREATE TABLE __WDB_SCHEMA__.floatvalueitem (
    valuegroupid				integer NOT NULL,
    referencetime				timestamp with time zone NOT NULL,
    maxdataversion				integer NOT NULL,
    confidencecode				integer NOT NULL,
    value						real NOT NULL,
    valuestoretime				timestamp with time zone NOT NULL
);

REVOKE ALL ON __WDB_SCHEMA__.floatvalueitem FROM public;
GRANT ALL ON __WDB_SCHEMA__.floatvalueitem TO wdb_admin;
GRANT SELECT, DELETE ON __WDB_SCHEMA__.floatvalueitem TO wdb_clean;


--
-- Name: GRIDValue 
--
CREATE TABLE __WDB_SCHEMA__.gridvalue (
    valueid 					bigserial NOT NULL,
    valuetype 					integer NOT NULL,   
	dataproviderid 				bigint NOT NULL,
    placeid 					bigint NOT NULL,
    referencetime				timestamp with time zone NOT NULL,
	validtimefrom 				timestamp with time zone NOT NULL,
    validtimeto 				timestamp with time zone NOT NULL,
    validtimeindeterminatecode	integer NOT NULL,  
	valueparameterid 			integer NOT NULL, 
	levelparameterid 			integer NOT NULL,
    levelfrom 					real NOT NULL,
    levelto 					real NOT NULL,
    levelindeterminatecode		integer NOT NULL,
    dataversion 				integer NOT NULL,
	maxdataversion 				integer NOT NULL,
    confidencecode 				integer NOT NULL,
    value 						bigint NOT NULL,
    valuestoretime 				timestamp with time zone NOT NULL
);

REVOKE ALL ON __WDB_SCHEMA__.gridvalue FROM public;
GRANT ALL ON __WDB_SCHEMA__.gridvalue TO wdb_admin;
GRANT SELECT, DELETE ON __WDB_SCHEMA__.gridvalue TO wdb_clean;
REVOKE ALL ON __WDB_SCHEMA__.gridvalue_valueid_seq FROM public;
GRANT ALL ON __WDB_SCHEMA__.gridvalue_valueid_seq TO wdb_admin;


CREATE TABLE __WDB_SCHEMA__.valueadditionallevelinfo (
    valueid 					bigint NOT NULL,
    valuetype					character varying(80) NOT NULL,
    levelparameterid			integer NOT NULL,
    levelfrom					real NOT NULL,
    levelto						real NOT NULL,
    levelindeterminatecode		integer NOT NULL
);

REVOKE ALL ON __WDB_SCHEMA__.valueadditionallevelinfo FROM public;
GRANT ALL ON __WDB_SCHEMA__.valueadditionallevelinfo TO wdb_admin;
--GRANT INSERT ON  __WDB_SCHEMA__.valueadditionallevelinfo TO wdb_write;
--GRANT SELECT, DELETE ON __WDB_SCHEMA__.valueadditionallevelinfo TO wdb_clean;


--
-- WCI Tables
--
CREATE TABLE __WDB_SCHEMA__.defaultnamespace (
	rolname 				NAME NOT NULL PRIMARY KEY,
	dataprovidernamespaceid integer NOT NULL REFERENCES __WDB_SCHEMA__.namespace (namespaceid),
	placenamespaceid		integer NOT NULL REFERENCES __WDB_SCHEMA__.namespace (namespaceid),
	parameternamespaceid	integer NOT NULL REFERENCES __WDB_SCHEMA__.namespace (namespaceid)
);

REVOKE ALL ON __WDB_SCHEMA__.defaultnamespace FROM public;
GRANT ALL ON __WDB_SCHEMA__.defaultnamespace TO wdb_admin;
