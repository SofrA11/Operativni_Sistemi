#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define N 10

int buffer[N];
pthread_mutex_t mutex1;

void *thread1(void *arg)
{
	int i = 0;
	
	while (i < N)
	{	
		pthread_mutex_lock(&mutex1);
		buffer[i] = (int)(rand() % 300);
		pthread_mutex_unlock(&mutex1);		
		i+=2;		
		//sleep(1);
	}
	
}
void *thread2(void *arg)
{
	int i = 1;
	
	while (i < N)
	{		
		pthread_mutex_lock(&mutex1);
		buffer[i] =(int)(rand() % 200 + 300);
		pthread_mutex_unlock(&mutex1);
		i+=2;		
		//sleep(1);
	}	
}

int main()
{
	srand(time(NULL));
	pthread_t nit1, nit2;
	pthread_mutex_init(&mutex1, NULL);

	for (int j = 0; j < 5; j++)
	{
		pthread_create(&nit1, 0, (void *)thread1, (void *)NULL);
		pthread_create(&nit2, 0, (void *)thread2, (void *)NULL);

		pthread_join(nit1, NULL);
		pthread_join(nit2, NULL);

		int sum = 0;

		for (int i = 0; i < N; i++)
		{
			sum += buffer[i];
		}
		if (sum > 2000)
		{
			printf("Suma %d je veca od 2000 \n ", sum);
		}
		else
		{
			printf("Suma %d je manja od 2000 \n", sum);
		}
		//sleep(3);
	}
	pthread_mutex_destroy(&mutex1);
	return 0;
}
