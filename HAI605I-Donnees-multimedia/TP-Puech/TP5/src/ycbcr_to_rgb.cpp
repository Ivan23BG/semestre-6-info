//
// Created by Ivan on 28/02/2024.
//
// ycbcr_to_rgb.cpp: convertit 3 images pgm en une image ppm

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char *argv[]) {
    char cNomImgLueY[250], cNomImgLueCb[250], cNomImgLueCr[250], cNomImgEcrite[250];
    int nH, nW, nTaille;
    if (argc != 4) {
        printf("Usage: ImageIn_Y.pgm ImageIn_Cb.pgm ImageIn_Cr.pgm\n");
        exit(1);
    }
    sscanf(argv[1], "%s", cNomImgLueY);
    sscanf(argv[2], "%s", cNomImgLueCb);
    sscanf(argv[3], "%s", cNomImgLueCr);
    // rename the output file to be %s_YCbCr-to-rgb.ppm
    // where %s is the input file name without the extension or Y
    char *p = strrchr(cNomImgLueY, '.');
    p-=2;
    if (p != NULL) {
        *p = '\0';
    }
    sprintf(cNomImgEcrite, "%s_YCbCr-to-rgb.ppm", cNomImgLueY);
    sprintf(cNomImgLueY, "%s_Y.pgm", cNomImgLueY);

    OCTET *ImgInY, *ImgInCb, *ImgInCr, *ImgOut;
    lire_nb_lignes_colonnes_image_pgm(cNomImgLueY, &nH, &nW);
    nTaille = nH * nW;
    allocation_tableau(ImgInY, OCTET, nTaille);
    lire_image_pgm(cNomImgLueY, ImgInY, nH * nW);
    allocation_tableau(ImgInCb, OCTET, nTaille);
    lire_image_pgm(cNomImgLueCb, ImgInCb, nH * nW);
    allocation_tableau(ImgInCr, OCTET, nTaille);
    lire_image_pgm(cNomImgLueCr, ImgInCr, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille * 3);

    // Conversion from YCbCr to RGB
    double temp;
    for (int i = 0; i < nTaille; i++) {
        temp = ImgInY[i] + 1.402 * (ImgInCr[i] - 128);
        ImgOut[i * 3] = (temp < 0) ? 0 : ((temp > 255) ? 255 : (int)temp);

        temp = ImgInY[i] - 0.34414 * (ImgInCb[i] - 128) - 0.714414 * (ImgInCr[i] - 128);
        ImgOut[i * 3 + 1] = (temp < 0) ? 0 : ((temp > 255) ? 255 : (int)temp);

        temp = ImgInY[i] + 1.772 * (ImgInCb[i] - 128);
        ImgOut[i * 3 + 2] = (temp < 0) ? 0 : ((temp > 255) ? 255 : (int)temp);
    }


    ecrire_image_ppm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgInY);
    free(ImgInCb);
    free(ImgInCr);
    free(ImgOut);

    return 1;
}