#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define V 7
#define qAresta 42 
#define nullAresta 0
#define qtdComb 720  // Numero de vertices -1 (!fatorial)

// como representar em lista de arestas?
struct Aresta{
	int vEmergente;
	int vIncidente;
	float peso;
}aresta[qAresta];

struct Caixeiro{
	int combinacao[V+1];
	float custo;
}combCaxViaj[qtdComb];

int posCx = 0;




struct Caminho{
	char texto[8*V];
}caminho[V];

float vetorCusto[V];

int mAdj[V][V];

//funções
void inicializar();
void inicializarAresta();
void imprimirListaAresta();
void imprimirMatriz();
void transformarArestaEmMatriz();
void transformarMatrizEmAresta();
void imprimirVetorCusto();
void imprimirCaminhos();
void caixeiro(int vInicio);
void imprimirCaixeiro();
void buscarMenorRota();
void calcularPesos();
void combinacoes(int vetor[], int n, int combinacao[],
		int posicao, int k, int utilizados[]);


void main(void){	

	inicializar();
	imprimirMatriz();
	transformarMatrizEmAresta();
	imprimirListaAresta();
	caixeiro(5);
	imprimirCaixeiro();
	buscarMenorRota();	   

}

// criar a função de inicialização
void inicializar(){
	setlocale(LC_ALL,"Portuguese");
	
	int i, j;
	for(i = 0; i < V; i++)
		vetorCusto[i] = 8015056586684760100;

	for(i = 0; i < V;i++)
		for(j = 0; j < V;j++)
			mAdj[i][j] = nullAresta;
			
	//vertice 0
	mAdj[0][1] = 3; 
	mAdj[0][2] = 4;
	mAdj[0][3] = 11;
	mAdj[0][4] = 2;
	mAdj[0][5] = 5;
	mAdj[0][6] = 3;
	
		
	//vertice 1
	mAdj[1][0] = 3;
	mAdj[1][2] = 8;
	mAdj[1][3] = 9;
	mAdj[1][4] = 1;
	mAdj[1][5] = 6;
	mAdj[1][6] = 4;

		
	//vertice 2
	mAdj[2][0] = 4;
	mAdj[2][1] = 8;
	mAdj[2][3] = 7;
	mAdj[2][4] = 3;
	mAdj[2][5] = 9;
	mAdj[2][6] = 7;
 
	
	//vertice 3
	mAdj[3][0] = 11;
	mAdj[3][1] = 9;
	mAdj[3][2] = 7;
	mAdj[3][4] = 12;
	mAdj[3][5] = 6;
	mAdj[3][6] = 8;

	//vertice 4
	mAdj[4][0] = 2;
	mAdj[4][1] = 1;
	mAdj[4][2] = 3;
	mAdj[4][3] = 12;
	mAdj[4][5] = 4;
	mAdj[4][6] = 10;
	
	//vertice 5
	mAdj[5][0] = 5;
	mAdj[5][1] = 6;
	mAdj[5][2] = 9;
	mAdj[5][3] = 6;
	mAdj[5][4] = 7;
	mAdj[5][6] = 15;
	
	//vertice 6
	mAdj[6][0] = 3;
	mAdj[6][1] = 4;
	mAdj[6][2] = 7;
	mAdj[6][3] = 8;
	mAdj[6][4] = 10;
	mAdj[6][5] = 15;

	
}

// criar a função de impressão da matriz
void imprimirMatriz(){
	int i,j;
	for(i=0;i<30;i++) printf("=");
	printf("\n           Matriz          \n");
	for(i=0;i<30;i++) printf("-");
	printf("\n");
	for(i=0;i < V;i++){
		for(j=0;j< V;j++){
			printf("%d\t",mAdj[i][j]);
		}
		printf("\n");
	}
	for(i=0;i<30;i++) printf("=");
	printf("\n");
}

void imprimirListaAresta(){
	int i;
	for(i=0;i<30;i++) printf("=");
	printf("\n     Lista de aresta          \n");
	for(i=0;i<30;i++) printf("-");
	printf("\n");
	for(i = 0; i < qAresta; i++){
		printf("\t%d  ==>  %d\t%.f\n",aresta[i].vEmergente,aresta[i].vIncidente,aresta[i].peso);
	}
	for(i=0;i<30;i++) printf("=");
	printf("\n");
}

