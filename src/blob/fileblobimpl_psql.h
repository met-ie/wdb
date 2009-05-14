/*
 wdb

 Copyright (C) 2009 met.no

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


#ifndef FILEBLOBIMPL_C_H_
#define FILEBLOBIMPL_C_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef long long FileId;


/**
 * Nothrow variation of file with same name. ereports postgresql error instead
 */
void writeFile_(FileId id, const char * data, int dataSize);

/**
 * Nothrow variation of file with same name. ereports postgresql error instead
 */
void dropFile_(FileId id);

/**
 * Nothrow variation of file with same name. ereports postgresql error instead
 */
void readFile_(FileId id, char * out, int readSize);

/**
 * Nothrow variation of file with same name. ereports postgresql error instead
 */
float readFloatFromFile_(FileId id, int position);

/**
 * Must have been called once before using file system functions
 */
bool doInitializeFileStorage();

#ifdef __cplusplus
}
#endif


#endif /* FILEBLOBIMPL_C_H_ */