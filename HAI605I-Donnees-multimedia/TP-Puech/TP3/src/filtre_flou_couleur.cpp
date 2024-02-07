//
// Created by Ivan on 06/02/2024.
//
// test_grey_n.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "../../librairie/image_ppm.h"

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
    for (int i = 0; i < nTaille; i++) {
        ImgOut[i] = ImgIn[i];
    }


    for (int i=3; i < (nW*3)-3; i+=3)
    {
        for (int j=1; j < nH-1; j+=1){
            ImgOut[j*nW*3+i] = (ImgIn[j*nW*3+i]+ImgIn[(j-1)*nW*3+i]+ImgIn[(j+1)*nW*3+i]
            +ImgIn[j*nW*3+(i-3)]+ImgIn[(j-1)*nW*3+(i-3)]+ImgIn[(j+1)*nW*3+(i-3)]
            +ImgIn[j*nW*3+(i+3)]+ImgIn[(j-1)*nW*3+(i+3)]+ImgIn[(j+1)*nW*3+(i+3)])/9;

            ImgOut[j*nW*3+i+1] = (ImgIn[j*nW*3+i+1]+ImgIn[(j-1)*nW*3+i+1]+ImgIn[(j+1)*nW*3+i+1]
            +ImgIn[j*nW*3+(i+1-3)]+ImgIn[(j-1)*nW*3+(i+1-3)]+ImgIn[(j+1)*nW*3+(i+1-3)]
            +ImgIn[j*nW*3+(i+1+3)]+ImgIn[(j-1)*nW*3+(i+1+3)]+ImgIn[(j+1)*nW*3+(i+1+3)])/9;

            ImgOut[j*nW*3+i+2] = (ImgIn[j*nW*3+i+2]+ImgIn[(j-1)*nW*3+i+2]+ImgIn[(j+1)*nW*3+i+2]
            +ImgIn[j*nW*3+(i+2-3)]+ImgIn[(j-1)*nW*3+(i+2-3)]+ImgIn[(j+1)*nW*3+(i+2-3)]
            +ImgIn[j*nW*3+(i+2+3)]+ImgIn[(j-1)*nW*3+(i+2+3)]+ImgIn[(j+1)*nW*3+(i+2+3)])/9;
            
        }
    }

    ecrire_image_ppm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn);
    free(ImgOut);

    return 1;
}
