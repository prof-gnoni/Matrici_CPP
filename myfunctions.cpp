#include "myfunctions.h"
#include <iostream>
#include <cstdlib> // Per rand() e srand()
#include <ctime>   // Per time()

// 1. CONTEGGIO CIFRE (Algoritmo per la terza superiore)
int contaCifre(int n) {
    if (n == 0) return 1;
    if (n < 0) n = -n; // Lavoriamo sul valore assoluto

    int contatore = 0;
    while (n > 0) {
        n = n / 10; // Divisione intera per rimuovere l'ultima cifra
        contatore++;
    }
    return contatore;
}

// 2. CALCOLO LARGHEZZA MASSIMA (Considerando il segno meno)
int calcolaLarghezzaMassima(int mat[MAX][MAX], int r, int c) {
    int maxIngombro = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            int attuale = contaCifre(mat[i][j]);
            if (mat[i][j] < 0) attuale++; // Aggiunge spazio per il '-'

            if (attuale > maxIngombro) maxIngombro = attuale;
        }
    }
    return maxIngombro;
}

// 3. CARICAMENTO MANUALE
void caricaManuale(int mat[MAX][MAX], int r, int c) {
    std::cout << "\n--- Inserimento Manuale (" << r << "x" << c << ") ---\n";
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            std::cout << "Elemento [" << i << "][" << j << "]: ";
            while (!(std::cin >> mat[i][j])) {
                std::cout << "Errore! Inserisci un numero intero: ";
                std::cin.clear();
                std::cin.ignore(1000, '\n');
            }
        }
    }
}

// 4. CARICAMENTO AUTOMATICO
void caricaAutomatico(int mat[MAX][MAX], int r, int c, int min, int max) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            mat[i][j] = rand() % (max - min + 1) + min;
        }
    }
}

// 5. STAMPA BOXATA DINAMICA (Cross-Platform Mac/Windows)
void stampaMatriceBoxDinamica(int mat[MAX][MAX], int r, int c) {
    int larz = calcolaLarghezzaMassima(mat, r, c) + 2;

    // Definiamo i pezzi della griglia (versione universale Mac/Linux)
    // Per Windows in lab, se non li vedi, usa +, -, |
    const char* TL = "╔"; const char* TR = "╗";
    const char* BL = "╚"; const char* BR = "╝";
    const char* H  = "═"; const char* V  = "║";
    const char* TM = "╦"; const char* BM = "╩";
    const char* MM = "╬"; const char* ML = "╠";
    const char* MR = "╣";

    // 1. BORDO SUPERIORE
    std::cout << TL;
    for (int j = 0; j < c; j++) {
        for (int k = 0; k < larz; k++) std::cout << H;
        if (j < c - 1) std::cout << TM;
    }
    std::cout << TR << std::endl;

    // 2. CORPO MATRICE
    for (int i = 0; i < r; i++) {
        std::cout << V;
        for (int j = 0; j < c; j++) {
            // Allineamento centrato/destra manuale
            int n = mat[i][j];
            int cifre = contaCifre(n);
            if (n < 0) cifre++;

            int spaziTotali = larz - cifre;
            int spaziDx = spaziTotali / 2;
            int spaziSx = spaziTotali - spaziDx;

            for (int k = 0; k < spaziSx; k++) std::cout << " ";
            std::cout << n;
            for (int k = 0; k < spaziDx; k++) std::cout << " ";
            std::cout << V;
        }
        std::cout << std::endl;

        // 3. DIVISORE ORIZZONTALE (solo se non è l'ultima riga)
        if (i < r - 1) {
            std::cout << ML;
            for (int j = 0; j < c; j++) {
                for (int k = 0; k < larz; k++) std::cout << H;
                if (j < c - 1) std::cout << MM;
            }
            std::cout << MR << std::endl;
        }
    }

    // 4. BORDO INFERIORE
    std::cout << BL;
    for (int j = 0; j < c; j++) {
        for (int k = 0; k < larz; k++) std::cout << H;
        if (j < c - 1) std::cout << BM;
    }
    std::cout << BR << std::endl;
}

