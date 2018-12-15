#include <stdio.h>
#include<stdlib.h>
#include "grafos.h"
#define BRANCO 1
#define PRETO 3
#define CINZA 2
#define EXISTECAMINHO 0

/*documentação das funções*/

void ordenacaoTopologica(Grafo *g);/*exibe a ordenação topológica do grafo G*/

void visita (Grafo *g, int *cor,int u,int *ordenado,int *ordenacao);/*função auxiliar da ordenação topológica*/

void caixeiroViajante (Grafo g);/*percorre todo o grafo G visitando todos os vertices exatamente 1 vez*/

void viagem (Grafo g, int *cor,int u,int *d,int *caminho, int nivel);/*função auxiliar do caixeiro viajante*/

void kruskal (Grafo G); /* gera a AGM do grafo G*/

int caminho (Grafo *g, int origem,int destino);/*utiliza o algoritmo de dijkstra para verificar se existe um caminho entre o vertice de origem e o vertice de destino, vai servir de auxiliar no algoritmo de kruskal*/

void SelectionSort(int *vet,int n); /*metodo simples de ordenação de um vetor*/


void prim (Grafo g, int origem); /*cria a arvore geradora minima do grafo G*/

int grau (Grafo G, int vertice); /*retorna o grau do vertice dentro do grafo G*/

void ordenacaoTopologica(Grafo *g)
{
	if (g->tipo == NORIENTADO)
		printf("/nNão é possível fazer a ordenacao topologica de grafos nao orientados.");
	else{
	int cor[g->vertices + 1];/*vetor de cores do algoritmo*/
	int i;
	for (i=1;i<=g->vertices;i++)
		cor[i] = BRANCO;
	int ordenacao[g->vertices];
	int ordenado = 0;
	for (i=1; i<=g->vertices;i++)
		if (cor[i] == BRANCO)
			visita(g,&cor[0],i,&ordenado,&ordenacao[0]);
	printf("\n");
	for(i=0;i<g->vertices;i++)
		printf("%d ", ordenacao[i]);
}

}

void visita (Grafo *g, int *cor,int u,int *ordenado,int *ordenacao)
{

	cor[u] = CINZA;

	int i;

	for (i=1;i<=g->vertices;i++)
	{
		if(g->matrizAdj[u][i] !=0 && cor[i] == BRANCO)
		{
			visita(g,cor,i,ordenado,ordenacao);
		}
	}
	cor [u] = PRETO;
	ordenacao [*ordenado] = u;
	(*ordenado) ++;
}

void caixeiroViajante (Grafo g)
{
	int cor[g.vertices + 1];
	int i,caminho[g.vertices+1],d=0;
	for(i=1;i<=g.vertices;i++)
		cor[i] = BRANCO;


	int u = 1+rand()%g.vertices;
	viagem(g,&cor[0],u,&d,&caminho[0],0);

	d = d+ g.matrizAdj[u][caminho[g.vertices-1]];
	caminho[g.vertices] = u;

	printf("\nCaminho: ");
	for (i=0;i<=g.vertices;i++)
		printf("%d ",caminho[i]);


	printf("\n Distancia percorrida %d",d);


}

void viagem (Grafo g, int *cor,int u,int *d,int *caminho, int nivel)
{
	int i;
	cor[u] = PRETO;
	caminho[nivel] = u;
	nivel++;
	for (i=1;i<=g.vertices;i++)
		if (i!=u && g.matrizAdj[u][i] != 0 && cor[i] == BRANCO)
		{
			*d = *d + g.matrizAdj[u][i];

			viagem (g,cor,i,d,caminho,nivel);
		}

}

void kruskal (Grafo g)
{

	if (g.tipo == ORIENTADO)
	{
		printf("\nSó é possível encontrar uma árvore geradora mínima partindo de grafos não orientados.");

	}else{


	Grafo agm;

	novoGrafoAGM (&agm,g.vertices);/*grafo que representará a arvore geradora minima*/

	int i,j; /*irão percorrer a matriz de adjacencia em busca da aresta de menor peso;*/
	int aux,auxi,auxj;

	/*como o grafo é não orientado, podemos pegar somente a matriz triangular superior pra contabilizar os pesos, para isso criaremos um vetor e colocaremos nele todos os pesos*/
	int quantidadepesos=0;
	for(i=1;i<g.vertices;i++)
	{
		quantidadepesos+=i;
	}


	int pesos[quantidadepesos];/*cria um vetor do tamanho da quantidade de pesos*/

	for(i=1,aux=0; i<=g.vertices; i++)
		for (j=i+1;j<=g.vertices;j++)
			pesos[aux++] = g.matrizAdj[i][j];



	SelectionSort (&pesos[0],quantidadepesos);/*ordena o vetor de pesos*/

	int cont = 0;

	do {
		aux = pesos[cont];/*aux recebe a aresta de menor peso ainda não visitada*/
		for (i=1;i<=g.vertices;i++)
			for (j=i+1;j<=g.vertices;j++)
				if (g.matrizAdj[i][j] == aux && (auxi != i || auxj!=j))
					goto ACHOU;

ACHOU:
	auxi = i;
	auxj = j;
	aux = caminho (&agm,i,j) ;
		if (aux != EXISTECAMINHO){
			adcArestaNOrientada(&agm,i,j,g.matrizAdj[i][j]);

		}


		cont ++;
	}while (cont !=quantidadepesos);

	imprimeMatrizAdj(agm);


}
}


