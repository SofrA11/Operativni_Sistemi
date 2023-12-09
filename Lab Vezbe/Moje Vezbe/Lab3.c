/*Korišćenjem programskog jezika C kreirati Linux program koji kreira dve dodatne niti koje komuniciraju korišćenjem deljenog niza od 5 celobrojnih vrednosti. Glavna nit u deljeni niz upisuje slučajno generisane vrednosti u opsegu -10 do 10. Po završetku popunjavanja niza prva dodatna nit u tom deljenom nizu sve negativne vrednosti menja njihovim apsolutnim vrednostima. Kada prva dodatna nit završi modifikaciju niza druga dodatna niz prvi element niza menja srednjom vrednošću svih elemenata niza. Pošto druga dodatna nit završi upis vrednosti na poziciju prvog elementa niza glavni program na ekranu štampa sve elemente niza i izlazi. */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define N 5
/*Deljivi resurs koji se definise kao globalna promenljiva*/
int niz[N];
/*Semafori za medjusobno iskljucenje prilikom priatupanja deljivom resursu*/
pthread_mutex_t mutex1,mutex2;
void * nit1(void * arg)
{

while(1)
{
pthread_mutex_lock(&mutex1);


for(int i=0;i<5;i++)
{
    if(niz[i]<0)
    {
        niz[i]=niz[i]*(-1);
    }
}

pthread_mutex_unlock(&mutex1);
break;
}

}
void * nit2(void * arg)
{
int pos;
while(1)
{
/*Pristupanje deljivom resursu u KS*/
pthread_mutex_lock(&mutex2);
int sum=0;
for(int i=0;i<5;i++)
{
    sum+=niz[i];
}
int avg = sum/5;
niz[0]=avg;
pthread_mutex_unlock(&mutex2);
break;
}

}

int main()
{
for(int i=0;i<5;i++)
{
    niz[i]=(int)(rand() % 21 - 10);
}
pthread_t n1, n2;
/*Kreiranje mutex-a*/
pthread_mutex_init(&mutex1, NULL);
pthread_mutex_init(&mutex2, NULL);
/*Kreiranej nit*/
pthread_create(&n1, NULL, (void *)nit1, (void *)NULL);
sleep(2);
pthread_create(&n2, NULL, (void *)nit2, (void *)NULL);
/*Ceka se da se niti n1, n2, n3 zavrse*/
pthread_join(n1, NULL);
pthread_join(n2, NULL);
/*Unistavaju se mutex-i*/
pthread_mutex_destroy(&mutex1);
pthread_mutex_destroy(&mutex2);
for(int i=0;i<5;i++)
{
   printf("%d", niz[i]);
}
int o=1;
}
