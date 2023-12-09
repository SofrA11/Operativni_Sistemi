/*Korišćenjem programskog jezika C napisati Linux program koji iz tekućeg
direktorijum kopira proizvoljnu datoteku u direktorijum tmp koji se nalazi u
tekućem direktorijumu.*/

/*Program koji iz tekuceg direktorijuma kopira proizvoljnu
direktorijum tmp koji se nalazi u tekucem direktorijumu*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
main() {
    int pid;
    char datoteka[100];
    /*Sa standardnog ulaza citamo ime datoteke koju zelimo da kopiramo*/
    scanf("%s", datoteka);
    pid = fork();
    if (pid == 0) { /*Izvrsava proces dete koji ce obaviti kopiranje
                   Kopiranje se vrsi komandom: cp ime_dat ./tmp
                   Koristimo funkciju execlp jer ulazne argumente procesa koji
                   pozivamo prosledjujemo u vidu liste a izvrsna datoteka (Linux
                   komanda cp) se nalazi negde na putanji koja je definisana
                   environment promenljivom PATH. Prvi argument je ime izvrsne
                   datoteke koju pozivamo, drugi argument odgovara argv[0]
                   i
                   opet je ime datoteke koju pozivamo, treci argument je argv[1]
                   i predstavlja datoteku koju kopiramo, cetvrti argument
                   odgovara argv[2] i predstavlja putanju gde kopiramo i peti
                   argument je NULL da bi ukazao na kraj liste argumenata*/
        if (execlp("cp", "cp", datoteka, "./tmp", NULL) < 0) {
            printf("Doslo je do greske!\n");
            exit(1);
        } else {
            /*Izvrsava proces roditelj koji ceka da se njegov proces dete zavrsi
                    odnosno da se kopiranje izvrsi*/
            wait(NULL);
        }
    }
    return 0;
}