/*
 * symbol.c
 *
 *  Created on: 2013-3-15
 *      Author: y
 */

#include "global.h"

char lexemes[STR_MAX];
int lastchar = 0;
int lastentry = 0;

symentry keywords[] = {
		{"if",		IF},
		{"else",	ELSE},
		{"while",	WHILE},

		{"void",	VOID},
		{"int",		INT},
		{"bool",	BOOL},
		{"float",	FLOAT},
		{"char",	CHAR},
		{"string",	STRING},

		{"break",	BREAK},
		{"continue",CONTINUE},

		{"main",	MAIN},
		{"return",	RETURN},

		{"true",	B_TRUE},
		{"false",	B_FALSE},

		{"and",		AND},
		{"or",		OR},
		{"not",		NOT},

		{0,		0}
};

void init_symbol() {
	symentry * p;
	for(p = keywords; p->token; p++)
		insert(p->lexptr, p->token);
}

int look_up(char * s){
	int p;
	for(p = lastentry; p > 0; p--)
		if(strcmp(s, symtable[p].lexptr) == 0)
			return p;
	return 0;
}

int insert(char * s, int token){
	int len = 0;
	len = strlen(s);
	if(len + lastchar + 1 >= STR_MAX)
		error_handle(lineno, "lexemes full");
	if(lastentry + 1 >= SYM_MAX)
		error_handle(lineno, "symbol table full");
	lastentry += 1;
	symtable[lastentry].token = token;
	symtable[lastentry].lexptr = &lexemes[lastchar];
	strcpy(&lexemes[lastchar], s);
	lastchar += ( len + 1 );
	return lastentry;
}

/*
int insert_str(){
}
*/



