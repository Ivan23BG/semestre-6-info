//
// Created by Ivan on 10/02/2024.
//

#include "erosion_grey2.h"

void erosion_grey(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW, char *cNomImgEcrite) {

    int nTaille = nH * nW;
    // initialize ImgOut to ImgIn
    for (int i = 0; i < nTaille; i++) {
        ImgOut[i] = ImgIn[i];
    }
    int min;

    // excluding edge cases
    for (int i = 1; i < nH-1; i++) {
        for (int j = 1; j < nW - 1; j++) {
            // replace pixel with minimum value of its neighbors
            min = 255;
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    if (ImgIn[(i + k) * nW + (j + l)] < min) {
                        min = ImgIn[(i + k) * nW + (j + l)];
                    }
                }
            }
            ImgOut[i * nW + j] = min;
        }
    }

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
    return;
}