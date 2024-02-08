%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
%}
%%
^[ \t]*\n {return 301;/* Suppression des lignes blanches */}
^[ \t]+ {return 301;/* Suppression des débuts de ligne blancs */}
[ \t]+$ {return 302;/* Suppression des fins de ligne blancs */}
[ \t][ \t]+ {return 303;/* Remplacement des multiples blancs */}
. {return 300;/* Conservation des autres lignes */}
\n {return 300;/* Conservation des autres lignes */}
%%
int main(int argc, char** argv) 
{
    if (argc != 2) {
        printf("Utilisation : entree.txt\n");
        exit(1);
    }
    FILE* entree = fopen(argv[1], "r");
    FILE* sortie = fopen("sortie.txt", "w+");
    if (entree)
        yyin = entree;
    else {
        printf("Erreur dans l'entree\n");
        exit(1);
    }
    int j;
    while ((j=yylex())!=0) {
        if (j == 301) {
            //printf("suppr\n");
        } else {
            if (j == 302) {
                // fprintf(sortie, "\n");
            } else {
                if (j == 303) {
                    fprintf(sortie, "-");
                } else {
                    if (j == 300) {
                        fprintf(sortie, "%s", yytext);
                    } else {
                        printf("Code non reconnu : %d %s\n", j, yytext);
                    }
                }
            }
        }
    }

    return 1;
}