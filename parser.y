%{
    #include <cstdio>
    #include <iostream>
	#include <vector>
	
	#include "symbolTable.h"
	#include "emitter.h"

    using namespace std;

	extern symbolTable table;
	extern emitter emit;
	
    extern int yylex();
    void yyerror(const char *s);

//------variables	
	vector<int> varsIndexesToAssign;
	
	
//------methods
  
    void onProgramIdentifier(int programIndex);

   
    void onProgramBegin();
	
 
    void onProgramEnd();
    
	void onVarDeclaration();
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
%token TOKEN_VAR
%token TOKEN_INT
%token TOKEN_REAL

%token TOKEN_ID


%%
//------------------------------------------- 
//----------- GRAMMAR DEFINITION ------------ 
//------------------------------------------- 
program: 
	TOKEN_PROGRAM program_identifier ';' var_declarations main_instruction_block{
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
//---------- Variables declarations-------
var_declarations:
	var_declarations TOKEN_VAR var_list ':' var_type ';'{
		cout << "BISON FOUND var declarations" << endl;
		for (int i = 0; i < varsIndexesToAssign.size(); i++){
			table.assignVar(varsIndexesToAssign[i],static_cast<SymbolType>($5));
		}
		varsIndexesToAssign.clear();
	}
	|
	{}
	
;

var_list:
	TOKEN_ID{
	cout << "BISON FOUND var list" << endl; 
		varsIndexesToAssign.push_back($1);
	}
	|
	var_list ',' TOKEN_ID{
	cout << "BISON FOUND var list" << endl;
		varsIndexesToAssign.push_back($3);
	}
;	
var_type :
	TOKEN_INT{
		cout << "BISON FOUND INTEGER_TYPE" << endl; 
		$$=ST_VAR_INT;
	}
	| 
	TOKEN_REAL{
		cout << "BISON FOUND REAL_TYPE" << endl;
		$$=ST_VAR_REAL;
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
	table.setSymbolType(programIndex,ST_PROGAM_IDENTIFIER);
	emit.putProgram(s.lexem);
	
}

void onProgramBegin() {
    cout<<"BISON PROGRAM BEGIN"<<endl;
}

void onProgramEnd() {
      cout<<"BISON PROGRAM END"<<endl;
	  emit.putEnd();
}

void onVarDeclaration(){
	 cout<<"BISON VAR DECLARATION"<<endl;
}


