//
// Created by August on 14.02.2025.
//
#include <stdio.h>
#include "DisplayData.h"
#include "config.h"


void DisplayData(double Dane[MAKS_KNOTS][3], int const KnotNumber)
    {
    for (int i = 0; i < KnotNumber; i++) {
        printf("x%d = %lf, f(x%d) = %lf, f'(x%d) = %lf\n", i + 1, Dane[i][0], i + 1, Dane[i][1], i + 1, Dane[i][2]);
    }
}
