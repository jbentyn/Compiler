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
    this->nextTempNumber = 0;
}

int symbolTable::putIdentifier(string name) {
    //if identifier has been declared
    for (int i = 0; i < table.size(); i++){
        if (name.compare(table[i].lexem) == 0){
            cout<<"identifier already stored"<<endl;
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

int symbolTable::putNumber(string lexem,SymbolType type){
    symbol s;
    s.lexem=lexem;
    s.type=type;
    table.push_back(s);
    return table.size()-1;
}

int symbolTable::putTemp(SymbolType type){
    symbol s;
    stringstream ss;
    ss << nextTempNumber++;
    s.lexem="$t"+ss.str();
    s.type=type;
    table.push_back(s);
    assignVar(table.size()-1,type);
    return table.size()-1;
}

symbol& symbolTable::getSymbol(int index) {
    return table[index];
}

void symbolTable::setSymbolType(int index, SymbolType type) {
    table[index].type = type;
}

void symbolTable::printAll() {
    cout<<"table size "<<table.size()<<endl;
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

