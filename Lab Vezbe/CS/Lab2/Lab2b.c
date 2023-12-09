/*Modifikovati rešenje iz Zadatka 1 tako da novokreirani shell može koristiti
batch datoteke. To su obične tekstualne datoteke u kojima je u svakoj liniji po
jedna komanda koju shell treba da izvrši.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
// maksimalan broj argumenata komande koju shell poziva
#define NUMARGS 20
/*Funkcija prihvata komandu i obradjuje je. U slucaju da je komanda logout
funkcija vraca 1. U svim ostalim slucajevima vraca 0*/
int
obrada(char *komanda) {
    char *argumenti[20]; /*Ulazni argumenti komande koju je korisnik zadao*/
    int noArgs;
    /*Broj ulaznih argumenata komande koju je korisnik
    zadao*/
    int retStatus;
    /*Povratna vrednost sa kojom se komanda zavrsila */
    int pid;
    /* Argumenti komande se izdvajaju kao tokeni. Za izdvajanje argumenata se
    koristi funkcija strtok. */
    noArgs = 0;
    argumenti[noArgs++] = strtok(komanda, " \n");
    while ((argumenti[noArgs++] = strtok(0, " \n")) != NULL) {
    }
    if (strcmp(komanda, "logout") != 0) {
        pid = fork();
        if (pid == 0) {
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
            return 0;
        }
    } else
        return 1;
}
int
obrada_dat(char *batch) {
    FILE *f;
    char komanda[100];
    int ret = 0;
    /*Komanda koja se cita iz batch datoteke*/
    f = fopen(batch, "r");
    /*Ukoliko je datoteka uspesno otvorena cita se linija po linija i izvrsavaju
    se kao standardne komande */
    if (f != 0) {
        fgets(komanda, 100, f);
        while (!feof(f)) {
            ret = obrada(komanda); /*Svaka linija batch datoteke se izvrsava
             kao standardna datoteka */
            /*Ako je obradjena komanda logout prekida se dalja obrada
             * batchdatotke*/
            if (ret == 1)
                return ret;
            fgets(komanda, 100, f);
        }
    } else
        printf("Greska prilikom otvaranja batch datoteke\n");
    return ret;
}
int
main(int argc, char *argv[]) {
    char komanda[100];
    int ret = 0;
    /*Komanda koju korisnik zadaje i koja se cita sa standardnog ulaza */
    do {
        /* Prikazuje se prompt*/
        printf("\nprompt> ");
        /*Cita se komanda*/
        gets(komanda);
        /*Batch datoteka se zadaje tako sto se na pocetku doda karakter @. U
        toj situaciji se poziva funkcija za obradu batch datoteke */
        if (komanda[0] == '@') {
            /*Uklanjamo znak @ na pocetku i uzimamo samo prvi token iz
            komande */
            char *batch = strtok(komanda + 1, " ");
            ret = obrada_dat(batch);
        } else
            /*Nije batch datoteke. Ide standardna obrada */
            ret = obrada(komanda);
    }
    /*Petlja se izvrsava sve dok neka od funkcija ne vrati 1 sto je znak da je
    specificirana logout komanda */
    while (ret == 0);
}