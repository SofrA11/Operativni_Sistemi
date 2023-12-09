/*Korišćenjem programskog jezika C napisati Linux koji na standardnom izlazu
ispisuje rečenicu “Ovo je test za niti!” pri čemu svaku reč u rečenici ispisuje
posebna nit.*/

/*Program koji na standardnom izlazu ispisuje recenicu "Ovo je test za niti!"
pri cemu svaku rec ispisuje posebna nit*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define N 5
/*Niz koji sadrzi reci koje se stampaju deklarisemo kao globalnu promenljivu
kako bi bile vidljive u svim funkcijama pa i u funkciji niti*/
char reci[N][20] = {"Ovo", "je", "test", "za", "niti!"};
/*Struktura koja definise ulazne argumente niti*/
struct argument { /*Redni broj reci koja se stampa*/
    int rec;
    /*Nit koja treba da odstampa prethodnu rec i koja se zbog toga ceka*/
    pthread_t prethodna_nit;
};
/*Funkcija niti*/
void *
stampanje(void *arg) {
    /*Ulazni argument je struktura kojaniti[i]; sadrzi neophodne informacije za
    stampanje*/
    struct argument *p = (struct argument *) arg;
    /*samo nit koja stampa prvu rec ne ceka prethodnu nit. Sve ostale niti
    cekaju nit koja stampa prethodnu rec*/
    if (p->rec > 0)
        pthread_join(p->prethodna_nit, NULL);
    printf(" %s", reci[p->rec]);
    sleep(3);
}
int
main() {
    int i;
    /*Niz ulaznih argumenata niti. Po jedan za svaku nit.*/
    struct argument args[N];
    /*Niz identifikatora niti. Po jedan za svaku rec*/
    pthread_t niti[N];
    /*Kreiramo niti */
    for (i = 0; i < N; i++) {
        args[i].rec = i;
        if (i > 0)
            args[i].prethodna_nit = niti[i - 1];
        pthread_create(&niti[i], NULL, (void *) stampanje /*funkcija
  nit*/, (void *) &args[i] /*ulazni argument niti */);
    }
    /*Main f-ja ceka da se poslednja nit zavrsi*/
    pthread_join(niti[N - 1], NULL);
    return 0;
}
