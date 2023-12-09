/*Modifikovati jednostavnu implementaciju shell-a (iz laboratorijske vežbe II-1)
dodavanjem podrškeza pipe ( | ) odnosno mogućnost preusmeravanja izlaza jedne
komande na ulaz druge. Uzeti da najviše dve komande mogu da budu povezane
pipe-om.*/

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
    int pipePos;
    /*Pozicija simbola | ukoliko se on nalazi u zadatoj
    komandi*/
    int retStatus;
    /*Povratna vrednost sa kojom se komanda zavrsila */
    int pd[2];
    /*Krajevi datavoda koji ce se koristiti za komunikaciju
    izmedju dva procesa*/
    char *argumenti1[20]; /*Pomocni niz ulaznih argumenata */
    int i;
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
        /*Utvrdjuje se da li se medju argumentima komande nalazi simbol | */
        pipePos = 0;
        while ((pipePos < noArgs - 1) && (strcmp(argumenti[pipePos], "|") != 0))
            pipePos++;
        /*Naisli smo na simbol | . To znacu da postoje dve komande koje treba
        da izvrsimo i kod kojih treba da izvrsimo preusmeravanja izlaza jedne na
        ulaz druge*/
        if (pipePos < noArgs - 1) {
            /*Kreira se datavod*/
            pipe(pd);
            /*Prva komanda*/
            if (fork() == 0) {
                sleep(5);
                for (i = 0; i < pipePos; i++)
                    argumenti[i] = argumenti[i];
                argumenti1[pipePos] = NULL;
                /*Zatvara se kraj datavoda koji se koristi za citanje */
                close(pd[0]);
                /*Standardni
                izlaz
                se
                preusmerava
                na
                ulaz
                datavoda
                za
                pisanje*/
                close(1);
                dup(pd[1]);
                /*Ucitava se izvrsna datoteka*/
                // execvp(argumenti1[0], argumenti1);
                execlp("ls", "ls", NULL);
                printf("Greska prilikom izvrsavanja komande\n");
                exit(-1);
            }
            /*Druga komanda*/
            if (fork() == 0) {
                sleep(5);
                for (i = pipePos + 1; i < noArgs; i++)
                    argumenti1[i - pipePos - 1] = argumenti[i];
                /*Zatvara se kraj datavoda za pisanje*/
                close(pd[1]);
                /*Standardni
                ulaz
                se
                preusmerava
                na
                kraj
                datavoda
                za
                citanje*/
                close(0);
                dup(pd[0]);
                /*Ucitava se izvrsna datoteka*/
                execvp(argumenti1[0], argumenti1);
                // execlp("more", "more", NULL);
                printf("Gresak prilikom izvrsavanja komande\n");
                exit(-1);
            }
            close(pd[0]);
            close(pd[1]);
        }
        /*Ako nismo nasli | sve se izvrsava kao i ranije*/
        else if (fork() == 0) {
            /*U novom procesu shell izvrsava zadatu komandu odgvarajucom
        verzijom execkomande. Ukoliko exec komanda vrati neki kod to znaci da je
        doslo do greske i treba eksplicitno prekinuti novi proces komandom exit.
        U novom procesu shell izvrsava zadatu komandu*/
            sleep(5);
            /*Ukoliko je na kraju komande zadat & treba ga ukloniti iz vektora
            argumenata koji se prosledjuj novom procesu*/
            if (strcmp(argumenti[noArgs - 2], "&") == 0)
                argumenti[noArgs - 2] = NULL;
            execvp(argumenti[0], argumenti);
            printf("\nGRESKA PRI IZVRSENJU KOMANDE!\n");
            exit(-1);
        }
        if (strcmp(argumenti[noArgs - 2], "&") != 0 && pipePos < noArgs) {
            wait(NULL);
            wait(NULL);
        } else if (strcmp(argumenti[noArgs - 2], "&") != 0)
            /* Ukoliko je poslednji navedeni argument nije & treba sacekati da
            se novi proces
            * zavrsi pre prikaza prompt-a. */
            wait(&retStatus);
        /* Ponoviti prikazivanje prompta i izdvajanje argumenata */
        printf("\nprompt> ");
        gets(komanda);
        noArgs = 0;
        argumenti[noArgs++] = strtok(komanda, " ");
        while ((argumenti[noArgs++] = strtok(0, " ")) != NULL) {
        }
    }
}