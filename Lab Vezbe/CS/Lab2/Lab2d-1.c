/*Korišćenjem programskog jezika C napisati Linux program koji na standardnom
izlazu štampa sve svoje ulazne argumente ukoliko ih ima. Kreirati drugi program
koji poziva prethodni program i prosleđuje mu sve svoje argumente (za kreiranje
iskoristiti sistemske pozive execl i execv).*/

/*Prvi program koji sve svoje ulazne argumente stampa na standardnom izlazu.
Program je implementiran u datoteci II-1-4a.c*/
#include <stdio.h>
#include <stdlib.h>
int
main(int argc, char *argv[]) {
    int i;
    /*U petlji se stampaju svi ulazni argumenti programa*/
    for (i = 0; i < argc; i++)
        printf("argv[%d] = %s\n", i, argv[i]);
    return 0;
}