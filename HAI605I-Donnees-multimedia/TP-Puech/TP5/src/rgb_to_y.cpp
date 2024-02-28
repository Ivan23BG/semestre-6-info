//
// Created by Ivan on 28/02/2024.
//
// rgb_to_y.cpp is a program that converts an image from RGB to Y colour space.

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char *argv[]) {
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille;
    if (argc != 2) {
        printf("Usage: ImageIn.pgm\n");
        exit(1);
    }
    sscanf(argv[1], "%s", cNomImgLue);
    // rename the output file to %s_rgb-to-y.pgm
    char *p = strrchr(cNomImgLue, '.');
    *p = 0;
    sprintf(cNomImgEcrite, "%s_rgb-to-y.pgm", cNomImgLue);
    sprintf(cNomImgLue, "%s.ppm", cNomImgLue);


    OCTET *ImgIn, *ImgOut;

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);

    // Conversion from RGB to Y with immediate capping to 0-255
    double temp;
    for (int i = 0; i < nTaille; i++) {
        temp = 0.299 * ImgIn[i * 3] + 0.587 * ImgIn[i * 3 + 1] + 0.114 * ImgIn[i * 3 + 2];
        ImgOut[i] = (temp < 0) ? 0 : ((temp > 255) ? 255 : (int)temp);
    }

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn);
    free(ImgOut);
    return 1;
}