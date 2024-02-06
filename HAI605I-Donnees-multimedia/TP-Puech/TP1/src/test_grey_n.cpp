//
// Created by Ivan on 06/02/2024.
//
// test_grey_n.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "../../librairie/image_ppm.h"

int main(int argc, char *argv[]) {
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, Sn;

    if (argc != 4) {
        printf("Usage: ImageIn.pgm ImageOut.pgm Nombre-de-seuils \n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);
    sscanf(argv[3], "%d", &Sn);
    /* ensure Sn is at least equal to 2 */
    while (Sn < 2) {
        printf("Nombre de seuils doit être supérieur ou égal à 2, réessayez\n");
        scanf("%d", &Sn);
    }

    OCTET *ImgIn, *ImgOut;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);

    //   for (int i=0; i < nTaille; i++)
    // {
    //  if ( ImgIn[i] < S) ImgOut[i]=0; else ImgOut[i]=255;
    //  }
    int tab_seuil[Sn];
    printf("Inserez les %d seuils par ordre croissant\n", Sn);
    for (int i = 0; i < Sn; i++) {
        scanf("%d", &tab_seuil[i]);
    }
    /* initialise output image to 255 */
    for (int i = 0; i < nTaille; i++)
        ImgOut[i] = 255;
    for (int i = 0; i < nH; i++)
        for (int j = 0; j < nW; j++) {
            for (int k = 0; k < Sn; k++) {
                if (ImgIn[i * nW + j] < tab_seuil[k]) {
                    ImgOut[i * nW + j] = k * 255 / (Sn - 1);
                    break;
                }
            }
        }

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn);
    free(ImgOut);

    return 1;
}
