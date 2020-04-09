%{
/* this is yacc specification */
#include <stdio.h>
#include <string.h>
int yylex();
%}
%token ID NUM WHILE
%right '='
%left '+' '-'
%left '*' '/'
%left UMINUS
%%
S : WHILE{whileStart();} '(' E ')'{showCondition();} E ';'{endLoop();}
  ;
E : V '=' E{assignmentGeneration();}
  | E '+'{push();} E{simpleExp();} 
  | E '-'{push();} E{simpleExp();} 
  | E '*'{push();} E{simpleExp();} 
  | E '/'{push();} E{simpleExp();} 
  | '(' E ')'
  | '-'{push();} E{unaryMinusGeneration();} %prec UMINUS
  | V
  | NUM{push();}
  ;
V : ID{push();}
  ;
%%
char stack[100][10]; //Stack of size 100 with 10 chars
int stack_top = 0;
char id_count[2] = "0";
char temp[2] = "t";

int main()
{
    printf("Enter While Expression:");
    yyparse(); //Calls main lex function
}

void push()
{
    strcpy(stack[++stack_top],yytext);
}

void whileStart()
{
    printf("Begin\n");
}

void showCondition()
{
    strcpy(temp,"t");
    strcat(temp,id_count);
    printf("%s = not %s\nif %s goto END",temp,stack[stack_top],temp);
    id_count[0]++;
}

void endLoop()
{
    printf("END\n");
}

void assignmentGeneration()
{
    printf("%s = %s\n",stack[stack_top - 2],stack[stack_top]);
    stack_top -= 2;
}

void unaryMinusGeneration()
{
    strcpy(temp,"t");
    strcat(temp,id_count);
    printf("%s = -%s",temp,stack[stack_top]);
    id_count[0]++;
}

void simpleExp()
{
    strcpy(temp,"t");
    strcat(temp,id_count);
    printf("%s = %s %s %s\n",temp,stack[stack_top - 2],stack[stack_top-1],stack[stack_top]);
    stack_top -= 2;
    id_count[0] ++;
}

int yyerror()
{
}
int yywrap()
{
return 1;
}
