%option noyywrap

%{
// Maria Deslis
// Spring 2013
// No longer crippled SimpleCalc

#include <stdio.h>
#include <string.h>
#include "simpleCalc.tab.h"

int extract_reg(char *s);
void token(int tkn);

extern int verbose;

%}

%%

[rR][_A-Za-z]*[0-4] { yylval.ival = extract_reg(yytext); token(I_REG) ; return I_REG; }
[rR][_A-Za-z]*[5-9] { yylval.ival = extract_reg(yytext); token(F_REG); return F_REG; }
[0-9]+	{ yylval.ival = atoi(yytext); token(I_NUM); return I_NUM; }
[0-9]+\.[0-9]*|[0-9]*\.[0-9]+	{ yylval.fval = atof(yytext); token(F_NUM); return F_NUM; }
\/\/.*[\n]   {;} // Ignore end of line comment
\/\*([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\*+\/ {;} // Ignore block comments
[ \t]	;		/* ignore white space */
[\r\n]   	;		/* ignore white space */
.	    {token(yytext[0]); return yytext[0];}
<<EOF>> {token(0); return 0;}

%%

/*---------------------------------------------------------------------------*/
/* 5. Other C code that we need.                                           */
 
yyerror(char *errmsg)
{
    fprintf(stderr, "%s\n", errmsg);
}

void token(int tkn)
{
	if (verbose)
	{

		switch(tkn)
		{
			case I_NUM: printf("TOKEN: %s (%i from %s)\n", "I_NUM", yylval.ival, yytext); break;
			case F_NUM: printf("TOKEN: %s (%g from %s)\n", "F_NUM", yylval.fval, yytext); break;
			case I_REG: printf("TOKEN: %s (%i from %s)\n", "I_REG", yylval.ival, yytext); break;
			case F_REG: printf("TOKEN: %s (%i from %s)\n", "F_REG", yylval.ival, yytext); break;
			case 0    : printf("TOKEN: %s\n", "<<EOF>>"); break;
			default   : printf("TOKEN: %c\n", tkn); break;
		}
	}
}

// This function assumes that the string passed is a properly recognized token
int extract_reg(char *s)
{
	int reg;
	
	while (*(s+1)) // Start with second character
		s++;
	reg = *s - '0'; // Convert to a number
	return ((reg<5)? reg : reg - 5); // Adjust fp reg index
}

int readsArg(char* command);
void dryOpen();

int main(int argc, char *argv[])
{
	if (argc == 2) { // Text file and no -v && No file and -v
		int dashV = readsArg(argv[1]);
		//-v flag was passed
		if (dashV == 2) {
			verbose = 1;
			yyin = stdin;
		} else {
			verbose = 0;
			dryOpen(argc, argv);
		}
	} else if (argc == 3) { // Text file and -v
		dryOpen(argc, argv);
		verbose = 1;
	} else { 	// No file and no -v
		yyin = stdin;
	}

	
	yyparse();
}

int readsArg(char* command) {
	if (command[0] == '-' && command[1] == 'v') {
		return 2; //return flag
	} else {
		return 1; // cause we don't know what it is and we just return the file
	}
}

void dryOpen(int argc, char* argv[]) {
	yyin = fopen(argv[1], "rt");
	if (!yyin)
	{
		printf("Failed to open input file <%s>\n", argv[1]);
		exit(1);
	}
}