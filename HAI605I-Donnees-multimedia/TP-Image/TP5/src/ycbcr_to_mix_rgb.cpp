//
// Created by Ivan on 28/02/2024.
//
// ycbcr_to_mix_rgb.cpp: convertit une image YCbCr en une image 6 images RGB
// en inversant les composantes R, G et B.

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char *argv[]) {
    char cNomImgLueY[250], cNomImgLueCb[250], cNomImgLueCr[250];
    char cNomImgEcriteRGB[250], cNomImgEcriteRBG[250], cNomImgEcriteBRG[250], cNomImgEcriteBGR[250], cNomImgEcriteGRB[250], cNomImgEcriteGBR[250];
    int nH, nW, nTaille;
    if (argc != 4) {
        printf("Usage: ImageIn_Y.pgm ImageIn_Cb.pgm ImageIn_Cr.pgm\n");
        exit(1);
    }
    sscanf(argv[1], "%s", cNomImgLueY);
    sscanf(argv[2], "%s", cNomImgLueCb);
    sscanf(argv[3], "%s", cNomImgLueCr);
    // rename the output files to be %s-RGB.ppm, %s-RBG.ppm, %s-BRG.ppm, %s-BGR.ppm, %s-GRB.ppm, %s-GBR.ppm
    char *p = strrchr(cNomImgLueY, '.');
    p-=2;
    *p = 0;
    sprintf(cNomImgEcriteRGB, "%s_mix-RGB.ppm", cNomImgLueY);
    sprintf(cNomImgEcriteRBG, "%s_mix-RBG.ppm", cNomImgLueY);
    sprintf(cNomImgEcriteBRG, "%s_mix-BRG.ppm", cNomImgLueY);
    sprintf(cNomImgEcriteBGR, "%s_mix-BGR.ppm", cNomImgLueY);
    sprintf(cNomImgEcriteGRB, "%s_mix-GRB.ppm", cNomImgLueY);
    sprintf(cNomImgEcriteGBR, "%s_mix-GBR.ppm", cNomImgLueY);
    sprintf(cNomImgLueY, "%s_Y.pgm", cNomImgLueY);


    OCTET *ImgInY, *ImgInCb, *ImgInCr, *ImgOutRGB, *ImgOutRBG, *ImgOutBRG, *ImgOutBGR, *ImgOutGRB, *ImgOutGBR;
    lire_nb_lignes_colonnes_image_pgm(cNomImgLueY, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgInY, OCTET, nTaille);
    lire_image_pgm(cNomImgLueY, ImgInY, nH * nW);
    allocation_tableau(ImgInCb, OCTET, nTaille);
    lire_image_pgm(cNomImgLueCb, ImgInCb, nH * nW);
    allocation_tableau(ImgInCr, OCTET, nTaille);
    lire_image_pgm(cNomImgLueCr, ImgInCr, nH * nW);

    allocation_tableau(ImgOutRGB, OCTET, nTaille * 3);
    allocation_tableau(ImgOutRBG, OCTET, nTaille * 3);
    allocation_tableau(ImgOutBRG, OCTET, nTaille * 3);
    allocation_tableau(ImgOutBGR, OCTET, nTaille * 3);
    allocation_tableau(ImgOutGRB, OCTET, nTaille * 3);
    allocation_tableau(ImgOutGBR, OCTET, nTaille * 3);

    // Conversion from YCbCr to various RGB colour spaces with immediate capping to 0-255
    double temp;
    for (int i = 0; i < nTaille; i++) {
        temp = ImgInY[i] + 1.402 * (ImgInCr[i] - 128);
        ImgOutRGB[i * 3] = ImgOutRBG[i * 3]
                = ImgOutBRG[i * 3 + 1] = ImgOutBGR[i * 3 + 2]
                        = ImgOutGRB[i * 3 + 1] = ImgOutGBR[i * 3 + 2]
                                = (temp < 0) ? 0 : ((temp > 255) ? 255 : (int)temp);

        temp = ImgInY[i] - 0.344136 * (ImgInCb[i] - 128) - 0.714136 * (ImgInCr[i] - 128);
        ImgOutRGB[i * 3 + 1] = ImgOutRBG[i * 3 + 2]
                = ImgOutBRG[i * 3 + 2] = ImgOutBGR[i * 3 + 1]
                        = ImgOutGRB[i * 3] = ImgOutGBR[i * 3]
                                = (temp < 0) ? 0 : ((temp > 255) ? 255 : (int)temp);
        temp = ImgInY[i] + 1.772 * (ImgInCb[i] - 128);

        ImgOutRGB[i * 3 + 2] = ImgOutRBG[i * 3 + 1]
                = ImgOutBRG[i * 3] = ImgOutBGR[i * 3]
                        = ImgOutGRB[i * 3 + 2] = ImgOutGBR[i * 3 + 1]
                                = (temp < 0) ? 0 : ((temp > 255) ? 255 : (int)temp);
    }


    ecrire_image_ppm(cNomImgEcriteRGB, ImgOutRGB, nH, nW);
    ecrire_image_ppm(cNomImgEcriteRBG, ImgOutRBG, nH, nW);
    ecrire_image_ppm(cNomImgEcriteBRG, ImgOutBRG, nH, nW);
    ecrire_image_ppm(cNomImgEcriteBGR, ImgOutBGR, nH, nW);
    ecrire_image_ppm(cNomImgEcriteGRB, ImgOutGRB, nH, nW);
    ecrire_image_ppm(cNomImgEcriteGBR, ImgOutGBR, nH, nW);

    free(ImgInY);
    free(ImgInCb);
    free(ImgInCr);
    free(ImgOutRGB);
    free(ImgOutRBG);
    free(ImgOutBRG);
    free(ImgOutBGR);
    free(ImgOutGRB);
    free(ImgOutGBR);

    return 1;
}