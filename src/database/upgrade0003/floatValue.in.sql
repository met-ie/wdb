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
SET SESSION client_min_messages TO 'warning';

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
-- Constraints
--
ALTER TABLE ONLY __WDB_SCHEMA__.floatvaluegroup
    ADD CONSTRAINT floatvalue_pkey PRIMARY KEY (valuegroupid);

ALTER TABLE ONLY __WDB_SCHEMA__.floatvalueitem
    ADD CONSTRAINT floatvalue_pkey PRIMARY KEY (valuegroupid, referencetime, dataversion);
    
--
-- Foreign Key Constraints
--				
ALTER TABLE __WDB_SCHEMA__.floatvaluegroup
	ADD FOREIGN KEY (dataproviderid)
					REFERENCES __WDB_SCHEMA__.dataprovider
					ON DELETE RESTRICT
					ON UPDATE CASCADE;


ALTER TABLE __WDB_SCHEMA__.floatvaluegroup
	ADD FOREIGN KEY (placeid)
					REFERENCES __WDB_SCHEMA__.placedefinition
					ON DELETE RESTRICT
					ON UPDATE CASCADE;


ALTER TABLE __WDB_SCHEMA__.floatvaluegroup
	ADD FOREIGN KEY (validtimeindeterminatecode)
					REFERENCES __WDB_SCHEMA__.timeindeterminatetype
					ON DELETE RESTRICT
					ON UPDATE CASCADE;


ALTER TABLE __WDB_SCHEMA__.floatvaluegroup
	ADD FOREIGN KEY (valueparameterid)
					REFERENCES __WDB_SCHEMA__.parameter
					ON DELETE RESTRICT
					ON UPDATE CASCADE;


ALTER TABLE __WDB_SCHEMA__.floatvaluegroup
	ADD FOREIGN KEY (levelparameterid)
					REFERENCES __WDB_SCHEMA__.parameter
					ON DELETE RESTRICT
					ON UPDATE CASCADE;


ALTER TABLE __WDB_SCHEMA__.floatvaluegroup
	ADD FOREIGN KEY (levelindeterminatecode)
					REFERENCES __WDB_SCHEMA__.levelindeterminatetype
					ON DELETE RESTRICT
					ON UPDATE CASCADE;


ALTER TABLE __WDB_SCHEMA__.floatvalueitem
	ADD FOREIGN KEY (confidencecode)
					REFERENCES __WDB_SCHEMA__.qualityconfidencecode
					ON DELETE RESTRICT
					ON UPDATE CASCADE;


CREATE UNIQUE INDEX XAK1Wdb_FloatValue_TABLE_EXTENSION ON wdb_partition.FloatValue_TABLE_EXTENSION
(
       DataProviderId,
       ReferenceTime,
       DataVersion,
       PlaceId,
       ValueParameterId,
       LevelParameterId,
       LevelFrom,
       LevelTo,
       LevelIndeterminateCode,
       ValidTimeFrom,
       ValidTimeTo,
       ValidTimeIndeterminateCode
);

CREATE INDEX i_FloatValue_TABLE_EXTENSION ON wdb_partition.FloatValue_TABLE_EXTENSION
(
        dataproviderid,
        referencetime,
        placeid,
        valueparameterid
);

					