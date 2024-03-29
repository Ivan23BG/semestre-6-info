//
// Created by Ivan on 28/02/2024.
//
// modify.cpp: modifie la composante Y par + n.

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char *argv[]) {
    char cNomImgLueY[250];
    char cNomImgEcrite[250];
    int nH, nW, nTaille, n;
    if (argc != 3) {
        printf("Usage: ImageIn_Y.pgm n\n");
        exit(1);
    }
    sscanf(argv[1], "%s", cNomImgLueY);
    sscanf(argv[2], "%d", &n);
    // rename the output files to be %s-modif-n.pgm
    char *p = strrchr(cNomImgLueY, '.');
    p-=2;
    *p = 0;
    sprintf(cNomImgEcrite, "%s-modif-%d.pgm", cNomImgLueY, n);
    sprintf(cNomImgLueY, "%s_Y.pgm", cNomImgLueY);

    OCTET *ImgInY, *ImgOut;
    lire_nb_lignes_colonnes_image_pgm(cNomImgLueY, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgInY, OCTET, nTaille);
    lire_image_pgm(cNomImgLueY, ImgInY, nH * nW);

    allocation_tableau(ImgOut, OCTET, nTaille);

    for (int i = 0; i < nTaille; i++) {
        int temp = ImgInY[i] + n;
        ImgOut[i] = (temp < 0) ? 0 : ((temp > 255) ? 255 : temp);
    }

    ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgInY);
    free(ImgOut);
    return 1;
}