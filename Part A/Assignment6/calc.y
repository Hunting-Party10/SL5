%{
/* this is yacc specification */
#include <stdio.h>
%}
%token INTEGER
%left '-' '+'
%left '*' '/'
%nonassoc NEG
%%
statement: exp { printf("= %d\n",$1); }
;
exp: exp '+' exp { $$ = $1 + $3; }
| exp '-' exp { $$ = $1 - $3; }
| exp '*' exp { $$ = $1 * $3; }
| exp '/' exp { $$ = $1 / $3; }
| '-' exp %prec NEG { $$ = -$2; }
| '(' exp ')' { $$ = $2; }
| INTEGER { $$ = $1; }
;
%%
int main()
{
yyparse();
}
int yyerror()
{
}
int yywrap()
{
return 1;
}
