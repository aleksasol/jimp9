#include "backsubst.h"

/**
 * Zwraca 0 - wsteczne podstawienie zakonczone sukcesem
 * Zwraca 1 - błąd dzielenia przez 0 (element na diagonali = 0)
 * Zwraca 2 - błąd nieprawidłowych rozmiarów macierzy
 */
int backsubst(Matrix* x, Matrix* mat, Matrix* b) {
    // Sprawdzenie poprawności wymiarów:
    // Macierz główna musi być kwadratowa, a wektory b i x muszą mieć tyle samo wierszy.
    if (mat->r != mat->c || mat->r != b->r || x->r != b->r) {
        return 2;
    }

    int i, j;
    int n = mat->r;

    // Główna pętla: iterujemy od ostatniego wiersza do pierwszego
    for (i = n - 1; i >= 0; i--) {

        // Zabezpieczenie przed dzieleniem przez zero
        if (mat->data[i][i] == 0) {
            return 1;
        }

        double s = 0;

        // Sumowanie wyrazów, które już obliczyliśmy (stojących na prawo od przekątnej)
        for (j = i + 1; j < n; j++) {
            s += mat->data[i][j] * x->data[j][0];
        }

        // Obliczenie końcowej wartości x[i]
        x->data[i][0] = (b->data[i][0] - s) / mat->data[i][i];
    }

    return 0;
}

