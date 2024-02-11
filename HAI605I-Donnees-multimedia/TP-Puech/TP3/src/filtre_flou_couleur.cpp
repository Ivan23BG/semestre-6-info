//
// Created by Ivan on 06/02/2024.
//
// filtre_flou_couleur.cpp : Floute une image en couleur

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char *argv[]) {
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, nR, nG, nB;

    if (argc != 3) {
        printf("Usage: ImageIn.pgm ImageOut.pgm \n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);

    OCTET *ImgIn, *ImgOut;

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille3);

    // initialise output image to be the same as input
    for (int i = 0; i < nTaille3; i++) {
        ImgOut[i] = ImgIn[i];
    }

    // apply the filter
    for (int i = 1; i < nH-1; i++){
        for (int j = 3; j < (nW-1)*3; j+=3) {
            // p_out(i,j)= ( p(i,j)+p(i-1,j)+p(i+1,j)+p(i,j-3)+p(i,j+3)+p(i-1,j-3)+p(i-1,j+3)+p(i+1,j-3)+p(i+1,j+3) )/9.
            nR = (ImgIn[i * nW*3 + j] + ImgIn[(i-1) * nW*3 + j] + ImgIn[(i+1) * nW*3 + j]
                    + ImgIn[i * nW*3 + j-3] + ImgIn[i * nW*3 + j+3] + ImgIn[(i-1) * nW*3 + j-3]
                    + ImgIn[(i-1) * nW*3 + j+3] + ImgIn[(i+1) * nW*3 + j-3] + ImgIn[(i+1) * nW*3 + j+3]) / 9;
            nG = (ImgIn[i * nW*3 + j + 1] + ImgIn[(i-1) * nW*3 + j + 1] + ImgIn[(i+1) * nW*3 + j + 1]
                    + ImgIn[i * nW*3 + j - 2] + ImgIn[i * nW*3 + j + 4] + ImgIn[(i-1) * nW*3 + j - 2]
                    + ImgIn[(i-1) * nW*3 + j + 4] + ImgIn[(i+1) * nW*3 + j - 2] + ImgIn[(i+1) * nW*3 + j + 4]) / 9;
            nB = (ImgIn[i * nW*3 + j + 2] + ImgIn[(i-1) * nW*3 + j + 2] + ImgIn[(i+1) * nW*3 + j + 2]
                    + ImgIn[i * nW*3 + j - 1] + ImgIn[i * nW*3 + j + 5] + ImgIn[(i-1) * nW*3 + j - 1]
                    + ImgIn[(i-1) * nW*3 + j + 5] + ImgIn[(i+1) * nW*3 + j - 1] + ImgIn[(i+1) * nW*3 + j + 5]) / 9;
            ImgOut[i * nW*3 + j] = nR;
            ImgOut[i * nW*3 + j + 1] = nG;
            ImgOut[i * nW*3 + j + 2] = nB;
        }
    }



    ecrire_image_ppm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn);
    free(ImgOut);

    return 1;
}
