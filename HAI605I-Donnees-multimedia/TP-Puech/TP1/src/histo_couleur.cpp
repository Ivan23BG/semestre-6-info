//
// Created by Ivan on 06/02/2024.
//
// histo_couleur.cpp : enregistre les donnees d'une image en couleur

#include <stdio.h>
#include "../../librairie/image_ppm.h"

int main(int argc, char *argv[]) {
    char cNomImgLue[250], cNomFicSort[255];
    int nH, nW, nTaille;

    if (argc < 2 || argc > 3) {
        printf("Usage: ImageIn.ppm Optional-FicOut.dat\n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    if (argc == 3) {
        sscanf(argv[2], "%s", cNomFicSort);
    } else {
        sprintf(cNomFicSort, "out/histo-col.dat");
    }

    OCTET *ImgIn;

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);

    // initialize tabs to 0
    int tabR[256], tabG[256], tabB[256];
    for (int i = 0; i < 256; i++) {
        tabR[i] = 0;
        tabG[i] = 0;
        tabB[i] = 0;
    }

    // Open file for writing
    FILE *fp = fopen(cNomFicSort, "w+");

    // Update array
    for (int i = 0; i < nTaille3; i += 3) {
        tabR[ImgIn[i]]++;
        tabG[ImgIn[i+1]]++;
        tabB[ImgIn[i+2]]++;
    }

    // Output data
    for (int i = 0; i < 256; i++) {
        // printf("%d %d %d %d\n", i, tabR[i], tabG[i], tabB[i]);
        fprintf(fp, "%d %d %d %d\n", i, tabR[i], tabG[i], tabB[i]);
    }

    fclose(fp);

    free(ImgIn);

    return 1;
}
