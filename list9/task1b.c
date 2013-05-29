#include <stdio.h>
#include <stdlib.h>
#define STALA 67

int main(int argc, char *argv[]) {

    if(argc < 4) {
        fprintf(stderr, "Za malo parametrow.");
        return 0;
    }

    int i, n = atoi(argv[2]);
    int j, k = atoi(argv[3]);

    long long q;

    if(k > n || STALA < n) {
        fprintf(stderr, "Bledne parametry");
        return 0;
    }

    FILE *plik = fopen(argv[1], "r");

    if(!plik) {
        fprintf(stderr, "Nie mozna otworzyc pliku");
        return 0;
    }

    for(j = 0; j < n + 1; j++) {
        for(i = 0; i <= j; i++) {
            fscanf(plik, "%lld", &q);
            if(j == n && i == k)
                break;
        }
    }

    fclose(plik);
    printf("%lld", q);

    return 0;
}
