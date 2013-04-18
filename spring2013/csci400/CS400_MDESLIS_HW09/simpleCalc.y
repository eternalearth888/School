%{
// Maria Deslis
// Spring 2013
// Slightly less crippled SimpleCalc

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define VERBOSE (0)

int endProgram(void);
void rule(char *lhs, char *rhs, int type, void *ival);

int verbose = VERBOSE;
float f_reg[5] = {0};
int   i_reg[5] = {0};

%}

%union {
   float fval;
   int ival;
}

%token <ival> I_REG
%token <ival> F_REG
%token <ival> I_NUM
%token <fval> F_NUM	 

%left '+'
%left '-'
%left '*'
%left '/'
%right '^'

%type <fval> f_expr
%type <fval> f_term
%type <fval> f_factor
%type <fval> f_value
%type <ival> i_expr
%type <ival> i_term
%type <ival> i_factor
%type <ival> i_value

%defines
%%
program: 
		statement 					{	rule("program", "statement", 0, NULL);
										return endProgram(); 
									}
	|	'{' statements '}'			{	rule("program", "'{' statements '}'", 0, NULL);
										return endProgram();
									}
	;

statements: 
		statement ';' statements	{	rule("statements", "statement ';' statements", 0, NULL); }
	|	statement ';'				{	rule("statements", "statement ';'", 0, NULL); }
	;
	
statement:	
		F_REG '=' f_expr	 		{	f_reg[$1] = $3; 	rule("statement", "F_REG '=' f_expr", 0, NULL); }
	|	F_REG '=' i_expr	 		{	f_reg[$1] = $3; 	rule("statement", "F_REG '=' i_expr", 0, NULL); }
	|	I_REG '=' f_expr	 		{	i_reg[$1] = $3; 	rule("statement", "I_REG '=' f_expr", 0, NULL); }
	|	I_REG '=' i_expr	 		{	i_reg[$1] = $3; 	rule("statement", "I_REG '=' i_expr", 0, NULL); }
	|	f_expr						{	rule("statement", "f_expr", 0, NULL); }
	|	i_expr						{	rule("statement", "i_expr", 0, NULL); }
	|	'?' f_expr					{	printf("ANS> %g\n", $2); }
	|	'?' i_expr					{	printf("ANS> %i\n", $2); }
	;

f_expr:
		f_expr '+' f_term			{	$$ = $1 + $3;		rule("f_expr", "f_expr '+' f_term", 1, &$$); }
	|	f_expr '+' i_term			{	$$ = $1 + $3;		rule("f_expr", "f_expr '+' i_term", 1, &$$); }
	|	i_expr '+' f_term			{	$$ = $1 + $3;		rule("f_expr", "i_expr '+' f_term", 1, &$$); }
	|	f_expr '-' f_term			{	$$ = $1 - $3;		rule("f_expr", "f_expr '-' f_term", 1, &$$); }
	|	f_expr '-' i_term			{	$$ = $1 - $3;		rule("f_expr", "f_expr '-' i_term", 1, &$$); }
	|	i_expr '-' f_term			{	$$ = $1 - $3;		rule("f_expr", "i_expr '-' f_term", 1, &$$); }
	|	f_term						{	$$ = $1;			rule("f_expr", "f_term", 1, &$$); }
	;
	
i_expr:
		i_expr '+' i_term			{	$$ = $1 + $3;		rule("i_expr", "i_expr '+' i_term", 0, &$$); }
	|	i_expr '-' i_term			{	$$ = $1 - $3;		rule("i_expr", "i_expr '-' i_term", 0, &$$); }
	|	i_term						{	$$ = $1;			rule("i_expr", "i_term", 0, &$$); }
	;
	
f_term:
		f_term '*' f_factor			{	$$ = $1 * $3;		rule("f_term", "f_term '*' f_factor", 1, &$$); }
	|	f_term '*' i_factor			{	$$ = $1 * $3;		rule("f_term", "f_term '*' i_factor", 1, &$$); }
	|	i_term '*' f_factor			{	$$ = $1 * $3;		rule("f_term", "i_term '*' f_factor", 1, &$$); }
	|	f_term '/' f_factor			{	$$ = $1 / $3;		rule("f_term", "f_term '/' f_factor", 1, &$$); }
	|	f_term '/' i_factor			{	$$ = $1 / $3;		rule("f_term", "f_term '/' i_factor", 1, &$$); }
	|	i_term '/' f_factor			{	$$ = $1 / $3;		rule("f_term", "i_term '/' f_factor", 1, &$$); }
	|	f_factor					{	$$ = $1; 			rule("f_term", "f_factor", 1, &$$); }
	;
	
i_term:
		i_term '*' i_factor			{	$$ = $1 * $3;		rule("i_term", "i_term '*' i_factor", 0, &$$); }
	|	i_term '/' i_factor			{	$$ = $1 / $3;		rule("i_term", "i_term '/' i_factor", 0, &$$); }
	|	i_factor					{	$$ = $1;			rule("i_term", "i_factor", 0, &$$); }
	;

f_factor:
		f_value '^' f_factor		{	$$ = pow($1,$3);	rule("f_factor", "f_value '^' f_factor", 1, &$$); }
	|	f_value '^' i_factor		{	$$ = pow($1,$3);	rule("f_factor", "f_value '^' i_factor", 1, &$$); }
	|	i_value '^' f_factor		{	$$ = pow($1,$3);	rule("f_factor", "i_value '^' f_factor", 1, &$$); }
	|	i_value '^' i_factor		{	$$ = pow($1,$3);	rule("f_factor", "i_value '^' i_factor", 1, &$$); }
	|	f_value						{	$$ = $1;			rule("f_factor", "f_value", 1, &$$); }
	;
	
i_factor:
		i_value						{	$$ = $1;			rule("i_factor", "i_value", 0, &$$); }
	;
	
f_value: 
		F_NUM						{	$$ = $1;			rule("f_value", "F_NUM", 1, &$$); }
	|   F_REG						{	$$ = f_reg[$1];		rule("f_value", "F_REG", 1, &$$); }
	|	'(' f_expr ')'				{	$$ = $2;			rule("f_value", "'(' f_expr ')'", 1, &$$); }
	|	'+' f_value					{ 	$$ = 0 + $2;		rule("f_value", "'+' f_value", 0, &$$); }
	|	'-' f_value					{   $$ = 0 - $2;		rule("f_value", "'-' f_value", 0, &$$); }
	;

i_value: 
		I_NUM						{	$$ = $1;			rule("i_value", "I_NUM", 0, &$$); }
	|	I_REG						{	$$ = i_reg[$1];		rule("i_value", "I_REG", 0, &$$); }
	|	'(' i_expr ')'				{	$$ = $2;			rule("i_value", "'(' i_expr ')'", 0, &$$); }
	|	'+' i_value					{ 	$$ = 0 + $2;		rule("i_value", "'+' i_value", 0, &$$); }
	|	'-' i_value					{   $$ = 0 - $2;		rule("i_value", "'-' i_value", 0, &$$); }
	;
	
%%

void rule(char *lhs, char *rhs, int type, void *val)
{
	if (verbose)
	{
		if (val) // Make sure a value is included 
			switch(type)
			{
				case 0:	printf("%40s => %s (%i)\n", lhs, rhs, *((int*)val)); break;
				case 1:	printf("%40s => %s (%f)\n", lhs, rhs, *((float*)val)); break;
			}
		else     // print out only the rule 
			printf("%40s => %s\n", lhs, rhs);
	}
}

int endProgram(void)
{
	printf("Press ENTER to exit:");
	fgetc(stdin);
	return 0;
}

