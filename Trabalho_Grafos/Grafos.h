#include <stdio.h>
#include <stdlib.h>
#define BRANCO 10
#define CINZA 20
#define PRETO 30


typedef struct{
    int aresta;
    int peso;
}Adj; /*adj é uma estrutura criada para simular uma aresta*/

typedef struct{
    int no;
    Adj *adj;
}No;/*Um nó possui um numero de identificação e uma "lista" de adjascencia*/

typedef struct{
    No *vertice;
    int grau;

}Grafo;/*Um grafo nada mais é do que um vetor de nós*/

void SelectionSort(int *vet,int n){
    int aux;
    int i,j,min;
    for (i=1;i<=(n);i++) {
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


void novoGrafo (Grafo *g, int vertices) /*recebe um grafo vazio e a quantidade de vertices e inicializa o grafo*/
{

    g->vertice = (No*)calloc(vertices+1,sizeof(No));
    g->grau = vertices;
    int i,j;
    for (i=1;i<=vertices;i++)
    {
        g->vertice[i].adj = (Adj*) calloc(vertices+1,sizeof(Adj));
        g->vertice[i].no = i;
        for(j=1;j<=vertices;j++)
        {
            g->vertice[i].adj[j].aresta = 0;
            g->vertice[i].adj[j].peso = 0;
        }
    }

}

void adcAresta (Grafo *g, int vertice1, int vertice2, int peso)/*adiciona uma aresta entre os vertices 1 e 2, caso ja exista uma aresta entre eles, não faz nada*/
{

 int arestas = numeroArestas(g);

    if (vertice1 == vertice2)
        return;
    if (g->vertice[vertice1].adj[vertice2].aresta == 0){
    g->vertice[vertice1].adj[vertice2].aresta = arestas+1;/*adiciona o vertice 2 a lista de adjascencia do vertice 1*/
    g->vertice[vertice1].adj[vertice2].peso = peso;

    g->vertice[vertice2].adj[vertice1].aresta = arestas+1;/*adiciona o vertice 1 a lista de adjascencia do vertice 2*/
    g->vertice[vertice2].adj[vertice1].peso = peso;
    }
printf("Aresta adicionada\n");
}

int numeroArestas(Grafo *g)
{
    int i,numeroDeArestas =0;
    for(i=1;i<=g->grau;i++)
        numeroDeArestas+=grauVertice(g,i);

    return numeroDeArestas/2;/*a soma dos graus de todos os vertices é o dobro do numero de arestas*/
}

void trocaPeso (Grafo *g, int vertice1, int vertice2, int peso)/*troca o peso de uma aresta entre os vertices 1 e 2, caso não haja uma aresta lá, não faz nada*/
{
    if (g->vertice[vertice1].adj[vertice2].aresta != 0)
    {
        g->vertice[vertice1].adj[vertice2].peso = peso; /*troca o peso na lista de adjascencia do vertice 1*/
        g->vertice[vertice2].adj[vertice1].peso = peso; /*troca o peso na lista de adjascencia do vertice 2*/
        printf("\nPeso trocado");
    }
}

int* arestaAdj (Grafo *g, int arestaA)/*retorna um vetor de inteiros com as arestas adjascentes a uma arestaA, o 0 marca o final do vetor*/
{
    int arestas = numeroArestas(g);
    int *retorno = (int*)calloc(arestas,sizeof(int));
    int i,j,a,b=0;

    for(i=0;i<arestas;i++)
        retorno[i] = 0;


    if (arestaA > arestas || arestaA <=0)
        return retorno;


    for (i=1;i<=g->grau;i++)
    {
        for (j=1;j<=g->grau;i++)
        {
            if (g->vertice[i].adj[j].aresta == arestaA)
                goto ENCONTROUARESTA;
        }
    }

ENCONTROUARESTA:/*indica que os numeros i e j marcam os dois vertices que sao incidentes a aresta A*/
    for (a=1;a<=g->grau;a++)/*percorre a lista de adjascencia do vertice i*/
    {
        if (!presente(g,retorno,g->vertice[i].adj[a].aresta)&& g->vertice[i].adj[a].aresta!=0 && g->vertice[i].adj[a].aresta!= arestaA ){
            retorno[b] = g->vertice[i].adj[a].aresta;
            b++;

        }
    }
    for (a=1;a<=g->grau;a++)/*percorre a lista de adjascencia do vertice j*/
    {
        if (!presente(g,retorno,g->vertice[j].adj[a].aresta) && g->vertice[j].adj[a].aresta!=0 && g->vertice[j].adj[a].aresta!= arestaA){
            retorno[b] = g->vertice[j].adj[a].aresta;
            b++;


        }

    }

    return retorno;

}

int presente (Grafo *g, int *retorno, int a)/*verifica se um inteiro a está presente em um vetor de inteiros*/
{
    int i=0, arestas = numeroArestas(g);
    for(i=0;i<=arestas;i++)
    {
        if(retorno [i] == 0)
            return 0;
        if (retorno [i] == a)
            return 1;
    }
}

int* verticeAdj (Grafo *g, int verticeV)/*retorna um vetor de inteiros com os vertices adjascentes a um verticeV, o 0 marca o final do vetor*/
{
    int aux,b=0;
    int *retorno=(int*)calloc(g->grau,sizeof(int));
    for(aux=0;aux<g->grau;aux++)
    {
        retorno[aux] = 0;
    }

    for(aux=1;aux<=g->grau;aux++)
    {
        if (g->vertice[verticeV].adj[aux].aresta != 0){
            retorno[b] = aux;
            b++;
        }
    }
    return retorno;
}

int* arestaInc (Grafo *g, int verticeV)/*retorna um vetor de inteiros com as arestas incidentes a um verticeV, o 0 marca o final do vetor*/
{
    int aux,b=0;
    int *retorno=(int*)calloc(g->grau,sizeof(int));

    for(aux=0;aux<g->grau;aux++)
    {
        retorno[aux] = 0;
    }

    for(aux=1;aux<=g->grau;aux++)
    {
        if (g->vertice[verticeV].adj[aux].aresta != 0){
            retorno[b] = g->vertice[verticeV].adj[aux].aresta;
            b++;
        }
    }
    return retorno;
}

int* verticeInc(Grafo *g, int arestaA)/*retorna um vetor de inteiros com os vertices incidentes a uma arestaA, o 0 marca o final do vetor*/
{
    int arestas = numeroArestas(g);
    int *retorno=(int*)calloc(arestas,sizeof(int));
    int i,j,a;
    for(i=0;i<arestas;i++)
        retorno[i] = 0;

    if (arestaA > arestas || arestaA <=0)
        return retorno;

    for (i=1;i<=g->grau;i++)
    {
        for (j=1;j<=g->grau;j++)
        {
            if (g->vertice[i].adj[j].aresta == arestaA)
              {
                      retorno[0] = i;
                      retorno[1] = j;
                      break;
              }
        }

    }


    return retorno;
}

int grauVertice (Grafo *g, int verticeV)/*retorna o grau de um vertice V*/
{
    int grau=0,i;
    for (i=1;i<=g->grau;i++)
    {
        if (g->vertice[verticeV].adj[i].aresta != 0){ /*aresta = 0 significa que a aresta não existe, portanto só somaremos as arestas existentes*/
            grau++;
        }
    }
    return grau;
}

void adcArestaAleatoria(Grafo *g,int n)/*adiciona n arestas aleatorias dentro do grafo g*/
{
    int vertice1,vertice2,peso,i=1;
    while (i<=n){
        vertice1 = 1+rand()%(g->grau);
        vertice2 = 1+rand()%(g->grau);
        peso = 1+rand()%100;
        if (g->vertice[vertice1].adj[vertice2].aresta == 0 && vertice1 != vertice2 && vertice1 <=g->grau && vertice2 <=g->grau){
            adcAresta(g,vertice1,vertice2,peso);
            i++;
        }
    }
}

int* grafoIsomorfo(Grafo *g){
    int i;

    int *vet_grau=(int*)calloc(g->grau+1,sizeof(int));
    for(i=1;i<=g->grau;i++){
        vet_grau[i] = grauVertice(g,i);
    }
    SelectionSort(vet_grau,g->grau+1);
    return vet_grau;
}

void imprimeGrafoLista(Grafo *g)
{
    int *vetor, cont,cont2;
    for(cont = 1; cont<=g->grau;cont++)
    {
        vetor = verticeAdj(g,cont);
        printf("\n%d",cont);
        for (cont2=0; vetor[cont2] != 0; cont2++)
        {
            if (vetor[cont2] != 0)
                printf(" -> %d",vetor[cont2]);
        }
    }
}

void imprimeGrafoMatrizAdj(Grafo *g)
{
    int matriz [g->grau+1][g->grau+1];
    int i,j;
    for (i=1;i<=g->grau;i++)
        for (j=1;j<=g->grau;j++)
            matriz[i][j]= 0;

    for(i=1;i<=g->grau;i++){
        for(j=1;j<=g->grau;j++){
            if(i==j)
                matriz[i][j] = 0;
            else{
                if(g->vertice[i].adj[j].aresta == 0)
                    matriz[i][j] = 0;
                else matriz[i][j] = g->vertice[i].adj[j].peso;
            }
        }

    }



    printf("\n\nMATRIZ DE ADJACENCIA\n\n");
    printf("\t|");

    for (i=1;i<=g->grau;i++)
        printf(" %3d |",i);




    for (i=1;i<=g->grau;i++){
        printf("\n%7d |",i);
        for (j=1;j<=g->grau;j++){
            printf(" %3d |",matriz[i][j]);

        }

    }
}


int adjacente (Grafo *g, int vertice1, int vertice2){
    int *adj = verticeAdj(g,vertice1);
    int i;
    for(i=0;i<g->grau;i++)
    {
        if (adj[i] == vertice2)
            return 1;
    }
    return 0;

}

void imprimeGrafoMatrizInc(Grafo *g){
    int numArestas = numeroArestas(g);
    int *verticesInc;
    int matriz[g->grau +1][numArestas+1];
    int i,j;

    for(i=0;i<=numArestas;i++)
        for(j=0;j<=g->grau;j++)
            matriz [j][i] =0;


    for(i=1;i<=numArestas;i++)
    {

        verticesInc = verticeInc(g,i);
        if(i==5)
        printf("\n%d %d",verticesInc[0],verticesInc[1]);
        matriz[verticesInc[0]] [i] = 1;
        matriz[verticesInc[1]] [i] = 1;

}

printf("\n\nMATRIZ DE INCIDENCIA\n\n");


printf("\t ");
for(i=1;i<=numArestas;i++)
    printf(" %3d |",i);

for(i=1;i<=g->grau;i++){
        printf("\n%7d |",i);
    for(j=1;j<=numArestas;j++){
        printf(" %3d |",matriz[i][j]);

}
}
}
void trocaVertice(Grafo *g, int vertice1, int vertice2){
    No aux;
    Adj aux2;
    int i,j;
        if (adjacente(g,vertice1,vertice2))
    {
        aux2 = g->vertice[vertice1].adj[vertice2];
        g->vertice[vertice1].adj[vertice2] = g->vertice[vertice1].adj[vertice1];
        g->vertice[vertice1].adj[vertice1] = aux2;


        aux2 = g->vertice[vertice2].adj[vertice2];
        g->vertice[vertice2].adj[vertice2] = g->vertice[vertice2].adj[vertice1];
        g->vertice[vertice2].adj[vertice1] = aux2;
    }
    aux = g->vertice[vertice1];
    g->vertice[vertice1] = g->vertice[vertice2];
    g->vertice[vertice2] = aux;

    for (i=1;i<=g->grau;i++){
            for(j=1;j<=g->grau;j++){
                if (i==vertice1 || i==vertice2){}
                else {
                    aux2 = g->vertice[i].adj[vertice1];
                    g->vertice[i].adj[vertice1] = g->vertice[i].adj[vertice2];
                    g->vertice[i].adj[vertice2]=aux2;
                }
            }

    }



}

void grafoDMACS(Grafo *z){

	FILE *file;
	file = fopen ("grafo.txt", "r"); /*ota dando erro aki, tem alguma outra forma de faer isso?*/

	if (file == NULL){
		printf ("Nao foi possivel abrir o arquivo.\n"); /*Caso o nome do arquivo seja informado de forma incorreta, aparecerá essa mensagem*/
		system ("pause");
		return;
	}

    int a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t; /*uma variavel para cada numero do arquivo txt*/

    fscanf (file, "%i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i", &a, &b, &c, &d, &e, &f, &g, &h, &i, &j, &k, &l, &m, &n, &o, &p, &q, &r, &s, &t); /*ligando cada variável ao %i para que seja feita a impressão ou possíveis alterações*/
	novoGrafo(z,a);
    adcAresta(z,c,d,e);
    adcAresta(z,f,g,h);
    adcAresta(z,i,j,k);
    adcAresta(z,l,m,n);
    adcAresta(z,o,p,q);
    adcAresta(z,r,s,t);
	printf("Grafo criado!\n");
	fclose (file);
}

//estrutura para a fila...
typedef struct celula{
    int i;
    struct celula *prox;
}Celula;

typedef struct{
    Celula *prim;
    Celula *ult;
}Fila;

int FilaVazia (Fila F)
{
    if (F.prim == F.ult)
        return 1;
    return 0;
}

void novaFila (Fila *f){
    f->prim = (Celula*) malloc(sizeof(Celula));
    f -> ult = f-> prim;
    f->prim->prox = NULL;
}

void PoeVerticeNaFila(Fila *f,int num)
{
    Celula *aux= (Celula*)malloc(sizeof(Celula));

    aux -> prox = NULL;
    aux -> i = num;

    f -> ult -> prox = aux;
        printf("\npassou aqui");
    f-> ult = aux;


}

void RetiraVerticeFila(Fila f){
    if(!FilaVazia(f)){
    Celula *aux = f.prim ->prox;
    f.prim->prox = aux -> prox;
    free(aux);
    }

}
int presente2 (int num, int *a, int tamA)
{
    int i;
    for(i=0;i<tamA;i++){
        if (a[i] == num)
            return 1;
    }
    return 0;
}
void BuscaEmLargura(Grafo *G,int raiz){
//    int raiz;
//    printf("\nDigite o ponto inicial da busca: ");
//    scanf("%d",&raiz);
    int *verticesMarcados = (int*)malloc(G->grau * sizeof(int));//vetor de vertices marcados
    int tamVerticesMarcados= 0;
    int vertice1;
    int cont=0;
    int naoVisitados[G->grau+1];
    for(cont=0;cont<G->grau;cont++)
    {
        naoVisitados[cont] = 0;
    }
    int *p;
    Fila F;
    novaFila(&F);
    Celula *aux;

    verticesMarcados[0] = raiz;//marca raiz
    tamVerticesMarcados++;
    //poe raiz na fila
    aux= (Celula*)malloc(sizeof(Celula));

    aux -> prox = NULL;
    aux -> i = raiz;

    F . ult -> prox = aux;
    F. ult = aux;

    while(tamVerticesMarcados < G->grau){//enquanto a fila nao esta vazia
            if (F.prim->prox != NULL){
        vertice1 = F.prim->prox->i;//vertice que esta no inicio da fila
         p = verticeAdj(G,vertice1);// Ladj = lista de adjacencia de vertice1

        cont=0;
        while(p[cont]!=0){//enquanto a lista de adjacencia do vertice1 nao acaba
            if(!presente2(p[cont],verticesMarcados,tamVerticesMarcados)){//busca p->vertice no vetor verticesMarcados ///////////////////////////////////////////////////////////MARCADO
                verticesMarcados[tamVerticesMarcados++] = p[cont];//marcou p->vertice
                //PoeVerticeNaFila(&F , p[cont]);//poe p->vertice na fila

                    aux= (Celula*)malloc(sizeof(Celula));

                    aux -> prox = NULL;
                    aux -> i = p[cont];

                    F . ult -> prox = aux;
                    F. ult = aux;
                //arestas que compoem arvore geradora mínima, aresta (vertice1, p->vertice)
            }

            cont++;
        }
        RetiraVerticeFila(F);
            } else{
                verticesMarcados[tamVerticesMarcados++] = -1;
            }
    }
    int flag=0;
    for(cont=0;cont<tamVerticesMarcados;cont++)
    {
        if (verticesMarcados[cont] == -1)
            flag = 1;
    }
    int cont2= 0;
    int flag2;
    if (flag ==1)
    {
        for(cont=1;cont<=G->grau;cont++)
        {
            flag2=1;
            for(cont2=0;cont2<tamVerticesMarcados;cont2++)
                if (cont == verticesMarcados[cont2])
                    flag2 =0;

            if (flag2 == 1)
            {
                naoVisitados[cont] = cont;

            }


        }

    }
    printf("\nCaminho seguido pelo algoritmo: ");
    for(cont=0;cont<tamVerticesMarcados;cont++)
        if (verticesMarcados[cont] != -1)
        printf("%d ",verticesMarcados[cont]);
    printf("\nVertices nao visitados: ");
    if (flag == 1)
    {
        for(cont=0;cont<=G->grau;cont++)
        if(naoVisitados[cont] != 0)
        printf("%d ",naoVisitados[cont]);
    }
}



int tempo =0;
int NIVEL;
void BuscaEmProfundidade(Grafo *g,int inicio){
    int u=1,i;
    int flag=0;
    int d[g->grau +1];
    for (u=1;u<=g->grau;u++)
        d[u] = -1;
    int cor[g->grau+1];


    for(u=1;u<=g->grau;u++)
        cor[u] = BRANCO;

    visita(g,inicio,&cor[0],&d[0]);
    printf("\nAlcance do vertice %d:",inicio);
    for(u=1;u<=g->grau;u++){
        if(d[u] == -1)
            printf("\n\tVertice %d nao pode ser alcancado.",u);
        else printf("\n\tVertice %d alcancado com tempo %d",u,d[u]);
    }

    printf ("\n\nCaminho do algoritmo: %d",inicio);
    for(i=2;i<=tempo;i++)
    {
        for(u=1;u<=g->grau;u++)
       {
           if (d[u] == i)
            printf(" -> %d",u);
           if(d[u] == -1)
            flag =1;
       }
    }
    if (flag == 1){
    printf("\n\nVertices nao visitados: ");

    for (u=1;u<=g->grau;u++)
    {
        if(d[u] == -1 && flag ==1){
            printf("%d",u);
            flag = 0;
        }else if (d[u]== -1){
            printf(", %d",u);
        }

    }
    printf(".\n");
    }
}

void visita (Grafo *g, int u,int *cor, int *d)
{
    int *adjacente = verticeAdj(g,u);

    int i,a, flag = 0;
    a = grauVertice(g,u);

    int v;
    cor[u] = CINZA;
    tempo++;
    d[u] = tempo;
    for(i=0;adjacente[i]!=0;i++){
        v = adjacente[i];
        if (cor[v] == BRANCO)
            visita(g,v,cor,d);
        cor[u] = PRETO;

    }

}

void dijkstra (Grafo *g, int origem)
{
    int S[g->grau+1]; //s eh o subconjunto dos nós rotulados pemanentemente
    int d[g->grau+1];
    int N[g->grau+1];
    int pred[g->grau+1];
    int i,j,cont,min=999999;
    int *adjs;

    for(i=1;i<=g->grau;i++){
        d[i] = 1000000;
        S[i] = BRANCO;
        N[i] = PRETO;
        pred[i] = -1;
    }
    d[origem] = 0;
    pred[origem] = 0;
    adjs = verticeAdj(g,origem);
    for(i=0;adjs[i]!=0;i++){
        d[adjs[i]] = g->vertice[origem].adj[adjs[i]].peso;
        pred[adjs[i]] = origem;
    }

    for(cont=1;cont<=g->grau;cont++)
    {
        min = 999999;
        for(j=1;j<=g->grau;j++)
        {
            if(d[j] != 0 && d[j]<min && N[j] == PRETO){
                min = d[j];
                i = j;
            }
        }

        S[i] = PRETO;
        N[i] = BRANCO;

        adjs = verticeAdj(g,i);

        for(j=0;adjs[j] != 0; j++)
        {
            if (d[adjs[j]]> d[i] + g->vertice[i].adj[adjs[j]].peso){
                d[adjs[j]] = d[i] + g->vertice[i].adj[adjs[j]].peso;
                pred[adjs[j]] = i;
            }
        }
    }

    printf("\nPartindo do vertice %d\n\n",origem);
    for(i=1;i<=g->grau;i++)
    {
        if (i!=origem){

        if(d[i] == 1000000)
            printf("\nO vertice %d nao pode ser alcançado",i);
        else
            printf("\nDistancia minima ate o vertice %d: %d",i,d[i]);
        }
    }
printf("\n\n");
    for(i=1;i<=g->grau;i++)
    {

        if (i!=origem){
        if(pred[i] == -1)
            printf("\nO vertice %d nao pode ser alcançado",i);
        else
        printf("\nPai do vertice %d: %d",i,pred[i]);

    }



}}

void caminhoMinimo(Grafo *g, int origem, int destino){
        int S[g->grau+1]; //s eh o subconjunto dos nós rotulados pemanentemente
    int d[g->grau+1];
    int N[g->grau+1];
    int pred[g->grau+1];
    int i,j,cont,min=999999;
    int *adjs;

    for(i=1;i<=g->grau;i++){
        d[i] = 1000000;
        S[i] = BRANCO;
        N[i] = PRETO;
        pred[i] = -1;
    }
    d[origem] = 0;
    pred[origem] = 0;
    adjs = verticeAdj(g,origem);
    for(i=0;adjs[i]!=0;i++){
        d[adjs[i]] = g->vertice[origem].adj[adjs[i]].peso;
        pred[adjs[i]] = origem;
    }

    for(cont=1;cont<=g->grau;cont++)
    {
        min = 999999;
        for(j=1;j<=g->grau;j++)
        {
            if(d[j] != 0 && d[j]<min && N[j] == PRETO){
                min = d[j];
                i = j;
            }
        }

        S[i] = PRETO;
        N[i] = BRANCO;

        adjs = verticeAdj(g,i);

        for(j=0;adjs[j] != 0; j++)
        {
            if (d[adjs[j]]> d[i] + g->vertice[i].adj[adjs[j]].peso){
                d[adjs[j]] = d[i] + g->vertice[i].adj[adjs[j]].peso;
                pred[adjs[j]] = i;
            }
        }
    }
    if(pred[destino] != -1){
    printf("\nCaminho Minimo: %d",destino);
    int aux;
    for (aux = pred[destino];aux != origem; aux = pred[aux])
        printf(" <- %d",aux);
    printf(" <- %d\n\n",origem);


    printf("\nCusto Minimo: %d\n\n",d[destino]);
    }
    else printf("\n\nNao existe caminho entre %d e %d...\n\n",origem,destino);
}
