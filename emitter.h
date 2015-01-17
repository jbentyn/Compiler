/* 
 * File:   emitter.h
 * Author: Kuba
 *
 * Created on 14 stycznia 2015, 10:15
 */

#ifndef EMITTER_H
#define	EMITTER_H


#include <sstream>
#include <fstream>
#include <vector>

#include "symbolTable.h"
#include "symbol.h"

using namespace std;

 

class emitter {
public:
    symbolTable& table;
    
    emitter(symbolTable& table);

    
    void putProgram(string programName);
    void putEnd();
    void putAssign(int left,int right);
    
    void putWrite(int index);
    
    void flush(const char* fileName) ;
    virtual ~emitter();
private:
    stringstream output;
};

#endif	/* EMITTER_H */

