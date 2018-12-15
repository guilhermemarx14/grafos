#include <stdio.h>
#include <stdlib.h>


#define BRANCO 0
#define CINZA -1
#define PRETO 1


typedef struct{

    int **matriz;
    int *grau;
    int nvertices;
    int *cor;

} grafo;

grafo g;

void init_G()
{

    int i;
    g.matriz=malloc((31000)*sizeof(int));
    g.grau=malloc((31000)*sizeof(int));
    g.cor=malloc((31000)*sizeof(int));
    for(i=0;i<31000;i++)g.matriz[i]=malloc((31000)*sizeof(int));
}

void init_grafo(int m){

    g.nvertices = 0;
    int i;
    for( i = 0; i <m; i++)
        {
            g.grau[i] =0;
            g.cor[i] = 0;
        }

}

void dfs(int u,int *cont) {
    g.cor[u] = CINZA;
    int i,j;
    
		for( i=0; i<g.grau[u]; i++) {
	        int v = g.matriz[u][i];
	        if(g.cor[v] == BRANCO) {
	           dfs(v,cont);
	        } if(g.cor[v] == CINZA) {
	            (*cont)++;
	        }
	    }
    g.cor[u] = PRETO;
}

int main(){

    int x, y, vertice1,vertice2,i,vezes;

    init_G();
    init_grafo(10000);
    

    int inicio;
    int c = 0;
    
    scanf("%d",& vezes);
    
    for(i = 0;i<vezes ; i++){
        scanf("%d %d", &x, &y);
        if(i==0)
        inicio=x-1;
        
        g.matriz[x-1][g.grau[x-1]++] = y-1;

    }
    for(i=0;i<10000;i++){
    	
    	if(g.cor[i]==BRANCO){
    		dfs(i,&c);
		}
	}
    
    printf("\n %d casamentos", c);
    init_grafo(g.nvertices+2);
    
    return 0;
}

