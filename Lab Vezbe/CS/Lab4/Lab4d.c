/*Korišćenjem programskog jezika C napisati Linux program koji kao ulazni
argument prihvata putanju do jedne izvršne datoteke. Program treba da pozove na
izvršenje tako prosleđenu izvršnu datoteku i njen izlaz prikazuje na standardnom
izlazu ekran po ekran. Ovo se postiže tako što se izlaz pozvane izvršne datoteke
prosleđuje programu more korišćenjem datavoda.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <unistd.h>

int
main(int argc, char *argv[]) {
    int pd[2];
    int pid;
    char *args[10];
    int i;
    if (pipe(pd) < 0)
        exit(1);
    pid = fork();
    if (pid == 0) {
        close(1);
        dup(pd[1]);
        for (i = 1; i < argc; i++)
            args[i - 1] = argv[i];
        args[argc - 1] = NULL;
        // execlp(argv[1], argv[1], NULL);
        execvp(args[0], args);
    } else {
        close(0);
        dup(pd[0]);
        execlp("more", "more", NULL);
    }
}