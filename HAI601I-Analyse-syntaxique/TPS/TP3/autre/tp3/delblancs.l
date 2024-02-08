%{

%}
%%
[ \t]*\n {return 300;}
[ \t]+[^ \t\n] {return 301;}
[^ \t\n][ \t]+\n? {return 302;}
[ \t][ \t]+ {return 303;}
.*\t.*\n
%%
main() 
{int j; 
char *invite="Saisissez un mot suivi de EOF (CTRL-D) : ";
printf(invite);
while ((j=yylex())!=0) 
printf("\nJeton : %i; de lexeme %s\n%s", j, yytext, invite);}