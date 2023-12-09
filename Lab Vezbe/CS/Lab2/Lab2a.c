/*Korišćenjem programskog jezika C napisati Linux program koji treba da simulira
funkcionisanje jednostavnog shell-a. Ovaj shell treba da izvršava programe koji
se mogu naći u tekućem direktorijumu ili u bilo kom direktorijumu koji je
naveden u PATH promenljivoj okruženja. Takođe, omogućeno je da se navođenjem
znaka & kao poslednjeg argumenta komandne linije shell pozvani program izvršava
u pozadini, a odmah prikaže prompt koji je spreman da primi novu komandu.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// maksimalan broj argumenata komande koju shell poziva
#define NUMARGS 20
int
main(int argc, char *argv[]) {
    char komanda[100];
    /*Komanda koju korisnik zadaje i koja se cita sa
    standardnog ulaza*/
    char *argumenti[20]; /*Ulazni argumenti komande koju je korisnik zadao*/
    int noArgs;
    /*Broj ulaznih argumenata komande koju je korisnik
    zadao*/
    int retStatus;
    /*Povratna vrednost sa kojom se komanda zavrsila */
    /* Prikazuje se prompt*/
    printf("\nprompt> ");
    /*Cita se komanda*/
    gets(komanda);
    /* Argumenti komande se izdvajaju kao tokeni. Za izdvajanje argumenata se
    koristi funkcija strtok. */
    noArgs = 0;
    argumenti[noArgs++] = strtok(komanda, " ");
    while ((argumenti[noArgs++] = strtok(0, " ")) != NULL) {
    }
    /*Ukoliko je zadata komanda LOGOUT shell zavrsava sa svojim radom*/
    while (strcmp(komanda, "logout") != 0) {
        if (fork() == 0) {
            /* U novom procesu shell izvrsava zadatu komandu odgvarajucom
            verzijom exec
            * komande. Ukoliko exec komanda vrati neki kod to znaci da je doslo
            do greske i
            * treba eksplicitno prekinuti novi proces komandom exit.
            * U novom procesu shell izvrsava zadatu komandu */
            sleep(5);
            /*Ukoliko je na kraju komande zadat & treba ga ukloniti iz vektora
            argumenata koji se prosledjuj novom procesu*/
            if (strcmp(argumenti[noArgs - 2], "&") == 0)
                argumenti[noArgs - 2] = NULL;
            execvp(argumenti[0], argumenti);
            printf("\nGRESKA PRI IZVRSENJU KOMANDE!\n");
            exit(-1);
        } else {
            if (strcmp(argumenti[noArgs - 2], "&") != 0)
                /* Ukoliko je poslednji navedeni argument nije & treba sacekati
                da se novi proces
                * zavrsi pre prikaza prompt-a. */
                wait(&retStatus);
        }
        /* Ponoviti prikazivanje prompta i izdvajanje argumenata */
        printf("\nprompt> ");
        gets(komanda);
        noArgs = 0;
        argumenti[noArgs++] = strtok(komanda, " ");
        while ((argumenti[noArgs++] = strtok(0, " ")) != NULL) {
        }
    }
}