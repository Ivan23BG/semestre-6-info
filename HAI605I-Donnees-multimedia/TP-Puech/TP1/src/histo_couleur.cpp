//
// Created by Ivan on 06/02/2024.
//
// histo_couleur.cpp : cree un histogramme d'une image en couleur

#include <stdio.h>
#include "../../librairie/image_ppm.h"

int main(int argc, char *argv[]) {
    char cNomImgLue[250], cNomFicSort[250];
    int nH, nW, nTaille, nR, nG, nB;

    if (argc != 3) {
        printf("Usage: ImageIn.ppm FicOut.dat\n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomFicSort);

    OCTET *ImgIn;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);

    FILE *fp = fopen(cNomFicSort, "w+");
    for (int i = 0; i < nTaille3; i += 3) {
        // Sauvegarder les donnees dans un fichier
        fprintf(fp, "%d %d %d %d\n", (i+3) / 3 - 1, ImgIn[i], ImgIn[i + 1], ImgIn[i + 2]);
    }

    fclose(fp);
    free(ImgIn);
    return 1;
}
