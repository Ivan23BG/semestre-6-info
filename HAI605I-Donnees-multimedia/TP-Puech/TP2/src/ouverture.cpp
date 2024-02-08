//
// Created by Ivan on 08/02/2024.
//
// ouverture.cpp : Erode une image en niveau de gris puis dilate le resultat

#include <stdio.h>
#include "image_ppm.h"

// include dilatation and erosion
#include "dilatation2.h"
#include "erosion2.h"

// combine dilatation and erosion

int main(int argc, char *argv[]) {
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille;

    if (argc != 3) {
        printf("Usage: ImageIn.pgm ImageOut.pgm\n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);

    OCTET *ImgIn, *ImgOut, *ImgTmp;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);
    allocation_tableau(ImgTmp, OCTET, nTaille);

    // initialize ImgOut to ImgIn
    for (int i = 0; i < nTaille; i++) {
        ImgOut[i] = ImgIn[i];
    }
    // create temporary image
    for (int i = 0; i < nTaille; i++) {
        ImgTmp[i] = ImgIn[i];
    }
    // create temporary image name
    char cNomImgTmp[250];
    sprintf(cNomImgTmp, "%s-tmp.pgm", cNomImgEcrite);

    // erosion
    erosion(ImgIn, ImgTmp, nH, nW, cNomImgTmp);
    // dilatation
    dilatation(ImgTmp, ImgOut, nH, nW, cNomImgEcrite);

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn);
    free(ImgOut);
    free(ImgTmp);

    return 1;
}