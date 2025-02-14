#include <stdio.h>
#include "DividedDifference.h"
#include <string.h>
#include <tgmath.h>
#include "DisplayData.h"
#include "config.h"
#include "GenerateHermitPolynomial.h"
 //nasza tabela z danymi odnośnie wezlow
//Potrzeba nam x1, x2...xi. Musimy wiedzieć też, czy węzły są k - krotne. Tzn
//gdy na przykład x1 = x2.
int KnotNumber;
double Dane[MAKS_KNOTS][3];

int main()
{
    printf("Give the points in order, eg. x1, x2, x3... xn. \n When giving a knot with multiplicity, you have to input once more their derivative and value\n");
    printf("Input number of knots: ");
    scanf("%d", &KnotNumber);
    if (KnotNumber > MAKS_KNOTS) {
        printf("Don't make more than 1000 knots.\n");
        return 0;
    }
    for (int i = 0; i < KnotNumber; i++) {
        printf("Input Point %d", i + 1);
        scanf("%lf", &Dane[i][0]);

        printf("Input Value f(x) %d", i + 1);
        scanf("%lf", &Dane[i][1]);

        printf("Input derivative f'(x) %d", i + 1);
        scanf("%lf", &Dane[i][2]);
    }

DisplayData(Dane, KnotNumber);

    char polynomial[MAKS_KNOTS * 1000];
    generateHermitPolynomial(polynomial, KnotNumber, Dane);
    printf("Your Hermit's Polynomial:\n%s\n", polynomial);


    return 0;
}