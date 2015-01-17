/* 
 * File:   symbol.cpp
 * Author: Kuba
 * 
 * Created on 12 stycznia 2015, 09:12
 */

#include <sstream>

#include "symbol.h"


symbol::symbol() {
    this->adress=-1;
    this->type = ST_NONE;
}

void symbol::print(){
    cout<<"lexem "<<lexem<<" adress "<<adress<<" type "<< SymbolTypeStrings[type]<<endl;
}

symbol::~symbol() {
}

