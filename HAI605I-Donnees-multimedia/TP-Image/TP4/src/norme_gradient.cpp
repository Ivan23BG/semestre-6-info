//
// Created by Ivan on 14/02/2024.
//
// norme_gradient.cpp : cree une image de la norme du gradient

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char *argv[]) {
    char cNomImgLue[250], cNomImgEcrite[255];
    int nH, nW, nTaille, num;

    if (argc != 3) {
        printf("Usage: ImageIn.pgm ImageOut.pgm \n");
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


    // calcul du gradient pour chaque pixel
    for (int i = 0; i < nH; i++){
        for (int j = 0; j < nW; j++) {
            if (i == 0 || i == nH - 1 || j == 0 || j == nW - 1) {
                // ignore edges
                ImgOut[i * nW + j] = 0;
            } else {
                int dx = ImgIn[(i + 1) * nW + j] - ImgIn[(i - 1) * nW + j];
                int dy = ImgIn[i * nW + j + 1] - ImgIn[i * nW + j - 1];
                ImgOut[i * nW + j] = sqrt(dx * dx + dy * dy);
            }
        }
    }

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn);
    free(ImgOut);

    return 1;
}
