#include "gauss.h"
#include <math.h>
/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b){
    int n = mat->r; // Pobieranie rozmiaru macierzy

    for (int k = 0; k < n - 1; k++) {
        //  Implementacja wybor elementu glownego - wersja kuba
        
        int max = k;
        for (int i = k + 1; i < n; i++) {
            if (fabs(mat->data[i][k]) > fabs(mat->data[max][k])) {
                max = i;
            }
        }

        // Sprawdzenie czy macierz nie jest osobliwa
        if (fabs(mat->data[max][k]) < 1e-12) {
            return 1;
        }

        // Zamiana wierszy w macierzy A
        double* temp = mat->data[k];
        mat->data[k] = mat->data[max];
        mat->data[max] = temp;

        // Zamiana wierszy w wektorze b 
	double *temp_b = b->data[k];
	b->data[k] = b->data[max];
        b->data[max] = temp_b;

        // (koniec pivotingu) 
	
        // Właściwa eliminacja (zerowanie pod przekątną)
        for (int i = k + 1; i < n; i++) {
            double factor = mat->data[i][k] / mat->data[k][k];

            // Odejmowanie wiersza k od wiersza i w macierzy A
            for (int j = k; j < n; j++) {
                mat->data[i][j] -= factor * mat->data[k][j];
            }

            // Odejmowanie wiersza k od wiersza i w wektorze b
            b->data[i][0] -= factor * b->data[k][0];
        }
    }
		return 0;
}

