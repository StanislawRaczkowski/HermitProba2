#include <stdio.h>
#include "roznicaDzielona.h"
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>
#define MAKS_WEZLY 20
//Nie wiem czy to ważne, ale na razie limit węzłów na 20
double Dane[MAKS_WEZLY][3]; //nasza tabela z danymi odnośnie wezlow
//Potrzeba nam x1, x2...xi. Musimy wiedzieć też, czy węzły są k - krotne. Tzn
//gdy na przykład x1 = x2.
int LiczbaWezlow;

void WyswietlDane() {
    for (int i = 0; i < LiczbaWezlow; i++) {
        printf("x%d = %lf, f(x%d) = %lf, f'(x%d) = %lf\n", i + 1, Dane[i][0], i + 1, Dane[i][1], i + 1, Dane[i][2]);
    }
}

void generuj_wielomian_hermitea(char *wielomian) {
    char wyraz[1000];
    //Dobra, więc co tu się dzieje:
    //Tutaj obliczamy wielomain Hermite'a. Wzór na niego jest dosyć dziki, zalecam spojrzeć na wikipedię.
    //Postaram się jednak (głównie dla siebie w zasadzie) wyjaśnić po kolei co tu się dzieje.
    //Co robi strcpy? Ma kopiować łańcuch znaków, czyli de facto kopiuje W(x) = ... przed to, co wyjdzie z "wielomian"

    strcpy(wielomian, "W(x) = ");

    //i<2*LiczbWezlow - chodzi o to, by liczba iteracji była dla dwóch warunków (pochodna i wartość).
    for (int i = 0; i < 2 * LiczbaWezlow; i++) {
        double wspolczynnik = roznicaDzielona(Dane, LiczbaWezlow, 0, i);
        printf("Obliczam wspolczynnik dla i=%d, k=%d: %lf\n", 0, i, wspolczynnik);  // Debug


        //W tej części obliczamy współczynnik przed każdym wyrazem:
        //Tzn. jestto brane z naszego wcześniejszego ROZNICADZIELONA_H.
        //W praktyce (na kartce...) bralibyśmy sobie różnicę dzieloną lub wartość lub pochodną czyli przekątną
        //naszej tabelki.
        if (fabs(wspolczynnik) > 1e-10){
            //Nie do końca wiem jak to fabs działa,
            //Ważne, że usuwa wszystkie zerujące się wyrazy więc wynik jest przejrzysty
            if (i > 0 && wspolczynnik >= 0) {
                strcat(wielomian, "+ ");
            } else if (i > 0 && wspolczynnik < 0) {
                strcat(wielomian, "- ");
                wspolczynnik = -wspolczynnik;
            }
            //snprintf służy do "przekonwertowania współczynnika na znak". Po prostu chodzi o to, by nam się współczynnik
            //wyświetlał w tym wielomianie normalnie jakoś
            snprintf(wyraz, 1000, "%.2lf", wspolczynnik);
            strcat(wielomian, wyraz);

            for (int j = 0; j < i; j++) {
                //Tutaj dajemy nasze (x - xi).
                //[j/2] ponieważ teraz odwołujemy się do węzłów. Dlatego skoro mamy jeszcze w naszych Danych[][]
                //pochodną i wartość, no to przeskakujemy co dwa pola, więc mamy dzięki temu odwołanie się np.
                //dla j=0 i j=1 do Dane[0][0], j=2 j=3 do Dane [1][0]
                int index = j;
                snprintf(wyraz, 1000, "(x - %.2lf)", Dane[index][0]);
                //znak mnożenia pomiędzy współczynnikiem a (x - xi)
                strcat(wielomian, " * ");
                strcat(wielomian, wyraz);
            }
            //Spacja
            strcat(wielomian, " ");
        }
    }
}

int main()
{
    //Deklaracja zmiennych naszych do tablicy
    printf("Wezly podawaj po kolei numeracja, tzn. x1, x2, x3... xn. \n Podajac wezel o krotnosci musisz podac taka sama wartosc i pochodna\n");
    printf("Podaj, ile chcesz miec wezlow: ");
    scanf("%d", &LiczbaWezlow);
    if (LiczbaWezlow > MAKS_WEZLY) {
        printf("Nie dawaj wiecej niz 20 wezlow.\n");
        return 0;
    }
    for (int i = 0; i < LiczbaWezlow; i++) {
        printf("Podaj argument %d", i + 1);
        scanf("%lf", &Dane[i][0]);

        printf("Podaj wartosc f(x) %d", i + 1);
        scanf("%lf", &Dane[i][1]);

        printf("Podaj pochodna f'(x) %d", i + 1);
        scanf("%lf", &Dane[i][2]);
    }

WyswietlDane();

    //To jest do tworzenia danych na wykres.
    //Ten fragment kodu jest przekopiowany zupełnie z chataGpt, nie chciało mi się nad tym już myślec
    FILE *plik = fopen("wykres.txt", "w");
    if (plik == NULL) {
        printf("Błąd przy tworzeniu pliku wykresu.\n");
        return 1;
    }

    char wielomian[MAKS_WEZLY * 1000];
    generuj_wielomian_hermitea(wielomian);
    printf("Wielomian Hermite'a:\n%s\n", wielomian);


    return 0;
    //I to chyba tyle.
}