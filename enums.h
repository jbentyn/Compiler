/* 
 * File:   enums.h
 * Author: Kuba
 *
 * Created on 16 stycznia 2015, 14:14
 */

#ifndef ENUMS_H
#define	ENUMS_H



enum SymbolType{
    ST_NONE,
    ST_PROGAM_IDENTIFIER,
    ST_VAR_INT,
    ST_VAR_REAL
};
static const char * SymbolTypeStrings[] = { "NONE", "PROGRAM_ID","INT","REAL" };

static int INT_SIZE=4;
static int REAL_SIZE=8;

#endif	/* ENUMS_H */

