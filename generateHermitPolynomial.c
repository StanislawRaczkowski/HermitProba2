#include "generateHermitPolynomial.h"
#include <stdio.h>
#include <string.h>
#include "config.h"
#include "DividedDifference.h"
#include <math.h>


void generateHermitPolynomial(char *polynomial, int KnotNumber, double Dane[MAKS_KNOTS][3]) {
    char word[1000];

    strcpy(polynomial, "W(x) = ");
    for (int i = 0; i < 2 * KnotNumber; i++) {
        double factor = DividedDifference(Dane, KnotNumber, 0, i);
        printf("Counting for i=%d, k=%d: %lf\n", 0, i, factor);  // Debug

        if (fabs(factor) > 1e-10){
            if (i > 0 && factor >= 0) {
                strcat(polynomial, "+ ");
            } else if (i > 0 && factor < 0) {
                strcat(polynomial, "- ");
                factor = -factor;
            }

            snprintf(word, 1000, "%.2lf", factor);
            strcat(polynomial, word);

            for (int j = 0; j < i; j++) {
                int index = j;
                snprintf(word, 1000, "(x - %.2lf)", Dane[index][0]);
                //znak mnożenia pomiędzy współczynnikiem a (x - xi)
                strcat(polynomial, " * ");
                strcat(polynomial, word);
            }
            strcat(polynomial, " ");
        }
    }
}
