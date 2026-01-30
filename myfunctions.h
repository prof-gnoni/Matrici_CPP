#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

#include <iostream>

// Costante globale per la dimensione massima
const int MAX = 20; 

// --- PROTOTIPI CARICAMENTO ---
void caricaManuale(int mat[MAX][MAX], int r, int c);
void caricaAutomatico(int mat[MAX][MAX], int r, int c, int min, int max);

// --- PROTOTIPI STAMPA ---
void stampaMatriceBoxDinamica(int mat[MAX][MAX], int r, int c);
void stampaMatriceSemplice(int mat[MAX][MAX], int r, int c);

// --- PROTOTIPI CALCOLO ---
void medieRighe(int mat[MAX][MAX], int r, int c);
void medieColonne(int mat[MAX][MAX], int r, int c);
void calcolaTraccia(int mat[MAX][MAX], int r, int c);
int calcolaDeterminante2x2(int mat[MAX][MAX]);

// --- PROTOTIPI UTILITÀ ---
int contaCifre(int n);
int calcolaLarghezzaMassima(int mat[MAX][MAX], int r, int c);
void estraiVettore(int mat[MAX][MAX], int r, int c);

#endif