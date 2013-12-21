/*
Maria Deslis
csci400 - Bahn
spring 2013
hw08 flex/bison
*/

%union{ /*typedef this to YYSTYPE*/
int i;
float f;
char *s;	
}

%token <f> FLOAT
%token <i> INTEGER
%token <s> STRING
%token NEWLINE

%type <f> expression
%type <f> term
%type <f> numeric
%type <f> stmt

%defines
%{ 
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int R0, R1, R2, R3, R4 = 0;
float R5, R6, R7, R8, R9 = 0;

void assignRegister(char* reg, float value);
float findRegister(char* reg);


%}
%%



program:	openBracket stmts closeBracket
|	openBracket stmts closeBracket NEWLINE
|	stmts NEWLINE
|	stmt ';' NEWLINE
;

openBracket:	'{';

closeBracket:	'}';

stmts:	stmt stmts
|	stmt
;

stmt:	STRING '=' expression ';' NEWLINE	{ printf("%s = %f\n", $1, $3); assignRegister($1, $3);}
|	expression ';' NEWLINE	{ printf("<stmt> -> <expression> = %f\n", $1); }
|	STRING ';' NEWLINE	{ printf("%s -> %f\n", $1, findRegister($1));}
|	expression ';'
|	NEWLINE 
;

expression:	expression '+' term	{ printf("<expression> -> <expression> + <term>\n"); $$ = $1 + $3; }
|	expression '-' term { printf("<expression> -> <expression> - <term>\n"); $$ = $1 - $3; }
|	term { printf("<expression> -> <term>\n");$$ = $1; }
;

term:	term '*' numeric { printf("<term> -> <term> * <numeric>\n"); $$ = $1 * $3; }
|	term '/' numeric { printf("<term> -> <term> / <numeric>\n"); $$ = $1 / $3; } 
| 	numeric '^' numeric	{ printf("<term> -> <numeric> ^ <numeric>\n"); $$ = pow($1, $3); }
|	numeric {printf("<term> -> <numeric>\n"); $$ = $1;}
;

numeric:	INTEGER { printf("<INTEGER>\n"); $$ = $1; }
|	FLOAT { printf("<FLOAT>\n"); $$ = $1; }
;

%%
void assignRegister(char* reg, float value) {
	char* magic;
	magic = (char *) malloc(2);
	sprintf(magic, "%c", reg[1]);

	switch(atoi(magic)) {
		case 0 : R0 = (int)value;
					break;
		case 1 : R1 = (int)value;
					break;
		case 2 : R2 = (int)value;
					break;
		case 3 : R3 = (int)value;
					break;
		case 4 : R4 = (int)value;
					break;
		case 5 : R5 = value;
					break;
		case 6 : R6 = value;
					break;
		case 7 : R7 = value;
					break;
		case 8 : R8 = value;
					break;
		case 9 : R9 = value;
					break;
	}
}

float findRegister(char* reg) {
	char * magic;
	magic = (char *) malloc(2);
	sprintf(magic, "%c", reg[1]);
	switch(atoi(magic))
	 {
		case 0 : return (float)R0;
					break;
		case 1 : return (float)R1;
					break;
		case 2 : return (float)R2;
					break;
		case 3 : return (float)R3;
					break;
		case 4 : return (float)R4;
					break;
		case 5 : return R5;
					break;
		case 6 : return R6;
					break;
		case 7 : return R7;
					break;
		case 8 : return R8;
					break;
		case 9 : return R9;
					break;
	}
}
