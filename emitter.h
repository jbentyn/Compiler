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

using namespace std;

class emitter {
public:
    emitter();
    emitter(const emitter& orig);
    
    void putProgram(string programName);
    void putEnd();
    void flush(const char* fileName) ;
    virtual ~emitter();
private:
    stringstream output;
};

#endif	/* EMITTER_H */

