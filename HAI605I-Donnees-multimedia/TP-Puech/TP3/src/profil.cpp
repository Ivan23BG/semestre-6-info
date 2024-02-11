//
// Created by Ivan on 06/02/2024.
//
// profil.cpp : enregistre les donnees d'une partie d'une image

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char *argv[]) {
    char cNomImgLue[250], cNomFicSort[255], l_or_c[2];
    int nH, nW, nTaille, num;

    if (argc < 4 || argc > 5) {
        printf("Usage: ImageIn.pgm l_or_c num Optional-FicOut.dat\n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", l_or_c);
    sscanf(argv[3], "%d", &num);
    if (argc == 5) {
        sscanf(argv[4], "%s", cNomFicSort);
    } else {
        sprintf(cNomFicSort, "out/fich.dat");
    }

    OCTET *ImgIn;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);

    // Open file for writing
    FILE *fp = fopen(cNomFicSort, "w+");

    // Output data
    if (l_or_c[0] == 'l') { // if l_or_c is 'l' then we get the values of the specific line
        for (int i = 0; i < nW; i++) {
            // printf("%d %d\n", i, ImgIn[num * nW + i]);
            fprintf(fp, "%d %d\n", i, ImgIn[num * nW + i]);
        }
    } else { // if l_or_c is 'c' then we get the values of the specific column
        for (int i = 0; i < nH; i++) {
            // printf("%d %d\n", i, ImgIn[num * nW + i];
            fprintf(fp, "%d %d\n", i, ImgIn[i * nW + num]);
        }
    }

    fclose(fp);

    free(ImgIn);

    return 1;
}
