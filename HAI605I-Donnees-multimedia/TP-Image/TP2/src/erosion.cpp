//
// Created by Ivan on 08/02/2024.
//
// erosion.cpp : Erode une image en niveau de gris

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

    // excluding edge cases
    for (int i = 1; i < nH-1; i++)
        for (int j = 1; j < nW-1; j++) {
            // verify if the pixel has a white pixel in its 8-neighborhood
            if (
                    ImgIn[(i-1) * nW + j] == 255 || // top
                    ImgIn[(i-1) * nW + (j-1)] == 255 || // top-left
                    ImgIn[(i-1) * nW + (j+1)] == 255 || // top-right
                    ImgIn[i * nW + (j-1)] == 255 ||  // left
                    ImgIn[i * nW + j] == 255 ||  // center
                    ImgIn[i * nW + (j+1)] == 255 || // right
                    ImgIn[(i+1) * nW + j] == 255 || // bottom
                    ImgIn[(i+1) * nW + (j-1)] == 255 || // bottom-left
                    ImgIn[(i+1) * nW + (j+1)] == 255) { // bottom-right
                ImgOut[i * nW + j] = 255;
            } else {
                ImgOut[i * nW + j] = 0;
            }
        }



    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn);
    free(ImgOut);

    return 1;
}
