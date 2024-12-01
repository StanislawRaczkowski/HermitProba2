#include"roznicaDzielona.h"
#include<stdio.h>
#include<math.h>

int silnia(int n) {
  //To też wklejone, ta silnia potrzebna jest po prostu do działania jednego na dole
  return (n == 0 || n == 1) ? 1 : n * silnia(n - 1);
}
double roznicaDzielona(double Dane[][3], int wezly, int i, int k)

    {
  printf("Obliczam roznice dzielona dla i=%d, k=%d\n", i, k);  // Debug

  if (k == 0){
    //Czyli jeżeli mamy x0 => no to f[x0] = f(x0)
    return Dane[i][1];
    }
      //Czyli kiedy mamy k - krotny węzeł na przykład
      //To żeby uniknąć dostania 0/0 bierzemy pochodną po prostu
      if (k == 1 && i + 1 < wezly && Dane[i][0] == Dane[i+1][0]) {
        return Dane[i][2];
      }
  if (Dane[i][0] == Dane[i + k][0]) {
    return Dane[i][2] / silnia(k);
  }
  if (k + i < wezly) {
    double result = (roznicaDzielona(Dane, wezly, i + 1, k - 1) - roznicaDzielona(Dane, wezly, i, k - 1)) / (Dane[i + k][0] - Dane[i][0]);
    printf("Zwracam roznice dzielona: %lf\n", result);  // Debug
          return result;
        }

    return 0;
    }





