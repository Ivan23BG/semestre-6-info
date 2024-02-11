//
// Created by Ivan on 06/02/2024.
//
// filtre_flou1.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char *argv[]) {
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille;

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

    // initialise output image to be the same as input
    for (int i = 0; i < nTaille; i++) {
        ImgOut[i] = ImgIn[i];
    }

    // apply the filter
    for (int i = 1; i < nH-1; i++){
        for (int j = 1; j < nW-1; j++) {
            // p_out(i,j)= ( p(i,j)+p(i-1,j)+p(i+1,j)+p(i,j-1)+p(i,j+1) )/5.
            ImgOut[i * nW + j] = (ImgIn[i * nW + j]
                    + ImgIn[(i-1) * nW + j]
                    + ImgIn[(i+1) * nW + j]
                    + ImgIn[i * nW + j-1]
                    + ImgIn[i * nW + j+1]) / 5;
        }
    }

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn);
    free(ImgOut);

    return 1;
}
