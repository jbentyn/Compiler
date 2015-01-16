/* 
 * File:   emitter.cpp
 * Author: Kuba
 * 
 * Created on 14 stycznia 2015, 10:15
 */

#include "emitter.h"

emitter::emitter() {
}

emitter::emitter(const emitter& orig) {
}

emitter::~emitter() {
}

 void emitter::putProgram(string programName ){
     this->output<<";Program: "<<programName<<endl;
 }
 
 void emitter::flush(const char* fileName) {
    ofstream outputStream;
    outputStream.open(fileName, fstream::out);
    outputStream << this->output.str();
}
