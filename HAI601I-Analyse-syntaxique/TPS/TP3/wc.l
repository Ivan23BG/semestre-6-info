%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
%}
%%
\n {return 300;}
. {return 301;}
[^ \t\n]+[ \t\n] {return 302;}
%%
int main(int argc, char** argv) 
{
    char buff[255];
    if (argc != 2) {
        printf("Il faut deux paramètres\n");
        return 1;
    }
    FILE* entree = fopen(argv[1], "r");
    FILE* sortie = fopen("sortie", "w+");
    if (entree)
        yyin = entree;
    int j;
    int nbLignes = 0;
    int nbCaracteres = 0;
    int nbMots = 0;
    while ((j=yylex())!=0) {
        if (j == 300) {
            nbLignes++;
            nbCaracteres++;
        }
        else if (j == 301) {
            nbCaracteres++;
        }
        else if (j == 302) {
            int len = strlen(yytext);
            nbCaracteres += len;
            if (yytext[len-1] == '\n') nbLignes++;
            nbMots++;
            printf("Mot trouvé : %s\n", yytext);
        }
    }
    printf("il y a %d lignes et %d caractères avec %d mots \n", nbLignes, nbCaracteres, nbMots);
}