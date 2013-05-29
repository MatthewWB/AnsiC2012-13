#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Sito Eratostenesa */

void eratostenes (int n, int * primes);
int equate (const void * i, const  void * j);

int main(int argc, char *argv[]) {

    int i = 0, j = 0, temp = 0;
    int * buffer; int * primes;

    if(argc <= 2) {
        printf("Podano zbyt mala liczbe argumentow.");
        return 0;
    }

    char * inputFile = malloc(strlen(argv[1]) + 3);
    char * outputFile = malloc(strlen(argv[2]) + 4);

    strcpy(inputFile, argv[1]);
    strcat(inputFile, ".in");
    FILE *fileInput = fopen(inputFile, "r");
    free(inputFile);

    strcpy(outputFile, argv[2]);
    strcat(outputFile, ".out");
    FILE *fileOut = fopen(outputFile, "w");

    if(!fileInput || !fileOut){
        fprintf(stderr, "Blad z dzialaniem na plikach.");
        return 0;
    }

    fscanf(fileInput, "%d", &i);
    buffer = malloc(i * sizeof(int));

    /* przypisujemy poszczegolne elementy */
    for(j = 0; j < i; j++){
        fscanf(fileInput, "%d", &buffer[j]);
        if(buffer[j] > temp)
            temp = buffer[j];
    }
    fclose(fileInput);

    primes = malloc(temp * sizeof(int));
    eratostenes(temp, primes);
    qsort(buffer, i, sizeof(int), equate);

    for(j = 0; j < i; j++)
        if(primes[buffer[j] - 1] > 0 && buffer[j] > 1)
            fprintf(fileOut, "%d ", buffer[j]);

    fclose(fileOut);
    free(primes);
    free(buffer);

    return 0;
}

void eratostenes (int n, int * primes) {
    int i, j;
    /* ustawiamy 1 dla kazdego elementu */
    for(i = 0; i < n; i++)
        primes[i] = 1;

    for(i = 2; i * i <= n; i++)
        for(j = i + i; j <= n; j += i)
            primes[j - 1] = 0;
}

int equate (const void * i, const  void * j) {
    return (*(int*)i - *(int*)j );
}
