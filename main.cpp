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
emitter emit(table);

int main(int argc, char** argv) {

    yyparse();
    cout << endl << endl;
    table.printAll();

    emit.flush("out.asm");
    return 0;
}

