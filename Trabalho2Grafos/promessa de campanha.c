#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Vetor que guardara de um vertice foi visitado na DFS.
int ans[9999];

typedef struct grafo
{
    int nvertices;
    struct grafo *prox;//lista de vertices adjacentes ao vertice nvertices
}Grafo;

//Insere uma nova lista para o nvertices
Grafo *insereLista(int nvertices){
    Grafo *g = NULL;
    g = (Grafo*)malloc(sizeof(Grafo));
    g->nvertices = nvertices;
    g->prox = NULL;
    return g;
}

//Insere uma nova aresta que parte de vertice1 para vertice2
Grafo *insereAresta(Grafo *g[1000],int nvertices,int vertice2){
    Grafo *novo = insereLista(vertice2);
    Grafo *aux,*aux2;
    if(g[nvertices] == NULL)
        g[nvertices] = novo;
    else{
        aux = g[nvertices];
        aux2 = aux;
        while(aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novo;
    }
    return g[nvertices];
}

//busca em profundidade
void dfs ( Grafo *g[1000], int vertice1, int total ) {
    int stck[1000], visitado[1000]; //Pilha, Marcados de vertices visitados
    int stck_size = 0, pop; // Tamanho da pilha, auxiliar que guarda um elemento desempilhado.

	// Inicializa os dois vetores com zero.
    memset ( visitado, 0, sizeof( visitado ) );
    memset ( stck, 0, sizeof( stck ) );

	// Empilha todos os elementos na lista de adjacencia com o id "start".
    Grafo * aux = g[vertice1];

    while ( aux != NULL ) {
        stck_size ++;
        stck[ stck_size ] = aux->nvertices;
        aux = aux->prox;
    }
	
	// Marca "start" como visitado.

    visitado[ vertice1 ] = 1;
    int i;

    while ( stck_size > 0 ) {
		// Desempilha um elemento.
        pop = stck[ stck_size ];
        stck_size--; // Diminui o tamanho da pilha.

		// Caso o vertice desempilhado nao tenha sido visitado...
        if ( visitado[ pop ] == 0 ) {
			// Adiciona todos os seus vertices adjacentes na pilha caso nao tenham sido visitados.
            Grafo *aux2 = g[ pop ];
            while ( aux2 != NULL ) {
                if ( visitado[ aux2->nvertices] == 0 ) {
                    stck_size ++;
                    stck[ stck_size ] = aux2->nvertices;
                }
                aux2 = aux2->prox;
            }
			// Marca como visitado (vetor "visitado") E como alcancavel (vetor "ans").
            visitado[ pop ] = 1;
            ans[pop] = 1;
        }
    }
}

int main(){
	int t, n, m, x, y, i,k;
        scanf ( "%d", &t ); // Numero de casos de teste.
        for ( k = 1; k <= t; k++ ) {
            // Inicializacao do grafo e vetor resposta.
            Grafo *g[1000] = { };
            memset ( ans, 0, sizeof ( ans ) );

            scanf ( "%d", &n ); // Numero de vertices
            scanf ( "%d", &m ); // Numero de arestas.

            for ( i = 1; i <= m; i++ ) {
                scanf ( "%d %d", &x, &y );
                // Insere uma aresta que parte de x para y e de y para x.
                g[y] = insereAresta ( g, y, x );
                g[x] = insereAresta ( g, x, y );
            }
            // Imprime o "caso" conforme o enunciado do problema.
            printf ( "Caso #%d: ", k );

            // Resultado. Inicia com -1 pois a primeira DFS nao conta.
            int totalsets = -1;
            for ( i = 1; i <= n; i++ ) {
                // Caso um vertice nao tenha sido alcancado ainda, chamar outra DFS a partir dele.
                if ( ans[i] == 0 ) {
                    dfs ( g, i, n );
                    // Como nao foi alcancado anteriormente significa que precisa de uma estrada para este vertice.
                    totalsets++;
                }
            }
            if ( totalsets >= 1 ) 
                printf ("\nAinda falta(m) %d estrada(s)", totalsets );
            else printf ("\nA promessa foi cumprida" );  
        }

}



