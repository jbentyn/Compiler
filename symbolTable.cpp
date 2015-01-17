/* 
 * File:   symbolTable.cpp
 * Author: Kuba
 * 
 * Created on 16 stycznia 2015, 14:20
 */

#include "symbolTable.h"
#include "symbol.h"

symbolTable::symbolTable() {
    this->nextFreeAdress = 0;
}

int symbolTable::putIdentifier(string name) {
    //if identifier has been declared
    for (int i = 0; i < table.size(); i++){
        if (name.compare(table[i].lexem) == 0){
            return i;
        }
    }
    symbol s;
    s.lexem = name;
    table.push_back(s);
    return table.size() - 1;
}

void symbolTable::assignVar(int index, SymbolType type) {
    table[index].type=type;
    int assignedSize;
    cout<<"Assigned type "<<SymbolTypeStrings[type]<<endl;
    if (table[index].type == ST_VAR_INT) {
        assignedSize=INT_SIZE;
    }
    else if (table[index].type == ST_VAR_REAL) {
        assignedSize=REAL_SIZE;
    }
    cout<<"Assigned size "<<assignedSize<<endl;
    table[index].adress=this->nextFreeAdress;
    this->nextFreeAdress += assignedSize;
}

symbol& symbolTable::getSymbol(int index) {
    return table[index];
}

void symbolTable::setSymbolType(int index, SymbolType type) {
    table[index].type = type;
}

void symbolTable::printAll() {
    for (int i = 0; i < table.size(); i++) {
        cout << "index " << setw(3) << left << i;
        cout << "lexem " << setw(7) << left << table[i].lexem;
        cout << "adress " << setw(7) << left << table[i].adress;
        cout << "type " << setw(7) << left << SymbolTypeStrings[table[i].type];
        cout << endl;
    }
}

symbolTable::symbolTable(const symbolTable& orig) {
}

symbolTable::~symbolTable() {
}

