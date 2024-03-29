//
// Created by Ivan on 28/02/2024.
//
// eqm_pgm.cpp : calcule l'erreur quadratique moyenne entre deux images

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char *argv[]) {
    char cNomImgLue[250], cNomFicSort[250];
    int nH, nW, nTaille;

    if (argc != 2) {
        printf("Usage: ImageIn1.pgm n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    if (argc == 3) {
        sscanf(argv[2], "%s", cNomFicSort);
    } else {
        sprintf(cNomFicSort, "out/histo.dat");
    }

    OCTET *ImgIn;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);

    // calcul de l'erreur quadratique moyenne
    // initialize tab to 0
    double tab[256];
    for (int i = 0; i < 256; i++) {
        tab[i] = 0;
    }

    // Open file for writing
    FILE *fp = fopen(cNomFicSort, "w+");

    // Update array
    for (int i = 0; i < nTaille; i++) {
        tab[ImgIn[i]] += 1;
    }
    for (int i = 0; i < 256; i++) {
        tab[i] /= nTaille;
    }

    // Output data
    for (int i = 0; i < 256; i++) {
        // printf("%d %d\n", i, tab[i]);
        fprintf(fp, "%d %f\n", i, tab[i]);
    }

    fclose(fp);

    free(ImgIn);

    return 1;
}
