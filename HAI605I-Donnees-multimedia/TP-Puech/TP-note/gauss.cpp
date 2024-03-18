//
// Created by Ivan on 14/02/2024.
//
// filtre_gaussien.cpp : applique un filtre gaussien sur une image

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char *argv[]) {
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, n;
    if (argc != 4) {
        printf("Usage: ImageIn.pgm ImageOut.pgm n\n");
        exit(1);
    }
    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);
    sscanf(argv[3], "%d", &n);

    OCTET *ImgIn, *ImgOut;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);

    // apply the filter
    for (int i = 0; i < nH; i++){
        for (int j = 0; j < nW; j++) {
            float sum = 0;
            float count = 0;
            for (int k = -n; k <= n; k++) {
                for (int l = -n; l <= n; l++) {
                    if (i + k >= 0 && i + k < nH && j + l >= 0 && j + l < nW) {
                        float g = exp(-(k * k + l * l) / (2 * n * n));
                        sum += g * ImgIn[(i + k) * nW + j + l];
                        count += g;
                    }
                }
            }
            ImgOut[i * nW + j] = sum / count;
        }
    }

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn);
    free(ImgOut);
    return 1;
}