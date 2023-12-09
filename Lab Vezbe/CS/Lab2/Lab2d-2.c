/*Korišćenjem programskog jezika C napisati Linux program koji na standardnom
izlazu štampa sve svoje ulazne argumente ukoliko ih ima. Kreirati drugi program
koji poziva prethodni program i prosleđuje mu sve svoje argumente (za kreiranje
iskoristiti sistemske pozive execl i execv).*/

/*Drugi program koji poziva prvi program i prosledjuje mu sve svoje ulazne
argumente. Program je implementiran u datoteci II-1-4b.c*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ARGS       20
#define MAX_ARG_LENGTH 100

int
main(int argc, char *argv[]) {
    int i;
    char *argumenti[MAX_ARGS];
    /*Argument na poziciji 0 je uvek jednak imenu programa koji pozivamo. */
    argumenti[0] = (char *) malloc(MAX_ARG_LENGTH * sizeof(char));
    strcpy(argumenti[0], "II-1-4a");
    /*Sve ostale ulazne argumente (osim nultog) kopiramo u vektor sa argumetnima
    koji cemo proslediti programu koji pozivamo*/
    for (i = 1; i < argc; i++) {
        argumenti[i] = (char *) malloc(MAX_ARG_LENGTH * sizeof(char));
        strcpy(argumenti[i], argv[i]);
    }
    /*Poslednji argument mora da bude NULL da bi ukazao na kraj vektora sa
    argumentima*/
    argumenti[argc] = NULL;
    if (fork() == 0) { /*Izvrsava novokreirani proces*/
        if (execv("./II-1-4a", argumenti) < 0) {
            printf("Doslo je do greske!\n");
            exit(1);
        }
    } else
        /*Izvrsava proces roditelj koji ceka da se dete zavrsi*/
        wait(NULL);
    /*Oslobadjamo memoriju koja je zauzeta za vektor argumenata */
    for (i = 0; i < argc; i++)
        free(argumenti[i]);
    return 0;
}