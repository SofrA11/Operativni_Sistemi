#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void generisiMatricu(int N)
{
int matr[N][N];
int broj =1;

	for(int i=0;i<N;i++)
	{ for(int j=0;j<N;j++)
	{
		matr[i][j]=broj++;
	}
	}
	
	for(int i=0;i<N;i++)
	{ for(int j=0;j<N;j++)
	{
		printf("%d  ",matr[i][j]);
	}
	printf("\n");
	
	}

}


int main(int argc, char* argv[]){
int N = atoi(argv[1]);

generisiMatricu(N);

return 0;

}




