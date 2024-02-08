/**
 * @file afd.h
 * @brief Définition d'un AFD du langage C
 * @author Michel Meynard
 */
#define EINIT 0
#define EI 1
#define EIF 2
#define EID 3
#define ESEP 4
#define ECHIFFRE 5
#define EFLOAT 6
#define EP 7
#define ESLASH 8
#define ESLASHET 9
#define ESLASHDET 10
#define EDSLASH 11
#define ECOM 12
#define ECOM2 13
#define NBETAT 14
#define OTHER 300
#define IF 301;
#define LITID 302;
#define LITSEP 303;
#define LITENT 304;
#define LITDEC 305;
#define LITCOM 306;
#define LITCOM2 307; /* jetons des états finaux */

int TRANS[NBETAT][256];		/* table de transition : état suivant */
int JETON[NBETAT];		/* jeton (1-32000) ou non final (0) ? */

void classe(int ed, int cd, int cf, int ef);


void creerAfd(){			/* Construction de l'AFD */
  int i;int j;			/* variables locales */
  for (i=0;i<NBETAT;i++){
    for(j=0;j<256;j++) TRANS[i][j]=-1; /* init vide */
    JETON[i]=0;			/* init tous états non finaux */
  }
  /* Transitions de l'AFD */
  classe(EINIT, EI, 'i', 'i');
  classe(EI, EIF, 'f', 'f');
  classe(EIF, EID, 'a', 'z');
  classe(EIF, EID, 'A', 'Z');
  classe(EIF, EID, '0', '9');
  classe(EID, EID, '_', '_');
  classe(EID, EID, 'a', 'z');
  classe(EID, EID, 'A', 'Z');
  classe(EID, EID, '0', '9');
  classe(EID, EID, '_', '_');
  classe(EI, EID, 'a', 'e');
  classe(EI, EID, 'g', 'z');
  classe(EI, EID, 'A', 'Z');
  classe(EI, EID, '0', '9');
  classe(EI, EID, '_', '_');
  classe(EINIT, EID, 'a', 'h');
  classe(EINIT, EID, 'j', 'z');
  classe(EINIT, EID, 'A', 'Z');
  classe(EINIT, ESEP, '\t', '\t');
  classe(EINIT, ESEP, ' ', ' ');
  classe(EINIT, ESEP, '\n', '\n');
  classe(ESEP, ESEP, '\t', '\t');
  classe(ESEP, ESEP, ' ', ' ');
  classe(ESEP, ESEP, '\n', '\n');
  classe(EINIT, ECHIFFRE, '0', '9');
  classe(ECHIFFRE, ECHIFFRE, '0', '9');
  classe(ECHIFFRE, EFLOAT, '.', '.');
  classe(EFLOAT, EFLOAT, '0', '9');
  classe(EINIT, EP, '.', '.');
  classe(EP, EFLOAT, '0', '9');
  classe(ESLASH, ESLASHET, '*', '*');
  classe(ESLASHET, ESLASHET, 0, '*'-1);
  classe(ESLASHET, ESLASHET, '*'+1, 255);
  classe(ESLASHET, ESLASHDET, '*', '*');
  classe(ESLASHDET, ESLASHDET, '*', '*');
  classe(ESLASHDET, ESLASHET, 0, '*'-1);
  classe(ESLASHDET, ESLASHET, '*'+1, '/'-1);
  classe(ESLASHDET, ESLASHET, '/'+1, 255);
  classe(ESLASHDET, ECOM2, '/', '/');
  classe(ESLASH, EDSLASH, '/', '/');
  classe(EDSLASH, EDSLASH, 0, '\n'-1);
  classe(EDSLASH, EDSLASH, '\n'+1, 255);
  classe(EDSLASH, ECOM, '\n', '\n');
  JETON[EI]=OTHER;
  JETON[EIF]=IF;
  JETON[EID]=LITID;
  JETON[ESEP]=LITSEP;
  JETON[ECHIFFRE]=LITENT;
  JETON[EFLOAT]=LITDEC;
  JETON[ECOM]=LITCOM;
  JETON[ECOM2]=LITCOM2; /* jetons des états finaux */
} /* les bd sont à filtrer : commentaires */

/** construit un ensemble de transitions de ed à ef pour un intervale de char
*@param ed l'état de départ
*@param ef l'état final
*@param cd char de début
*@param cf char de fin
*/
void classe(int ed, int cd, int cf, int ef) {
  int c = cf;
  while (c <= ef) {
    TRANS[ed][c] = cd;
    c++;
  }
}