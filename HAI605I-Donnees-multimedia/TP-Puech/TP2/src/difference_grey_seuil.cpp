//
// Created by Ivan on 10/02/2024.
//
// difference_grey_seuil.cpp : Renvoie le contour d'une image

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char *argv[]) {
    char cNomImgLue1[250], cNomImgLue2[250], cNomImgEcrite[250];
    int nH, nW, nTaille;

    if (argc != 5) {
        printf("Usage: ImageIn1.pgm ImageIn2.pgm ImageOut.pgm Seuil\n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue1);
    sscanf(argv[2], "%s", cNomImgLue2);
    sscanf(argv[3], "%s", cNomImgEcrite);
    int seuil = atoi(argv[4]);

    OCTET *ImgIn1, *ImgIn2, *ImgOut;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue1, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn1, OCTET, nTaille);
    lire_image_pgm(cNomImgLue1, ImgIn1, nH * nW);
    allocation_tableau(ImgIn2, OCTET, nTaille);
    lire_image_pgm(cNomImgLue2, ImgIn2, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);

    // initialize ImgOut to ImgIn
    for (int i = 0; i < nTaille; i++) {
        ImgOut[i] = ImgIn1[i];
    }

    // excluding edge cases
    for (int i = 1; i < nH-1; i++)
        for (int j = 1; j < nW-1; j++) {
            // verify if difference is greater than threshold
            if (abs(ImgIn1[i * nW + j] - ImgIn2[i * nW + j]) > seuil) {
                ImgOut[i * nW + j] = 0;
            } else {
                ImgOut[i * nW + j] = 255;
            }
        }

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn1);
    free(ImgIn2);
    free(ImgOut);

    return 1;
}
