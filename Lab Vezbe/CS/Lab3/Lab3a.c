/*Korišćenjem programskog jezika C napisati Linux program koji na standardnom
izlazu ispisuje rečenicu “Ovo je test za semafore.” Pri čemu svaku reč u
rečenici ispisuje posebna nit. Niti sinhronizovati korišćenjem semafora.*/
//POSIX semafori
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#define N 3
/* Niz koji sadrzi reci recenice */
char reci[N][20] = {"This ", "is ", "SPARTAAA !!!"};
/* Niz od 4 semafora. */
sem_t sems[N - 1];
/* Funkcija niti. */
void *
stampanje(void *arg) {
    /* Ulazni argument je struktura argument */
    int p = *((int *) arg);
    /* Samo prva nit odmah stampa svoju rec, ostale moraju da sacekaju
    prethodnu */
    if (p > 0)
        sem_wait(&sems[p - 1]);

    // Modifikacija da prikazuje koji je semafor sta napisao
    printf(" %d. Semafor stampa: %s \n", p + 1, reci[p]);
    sleep(1);
    if (p < 4)
        sem_post(&sems[p]);  
}
int
main() {
    int i;
    /* Niz ulaznih argumenata niti */
    int args[N];
    /* Niz identifikatora niti */
    pthread_t niti[N];
    /* Inicijalizacija semafora. */
    for (i = 0; i < N - 1; i++)
        sem_init(&sems[i], 0, 0);
    /* Kreiramo niti */
    for (i = 0; i < N; i++) {
        args[i] = i;
        pthread_create(&niti[i], NULL, (void *) stampanje, &args[i]);
    }
    /* Main funkcija ceka da se sve niti zavrse */
    for (i = 0; i < N; i++)
        pthread_join(niti[i], NULL);
    return 0;
}
