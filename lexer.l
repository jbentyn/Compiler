%{
    #include <iostream>
    
    #include "parser.h"
	#include "symbolTable.h"
	#include "enums.h"
	#include "emitter.h"
	
    using namespace std;
	extern symbolTable table;
%}



identifier			[a-zA-Z]([[:alnum:]])*
real_number			{int_number}\.[0-9]+
int_number			-?[0-9]+


op_assign			":="

%%
[[:blank:]\r] {/* SKIP */}

[\n] {
	cout << "FLEX new line" << endl;
}

"program" {
	cout << "FLEX program" << endl;
	return TOKEN_PROGRAM;
}


"begin"	{
	cout << "FLEX begin" << endl;
	return TOKEN_BEGIN;
}

"var" {
	cout << "FLEX var" << endl;
	return TOKEN_VAR;
}

"integer" {
	cout << "FLEX integer" << endl;
	return TOKEN_INT;
}

"real" {
	cout << "FLEX real" << endl;
	return TOKEN_REAL;
}

"end" {
	cout << "FLEX end" << endl;
	return TOKEN_END;	
}

"write" {
	cout << "FLEX write" << endl;
	return TOKEN_WRITE;	
}

{op_assign} {
	cout << "FLEX operator assign" << endl;
	return TOKEN_OP_ASSIGN;	
}

{identifier} {
	cout<<"FLEX identifier "<<yytext<<endl;
	yylval=table.putIdentifier(yytext);
	cout<<"YYVAL identifier "<<yylval<<endl;
	return TOKEN_ID;
}

{int_number} {
	cout<<"FLEX int_number "<<yytext<<endl;
	yylval=table.putNumber(yytext,ST_NUM_INT);
	return TOKEN_NUM_INT;
}

{real_number} {
	cout<<"FLEX int_number "<<yytext<<endl;
	yylval=table.putNumber(yytext,ST_NUM_REAL);
	return TOKEN_NUM_REAL;
}

. {
	cout << "FLEX unknown: " << *yytext << "" << endl;
	return *yytext;
}
%%