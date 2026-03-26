#include <stdio.h>
#include <locale.h>
#define V 7

int mAdj[V][V];

void main(void){
	popular();
	imprimirMatriz();
}

void popular(){
		setlocale(LC_ALL,"Portuguese");
	//vertice 1			//vertice 2			//vertice 3
	mAdj[0][1] = 1;		mAdj[1][0] = 1;		mAdj[2][1] = 1;
	mAdj[0][3] = 1;		mAdj[1][2] = 1;		mAdj[2][3] = 1;
	mAdj[0][4] = 1;		
			
	//vertice 4			//vertice 5			//vertice 6
	mAdj[3][0] = 1;		mAdj[4][0] = 1;		mAdj[5][3] = 1;
	mAdj[3][2] = 1;		
	mAdj[3][5] = 1;
	mAdj[3][6] = 1;
	
	//vertice 7
	mAdj[6][3] = 1;
}

void buscaEmLargura(){
		int vert, j;
	printf("\nInsira o vertice para mostrar os seus vizinhos: ");
	scanf("%d",&vert);
	printf("\nOs vizinhos do vertice %d sao: ",vert);
	for(j = 0; j < V; j++){
		if(mAdj[vert-1][j] == 1)
			printf("%d, ",j+1);
	}				
}


void imprimirMatriz(){
		int i, j;
	for(i = 0; i < V; i++){
		for(j =0; j < V; j++){
			printf("%d\t",mAdj[i][j]);
		}
		printf("\n");
	}
}



