/** @file analdesc.c
 *@author Michel Meynard
 *@brief Analyse descendante récursive d'expression arithmétique
 *
 * Ce fichier contient un reconnaisseur d'expressions arithmétiques composée de
 * littéraux entiers sur un car, des opérateurs +, * et du parenthésage ().
 * Remarque : soit rediriger en entrée un fichier, soit terminer par deux
 * caractères EOF (Ctrl-D), un pour lancer la lecture, l'autre comme "vrai" EOF.
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
/* les macros sont des blocs : pas de ';' apres */
#define AVANCER                                                                \
  {                                                                            \
    jeton = getchar();                                                         \
    numcar++;                                                                  \
  }
#define TEST_AVANCE(prevu)                                                     \
  {                                                                            \
    if (jeton == (prevu))                                                      \
      AVANCER else ERREUR_SYNTAXE                                              \
  }
#define ERREUR_SYNTAXE                                                         \
  {                                                                            \
    printf("\nMot non reconnu : erreur de syntaxe \
au caractère numéro %d \n",                                                    \
           numcar);                                                            \
    exit(1);                                                                   \
  }

char* E();
char* R(char*);
char* T();
char* S(char*);
char* F();   /* déclars */
int jeton;      /* caractère courant du flot d'entrée */
int numcar = 0; /* numero du caractère courant (jeton) */
char *E() {
  char *res = malloc(sizeof(char) * 255);
  sprintf(res,"%s",R(T()));
  // printf("%s", res);
  return res;
}
char* R(char *a) {
  if (jeton == '+') { /* regle : R->+TR */
    AVANCER
    char *res = malloc(sizeof(char) * 255);
    sprintf(res,"%s%s+",a,R(T()));
    //printf("\n%s\n",res);
    return res;
  } else
    return a;
}
char *T() {
  return S(F());
}
char *S(char *a) {
  if (jeton == '*') { /* regle : S->*FS */
    AVANCER
    char *res = malloc(sizeof(char) * 255);
    sprintf(res,"%s%s*",a,S(F()));
    // printf("%s",res);
    return res;
  } else{
    char *res = malloc(sizeof(char) * 255);
    sprintf(res,"%s",a);
    return res;}
}
char *F() {
  if (jeton == '(') { /* regle : F->(E) */
    AVANCER
    char *res = malloc(sizeof(char) * 255);
    sprintf(res,"%s",E());
    TEST_AVANCE(')')
    return res;
  } else if (isdigit(jeton)) {/* regle : F->0|1|...|9 */
    char b = jeton;
    char *res = malloc(sizeof(char) * 255);
    sprintf(res,"%c",b);
    // printf("\njeton : %d\n", b);
    AVANCER
    return res;
    }
  else ERREUR_SYNTAXE;
}
int main() {    /* Fonction principale */
  AVANCER           /* initialiser jeton sur le premier car */
  char *a = E();              /* axiome */
  if (jeton == EOF) /* expression reconnue et rien après */
    printf("\nMot reconnu de valeur \n%s\n", a);
  else
    ERREUR_SYNTAXE /* expression reconnue mais il reste des car */
        return 0;
}