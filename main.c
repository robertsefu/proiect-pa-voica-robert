#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUMAR_HOMARI 100 // Definim o constanta pentru numarul maxim de homari

// Functie pentru a returna valoarea maxima dintre doua numere
int obtine_valoare_maxima(int valoare1, int valoare2) {
    return (valoare1 > valoare2) ? valoare1 : valoare2;
}

// Functie pentru a afisa homarii inclusi in plasa
void afisare_homari_selectati(int** matrice_dinamica, int* dimensiuni_homari, int* valori_homari, int total_homari, int capacitate_plasa) {
    printf("Homarii inclusi in plasa sunt:\n");
    int homar_curent = total_homari, capacitate_curenta = capacitate_plasa;
    while (homar_curent > 0 && capacitate_curenta > 0) {
        if (matrice_dinamica[homar_curent][capacitate_curenta] != matrice_dinamica[homar_curent - 1][capacitate_curenta]) { // Verificam daca homarul curent este inclus in solutia optima
            printf("Homar %d: Dimensiune = %d, Valoare = %d\n", homar_curent, dimensiuni_homari[homar_curent], valori_homari[homar_curent]);
            capacitate_curenta -= dimensiuni_homari[homar_curent]; // Reducem capacitatea plasei cu dimensiunea homarului inclus
        }
        homar_curent--; // Trecem la homarul anterior
    }
}

int main() {
    srand(time(NULL)); // Initializam generatorul de numere aleatorii

    int total_homari = MAX_NUMAR_HOMARI; // Setam numarul total de homari la maxim
    int capacitate_maxima_plasa = 1000 + rand() % 1000; // Generam o capacitate aleatorie intre 1000 si 1999

    int* dimensiuni_homari = (int*)malloc((total_homari + 1) * sizeof(int));
    int* valori_homari = (int*)malloc((total_homari + 1) * sizeof(int));
    int** matrice_dinamica = (int**)malloc((total_homari + 1) * sizeof(int*));
    for (int i = 0; i <= total_homari; i++) {
        matrice_dinamica[i] = (int*)malloc((capacitate_maxima_plasa + 1) * sizeof(int));
    }

    // Generam dimensiuni aleatorii intre 1 si 50 pentru fiecare homar
    for (int index_homar = 1; index_homar <= total_homari; index_homar++) {
        dimensiuni_homari[index_homar] = 1 + rand() % 50;
    }

    // Generam valori aleatorii intre 10 si 100 pentru fiecare homar
    for (int index_homar = 1; index_homar <= total_homari; index_homar++) {
        valori_homari[index_homar] = 10 + rand() % 91;
    }

    // Populam matricea dinamica cu valorile maxime obtinute pentru fiecare capacitate a plasei si numar de homari
    for (int homar = 0; homar <= total_homari; homar++) {
        for (int capacitate_curenta = 0; capacitate_curenta <= capacitate_maxima_plasa; capacitate_curenta++) {
            if (homar == 0 || capacitate_curenta == 0) {
                matrice_dinamica[homar][capacitate_curenta] = 0; // Initializam matricea dinamica cu 0 pentru cazul de baza (fara homari sau capacitate 0)
            } else if (dimensiuni_homari[homar] <= capacitate_curenta) { // Daca dimensiunea homarului este mai mica sau egala cu capacitatea plasei curente
                matrice_dinamica[homar][capacitate_curenta] = obtine_valoare_maxima(valori_homari[homar] + matrice_dinamica[homar - 1][capacitate_curenta - dimensiuni_homari[homar]], matrice_dinamica[homar - 1][capacitate_curenta]); // Alegem valoarea maxima dintre includerea si excluderea homarului curent
            } else {
                matrice_dinamica[homar][capacitate_curenta] = matrice_dinamica[homar - 1][capacitate_curenta]; // Copiem valoarea de pe linia anterioara daca homarul curent nu poate fi inclus
            }
        }
    }

    printf("Valoarea maxima este: %d\n", matrice_dinamica[total_homari][capacitate_maxima_plasa]); // Afisam valoarea maxima a homarilor care incap in plasa
    afisare_homari_selectati(matrice_dinamica, dimensiuni_homari, valori_homari, total_homari, capacitate_maxima_plasa); // Afisam homarii inclusi in plasa

    // Eliberam memoria alocata
    for (int i = 0; i <= total_homari; i++) {
        free(matrice_dinamica[i]);
    }
    free(matrice_dinamica);
    free(dimensiuni_homari);
    free(valori_homari);

    return 0; // Indicam terminarea cu succes a programului
}
