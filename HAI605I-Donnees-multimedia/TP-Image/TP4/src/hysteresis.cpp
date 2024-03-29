//
// Created by Ivan on 14/02/2024.
//
// hysteresis.cpp : applique un filtre de hysteresis sur une image

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char *argv[]) {
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, S, T;
    if (argc != 5) {
        printf("Usage: ImageIn.pgm ImageOut.pgm Seuil1 Seuil2\n");
        exit(1);
    }
    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);
    sscanf(argv[3], "%d", &S);
    sscanf(argv[4], "%d", &T);

    OCTET *ImgIn, *ImgOut;
    OCTET *ImgTemp;
    OCTET *ImgTemp2;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);
    allocation_tableau(ImgTemp, OCTET, nTaille);
    allocation_tableau(ImgTemp2, OCTET, nTaille);

    // read image twice
    // first time check if the norm of gradient is smaller than T or greater than S
    // second time check if the norm of gradient is between T and S and if it's connected to a pixel with norm greater
    // than S

    // first time
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
                    ImgTemp[i * nW + j] = 255;
                } else if (norm < T) {
                    ImgTemp[i * nW + j] = 0;
                } else {
                    ImgTemp[i * nW + j] = 128;
                }
            }
        }
    }

    // second time
    for (int i = 0; i < nH; i++){
        for (int j = 0; j < nW; j++) {
            if (i == 0 || i == nH - 1 || j == 0 || j == nW - 1) {
                // ignore edges
                ImgOut[i * nW + j] = 0;
            } else {
                if (ImgTemp[i * nW + j] == 128) {
                    int found = 0;
                    for (int k = -1; k <= 1; k++) {
                        for (int l = -1; l <= 1; l++) {
                            if (ImgTemp[(i + k) * nW + j + l] == 255) {
                                found = 1;
                            }
                        }
                    }
                    if (found) {
                        ImgTemp2[i * nW + j] = 255;
                    } else {
                        ImgTemp2[i * nW + j] = 0;
                    }
                } else {
                    ImgTemp2[i * nW + j] = ImgTemp[i * nW + j];
                }
            }
        }
    }

    ecrire_image_pgm(cNomImgEcrite, ImgTemp2, nH, nW);
    free(ImgIn);
    free(ImgOut);
    free(ImgTemp);
    free(ImgTemp2);
    return 1;
}