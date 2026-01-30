#include <iostream>
#include "myfunctions.h"

// Funzione locale al main per stampare il menu boxato
void stampaMenu() {
    // Usiamo stringhe UTF-8 dirette, più stabili tra Mac e CLion
    std::cout << "\n╔════════════════════════════════╗" << std::endl;
    std::cout << "║       GESTIONE MATRICI         ║" << std::endl;
    std::cout << "╠════════════════════════════════╣" << std::endl;
    std::cout << "║ 1. Caricamento Manuale         ║" << std::endl;
    std::cout << "║ 2. Caricamento Automatico      ║" << std::endl;
    std::cout << "║ 3. Stampa Griglia Completa     ║" << std::endl;
    std::cout << "║ 4. Medie Righe e Colonne       ║" << std::endl;
    std::cout << "║ 0. Esci                        ║" << std::endl;
    std::cout << "╚════════════════════════════════╝" << std::endl;
    std::cout << "Scelta: ";
}

int main() {
    int mat[MAX][MAX];
    int r = 0, c = 0;
    int scelta;

    // Forza il terminale Windows a usare la codifica corretta per i simboli
#ifdef _WIN32
    SetConsoleOutputCP(437); // Imposta la codifica OEM (quella dei char 201, 187, ecc.)
#endif

    // Richiesta righe distinta
    do {
        std::cout << "Inserisci il numero di RIGHE (da 1 a " << MAX << "): ";
        if (!(std::cin >> r)) {
            std::cout << "Errore: inserisci un numero intero!" << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            r = -1; // Forza il prosieguo del loop
            continue;
        }
        if (r <= 0 || r > MAX) {
            std::cout << "Valore non valido! Il limite massimo e' " << MAX << "." << std::endl;
        }
    } while (r <= 0 || r > MAX);

    // Richiesta colonne distinta
    do {
        std::cout << "Inserisci il numero di COLONNE (da 1 a " << MAX << "): ";
        if (!(std::cin >> c)) {
            std::cout << "Errore: inserisci un numero intero!" << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            c = -1;
            continue;
        }
        if (c <= 0 || c > MAX) {
            std::cout << "Valore non valido! Il limite massimo e' " << MAX << "." << std::endl;
        }
    } while (c <= 0 || c > MAX);

    do {
        stampaMenu();
        std::cin >> scelta;

        switch (scelta) {
            case 1:
                caricaManuale(mat, r, c);
                break;
            case 2:
                int rMin, rMax;
                std::cout << "Imposta il limite MINIMO per i numeri casuali: ";
                std::cin >> rMin;
                std::cout << "Imposta il limite MASSIMO per i numeri casuali: ";
                std::cin >> rMax;

                // Piccola correzione di sicurezza se l'utente inverte i valori
                if (rMin > rMax) {
                    int temp = rMin;
                    rMin = rMax;
                    rMax = temp;
                    std::cout << "(I limiti sono stati invertiti automaticamente)" << std::endl;
                }

                caricaAutomatico(mat, r, c, rMin, rMax);
                std::cout << "Matrice generata con successo!" << std::endl;
                break;
            case 3:
                stampaMatriceBoxDinamica(mat, r, c);
                break;
            case 4:
                medieRighe(mat, r, c);
                medieColonne(mat, r, c);
                break;
            case 5:
                calcolaTraccia(mat, r, c);
                break;
            case 6:
                if (r == 2 && c == 2) {
                    std::cout << "Determinante: " << calcolaDeterminante2x2(mat) << std::endl;
                } else {
                    std::cout << "Errore: Funzione disponibile solo per matrici 2x2.\n";
                }
                break;
            case 7:
                estraiVettore(mat, r, c);
                break;
            case 0:
                std::cout << "Chiusura programma. Arrivederci!\n";
                break;
            default:
                std::cout << "Opzione non valida!\n";
        }
    } while (scelta != 0);

    return 0;
}