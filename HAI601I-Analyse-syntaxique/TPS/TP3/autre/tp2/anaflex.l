%{

%}
%%
if|then|else|throw {return 300;}
0|[1-9][0-9]* {return 301;}
0[0-7]* {return 302;}
0x|([0-9][a-f][A-F])+ {return 303;}
[a-z]|[A-Z]([a-z]|[A-Z]|[0-9]|_)* {return 304;}
([0-9]+"."|"."[0-9])[0-9]*([eE][+-]?[1-9][0-9]*)? {return 305;}
[\t\n ]+ {return 306;}
"//".*\n  {return 306;}
"/*"([^*]|"*"+[^*\\])*"*"+"/" {return 306;}
%%
main() 
{int j; 
char *invite="Saisissez un mot suivi de EOF (CTRL-D) : ";
printf(invite);
while ((j=yylex())!=0) 
printf("\nJeton : %i; de lexeme %s\n%s", j, yytext, invite);}