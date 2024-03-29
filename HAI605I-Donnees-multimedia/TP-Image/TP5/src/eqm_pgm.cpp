//
// Created by Ivan on 28/02/2024.
//
// eqm_pgm.cpp : calcule l'erreur quadratique moyenne entre deux images

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char *argv[]) {
    char cNomImgLue1[250], cNomImgLue2[250];
    int nH, nW, nTaille;

    if (argc != 3) {
        printf("Usage: ImageIn1.pgm ImageIn2.pgm \n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue1);
    sscanf(argv[2], "%s", cNomImgLue2);

    OCTET *ImgIn1, *ImgIn2;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue1, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn1, OCTET, nTaille);
    lire_image_pgm(cNomImgLue1, ImgIn1, nH * nW);
    allocation_tableau(ImgIn2, OCTET, nTaille);
    lire_image_pgm(cNomImgLue2, ImgIn2, nH * nW);

    // calcul de l'erreur quadratique moyenne
    double eqm = 0;
    for (int i = 0; i < nTaille; i++) {
        eqm += (ImgIn1[i] - ImgIn2[i]) * (ImgIn1[i] - ImgIn2[i]);
    }
    eqm = eqm / nTaille;
    printf("Erreur quadratique moyenne : %f\n", eqm);

    free(ImgIn1);
    free(ImgIn2);

    return 1;
}
