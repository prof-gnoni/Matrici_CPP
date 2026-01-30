//
// Created by Emanuele Gnoni on 30/01/26.
//

#ifndef MATRICI_CPP_MYFUNCTIONS_H
#define MATRICI_CPP_MYFUNCTIONS_H

const int MAX = 20;

// Prototipi delle funzioni
void caricaManuale(int mat[MAX][MAX], int r, int c);
void caricaAutomatico(int mat[MAX][MAX], int r, int c, int min, int max);
void stampaMatrice(int mat[MAX][MAX], int r, int c);
void medieRighe(int mat[MAX][MAX], int r, int c);
void medieColonne(int mat[MAX][MAX], int r, int c);
void calcolaTraccia(int mat[MAX][MAX], int r, int c);
int calcolaDeterminante2x2(int mat[MAX][MAX]);
void estraiVettore(int mat[MAX][MAX], int r, int c);
int contaCifre(int n);
int calcolaLarghezzaMassima(int mat[MAX][MAX], int r, int c);
void stampaMatriceBoxDinamica(int mat[MAX][MAX], int r, int c);
void stampaMatriceBox(int mat[MAX][MAX], int r, int c);

#endif //MATRICI_CPP_MYFUNCTIONS_H