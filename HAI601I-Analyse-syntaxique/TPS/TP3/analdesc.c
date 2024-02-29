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

int E();
int R(int);
int T();
int S(int);
int F();   /* déclars */
int jeton;      /* caractère courant du flot d'entrée */
int numcar = 0; /* numero du caractère courant (jeton) */
int E() {
  int a = T(); /* regle : E->TR */
  int b = R(a);
  return b;
}
int R(int a) {
  if (jeton == '+') { /* regle : R->+TR */
    AVANCER
    int b = T();
    int c = R(b);
    return a + c;
  } else
    return a;
}
int T() {
  int a = F();
  int b = S(a); /* regle : T->FS */
  return b;
}
int S(int a) {
  if (jeton == '*') { /* regle : S->*FS */
    AVANCER
    int b = F();
    int c = S(b);
    return a * c;
  } else
    return a;
}
int F() {
  if (jeton == '(') { /* regle : F->(E) */
    AVANCER
    int a = E();
    TEST_AVANCE(')')
    return a;
  } else if (isdigit(jeton)) {/* regle : F->0|1|...|9 */
    int b = jeton - '0';
    // printf("\njeton : %d\n", b);
    AVANCER
    return b;
    }
  else ERREUR_SYNTAXE;
}
int main() {    /* Fonction principale */
  AVANCER           /* initialiser jeton sur le premier car */
  int a = E();              /* axiome */
  if (jeton == EOF) /* expression reconnue et rien après */
    printf("\nMot reconnu de valeur %d\n", a);
  else
    ERREUR_SYNTAXE /* expression reconnue mais il reste des car */
        return 0;
}