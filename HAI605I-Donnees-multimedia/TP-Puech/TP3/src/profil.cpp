//
// Created by Ivan on 06/02/2024.
//
// profil.cpp : affiche les donnees d'une partie d'une image

#include <stdio.h>
#include "../../librairie/image_ppm.h"

int main(int argc, char *argv[]) {
    char cNomImgLue[250], l_or_c[2];
    int nH, nW, nTaille, num;

    if (argc != 4) {
        printf("Usage: ImageIn.pgm (ligne (l) ou colonne (c)) num_de_l/c \n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", l_or_c);
    sscanf(argv[3], "%d", &num);

    OCTET *ImgIn;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);

    FILE *fp = fopen("fich.dat", "w+");

    if (strcmp(l_or_c, "l") == 0) {
        for (int i = 0; i < nW; i++) {
            // printf("%d\t%d\n", i, ImgIn[(num - 1) * nW + i]);
            fprintf(fp, "%d %d\n", i, ImgIn[(num - 1) * nW + i]);
        }
    } else {
        if (strcmp(l_or_c, "c") == 0) {
            for (int i = 0; i < nH; i++) {
                // printf("%d\t%d\n", i, ImgIn[(num-1) + nW * i]);
                fprintf(fp, "%d %d\n", i, ImgIn[(num-1) + nW * i]);
            }
        } else {
            printf("%s is not a valid option",l_or_c);
            exit(1);
        }
    }
    free(ImgIn);

    return 1;
}
