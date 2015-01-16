%{
    #include <cstdio>
    #include <iostream>
#include "symbolTable.h"
#include "emitter.h"
    using namespace std;

	extern symbolTable table;
	extern emitter emit;
	
    extern int yylex();
    void yyerror(const char *s);

    //---------------------------------------------------------------------
    //----------------- methods used during parse process -----------------
    //---------------------------------------------------------------------
    /**
     * Called when the program identifier is found.
     * Generates the startup jump
     */
    void onProgramIdentifier(int programIndex);

    /**
     * Called when the main begin statement is found.
     * Generates the startup label.
     */
    void onProgramBegin();
	
    /**
     * Called when the main end statement is found.
     * Generates the exit function.
     */
    void onProgramEnd();
    
  
%}
// -------------------------------------------
// ------------ TOKENS DEFINITION ------------
// -------------------------------------------
// BISON CONF
%define parse.error verbose

// RESERVED WORDS
%token TOKEN_PROGRAM
%token TOKEN_BEGIN
%token TOKEN_END



%token TOKEN_ID


%%
//------------------------------------------- 
//----------- GRAMMAR DEFINITION ------------ 
//------------------------------------------- 
program: 
	TOKEN_PROGRAM program_identifier ';' main_instruction_block{
		cout << "BISON FOUND PROGRAM: " << $$ << endl; 
	}										
;

program_identifier: 
	TOKEN_ID {
		onProgramIdentifier($1);
		
	}
;

main_instruction_block:
	main_begin  main_end '.' {
		cout << "BISON FOUND MAIN INSTRUCTION BLOCK" << endl; 
	}
;

main_begin: 
	TOKEN_BEGIN {
		onProgramBegin();
	}
;

main_end: 
	TOKEN_END {
		onProgramEnd();
	}
;


%%
//------------------------------------------- 
//-------- FINAL METHOD DECLARATIONS -------- 
//------------------------------------------- 
void yyerror(const char *error) {
    cout << "PARSING ERROR OCCURED: " << error << endl;
    exit(-1);
}

void onProgramIdentifier(int programIndex) {
    cout<<"BISON PROGRAM IDENTIFIER"<<programIndex<<endl;
	symbol& s = table.getSymbol(programIndex);
	emit.putProgram(s.lexem);
	
}

void onProgramBegin() {
    cout<<"BISON PROGRAM BRGIN"<<endl;
}

void onProgramEnd() {
      cout<<"BISON PROGRAM END"<<endl;
}

