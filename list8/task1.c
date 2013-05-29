#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int stacja1;
    int stacja2;
    int koszt;
} trasa;

typedef struct {
    int nr;
    int odwiedzony;
    int ile_tras;
    int trasa_dlugosc;
    int trasa_koszt;
    trasa * trasy;
} stacja;

void dodaj_trase(stacja * s, int a, int b, int c);
int * kolejka_dodaj(int ** kolejka, int x, int dlugosc);
int kolejka_pobierz(int ** kolejka, int dlugosc);

int main() {

    /* stacje kolejowe, odcinki torow */
    int n, m;
    /* trasa od, do, koszt */
    int a, b, c;
    stacja * stacje;
    /* stolica, ilosc miast wojewodzkich */
    int s, w;
    /* zmienne dla roznych petli */
    int x, y;
    /* aktualnie obliczane wojewodztwo */
    int woj;
    /* zmienne wykorzystywane do BFS */
    int v, u;
    /* zmienne pomocnicze */
    int i, dlugosc, koszt, minima = 0;
    /* kolejka stacji do przejrzenia */
    int * kolejka = NULL;
    /* i aktualna dlugosc tej kolejki */
    int kolejka_dlugosc = 0;
    /* wyliczone minima dla danej stacji wojewodzkiej oraz suma */
    int min_koszt, min_dlugosc, suma_koszt = 0;

    scanf("%d %d", &n, &m);

    stacje = (stacja *) malloc(n * sizeof(stacja));

    for (x = 0; x < n; x++) {
        stacje[x].nr = x;
        stacje[x].ile_tras = 0;
        stacje[x].odwiedzony = 0;
        stacje[x].trasy = NULL;
        stacje[x].trasa_dlugosc = 0;
        stacje[x].trasa_koszt = 0;
    }

    for (x = 0; x < m; x++) {
        scanf("%d %d %d", &a, &b, &c);
        if (a >= n || b >= n) {
            printf("Przerywam dzialanie! Niepoprawne dane: jedna ze stacji nie istnieje: %d, %d.\n", a, b);
            exit(1);
        }
        dodaj_trase(&(stacje[a]), a, b, c);
        dodaj_trase(&(stacje[b]), b, a, c);
    }

    scanf("%d %d", &s, &w);
    if (s >= n) {
        printf("Przerywam dzialanie! Niepoprawne dane: stolica nie istnieje: %d.\n", s);
        exit(1);
    }

    for (x = 0; x < w; x++) {
        scanf("%d", &woj);

        if (woj >= n) {
            printf("Przerywam dzialanie! Niepoprawne dane: stacja wojewodzka nie istnieje: %d.\n", x);
            exit(1);
        }

        /* zerujemy zmienne pomocnicze i pomocnicze wlasnosci stacji */
        minima = 0;
        for (y = 0; y < n; y++) {
            stacje[y].odwiedzony = 0;
            stacje[y].trasa_dlugosc = 0;
            stacje[y].trasa_koszt = 0;
        }

        stacje[woj].odwiedzony = 1;
        kolejka = kolejka_dodaj(&kolejka, woj, ++kolejka_dlugosc);

        while (kolejka_dlugosc > 0) {
            u = kolejka_pobierz(&kolejka, kolejka_dlugosc);
            kolejka_dlugosc--;

            for (v = 0; v < stacje[u].ile_tras; v++) {
                i = stacje[u].trasy[v].stacja1 == u ?
                    stacje[u].trasy[v].stacja2 : stacje[u].trasy[v].stacja1;
                /* jesli jestesmy w stolicy */
                if (i == s) {
                    dlugosc = stacje[u].trasa_dlugosc + 1;
                    koszt = stacje[u].trasa_koszt + stacje[u].trasy[v].koszt;

                    if (minima == 0) {
                        minima = 1;
                        min_dlugosc = dlugosc;
                        min_koszt = koszt;
                    } else {
                        if (dlugosc < min_dlugosc) {
                            min_dlugosc = dlugosc;
                            min_koszt = koszt;
                        } else
                            if (koszt < min_koszt)
                                min_koszt = koszt;
                    }
                    continue;
                }
                /* nie jestesmy w stolicy, stacje dodajemy do kolejki */
                if (stacje[i].odwiedzony == 0) {
                    stacje[i].odwiedzony = 1;
                    stacje[i].trasa_koszt = stacje[u].trasy[v].koszt + stacje[u].trasa_koszt;
                    stacje[i].trasa_dlugosc = stacje[u].trasa_dlugosc + 1;
                    kolejka = kolejka_dodaj(&kolejka, i, ++kolejka_dlugosc);
                }
            }
        }
        suma_koszt += min_koszt;
    }
    printf("%d\n", suma_koszt);
    return 0;
}

void dodaj_trase(stacja * s, int a, int b, int c) {
    s->ile_tras++;
    s->trasy = (trasa *) realloc(s->trasy, s->ile_tras * sizeof(trasa));
    s->trasy[s->ile_tras - 1].stacja1 = a;
    s->trasy[s->ile_tras - 1].stacja2 = b;
    s->trasy[s->ile_tras - 1].koszt = c;
}

/* dwie poniższe funkcje obsluguja kolejka dla BFS */

int * kolejka_dodaj(int ** kolejka, int x, int dlugosc) {
    int * k = *kolejka;
    k = (int *) realloc(k, dlugosc * sizeof(int));
    k[dlugosc-1] = x;
    return k;
}

int kolejka_pobierz(int ** kolejka, int dlugosc) {
    int * k = *kolejka;
    int pierwszy = k[0];
    int x;

    for (x = 1; x < dlugosc; x++)
        k[x-1] = k[x];

    if (dlugosc - 1 == 0) {
        free(*kolejka);
        *kolejka = NULL;
    } else
        *kolejka = (int *) realloc(k, (dlugosc - 1) * sizeof(int));

    return pierwszy;
}
