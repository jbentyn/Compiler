/* 
 * File:   enums.h
 * Author: Kuba
 *
 * Created on 16 stycznia 2015, 14:14
 */

#ifndef ENUMS_H
#define	ENUMS_H




static int INT_SIZE=4;
static int REAL_SIZE=8;

static const char * SymbolTypeStrings[] = { "NONE", "PROGRAM_ID","INT","REAL","NUM_INT","NUM_REAL" };
enum SymbolType{
    ST_NONE,
    ST_PROGAM_IDENTIFIER,
    ST_VAR_INT,
    ST_VAR_REAL,
    ST_NUM_INT,
    ST_NUM_REAL
};

static const char * OperatorTypeStrings[] = { "ADD", "SUB","MUL","DIV" };
enum OpertatorType{
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
};



#endif	/* ENUMS_H */

