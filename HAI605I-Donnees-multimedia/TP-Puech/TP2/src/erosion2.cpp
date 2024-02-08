//
// Created by Ivan on 08/02/2024.
//
// erosion2.cpp : Erode une image en niveau de gris

#include <stdio.h>
#include "erosion2.h"

void erosion(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW, char *cNomImgEcrite) {
    int nTaille = nH * nW;
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
    return;
}