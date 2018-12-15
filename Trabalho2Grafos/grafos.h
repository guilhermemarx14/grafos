#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define FAIL 0
#define ORIENTADO 1
#define NORIENTADO 0
#define AGM 5

/*biblioteca criada com o intuito de se criar estruturas para o trabalho prático 2 da disciplina de grafos*/

typedef struct
{
	int** matrizAdj;/*matriz de adjacencia do grafo*/
	int** matrizInc;/*matriz de incidencia do grafo*/
	int vertices;/*numero de vertices do grafo*/
	int arestas;/*numero de arestas do grafo*/
	int tipo; /*variavel que vai guardar se o grafo é orientado ou nao*/
}Grafo;

/*documentação das funções*/

void novoGrafo(Grafo *novo,int nvertices, int narestas); /*funcao cria o objeto grafo e o preenche chamando as funcoes de preenchumento*/

void preencheGrafoNOrientado(Grafo *g, int narestas); /* preenche um grafo não orientado*/

void preencheGrafoOrientado(Grafo *g, int narestas); /* preenche um grafo orientado*/

void destroiGrafo(Grafo *grafo); /* libera todos os espaços alocados na funcao do novo grafo, deixa a variavel grafo como se tivesse acabado de ser declarada*/

int adcArestaOrientada (Grafo *g,int verticeOrigem,int verticeDestino,int peso); /*adiciona uma aresta  orientada ao grafo g, caso a aresta ja exista, ou seja um laco ou seja invalida, retorna FAIL e nao faz nada, se tudo ocorrer bem, retorna OK*/

int adcArestaNOrientada (Grafo *g, int verticeOrigem, int verticeDestino, int peso); /*adiciona uma aresta nao orientada ao grafo g, caso a aresta ja exista, ou seja um laco ou seja invalida, retorna FAIL e nao faz nada, se tudo ocorrer bem, retorna OK*/

Grafo* criaGrafoCompleto (int nvertices);

void imprimeMatrizAdj (Grafo grafo); /*imprime a matriz de adjacencia do grafo*/

void imprimeMatrizInc (Grafo grafo); /*imprime a matriz de incidencia do grafo*/

void novoGrafoAGM (Grafo *agm,int vertices); /* cria o grafo que será, posteriormente uma arvore geradora minima */


void novoGrafo(Grafo *novo,int nvertices, int narestas)
{
	int cont;

	/*inicializando matriz de adjacencia*/
	novo->matrizAdj = (int **) calloc (nvertices+1,sizeof(int *));
	for (cont=1;cont<=nvertices;cont++)
		novo->matrizAdj[cont] = (int*) calloc (nvertices+1,sizeof(int));

	/*inicializando matriz de incidencia*/
	novo -> matrizInc = (int**) calloc(nvertices+1,sizeof(int*));
	for (cont=1;cont<=nvertices;cont++)
		novo -> matrizInc[cont] = calloc(narestas+1,sizeof(int));

	/*como calloc ja inicializa tudo com zero nao ha necessidade de zerar as entradas das matrizes*/
	novo->vertices = nvertices;
	novo->arestas = 0;

	int tipo;
	printf("\nDigite 1 para criar um grafo ORIENTADO e qualquer outro valor para um grafo NAO-ORIENTADO: ");
	scanf("%d",&tipo);

	if (tipo == ORIENTADO){
		preencheGrafoOrientado(novo,narestas);
	}
	else preencheGrafoNOrientado(novo,narestas);

}

void preencheGrafoNOrientado(Grafo *g, int narestas){
		int origem,destino,peso;
		g -> tipo = NORIENTADO;
	 	/*adicionando arestas ao grafo*/
		while (g->arestas < narestas)
		{
			printf("\n\nDigite os dois vértices e o peso: ");
			scanf ("%d %d %d", &origem, &destino,&peso);
			if (adcArestaNOrientada (g,origem,destino,peso) == OK)
				printf("\nAresta adicionada com sucesso");
			else printf("\nA aresta nao pode ser adicionada");

		}

}

