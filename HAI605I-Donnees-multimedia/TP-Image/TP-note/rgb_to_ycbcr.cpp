//
// Created by Ivan on 28/02/2024.
//
// rgb_to_ycbcr.cpp: convertit une image ppm en 3 images pgm

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char *argv[]) {
    char cNomImgLue[250], cNomImgEcriteY[250], cNomImgEcriteCb[250], cNomImgEcriteCr[250];
    int nH, nW, nTaille;
    if (argc != 2) {
        printf("Usage: ImageIn.ppm\n");
        exit(1);
    }
    sscanf(argv[1], "%s", cNomImgLue);
    // rename the output files to be %s_Y.pgm, %s_Cb.pgm, %s_Cr.pgm
    char *p = strrchr(cNomImgLue, '.');
    *p = 0;
    sprintf(cNomImgEcriteY, "%s_Y.pgm", cNomImgLue);
    sprintf(cNomImgEcriteCb, "%s_Cb.pgm", cNomImgLue);
    sprintf(cNomImgEcriteCr, "%s_Cr.pgm", cNomImgLue);
    sprintf(cNomImgLue, "%s.ppm", cNomImgLue);

    OCTET *ImgIn, *ImgOutY, *ImgOutCb, *ImgOutCr;

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOutY, OCTET, nTaille);
    allocation_tableau(ImgOutCb, OCTET, nTaille);
    allocation_tableau(ImgOutCr, OCTET, nTaille);

    // Conversion from RGB to YCbCr with immediate capping to 0-255
    double temp;
    for (int i = 0; i < nTaille; i++) {
        temp = 0.299 * ImgIn[i * 3] + 0.587 * ImgIn[i * 3 + 1] + 0.114 * ImgIn[i * 3 + 2];
        ImgOutY[i] = (temp < 0) ? 0 : ((temp > 255) ? 255 : (int)temp);

        temp = 128 - 0.168736 * ImgIn[i * 3] - 0.331264 * ImgIn[i * 3 + 1] + 0.5 * ImgIn[i * 3 + 2];
        ImgOutCb[i] = (temp < 0) ? 0 : ((temp > 255) ? 255 : (int)temp);

        temp = 128 + 0.5 * ImgIn[i * 3] - 0.418688 * ImgIn[i * 3 + 1] - 0.081312 * ImgIn[i * 3 + 2];
        ImgOutCr[i] = (temp < 0) ? 0 : ((temp > 255) ? 255 : (int)temp);
    }

    ecrire_image_pgm(cNomImgEcriteY, ImgOutY, nH, nW);
    ecrire_image_pgm(cNomImgEcriteCb, ImgOutCb, nH, nW);
    ecrire_image_pgm(cNomImgEcriteCr, ImgOutCr, nH, nW);

    free(ImgIn);
    free(ImgOutY);
    free(ImgOutCb);
    free(ImgOutCr);

    return 1;
}