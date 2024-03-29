//
// Created by Ivan on 14/02/2024.
//
// maxima_locaux.cpp : trouve les maxima locaux d'une image

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char *argv[]) {
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, S;

    if (argc != 4) {
        printf("Usage: ImageIn.pgm ImageOut.pgm Seuil\n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);
    sscanf(argv[3], "%d", &S);

    OCTET *ImgIn, *ImgOut;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);

    // find local maxima in regard to S
    // if the norm of gradient is greater than S, then it's a local maxima
    for (int i = 0; i < nH; i++){
        for (int j = 0; j < nW; j++) {
            if (i == 0 || i == nH - 1 || j == 0 || j == nW - 1) {
                // ignore edges
                ImgOut[i * nW + j] = 0;
            } else {
                int dx = ImgIn[(i + 1) * nW + j] - ImgIn[(i - 1) * nW + j];
                int dy = ImgIn[i * nW + j + 1] - ImgIn[i * nW + j - 1];
                int norm = sqrt(dx * dx + dy * dy);
                if (norm > S) {
                    ImgOut[i * nW + j] = 255;
                } else {
                    ImgOut[i * nW + j] = 0;
                }
            }
        }
    }

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn);
    free(ImgOut);

    return 1;
}