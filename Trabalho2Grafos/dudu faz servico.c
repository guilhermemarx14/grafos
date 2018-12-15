#include <stdio.h>
#include <stdlib.h>


#define BRANCO 0
#define CINZA -1
#define PRETO 1

//Conforme os vértices vão sendo visitados pela DFS eles vão mudando de cor, indicando o estado da busca atual. O pseudo-código da DFS fica da seguinte maneira:
//Inicialmente todos os vértices são pintados com a cor branca, indicando que eles ainda não foram visitados.
//Assim que um vértice é visitado, e antes dele ser “desvisitado”, sua cor passa a ser cinza.
//Para cada vértice sendo visitado, ele irá visitar todos os seus vizinhos.
//Quando um vértice é “desvisitado”, ou seja, a função chega ao final, a cor desse vértice passa a ser black.

//Para resolver o problema em específico (encontrar loops), podemos tirar vantagem do seguinte insight: se um vértice u da cor cinza visitar um vértice v 
//também de cor cinza, isso indica que há um caminho entre o vértice v que chegou até o vértice u, assim como há um caminho entre o vértice u que chega até o 
//vértice v, ou seja, um loop. 

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

int dfs(int u) {
    g.cor[u] = CINZA;
    int i;
    for( i=0; i<g.grau[u]; i++) {
        int v = g.matriz[u][i];
        if(g.cor[v] == BRANCO) {
            if(!dfs(v)) {
                return 0;
            }
        } else if(g.cor[v] == CINZA) {
            return 0;
        }
    }

    g.cor[u] = PRETO;
    return 1;
}

int main(){

    int x, y, m,i,vezes;

    init_G();
    init_grafo(31000);
    scanf("%d",&vezes);

    while(vezes--){


    scanf("%d %d", &g.nvertices, &m);

    int inicio;
    for(i = 0; i <m; i++){
        scanf("%d %d", &x, &y);
        if(i==0)
        inicio=x-1;
        g.matriz[x-1][g.grau[x-1]++] = y-1;

    }
    if(!dfs(inicio))printf("SIM\n\n");
    else printf("NAO\n\n");
    init_grafo(g.nvertices+2);
    }

    return 0;
}

