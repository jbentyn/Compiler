/* 
 * File:   emitter.cpp
 * Author: Kuba
 * 
 * Created on 14 stycznia 2015, 10:15
 */

#include "emitter.h"

emitter::emitter(symbolTable& table) : table(table) {
}

emitter::~emitter() {
}

void emitter::putProgram(string programName) {
    output << ";Program: " << programName << endl;
    output << "start:" << endl;
}

void emitter::putEnd() {
    output << "\t exit" << endl;
}

void emitter::putAssign(int left, int right) {
    cout << "Print Assign" << endl;
    symbol l = table.getSymbol(left);
    symbol r = table.getSymbol(right);

    if (l.type == ST_VAR_INT) {
        output << "\t mov.i ";
    } else if (l.type == ST_VAR_REAL) {
        output << "\t mov.r ";
    }

    writeNumOrVar(right);
    output<<",";
    writeNumOrVar(left);
    output << "\t\t; mov " << r.lexem << " " << l.lexem << endl;

}

void emitter::putWrite(int index) {
    cout << "Print write" << endl;

    symbol s = table.getSymbol(index);
    if (s.type == ST_NUM_INT || s.type == ST_VAR_INT) {
        output << "\t write.i ";
    }
 
    if (s.type == ST_NUM_REAL || s.type == ST_VAR_REAL) {
        output << "\t write.r ";
    }
    writeNumOrVar(index);
    output <<"\t\t; write "<<s.lexem<<endl;

}

int emitter::convertToRealVar(int symbolIndex) {
    symbol s = table.getSymbol(symbolIndex);
    if (s.type == ST_VAR_INT || s.type == ST_NUM_INT) {
        int temp = table.putTemp(ST_VAR_REAL);
        output << "\t inttoreal.r ";
        writeNumOrVar(symbolIndex);
        output << ",";
        writeNumOrVar(temp);
        output << "\t\t; inttoreal " << s.lexem << "," << table.getSymbol(temp).lexem << endl;
        return temp;
    }
    if ( s.type == ST_NUM_REAL){
         int temp = table.putTemp(ST_VAR_REAL);
         putAssign(temp,symbolIndex);
         return temp;
    }
     if (s.type == ST_VAR_REAL){
        return symbolIndex;
    }
}

void emitter::writeNumOrVar(int  symbolIndex){
    symbol s = table.getSymbol(symbolIndex);
    if (s.type == ST_VAR_INT || s.type == ST_VAR_REAL){
        output<<" "<<s.adress<<" ";
    }
    if (s.type == ST_NUM_INT || s.type == ST_NUM_REAL){
        output<<" #"<<s.lexem<<" ";
    }
}
void emitter::writeBinaryOperator(int left, int right, int dest,OpertatorType type){
    symbol l= table.getSymbol(left);
    symbol r=table.getSymbol(right);
    symbol destination= table.getSymbol(dest);
    
    
    
    if (type == OP_ADD){
        output<<"\t\t add";
    }
    if (type == OP_SUB){
        output<<"\t\t sub";
    }
    if (type == OP_MUL){
        output<<"\t\t mul";
    }
    if (type == OP_DIV){
        output<<"\t\t div";
    }
    if (destination.type == ST_VAR_INT){
        output<<".i ";
    }
    if (destination.type == ST_VAR_REAL){
         output<<".r ";
    }
    
    writeNumOrVar(left);
    output<<",";
    writeNumOrVar(right);
    output<<",";
    writeNumOrVar(dest);
    output<<"\t\t; binary operator "<<l.lexem<<", "<<r.lexem<<","<<destination.lexem<<endl;
}


int emitter::putBinaryOperator(int left, int right, OpertatorType type) {
    symbol l = table.getSymbol(left);
    symbol r = table.getSymbol(right);
    cout <<"left:"; l.print();
    cout <<"right:"; r.print();
    
    if ((l.type == ST_VAR_INT && r.type == ST_VAR_INT)
        || (l.type == ST_VAR_INT && r.type == ST_NUM_INT)
        || (l.type == ST_NUM_INT && r.type == ST_VAR_INT)
        || (l.type == ST_NUM_INT && r.type == ST_NUM_INT)) {
       
        int temp = table.putTemp(ST_VAR_INT);
        writeBinaryOperator(left, right, temp,type);
        return temp;
    }
    if ( (l.type == ST_VAR_INT && r.type == ST_VAR_REAL)
        || (l.type == ST_VAR_INT && r.type == ST_NUM_REAL)
        || (l.type == ST_VAR_REAL && r.type == ST_VAR_INT)
        || (l.type == ST_VAR_REAL && r.type == ST_NUM_INT)
        || (l.type == ST_NUM_INT && r.type == ST_VAR_REAL)
        || (l.type == ST_NUM_INT && r.type == ST_NUM_REAL)
        || (l.type == ST_NUM_REAL && r.type == ST_VAR_INT)
        || (l.type == ST_NUM_REAL && r.type == ST_NUM_INT)    ) {

        int temp = table.putTemp(ST_VAR_REAL);
        writeBinaryOperator(convertToRealVar(left), convertToRealVar(right), temp,type);
        return temp;
    }

    if ((l.type == ST_VAR_REAL && r.type == ST_VAR_REAL)
         || (l.type == ST_VAR_REAL && r.type == ST_NUM_REAL)
         || (l.type == ST_NUM_REAL && r.type == ST_VAR_REAL)
         || (l.type == ST_NUM_REAL && r.type == ST_NUM_REAL) ) {
        
        int temp = table.putTemp(ST_VAR_REAL);
        writeBinaryOperator(left, right, temp,type);
        return temp;
    }

}

//void emitter::writeAdd(int left, int right,int dest){
//    symbol l= table.getSymbol(left);
//    symbol r=table.getSymbol(right);
//    symbol destination= table.getSymbol(dest);
//    
//    if (destination.type == ST_VAR_INT){
//        output<<"\t add.i ";
//    }
//    if (destination.type == ST_VAR_REAL){
//         output<<"\t add.r ";
//    }
//    writeNumOrVar(left);
//    output<<",";
//    writeNumOrVar(right);
//    output<<",";
//    writeNumOrVar(dest);
//    output<<"\t\t; add "<<l.lexem<<", "<<r.lexem<<","<<destination.lexem<<endl;
//}


void emitter::flush(const char* fileName) {
    cout << "Printing to file" << endl;
    ofstream outputStream;
    outputStream.open(fileName, fstream::out);
    outputStream << this->output.str();
}
