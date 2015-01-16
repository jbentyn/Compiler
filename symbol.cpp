/* 
 * File:   symbol.cpp
 * Author: Kuba
 * 
 * Created on 12 stycznia 2015, 09:12
 */

#include "symbol.h"


symbol::symbol() {
    this->lexem="";
    this->adress=-1;
    this->type = NONE;
}

symbol::symbol(const symbol& orig) {
}

symbol::~symbol() {
}

