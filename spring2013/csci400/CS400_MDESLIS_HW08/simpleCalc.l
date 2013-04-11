/*
Maria Deslis
csci400 - Bahn
spring 2013
hw08 flex/bison
*/

%option noyywrap

%{
	#include "simpleCalc.tab.h"
	#include "string.h"

extern YYSTYPE yylval;

char* filter(char* filterR);
%}

DIGIT [0-9]
R [rR]
LETTERS [a-zA-Z_]

%%
{DIGIT}+	{ yylval.i = atoi(yytext); return INTEGER; } /* integer */

{DIGIT}*\.{DIGIT}+	{ yylval.f = atof(yytext); return FLOAT; } /* floating point */

{R}{LETTERS}*{DIGIT}+	{ yylval.s = filter(yytext); return STRING; } /* exercise 3 */

[ \t]+	;		/* ignore white space */
[\n]  return NEWLINE; /* return new line */
<<EOF>> return 0; /*return end of file */
.	return yytext[0]; /* everything else */
%%
/*---------------------------------------------------------------------------*/
/* 5. Other C code that we need.                                           */

yyerror(char *errmsg)
{
    fprintf(stderr, "%s\n", errmsg);
}

char* filter(char* filterR) 
{
	/* the r is the first character in the string, so just grab that character */
	char R = toupper(filterR[0]);

	/* the number is the last character in the string, so just grab that character */
	char num = filterR[strlen(filterR)-1];

	/* combine char R and char num */
	char* concat;

	concat = malloc(3);

	sprintf(concat, "%c%c", R, num);

	return concat;
}

int main(int argc, char ** argv)
{
	++argv, --argc;
	/* if you pass in a file, use it, otherwise do normal stuff */
	if (argc > 0) {
		yyin = fopen(argv[0], "r");
		} else {
		yyin = stdin;
	}

	yyparse();
}
