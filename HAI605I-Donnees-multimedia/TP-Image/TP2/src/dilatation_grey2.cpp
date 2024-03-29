//
// Created by Ivan on 10/02/2024.
//

#include "dilatation_grey2.h"

void dilatation_grey(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW, char *cNomImgEcrite) {

    int nTaille = nH * nW;
    // initialize ImgOut to ImgIn
    for (int i = 0; i < nTaille; i++) {
        ImgOut[i] = ImgIn[i];
    }

    int max;

    // excluding edge cases
    for (int i = 1; i < nH-1; i++) {
        for (int j = 1; j < nW-1; j++) {
            // replace pixel with maximum value of its neighbors
            max = 0;
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    if (ImgIn[(i+k)*nW + (j+l)] > max) {
                        max = ImgIn[(i+k)*nW + (j+l)];
                    }
                }
            }
            ImgOut[i*nW + j] = max;
        }
    }

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
    return;
}