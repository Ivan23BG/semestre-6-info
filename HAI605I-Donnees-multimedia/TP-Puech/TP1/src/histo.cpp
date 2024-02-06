//
// Created by Ivan on 06/02/2024.
//
// histo.cpp : enregistre les donnees d'une image

#include <stdio.h>
#include "../../librairie/image_ppm.h"

int main(int argc, char *argv[]) {
    char cNomImgLue[250], cNomFicSort[255];
    int nH, nW, nTaille;

    if (argc != 2) {
        printf("Usage: ImageIn.pgm \n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sprintf(cNomFicSort, "out/histo.dat");

    OCTET *ImgIn;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);

    FILE *fp = fopen(cNomFicSort, "w+");
    for (int i = 0; i < nTaille; i++) {
        // Afficher à l'écran les donnees de l'image
        printf("%d %d\n", i, ImgIn[i]);
        // Sauvegarder les donnees dans un fichier
        fprintf(fp, "%d %d\n", i, ImgIn[i]);
    }

    fclose(fp);

    free(ImgIn);

    return 1;
}
