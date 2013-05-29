#include <stdio.h>
#include <stdlib.h>
#define N 67

int main(int argc, char *argv[]) {

    if(argc < 1) {
        fprintf(stderr,"Za malo argumentow.");
        return 0;
    }

    int i, j;
    long long **pascal = malloc(N * sizeof(**pascal));

    FILE *plik = NULL;
    plik = fopen(argv[1], "w");

    if(!plik) {
        fprintf(stderr, "Nie mozna odczytac pliku.");
        return 0;
    }

    for (i = 0; i < N; i++) {
        pascal[i]= malloc((i + 1) * sizeof(*pascal[i]));
        pascal[i][0] = 1;
        pascal[i][i] = 1;
        fprintf(plik, "%lld ", pascal[i][0]);

        for (j = 0; j < i - 1; j++) {
            pascal[i][j + 1] = pascal[i - 1][j] + pascal[i - 1][j + 1];
            fprintf(plik, "%lld ", pascal[i][j + 1]);
        }
        if(i != 0) fprintf(plik, "%d", 1);

        fprintf(plik, "\n");
    }

    for(i = 0; i < N; i++)
        free(pascal[i]);
    free(*pascal);

    fclose(plik);
    return 0;
}