void transformarMatrizEmAresta(){
	// a partir da matriz de incidencia gera-se a lista de aresta
	int i, j, k = 0;
	for(i = 0; i < V;i++){
		for(j = 0; j < V;j++){
			if(mAdj[i][j] != nullAresta){
				aresta[k].vEmergente = i;
				aresta[k].vIncidente = j;
				aresta[k].peso = mAdj[i][j];
				k++;
			}
		}
	}
}

void imprimirVetorCusto(){
	int i;
	printf("\n\n--------- Vetor Custos --------\n");
	for(i = 0; i < V;i++){
		printf("%.f\n",vetorCusto[i]);
	}
	printf("\n\n--------------------------\n");
}

void imprimirCaminhos(){
	int i, j;
	printf("\n\n--------------- Vetor Caminhos com Custo ------------------\n");
	for(i=0;i < V;i++){
		printf("Custo = %.f\t%s\n",vetorCusto[i],caminho[i].texto);
	}
	printf("\n--------------------------------------------------------\n");
}

void caixeiro(int vInicio){
	int i,k = 0, vetor[V-1];
	//cria o vetor com os vertices diferentes de vInicio
	for(i = 0; i < V; i++){
		if(i != vInicio){
			vetor[k] = i;
			k++; 
		}
	}
	
	// Vetor temporário para armazenar as combinações
    int combinacao[V-1];

    // Vetor para marcar os números já utilizados
    int utilizados[V-1];
    for (i = 0; i < V-1; i++) {
        utilizados[i] = 0;
    }

    // cria todas as combinações do vetor com números distintos
    combinacoes(vetor, V-1, combinacao, 0, V-1, utilizados);
    
    // adiciona o primeiro e utlimo elemento que é vInicio
    for(i = 0; i < qtdComb;i++){
    	combCaxViaj[i].combinacao[0] = vInicio;
    	combCaxViaj[i].combinacao[V] = vInicio;
	}
	
	// calcula os pesos dos caminhos gerados
	
	calcularPesos(); 
}

void combinacoes(int vetor[], int n, int combinacao[], 
		int posicao, int k, int utilizados[]) {
    int i;
	if (posicao == k) {
        // Quando a combinação é completa, transfere para a estrutura       
        for (i = 0; i < k; i++) {        	
        	combCaxViaj[posCx].combinacao[i+1] = combinacao[i];
		}
		posCx++; 
        return;
    }

    for (i = 0; i < n; i++) {
        if (!utilizados[i]) { // Verifica se o número já foi utilizado
            combinacao[posicao] = vetor[i];
            utilizados[i] = 1; // Marca o número como utilizado
            combinacoes(vetor, n, combinacao, posicao + 1, k, utilizados);
            utilizados[i] = 0; // Desmarca o número para que possa ser utilizado em outra combinação
        }
    }
}

void calcularPesos(){
	int i, j, k;
	float soma;
	for(i = 0; i < qtdComb; i++){
		soma = 0;
		for(j = 0; j < V; j++){
			soma = soma + mAdj[combCaxViaj[i].combinacao[j]][combCaxViaj[i].combinacao[j+1]];
		}
		combCaxViaj[i].custo = soma;	
	}	
}

void buscarMenorRota(){
	int i, posicao;
	float menor = 2903809129823;
	for(i = 0; i < qtdComb; i++){
		if(combCaxViaj[i].custo < menor){
			menor = combCaxViaj[i].custo;
			posicao = i;
		}
	}
	printf("\n\nA menor Rota é : ");
	for(i = 0; i < V+1; i++){
		printf("%d ", combCaxViaj[posicao].combinacao[i]);
	}
	printf("  com custo: %0.f\n",combCaxViaj[posicao].custo);
}

void imprimirCaixeiro(){
	printf("\n\n======================= Caixeiro Viajante =========================\n");
	int i, j, k;
	for(i = 0; i < qtdComb; i++){
		for(j = 0; j < V; j++){
			printf("%d ",combCaxViaj[i].combinacao[j]);
		}
		printf("%d\t%0.f\n",combCaxViaj[i].combinacao[j],
		combCaxViaj[i].custo);		
	}
	printf("\n\n===================================================================\n");
}




