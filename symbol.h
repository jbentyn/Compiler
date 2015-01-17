/* 
 * File:   symbol.h
 * Author: Kuba
 *
 * Created on 12 stycznia 2015, 09:12
 */

#ifndef SYMBOL_H
#define	SYMBOL_H

#include <string>
#include <iomanip>
#include <iostream>

#include "enums.h"

using namespace std;

class symbol {
public:
    symbol();

    virtual ~symbol();
    
    //fields
    int adress;
    string lexem;
    SymbolType type;

    void print();
private:
   
};

#endif	/* SYMBOL_H */

