#include <iostream>
#include "myfunctions.h"

#ifdef _WIN32
#include <windows.h>
#endif

void stampaMenu() {
    std::cout << "\n╔════════════════════════════════╗" << std::endl;
    std::cout << "║       GESTIONE MATRICI         ║" << std::endl;
    std::cout << "╠════════════════════════════════╣" << std::endl;
    std::cout << "║ 1. Caricamento Manuale         ║" << std::endl;
    std::cout << "║ 2. Caricamento Automatico      ║" << std::endl; // Spazi corretti
    std::cout << "║ 3. Stampa Boxata (Griglia)     ║" << std::endl;
    std::cout << "║ 4. Stampa Semplice (Tabella)   ║" << std::endl;
    std::cout << "║ 5. Medie Righe (Colonna Box)   ║" << std::endl;
    std::cout << "║ 6. Medie Colonne (Riga Box)    ║" << std::endl;
    std::cout << "║ 7. Calcola Traccia             ║" << std::endl;
    std::cout << "║ 8. Calcola Determinante (2x2)  ║" << std::endl;
    std::cout << "║ 9. Estrai Riga o Colonna       ║" << std::endl;
    std::cout << "║ 0. Esci                        ║" << std::endl;
    std::cout << "╚════════════════════════════════╝" << std::endl;
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