void preencheGrafoOrientado (Grafo *g,int narestas)
{
		int origem,destino,peso;
		g -> tipo = ORIENTADO;
	 	/*adicionando arestas ao grafo*/
		while (g->arestas < narestas)
		{
			printf("\n\nDigite vertice de Origem, vertice de destino e peso: ");
			scanf ("%d %d %d", &origem, &destino,&peso);
			if (adcArestaOrientada (g,origem,destino,peso) == OK)
				printf("\nAresta adicionada com sucesso");
			else printf("\nA aresta nao pode ser adicionada");

		}


}
void destroiGrafo(Grafo *grafo)
{
	int cont;

	/*desalocando a matriz de adjacencia*/
	for (cont = 1; cont <= grafo->vertices; cont++)
	{
		free(grafo -> matrizAdj[cont]);
	}
	free(grafo-> matrizAdj);

	/*desalocando a matriz de incidencia*/
	if (grafo->tipo != AGM)
	for (cont =1; cont <=grafo->vertices; cont++)
	{
		free(grafo -> matrizInc[cont]);
	}
	if (grafo->tipo != AGM)
	free (grafo -> matrizInc);

}


int adcArestaOrientada (Grafo *g,int verticeOrigem,int verticeDestino,int peso)
{

	if (verticeOrigem > 0 && verticeDestino >0 &&
		 verticeOrigem <= g-> vertices && verticeDestino<= g->vertices && /*essas duas linhas garantem que o numero digitado será valido...*/
	       	 verticeOrigem != verticeDestino && /* garante que nao sera criado nenhum laço*/
		 g->matrizAdj[verticeOrigem][verticeDestino] == 0 )/*garante que nao existe aresta naquele lugar ainda*/
	{
		g->matrizAdj[verticeOrigem][verticeDestino] = peso;
	if (g->tipo != AGM)
		g->matrizInc[verticeOrigem][g->arestas] = 1;
	if (g->tipo != AGM)
		g->matrizInc[verticeDestino][g->arestas] = -1;
		g->arestas++;
		return OK;

	}
	else return FAIL;

}

int adcArestaNOrientada (Grafo *g, int verticeOrigem, int verticeDestino, int peso)
{
	int retorno = FAIL;
	if (adcArestaOrientada(g,verticeOrigem,verticeDestino,peso) == OK){
		g->arestas --;
		retorno = OK;
	}

	adcArestaOrientada(g,verticeDestino,verticeOrigem,peso);
return retorno;

}

Grafo* criaGrafoCompleto (int nvertices)
{
	Grafo *novo;
	novo = (Grafo*) malloc(sizeof(Grafo));
	int i,j,cont,peso,narestas;
	narestas = nvertices*(nvertices-1);
	narestas/=2;

	/*inicializando matriz de adjacencia*/
	novo->matrizAdj = (int **) calloc (nvertices+1,sizeof(int *));
	for (cont=1;cont<=nvertices;cont++)
		novo->matrizAdj[cont] = (int*) calloc (nvertices+1,sizeof(int));

	/*inicializando matriz de incidencia*/
	novo->matrizInc = (int**) calloc(nvertices+1,sizeof(int*));
	for (cont=1;cont<=nvertices;cont++)
		novo->matrizInc[cont] = calloc(narestas+1,sizeof(int));

	/*como calloc já inicializa tudo com zero não há necessidade de zerar as entradas das matrizes*/
	novo->vertices = nvertices;
	novo->arestas = 0;
	novo->tipo = NORIENTADO;

	for(i=1;i<=nvertices;i++)
		for (j=i+1;j<=nvertices;j++){
			peso = 1+rand()%1000;
			adcArestaNOrientada (novo,i,j,peso);
		}
	return novo;
}

void imprimeMatrizAdj (Grafo grafo)
{
	printf("\n");
	int i,j;
	for(i=1;i<=grafo.vertices;i++)
	{
		for (j=1;j<=grafo.vertices;j++)
			printf("%5d ",grafo.matrizAdj[i][j]);
		printf("\n");
	}

}

void imprimeMatrizInc (Grafo grafo)
{
	printf("\n");
	int i,j;
	for(i=1;i<=grafo.vertices;i++)
	{
		for (j=1;j<=grafo.arestas;j++)
			printf("%d ",grafo.matrizAdj[i][j]);
		printf("\n");
	}


}

void novoGrafoAGM (Grafo *novo,int nvertices)
{
	int cont;

	/*inicializando matriz de adjacencia*/
	novo->matrizAdj = (int **) calloc (nvertices+1,sizeof(int *));
	for (cont=1;cont<=nvertices;cont++)
		novo->matrizAdj[cont] = (int*) calloc (nvertices+1,sizeof(int));
	/*inicializando matriz de incidencia*/
	novo -> matrizInc = NULL;


	/*como calloc ja inicializa tudo com zero nao ha necessidade de zerar as entradas das matrizes*/
	novo->vertices = nvertices;
	novo->arestas = 0;
	novo->tipo = AGM;


}





