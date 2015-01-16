/* 
 * File:   symbolTable.h
 * Author: Kuba
 *
 * Created on 16 stycznia 2015, 14:20
 */

#ifndef SYMBOLTABLE_H
#define	SYMBOLTABLE_H

#include <vector>

#include "enums.h"
#include "symbol.h"
using namespace std;

class symbolTable {
public:
    symbolTable();
    symbolTable(SymbolType type);
    symbolTable(const symbolTable& orig);
    virtual ~symbolTable();
    int putProgramSymbol(string programName);
    int putIdentifier(string name);
    symbol& getSymbol(int index);
 
private:

    vector<symbol> table;
    int nextFreeAdress;
};

#endif	/* SYMBOLTABLE_H */