// 6. MEDIE, TRACCIA, DETERMINANTE E VETTORI
void medieRighe(int mat[MAX][MAX], int r, int c) {
    double medie[MAX];
    int larz = 8;

    // Calcolo
    for (int i = 0; i < r; i++) {
        double somma = 0;
        for (int j = 0; j < c; j++) somma += mat[i][j];
        medie[i] = somma / c;
    }

    std::cout << "\n--- MEDIE RIGHE (Vettore Colonna) ---\n";
    const char* TL = "╔"; const char* TR = "╗"; const char* BL = "╚"; const char* BR = "╝";
    const char* H  = "═"; const char* V  = "║";
    const char* ML = "╠"; const char* MR = "╣";

    // Bordo superiore
    std::cout << TL;
    for (int k = 0; k < larz; k++) std::cout << H;
    std::cout << TR << std::endl;

    // Righe
    for (int i = 0; i < r; i++) {
        std::cout << V;
        printf(" %6.2f ", medie[i]);
        std::cout << V << std::endl;

        // Divisore intermedio
        if (i < r - 1) {
            std::cout << ML;
            for (int k = 0; k < larz; k++) std::cout << H;
            std::cout << MR << std::endl;
        }
    }

    // Bordo inferiore
    std::cout << BL;
    for (int k = 0; k < larz; k++) std::cout << H;
    std::cout << BR << std::endl;
}

void medieColonne(int mat[MAX][MAX], int r, int c) {
    double medie[MAX];
    int larz = 8; // Larghezza fissa per le medie (es. 00.00)

    // Calcolo
    for (int j = 0; j < c; j++) {
        double somma = 0;
        for (int i = 0; i < r; i++) somma += mat[i][j];
        medie[j] = somma / r;
    }

    std::cout << "\n--- MEDIE COLONNE (Vettore Riga) ---\n";
    // Disegno griglia orizzontale
    const char* TL = "╔"; const char* TR = "╗"; const char* BL = "╚"; const char* BR = "╝";
    const char* H  = "═"; const char* V  = "║"; const char* TM = "╦"; const char* BM = "╩";

    // Bordo sopra
    std::cout << TL;
    for (int j = 0; j < c; j++) {
        for (int k = 0; k < larz; k++) std::cout << H;
        if (j < c - 1) std::cout << TM;
    }
    std::cout << TR << std::endl;

    // Contenuto (Medie)
    std::cout << V;
    for (int j = 0; j < c; j++) {
        printf(" %6.2f ", medie[j]); // Stampa il double con 2 decimali
        std::cout << V;
    }
    std::cout << std::endl;

    // Bordo sotto
    std::cout << BL;
    for (int j = 0; j < c; j++) {
        for (int k = 0; k < larz; k++) std::cout << H;
        if (j < c - 1) std::cout << BM;
    }
    std::cout << BR << std::endl;
}

void calcolaTraccia(int mat[MAX][MAX], int r, int c) {
    if (r != c) {
        std::cout << "Matrice non quadrata: traccia non definita.\n";
        return;
    }
    int traccia = 0;
    for (int i = 0; i < r; i++) traccia += mat[i][i];
    std::cout << "Traccia: " << traccia << std::endl;
}

int calcolaDeterminante2x2(int mat[MAX][MAX]) {
    return (mat[0][0] * mat[1][1]) - (mat[0][1] * mat[1][0]);
}

void estraiVettore(int mat[MAX][MAX], int r, int c) {
    int scelta, indice;
    std::cout << "1. Estrai Riga | 2. Estrai Colonna: ";
    std::cin >> scelta;
    std::cout << "Indice da estrarre: ";
    std::cin >> indice;

    if (scelta == 1 && indice < r) {
        for (int j = 0; j < c; j++) std::cout << mat[indice][j] << " ";
    } else if (scelta == 2 && indice < c) {
        for (int i = 0; i < r; i++) std::cout << mat[i][indice] << " ";
    } else {
        std::cout << "Indice errato!";
    }
    std::cout << std::endl;
}