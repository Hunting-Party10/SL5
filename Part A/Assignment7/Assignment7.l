%{
#include "Assignment8.tab.h"
extern int yylval;
%}

ALPHABET [A-Za-z]
NUMBER [0-9]
%%
while {return WHILE;}
{ALPHABET}({ALPHABET}|{NUMBER})* return ID;
{NUMBER}+ {yylval=atoi(yytext); return NUM;}
[ \t] ;
\n yyterminate();
. return yytext[0];
%%
