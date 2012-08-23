-- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
-- 
-- wdb - weather and water data storage
--
-- Copyright (C) 2007 - 2012 met.no
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


-- Place Indeterminate Code is used to specify various forms of indeterminate
-- locations.
CREATE TABLE __WDB_SCHEMA__.placeindeterminatetype (
    placeindeterminatecode		integer NOT NULL,
    placeindeterminatetype		character varying(80) NOT NULL,
    placeindeterminatedescription	character varying(255) NOT NULL
);

ALTER TABLE ONLY __WDB_SCHEMA__.placeindeterminatetype
    ADD CONSTRAINT placeindeterminatetype_pkey PRIMARY KEY (placeindeterminatecode);

CREATE UNIQUE INDEX XAK1Wdb_PlaceIndeterminateType ON __WDB_SCHEMA__.PlaceIndeterminateType
(
       PlaceIndeterminateType
);

REVOKE ALL ON __WDB_SCHEMA__.placeindeterminatetype FROM public;
GRANT ALL ON __WDB_SCHEMA__.placeindeterminatetype TO wdb_admin;

INSERT INTO __WDB_SCHEMA__.placeindeterminatetype VALUES ( 0, 'any', 'Values are valid for any location');
INSERT INTO __WDB_SCHEMA__.placeindeterminatetype VALUES ( 1, 'exact', 'Values are valid for the given place definition');
INSERT INTO __WDB_SCHEMA__.placeindeterminatetype VALUES ( 2, 'inside', 'Values are valid for positions inside the place definition given');
INSERT INTO __WDB_SCHEMA__.placeindeterminatetype VALUES ( 3, 'outside', 'Values are valid for positions outside the place definition given');
INSERT INTO __WDB_SCHEMA__.placeindeterminatetype VALUES ( 6, 'withheld', 'Place definition is known but withheld');
INSERT INTO __WDB_SCHEMA__.placeindeterminatetype VALUES ( 7, 'withdrawn', 'Place definition was given but has been retracted');
INSERT INTO __WDB_SCHEMA__.placeindeterminatetype VALUES ( 8, 'unknown', 'Place definition is unknown');
INSERT INTO __WDB_SCHEMA__.placeindeterminatetype VALUES ( 9, 'delayed', 'Place definition will be set later');



-- Place definition encodes a location on the earth
CREATE TABLE __WDB_SCHEMA__.placedefinition (
    placeid						bigserial NOT NULL,
    placeindeterminatecode 		integer NOT NULL,
    placegeometrytype 			character varying(80) NOT NULL,
    placestoretime				timestamp with time zone NOT NULL,
    CONSTRAINT placedefinition_placegeometrytype_check 
	CHECK (	((placegeometrytype)::text = 'grid'::text) OR
			((placegeometrytype)::text = 'line'::text) OR
			((placegeometrytype)::text = 'point'::text) OR
			((placegeometrytype)::text = 'polygon'::text) )
);
SELECT AddGeometryColumn('__WDB_SCHEMA__', 'placedefinition', 'placegeometry', 4030, 'GEOMETRY', 2);

ALTER TABLE ONLY __WDB_SCHEMA__.placedefinition
    ADD CONSTRAINT placedefiniton_pkey PRIMARY KEY (placeid);

ALTER TABLE __WDB_SCHEMA__.placedefinition
	ADD FOREIGN KEY (placeindeterminatecode)
					REFERENCES __WDB_SCHEMA__.placeindeterminatetype
					ON DELETE RESTRICT
					ON UPDATE RESTRICT;

REVOKE ALL ON __WDB_SCHEMA__.placedefinition FROM public;
GRANT ALL ON __WDB_SCHEMA__.placedefinition TO wdb_admin;
GRANT INSERT ON __WDB_SCHEMA__.placedefinition TO wdb_write;
GRANT SELECT, DELETE ON __WDB_SCHEMA__.placedefinition TO wdb_clean;
REVOKE ALL ON __WDB_SCHEMA__.placedefinition_placeid_seq FROM public;
GRANT ALL ON __WDB_SCHEMA__.placedefinition_placeid_seq TO wdb_admin;
GRANT SELECT,UPDATE ON __WDB_SCHEMA__.placedefinition_placeid_seq TO wdb_write;



-- Regular Grid
CREATE TABLE __WDB_SCHEMA__.placeregulargrid (
    placeid						bigint NOT NULL,
    numberx						integer NOT NULL,
    numbery						integer NOT NULL,
    incrementx					real NOT NULL,
    incrementy					real NOT NULL,
    startx						real NOT NULL,
    starty						real NOT NULL,
    originalsrid				integer NOT NULL
);

ALTER TABLE ONLY __WDB_SCHEMA__.placeregulargrid
    ADD CONSTRAINT placeregulargrid_pkey PRIMARY KEY (placeid);

ALTER TABLE ONLY __WDB_SCHEMA__.placeregulargrid
    ADD CONSTRAINT placeregulargrid_skey UNIQUE ( numberx,
    											  numbery,
    											  incrementx,
    											  incrementy,
    											  startx,
    											  starty,
    											  originalsrid );
    
ALTER TABLE __WDB_SCHEMA__.placeregulargrid
	ADD FOREIGN KEY (placeid)
					REFERENCES __WDB_SCHEMA__.placedefinition
					ON DELETE CASCADE
					ON UPDATE CASCADE;
					
REVOKE ALL ON __WDB_SCHEMA__.placeregulargrid FROM public;
GRANT ALL ON __WDB_SCHEMA__.placeregulargrid TO wdb_admin;
GRANT SELECT, DELETE ON __WDB_SCHEMA__.placeregulargrid TO wdb_clean;



-- Place Names
CREATE TABLE __WDB_SCHEMA__.placename (
    placeid 					bigint NOT NULL,
    placenamespaceid 			integer NOT NULL,
    placename 					character varying(255) NOT NULL,
    placenamevalidfrom 			timestamp with time zone NOT NULL,
    placenamevalidto 			timestamp with time zone NOT NULL,
    placenameupdatetime			timestamp with time zone NOT NULL default 'now',
    CHECK ( placenamevalidfrom <= placenamevalidto )
);

REVOKE ALL ON __WDB_SCHEMA__.placename FROM public;
GRANT ALL ON __WDB_SCHEMA__.placename TO wdb_admin;

ALTER TABLE ONLY __WDB_SCHEMA__.placename
    ADD CONSTRAINT placename_pkey PRIMARY KEY (placeid, placenamespaceid, placename, placenamevalidfrom);

ALTER TABLE ONLY __WDB_SCHEMA__.placename
	ADD CONSTRAINT placename_unique UNIQUE (placenamespaceid, placename, placenamevalidfrom);

ALTER TABLE __WDB_SCHEMA__.placename
	ADD FOREIGN KEY (placeid)
					REFERENCES __WDB_SCHEMA__.placedefinition
					ON DELETE CASCADE
					ON UPDATE CASCADE;

ALTER TABLE __WDB_SCHEMA__.placename
	ADD FOREIGN KEY (placenamespaceid)
					REFERENCES __WDB_SCHEMA__.namespace
					ON DELETE RESTRICT
					ON UPDATE CASCADE;

REVOKE ALL ON __WDB_SCHEMA__.placename FROM public;
GRANT ALL ON __WDB_SCHEMA__.placename TO wdb_admin;
