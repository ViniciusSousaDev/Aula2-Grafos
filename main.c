#include <stdio.h>
#include <locale.h>

#define V 5

int mAdj[V][V] = {0};

int main(void){
      setlocale(LC_ALL, "Portuguese");

      //vertice 1
      mAdj[0][1] = 1;
      mAdj[0][2] = 1;
      mAdj[0][3] = 1;
      
      //vertice 2
      mAdj[1][0] = 1;
      mAdj[1][2] = 1;
      mAdj[1][4] = 1;
      
      //vertice 3
      mAdj[2][0] = 1;
      mAdj[2][1] = 1;
      
      //vertice 4
      mAdj[3][0] = 1;
      
      //vertice 5
      mAdj[4][1] = 1;

      for(int i = 0; i < V; i++){
            for(int j = 0; j < V; j++){
                  printf("%d ", mAdj[i][j]);
            }
            printf("\n");
      }

      return 0;
}
