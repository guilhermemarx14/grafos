#ifdef WIN32
#define PAUSE 1
#else
#define PAUSE 0
#endif

#include <stdio.h>
#include <stdlib.h>
#include "algoritmos.h"

void pause(){
if(PAUSE==1){
   system("pause");
   system("cls");
}
else{

   system("read -p \"Pressione enter para continuar...\" saindo");
         system("clear");
}


}
int main()
{
	int nvertices,narestas,vertice1,vertice2,peso,op,cont, origem;
	Grafo g,*aux;
	printf("\nCriando um grafo...\n\n\n");
	printf("\nDigite o numero de vertices: ");
	scanf("%d",& nvertices);
	printf("\nDigite o numero de arestas: ");
	scanf("%d",& narestas);

	novoGrafo(&g,nvertices,narestas);

	MENU:
		pause();
    printf("\n\t\tMENU\nDigite o numero da opcao desejada:");
    printf("\n1-Ordenacao Topologica\n2-Algoritmo de Kruskal\n3-Algoritmo de Prim\n4-Caixeiro Viajante\n5-Sair\n");
    scanf("%d",&op);
    switch(op){
        case 1:
        ordenacaoTopologica(&g);
        break;

        case 2:
       	kruskal(g);
        break;

        case 3:
        printf ("Digite a origem: ");
        scanf ("%d", &origem);
        prim(g, origem);
        break;

        case 4:
        printf("\nDigite o numero de vertices do grafo: ");
        scanf("%d",&vertice1);
	aux = criaGrafoCompleto(vertice1);
        caixeiroViajante(*aux);
	destroiGrafo(aux);
        break;
	case 5:
	goto FINAL;
        default: printf("\nDigite um numero valido!");
        break;
    }
    printf("\n");

	goto MENU;

FINAL:
	if (PAUSE == 1)
		system("cls");
	else
	system("clear");

	printf("\nAlunos: GUILHERME MARX, PALOMA GOMES, TALITA SANTOS\n\n");
	destroiGrafo(&g);
    return 0;
}

