/* 
 * File:   symbolTable.h
 * Author: Kuba
 *
 * Created on 16 stycznia 2015, 14:20
 */

#ifndef SYMBOLTABLE_H
#define	SYMBOLTABLE_H

#include <vector>
#include <iomanip>
#include <iostream>

#include "enums.h"
#include "symbol.h"



using namespace std;

class symbolTable {
public:
    symbolTable();
    symbolTable(SymbolType type);
    symbolTable(const symbolTable& orig);
    virtual ~symbolTable();


    int putIdentifier(string name);
    void assignVar(int index, SymbolType type);
    int putNumber(string lexem,SymbolType type); 
    
    
    
    symbol& getSymbol(int index);
    void setSymbolType(int index, SymbolType type);
   
    void printAll();
private:

    vector<symbol> table;
    int nextFreeAdress;
};

#endif	/* SYMBOLTABLE_H */

