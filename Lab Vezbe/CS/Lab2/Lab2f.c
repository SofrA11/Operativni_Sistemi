/*Korišćenjem programskog jezika C napisati Linux koji sortira vrste celobrojne
matrice čiji se elementi unose sa tastature. Za sortiranje svake vrste pokrenuti
posebnu nit.*/

/*Program koji sortira vrste celobroje matrice pri cemu se za sortiranje svake
vrste pokrece posebna nit*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define N 4
/*matrica koju sortiram je deklarisana kao globalna promenljiva da bi bila
vidljiva u svim funkcijama pa samim tim i u funkciji niti*/
int a[N][N];
/*Funkcija niti*/
void *
sortiranje(void *arg) {
    /*Ulazni argument je redni broj vrste koju ce nit sortirati. Posto je ulazni
    argument void * potrebno ga je kastovati u int * a zatim ocitati vrednost*/
    int k = *((int *) arg);
    int i, j, pom;
    /*Sortiranje matrice */
    for (i = 0; i < N - 1; i++)
        for (j = i + 1; j < N; j++)
            if (a[k][i] > a[k][j]) {
                pom = a[k][i];
                a[k][i] = a[k][j];
                a[k][j] = pom;
            }
}
int
main() {
    int i, j;
    /*Niz identifikatora niti. Po jedan za svaku vrstu*/
    pthread_t niti[N];
    /*Sa standardnog ulaza citamo elemente matrice*/
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            scanf("%d", &a[i][j]);
    /*Kreiramo niti */
    for (i = 0; i < N; i++)
        pthread_create(
            &niti[i], NULL, (void *) sortiranje /*funkcija nit*/, (void *) &i /*ulazni argument niti odnosno u ovom slucaju redni broj vrste*/);
    /*Main f-ja ceka da se niti zavrse*/
    for (i = 0; i < N; i++)
        pthread_join(niti[i], NULL);
    /*Na standardni izlaz stampamo sortiranu matricu*/
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++)
            printf("%d\t", a[i][j]);
        printf("\n");
    }
    return 0;
}