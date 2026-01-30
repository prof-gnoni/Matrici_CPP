#include <iostream>
#include "myfunctions.h"

#ifdef _WIN32
#include <windows.h>
#endif

void stampaMenu() {
#ifdef _WIN32
    // Codici Extended ASCII per Windows (Code Page 437)
    unsigned char TL = 201; unsigned char TR = 187;
    unsigned char BL = 200; unsigned char BR = 188;
    unsigned char H  = 205; unsigned char V  = 186;
    unsigned char ML = 204; unsigned char MR = 185;
#else
    // Simboli UTF-8 per Mac
    const char* TL = "╔"; const char* TR = "╗";
    const char* BL = "╚"; const char* BR = "╝";
    const char* H  = "═"; const char* V  = "║";
    const char* ML = "╠"; const char* MR = "╣";
#endif

    std::cout << "\n" << TL;
    for(int i=0; i<32; i++) std::cout << H;
    std::cout << TR << std::endl;

    std::cout << V << "       GESTIONE MATRICI         " << V << std::endl;

    std::cout << ML;
    for(int i=0; i<32; i++) std::cout << H;
    std::cout << MR << std::endl;

    std::cout << V << " 1. Caricamento Manuale         " << V << std::endl;
    std::cout << V << " 2. Caricamento Automatico      " << V << std::endl;
    std::cout << V << " 3. Stampa Boxata (Griglia)     " << V << std::endl;
    std::cout << V << " 4. Stampa Semplice (Tabella)   " << V << std::endl;
    std::cout << V << " 5. Medie Righe (Colonna Box)   " << V << std::endl;
    std::cout << V << " 6. Medie Colonne (Riga Box)    " << V << std::endl;
    std::cout << V << " 7. Calcola Traccia             " << V << std::endl;
    std::cout << V << " 8. Calcola Determinante (2x2)  " << V << std::endl;
    std::cout << V << " 9. Estrai Riga o Colonna       " << V << std::endl;
    std::cout << V << " 0. Esci                        " << V << std::endl;

    std::cout << BL;
    for(int i=0; i<32; i++) std::cout << H;
    std::cout << BR << std::endl;

    std::cout << "Scelta: ";
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(437);
#endif

    int mat[MAX][MAX];
    int r, c, scelta;

    std::cout << "--- Configurazione Iniziale ---" << std::endl;

    do {
        std::cout << "Inserisci numero righe (1-" << MAX << "): ";
        if (!(std::cin >> r)) { std::cin.clear(); std::cin.ignore(1000, '\n'); r = -1; }
    } while (r <= 0 || r > MAX);

    do {
        std::cout << "Inserisci numero colonne (1-" << MAX << "): ";
        if (!(std::cin >> c)) { std::cin.clear(); std::cin.ignore(1000, '\n'); c = -1; }
    } while (c <= 0 || c > MAX);

    do {
        stampaMenu();
        std::cin >> scelta;

        switch (scelta) {
            case 1:
                caricaManuale(mat, r, c);
                break;
            case 2: {
                int rMin, rMax;
                std::cout << "Imposta il limite MINIMO per i numeri casuali: ";
                std::cin >> rMin;
                std::cout << "Imposta il limite MASSIMO per i numeri casuali: ";
                std::cin >> rMax;

                if (rMin > rMax) {
                    int temp = rMin;
                    rMin = rMax;
                    rMax = temp;
                    std::cout << "(I limiti sono stati invertiti automaticamente)" << std::endl;
                }
                caricaAutomatico(mat, r, c, rMin, rMax);
                break;
            }
            case 3:
                stampaMatriceBoxDinamica(mat, r, c);
                break;
            case 4:
                stampaMatriceSemplice(mat, r, c);
                break;
            case 5:
                medieRighe(mat, r, c);
                break;
            case 6:
                medieColonne(mat, r, c);
                break;
            case 7:
                calcolaTraccia(mat, r, c);
                break;
            case 8:
                if (r == 2 && c == 2) {
                    std::cout << "\nDeterminante (2x2): " << calcolaDeterminante2x2(mat) << std::endl;
                } else if (r != c) {
                    std::cout << "\nERRORE: Il determinante e' definito solo per matrici quadrate!" << std::endl;
                } else {
                    std::cout << "\nINFO: Al momento gestisco solo determinanti per matrici 2x2." << std::endl;
                }
                break;
            case 9:
                estraiVettore(mat, r, c);
                break;
            case 0:
                break;
            default:
                std::cout << "Scelta non valida." << std::endl;
        }
    } while (scelta != 0);

    return 0;
}