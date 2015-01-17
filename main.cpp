/* 
 * File:   main.cpp
 * Author: Kuba
 *
 * Created on 8 stycznia 2015, 09:19
 */

#include <cstdlib>
#include <iostream>

#include "lexer.h"
#include "parser.h"
#include "symbolTable.h"
#include "emitter.h"
using namespace std;

  symbolTable table;
  emitter emit;
    
int main(int argc, char** argv) {
    
  
    
    cout<<"Hello"<<endl;
    yyparse();
    
    table.printAll();
    emit.flush("out.asm");
    return 0;
}

