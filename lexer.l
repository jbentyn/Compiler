%{
    #include <iostream>
    
    #include "parser.h"
	#include "symbolTable.h"
#include "emitter.h"
	
    using namespace std;
	extern symbolTable table;
%}



identifier			[a-zA-Z]([[:alnum:]])*

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

{identifier} {
	cout<<"FLEX identifier "<<yytext<<endl;
	yylval=table.putIdentifier(yytext);
	cout<<"YYVAL identifier "<<yylval<<endl;
	return TOKEN_ID;
}

. {
	cout << "FLEX unknown: " << *yytext << "" << endl;
	return *yytext;
}
%%