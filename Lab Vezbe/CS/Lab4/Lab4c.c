/*Korišćenjem programskog jezika C napisati Linux program demonstrira mogućnosti
redirekcije standardnog ulaza i izlaza. Program prihvata dva ulazna argumenta:
putanju do izvršne datoteke i putanju do tekstualne datoteke. Program otvara
tekstualnu datoteku i redirektuje standardni izlaz na tu otvorenu datoteku.
Zatim kreira novi proces i učitava specificiranu izvršnu datoteku. Efekat ovog
programa je da se izlaz svakog pozvanog programa redirektuje u izabranu
tekstualnu datoteku.*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <unistd.h>
int
main(int argc, char *argv[]) {
    int fd;
    // Otvara tekstualnu datoteku
    fd = open(argv[2], O_CREAT | O_TRUNC | O_RDWR, 0777);
    // Redirektuje standardni izlaz na otvorenu tekstualnu datoteku
    dup2(fd, 1);
    // Zatvara deskriptor za datoteku (kopija ostaje)
    close(fd);
    // Poziva izvrsnu datoteku
    execlp(argv[1], argv[1], NULL);
    printf("Ne bi trebalo nikada da se izvrsi!");
}