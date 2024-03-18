//
// Created by Ivan on 28/02/2024.
//
// eqm_pgm.cpp : calcule l'erreur quadratique moyenne entre deux images

#include <stdio.h>
#include "image_ppm.h"
#include <math.h>

int main(int argc, char *argv[]) {
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille;


    sscanf(argv[1], "%s", cNomImgLue);
    char *p = strrchr(cNomImgLue, '.');
    *p = 0;
    sprintf(cNomImgEcrite, "%s_egal.pgm", cNomImgLue);
    sprintf(cNomImgLue, "%s.pgm", cNomImgLue);

    OCTET *ImgIn, *ImgOut;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);

    allocation_tableau(ImgOut, OCTET, nTaille);

    // calcul de l'erreur quadratique moyenne
    // initialize tab to 0
    double tab[256];
    double F[256];
    for (int i = 0; i < 256; i++) {
        tab[i] = 0;
        F[i] = 0;
    }

    // Update array
    for (int i = 0; i < nTaille; i++) {
        tab[ImgIn[i]] += 1;
    }
    for (int i = 0; i < 256; i++) {
        tab[i] /= nTaille;
    }
    F[0] = tab[0];
    for (int i = 1; i < 256; i++) {
        F[i] = F[i-1] + tab[i];
    }
    

    // Output data
    double temp;
    for (int i = 0; i < nTaille; i++) {
        temp = F[ImgIn[i]] * 255;
        temp = floor(temp);
        ImgOut[i] = (temp < 0) ? 0 : ((temp > 255) ? 255 : (int)temp);

    }

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);

    free(ImgIn);
    free(ImgOut);

    return 1;
}
