/* 
 * File:   emitter.cpp
 * Author: Kuba
 * 
 * Created on 14 stycznia 2015, 10:15
 */

#include "emitter.h"


emitter::emitter(symbolTable& table):table(table){
}



emitter::~emitter() {
}

 void emitter::putProgram(string programName ){
     output<<";Program: "<<programName<<endl;
     output<<"start:"<<endl;
 }
 
 void emitter::putEnd(){
     output<<"\t exit"<<endl;
 }
  
 void emitter::putAssign(int left,int right){
     cout<<"Print Assign"<<endl;
     symbol l = table.getSymbol(left);
     symbol r = table.getSymbol(right);
     
     if (l.type == ST_VAR_INT){
         output<<"\t mov.i ";
     }
     else if (l.type == ST_VAR_REAL){
         output<<"\t mov.r ";
     }
     
    
     
     if (r.type == ST_NUM_INT || r.type == ST_NUM_REAL ){
         output<<"#"<<r.lexem<<","<<l.adress;
     }
     else if (r.type == ST_VAR_INT || r.type == ST_VAR_REAL ){
         output<<r.adress<<","<<l.adress;
     }
      output<<"\t\t; mov "<<r.lexem<<" "<<l.lexem<<endl;
 
 }

void emitter::putWrite(int index) {
    cout << "Print write" << endl;

    symbol s = table.getSymbol(index);
    if (s.type == ST_NUM_INT) {
        output << "\t write.i #" << s.lexem << endl;
    }
    if (s.type == ST_VAR_INT) {
        output << "\t write.i " << s.adress << "\t\t; write " << s.lexem << endl;
    }
    if (s.type == ST_NUM_REAL) {
        output << "\t write.r #" << s.lexem << endl;
    }
    if (s.type == ST_VAR_REAL) {
        output << "\t write.r " << s.adress << "\t\t; write " << s.lexem << endl;
    }

}
 
 void emitter::flush(const char* fileName) {
     cout<<"Printing to file"<<endl;
    ofstream outputStream;
    outputStream.open(fileName, fstream::out);
    outputStream << this->output.str();
}
