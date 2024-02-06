//
// Created by Ivan on 06/02/2024.
//
// histo_couleur.cpp : cree un histogramme d'une image en couleur

#include <stdio.h>
#include "../../librairie/image_ppm.h"

int main(int argc, char *argv[]) {
    char cNomImgLue[250], cNomFicSort[250];
    int nH, nW, nTaille, nR, nG, nB, S_R, S_G, S_B;

    if (argc != 5) {
        printf("Usage: ImageIn.ppm Seuil_rouge Seuil_blue Seuil_vert \n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%d", &S_R);
    sscanf(argv[3], "%d", &S_G);
    sscanf(argv[4], "%d", &S_B);
    sprintf(cNomFicSort, "out/histo_couleur.dat");

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
