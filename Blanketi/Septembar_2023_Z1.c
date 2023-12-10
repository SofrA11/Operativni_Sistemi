/*Zadatak 1. Korišćenjem programskog jezika C napisati Linux progam koji sadrži bafer u koji se može smestiti 10 integer brojeva.
Jedna zasebna nit, kreirana prilikom startovanja programa, periodično generiše 10 slučajnih brojeva (u opsegu od 0 do 199) i upisuje ih u ovaj bafer.
Kada se u baferu nađe nova grupa brojeva, glavna nit (main funkcija) treba da odredi da li je zbir tih brojeva veći od 800 i odštampa adekvatnu poruku na standardnom izlazu.
Ovaj postupak generisanja 10 brojeva i ispitivanje vrednosti njihovog zbira treba da se ponavlja sve dok sračunat zbir ne prede 1000.
Adekvatno sinhronizovati rad niti koja generiše brojeve i glavne niti koja proverava njihov zbir. (25 poena)*/


#include<stdio.h>
#include<pthread.h>
#include<time.h>
#include<stdlib.h>

#define N 10
#define TRUE 1
#define FALSE 0

int buffer[N];
pthread_mutex_t mutex1;

void* nit(void* arg)
{

	pthread_mutex_lock(&mutex1);
	for( int i=0;i<N;i++)
	{	
		buffer[i] = rand()%50;
	}
	pthread_mutex_unlock(&mutex1);
	sleep(rand()%3);

}

int main()
{
srand(time(NULL));
pthread_t nit1;
pthread_mutex_init(&mutex1,NULL);
int suma=0;
pthread_create(&nit1,NULL,(void*)nit,(void*)NULL);
pthread_join(nit1,NULL);
int count=0;
pthread_mutex_lock(&mutex1);
while(suma<1000)
{
for( int i=0;i<N;i++)
{
suma+=buffer[i];
}
pthread_mutex_unlock(&mutex1);

printf("Suma %d. bach-a je: %d\n", count+1,suma);
count++;
}

pthread_mutex_destroy(&mutex1);

return 0;
}
