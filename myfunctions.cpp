#include "myfunctions.h"
#include <iostream>
#include <iomanip>
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

    // --- SEZIONE CROSS-PLATFORM PER I SIMBOLI ---
#ifdef _WIN32
    // Codici Extended ASCII (PC-8 / CP437) per Windows Lab
    unsigned char TL = 201; unsigned char TR = 187;
    unsigned char BL = 200; unsigned char BR = 188;
    unsigned char H  = 205; unsigned char V  = 186;
    unsigned char TM = 203; unsigned char BM = 202;
    unsigned char MM = 206; unsigned char ML = 204;
    unsigned char MR = 185;
#else
    // Stringhe UTF-8 per il tuo Mac
    const char* TL = "╔"; const char* TR = "╗";
    const char* BL = "╚"; const char* BR = "╝";
    const char* H  = "═"; const char* V  = "║";
    const char* TM = "╦"; const char* BM = "╩";
    const char* MM = "╬"; const char* ML = "╠";
    const char* MR = "╣";
#endif

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

        // 3. DIVISORE ORIZZONTALE (intermedio)
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
    int larzIntera = 8; // Spazio per il numero (es: 123.45)

    for (int i = 0; i < r; i++) {
        double somma = 0;
        for (int j = 0; j < c; j++) somma += mat[i][j];
        medie[i] = somma / c;
    }

    std::cout << "\n--- MEDIE RIGHE ---\n";

#ifdef _WIN32
    unsigned char TL=201, TR=187, BL=200, BR=188, H=205, V=186, ML=204, MR=185;
#else
    const char* TL="╔"; const char* TR="╗"; const char* BL="╚"; const char* BR="╝";
    const char* H ="═"; const char* V ="║"; const char* ML="╠"; const char* MR="╣";
#endif

    // La larghezza del bordo orizzontale deve includere i 2 spazi di padding (+2)
    int larzTotale = larzIntera + 2;

    std::cout << TL;
    for (int k = 0; k < larzTotale; k++) std::cout << H;
    std::cout << TR << std::endl;

    for (int i = 0; i < r; i++) {
        std::cout << V << " "; // Padding Sinistro
        std::cout << std::fixed << std::setprecision(2) << std::setw(larzIntera) << medie[i];
        std::cout << " " << V << std::endl; // Padding Destro

        if (i < r - 1) {
            std::cout << ML;
            for (int k = 0; k < larzTotale; k++) std::cout << H;
            std::cout << MR << std::endl;
        }
    }

    std::cout << BL;
    for (int k = 0; k < larzTotale; k++) std::cout << H;
    std::cout << BR << std::endl;
}

void medieColonne(int mat[MAX][MAX], int r, int c) {
    double medie[MAX];
    int larzIntera = 8;
    int larzTotale = larzIntera + 2; // Numero + 2 spazi di padding

    for (int j = 0; j < c; j++) {
        double somma = 0;
        for (int i = 0; i < r; i++) somma += mat[i][j];
        medie[j] = somma / r;
    }

    std::cout << "\n--- MEDIE COLONNE ---\n";

#ifdef _WIN32
    unsigned char TL=201, TR=187, BL=200, BR=188, H=205, V=186, TM=203, BM=202;
#else
    const char* TL="╔"; const char* TR="╗"; const char* BL="╚"; const char* BR="╝";
    const char* H ="═"; const char* V ="║"; const char* TM="╦"; const char* BM="╩";
#endif

    std::cout << TL;
    for (int j = 0; j < c; j++) {
        for (int k = 0; k < larzTotale; k++) std::cout << H;
        if (j < c - 1) std::cout << TM;
    }
    std::cout << TR << std::endl;

    std::cout << V;
    for (int j = 0; j < c; j++) {
        std::cout << " "; // Padding Sinistro
        std::cout << std::fixed << std::setprecision(2) << std::setw(larzIntera) << medie[j];
        std::cout << " " << V; // Padding Destro
    }
    std::cout << std::endl;

    std::cout << BL;
    for (int j = 0; j < c; j++) {
        for (int k = 0; k < larzTotale; k++) std::cout << H;
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

void stampaMatriceSemplice(int mat[MAX][MAX], int r, int c) {
    // 1. Troviamo l'ingombro massimo (es. 5 se il numero più lungo è -100)
    int larz = calcolaLarghezzaMassima(mat, r, c);

    // Aggiungiamo un po' di spazio extra tra le colonne (padding)
    int spaziatura = larz + 3;

    std::cout << "\n--- Visualizzazione Tabellare (Allineata a Destra) ---\n";

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            // std::setw(n) riserva n spazi e allinea a DESTRA il valore successivo
            std::cout << std::right << std::setw(spaziatura) << mat[i][j];
        }
        std::cout << std::endl; // Vai a capo alla fine di ogni riga
    }
    std::cout << "------------------------------------------------------\n";
}

void estraiVettore(int mat[MAX][MAX], int r, int c) {
    int tipo, indice;

    do {
        std::cout << "Vuoi estrarre una 1. RIGA o una 2. COLONNA? ";
        std::cin >> tipo;
    } while (tipo != 1 && tipo != 2);

    if (tipo == 1) {
        do {
            std::cout << "Inserisci l'indice della riga (0-" << r-1 << "): ";
            std::cin >> indice;
        } while (indice < 0 || indice >= r);

        std::cout << "Riga " << indice << ": ";
        for (int j = 0; j < c; j++) std::cout << mat[indice][j] << " ";
    } else {
        do {
            std::cout << "Inserisci l'indice della colonna (0-" << c-1 << "): ";
            std::cin >> indice;
        } while (indice < 0 || indice >= c);

        std::cout << "Colonna " << indice << ": ";
        for (int i = 0; i < r; i++) std::cout << mat[i][indice] << " ";
    }
    std::cout << std::endl;
}