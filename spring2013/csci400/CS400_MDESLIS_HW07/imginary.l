%option noyywrap

/*
 Declaring what a real number is
 csci400 
 spring2013
 hw07 flex
 Maria Deslis
*/

%{ 
/* need for the call to atof() below */
 #include <math.h> 
%}

DIGIT [0-9] 
ID [a-z][a-z0-9]*
 
%% 

-?{DIGIT}*\i { printf( "Imaginary number: %s\n", yytext ); }  /* a positive or negative real number */

[ \t\n]+ /* eat up whitespace */ 

. { printf( "Unrecognized character: %s\n", yytext ); } 

%% 

int main(int argc, char ** argv ) 
{ 
	++argv, --argc;
	
 /* skip over program name */
if ( argc > 0 ) 
    yyin = fopen( argv[0], "r" );
else yyin = stdin; 
yylex(); 

}
