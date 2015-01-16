/* 
 * File:   symbol.h
 * Author: Kuba
 *
 * Created on 12 stycznia 2015, 09:12
 */

#ifndef SYMBOL_H
#define	SYMBOL_H
#include <string>
#include "enums.h"
using namespace std;
class symbol {
public:
    symbol();
    symbol(const symbol& orig);
    virtual ~symbol();
    
    //fields
    int adress;
    string lexem;
    SymbolType type;
private:
   
};

#endif	/* SYMBOL_H */