int caminho (Grafo *g, int origem, int destino)
{
   int S[g->vertices+1]; /*s eh o subconjunto dos nós rotulados pemanentemente*/
    int d[g->vertices+1];
    int N[g->vertices+1];
    int pred[g->vertices+1];
    int i,j,cont,min=999999;
    int adjs[g->vertices+1];

    for(i=1;i<=g->vertices;i++){
        d[i] = 1000000;
        S[i] = BRANCO;
        N[i] = PRETO;
        pred[i] = -1;
    }
    d[origem] = 0;
    pred[origem] = 0;

    for(j=1;j<=g->vertices;j++){
		adjs[j] = g->matrizAdj[origem][j];

}
    for(i=1;i<=g->vertices;i++){
	if (adjs[i] != 0)
	{
       	 	d[i] = adjs[i];
       		pred[i] = origem;
	}
    }

    for(cont=1,i=1;cont<=g->vertices;cont++)
    {
        min = 999999;
        for(j=1;j<=g->vertices;j++)
        {
            if(d[j] != 0 && d[j]<min && N[j] == PRETO){
                min = d[j];
                i = j;
            }
        }

        S[i] = PRETO;
        N[i] = BRANCO;

        for(j=1;j<=g->vertices;j++)
		adjs[j] = g->matrizAdj[i][j];

        for(j=1;j<=g->vertices; j++)
        {
            if (adjs[j] != 0 && d[j]> d[i] + adjs[j]){
                d[j] = d[i] + adjs[j];
                pred[j] = i;
            }
        }
    }

if (pred[destino] != -1)
	return EXISTECAMINHO;
return -1;



}

void SelectionSort(int *vet,int n){
    int aux;
    int i,j,min;
    for (i=0;i<(n);i++) {
        min = i;
        for (j=(i+1);j<n;j++) {
            if(vet[j] < vet[min]) {
                min = j;
            }
        }
        if (i!=min) {
            aux = vet[i];
            vet[i] = vet[min];
            vet[min] = aux;
        }
    }
}





void prim (Grafo g, int origem)
{

	if (g.tipo == ORIENTADO)
	{
		printf("\nSó é possível encontrar uma árvore geradora mínima partindo de grafos não orientados.");

	}else{


	Grafo agm;

	novoGrafoAGM (&agm,g.vertices);/*grafo que representará a arvore geradora minima*/

	int *arvore; /*vetor que diz quais vertices já estão na arvore*/
	arvore = (int *) calloc (g.vertices+1,sizeof(int));
	arvore[origem] = 1;
	int i,j,aux,auxj,auxi; /*auxiliares para percorrer a matriz de adjacencia procurando pelo menor peso*/

	int cont=1;
	do {
		aux = 9999;
		for(i=1;i<=g.vertices;i++)
		{
			if (arvore[i] == 1)
				for (j=1;j<=g.vertices;j++)
				{
					if (g.matrizAdj[i][j] != 0 && i!=j && aux>g.matrizAdj[i][j] && arvore[j] == 0)
					{

						aux = g.matrizAdj[i][j];

						auxj = j;
						auxi=i;
					}
				}

		}

		arvore[auxj] = 1;
		adcArestaNOrientada (&agm, auxi, auxj,aux);
		cont++;
	}while (cont <= g.vertices);

	imprimeMatrizAdj(agm);


}
}


int grau (Grafo G, int vertice)
{
	int i; /*variavel que vai percorrer a linha do vertice contando seu grau*/
	int aux = 0; /* variavel que vai guardar o grau do vertice;*/
	for(i=1;i<=G.vertices;i++)
		if (G.matrizAdj[vertice][i] != 0)
			aux++;

	return aux;




}
