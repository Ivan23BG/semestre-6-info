//
// Created by Ivan on 10/02/2024.
//
// dilatation_grey.cpp : Dilate une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char *argv[]) {
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille;

    if (argc != 3) {
        printf("Usage: ImageIn.pgm ImageOut.pgm\n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);

    OCTET *ImgIn, *ImgOut;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);

    // initialize ImgOut to ImgIn
    for (int i = 0; i < nTaille; i++) {
        ImgOut[i] = ImgIn[i];
    }

    int max;

    // excluding edge cases
    for (int i = 1; i < nH-1; i++) {
        for (int j = 1; j < nW-1; j++) {
            // replace pixel with maximum value of its neighbors
            max = 0;
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    if (ImgIn[(i+k)*nW + (j+l)] > max) {
                        max = ImgIn[(i+k)*nW + (j+l)];
                    }
                }
            }
            ImgOut[i*nW + j] = max;
        }
    }

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn);
    free(ImgOut);

    return 1;
}

