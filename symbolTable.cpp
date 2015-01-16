/* 
 * File:   symbolTable.cpp
 * Author: Kuba
 * 
 * Created on 16 stycznia 2015, 14:20
 */

#include "symbolTable.h"
#include "symbol.h"

symbolTable::symbolTable() {
    this->nextFreeAdress=0;
}
    
int symbolTable::putProgramSymbol(string programName){
    symbol s;
    s.type=PROGAM_IDENTIFIER;
    s.lexem=programName;
    table.push_back(s);
    return table.size()-1;
}

 int symbolTable::putIdentifier(string name){
     symbol s;
     s.lexem=name;
     table.push_back(s);
     return table.size()-1;
 }


symbol& symbolTable::getSymbol(int index) {
    return table[index];
}




symbolTable::symbolTable(const symbolTable& orig) {
}

symbolTable::~symbolTable() {
}

