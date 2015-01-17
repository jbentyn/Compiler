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
	vector<int> argumentIndexesToAssign;
	
//------methods
  
    void onProgramIdentifier(int programIndex);

    void onProgramBegin();
	
    void onProgramEnd();
    
	void onVarDeclaration(int type);
	
	void onAssign(int left,int right);
	
	void onWrite();
	
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
%token TOKEN_WRITE

// NUMBERS
%token TOKEN_NUM_INT
%token TOKEN_NUM_REAL 

//OPERATORS
%token TOKEN_OP_ASSIGN

%token TOKEN_ID


%%
//------------------------------------------- 
//----------- GRAMMAR DEFINITION ------------ 
//------------------------------------------- 
program: 
	TOKEN_PROGRAM program_identifier '(' TOKEN_ID ',' TOKEN_ID ')' ';' var_declarations main_instruction_block{
		cout << "BISON FOUND PROGRAM: " << $$ << endl; 
	}										
;

program_identifier: 
	TOKEN_ID {
		onProgramIdentifier($1);
		
	}
;

main_instruction_block:
	main_begin instructions main_end '.' {
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
		 onVarDeclaration($5);
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

//---------- Instructions ----------------
expr :
	TOKEN_ID|
	TOKEN_NUM_INT|
	TOKEN_NUM_REAL{
		cout << "BISON FOUND EXPRESSION" << endl;
		$$=$1;
	}	
;

instructions:
	instructions TOKEN_ID TOKEN_OP_ASSIGN expr ';'{
		cout << "BISON FOUND ASSIGN" << endl;
		onAssign($2,$4);
	}
	| instructions procedure ';' {
	}
	|{}
;

// -------- Procedures
procedure: 
	TOKEN_WRITE '(' arguments ')' {
	cout << "BISON FOUND WRITE" << endl;
		onWrite();
	}
;

arguments:
	arguments ',' expr {
		cout << "BISON FOUND ARGUMENTS" << endl;
		argumentIndexesToAssign.push_back($3);
	}
	| expr {
		cout << "BISON FOUND ARGUMENTS" << endl;
		argumentIndexesToAssign.push_back($1);
	}
	|{}
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

void onVarDeclaration(int type){
	 cout<<"BISON VAR DECLARATION"<<endl;
	 for (int i = 0; i < varsIndexesToAssign.size(); i++){
			table.assignVar(varsIndexesToAssign[i],static_cast<SymbolType>(type));
		}
		varsIndexesToAssign.clear();
}

void onAssign(int left,int right){
	emit.putAssign(left,right);
}

void onWrite(){
	for (int i=0;i<argumentIndexesToAssign.size() ;i++){
		emit.putWrite(argumentIndexesToAssign[i]);
	}
	argumentIndexesToAssign.clear();
}
