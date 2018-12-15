#include "stdio.h"
#include "stdlib.h"
#include "Grafos.h"

int main(){
int op,op2,opcoes,cont,i,num_vertice,num_aresta,peso,vertice1,vertice2,arestaA,verticeV,num,num_v,num_a,v1,v2,p,vetor,a,arestas,vertices,grau_max,eh_ponderado,orig,dest,eh_diGrafo1,ini=5,origem,destino;
float peso1,dens;
Grafo g,h;
int *vet,*vet2,flag=0,*visitado,*custos;
ESCOLHANOVAMENTE:
    system("cls");
printf("\nComo deseja inserir o grafo?\n1.Grafo pronto(DIMACS)\n2.Montar grafo\n");
scanf("%d",&op);

if(op == 1){
	grafoDMACS(&g);
    goto PROXIMOMENU;
}else if(op == 2){
    printf("\nDeseja criar o grafo manualmente ou aleatorio? 1-Manualmente 2-Aleatorio ");
    scanf("%d",&op2);
    if(op2 == 1){
        printf("\nInforme o numero de vertices: ");
        scanf("%d",&num_vertice);
INFORMEADENSIDADE:
        printf("\nInforme a densidade(Entre 0 e 1): ");
        scanf("%f",&dens);
        if(dens <0 || dens >1)
        {
            printf("\nDigite um valor valido!!");
            goto INFORMEADENSIDADE;
        }
        num_aresta = (num_vertice*(num_vertice-1)*dens)/2;
        printf("\nO grafo tera %d arestas\n",num_aresta);
        novoGrafo(&g,num_vertice);
        for(cont=0;cont<num_aresta;cont++){
            printf("\nDigite os vertices e o peso:");
            scanf("%d",&vertice1);
            scanf("%d",&vertice2);
            scanf("%d",&peso);
            adcAresta (&g,vertice1,vertice2,peso);
        }
        goto PROXIMOMENU;
    }else if(op2 == 2){
        printf("\nDigite o numero de vertices do grafo: ");
        scanf("%d",&num_vertice);
INFORMEADENSIDADE2:
        printf("\nInforme a densidade(Entre 0 e 1): ");
        scanf("%f",&dens);
        if(dens <0 || dens >1)
        {
            printf("\nDigite um valor valido!!");
            goto INFORMEADENSIDADE2;
        }
        num_aresta = (num_vertice*(num_vertice-1)*dens)/2;
        printf("\nO grafo tera %d arestas\n",num_aresta);
        novoGrafo(&g,num_vertice);
		adcArestaAleatoria(&g,num_aresta);
		printf("\n");
		goto PROXIMOMENU;

    }else
        printf("\nDigite um numero valido\n");
        system("pause");
        goto ESCOLHANOVAMENTE;

}else
    printf("\nDigite um numero valido\n");
    system("pause");
    goto ESCOLHANOVAMENTE;
PROXIMOMENU:
system("pause");
system("cls");

do{
    printf("\n\tMENU:\n1.Verificar se os grafos sao isomorfos\n");
    printf("2.Imprimir arestas adjacentes a uma aresta A\n");
    printf("3.Imprimir vertices adjacentes a um vertice V\n");
    printf("4.Imprimir arestas incidentes a um vertice V\n");
    printf("5.Imprimir vertices incidentes a uma aresta A\n");
    printf("6.Imprimir o grau de um vertice\n");
    printf("7.Verificar se dois vertices sao adjacentes\n");
    printf("8.Substituir o peso de uma aresta\n");
    printf("9.Trocar dois vertices\n");
    printf("10.Algoritmo de Dijkstra\n");
    printf("11.Busca em largura\n");
    printf("12.Busca em profundidade\n");
    printf("13.Imprimir Lista de Adjacencia\n");
    printf("14.Imprimir Matriz de Incidencia\n");
    printf("15.Imprimir Matriz de Adjacencia\n");
    printf("16.Imprimir o nome dos integrantes\n");
    printf("17.Caminho minimo entre dois vertices.\n");
    printf("18.Voltar ao menu anterior\n");
    printf("19.Sair\n");
    scanf("%d",&opcoes);
    switch(opcoes){
    case 1:
        /*Criando novo grafo*/
        printf("\nInforme o numero de vertices: ");
        scanf("%d",&num_v);
INFORMEADENSIDADE3:
        printf("\nInforme a densidade(Entre 0 e 1): ");
        scanf("%f",&dens);
        if(dens <0 || dens >1)
        {
            printf("\nDigite um valor valido!!");
            goto INFORMEADENSIDADE3;
        }
        num_a = (num_v*(num_v-1)*dens)/2;
        printf("\nO grafo tera %d arestas\n",num_a);
        novoGrafo(&h,num_v);
        for(cont=0;cont<num_a;cont++){
            printf("\nDigite os vertices e o peso:");
            scanf("%d",&vertice1);
            scanf("%d",&vertice2);
            scanf("%d",&peso);
            adcAresta (&h,vertice1,vertice2,peso);
        }

        /*Comparando se os grafos sao isomorfos*/
        if(num_vertice==num_v && num_aresta==num_a ){

            vet = grafoIsomorfo(&g);
            vet2 = grafoIsomorfo(&h);
            a=0;
            for(cont=1;cont<=num_v;cont++){
                if(vet[cont]!=vet2[cont]){
                    a=-1;
                }

            }
            if(a==-1)
                printf("\nOs grafos nao sao isomorfos\n");
            else
                printf("\nOs grafos podem ser isomorfos\n");
        }else
            printf("\nOs grafos nao sao isomorfos\n");
        system("pause");
        system("cls");
        break;
    case 2:
        printf("\nDigite uma aresta: ");
        scanf("%d",&arestaA);

        vet = arestaAdj(&g,arestaA);
        printf("\nArestas adjacentes a aresta %d: ",arestaA);
            for(cont=0;vet[cont]!=0;cont++)
                printf(" %d ",vet[cont]);

        printf("\n");
        system("pause");
        system("cls");
        break;
    case 3:
        printf("\nDigite um vertice: ");
        scanf("%d",&verticeV);
        vet = verticeAdj (&g, verticeV);

        printf("\nVertices adjacentes ao vertice %d:",verticeV);
        for(cont=0;vet[cont]!=0;cont++)
            printf(" %d ",vet[cont]);

        printf("\n");
        system("pause");
        system("cls");
        break;
    case 4:
        printf("\nDigite um vertice: ");
        scanf("%d",&verticeV);
        vet = arestaInc (&g, verticeV);

         printf("\nArestas incidentes ao vertice %d:",verticeV);

        for(cont=0;vet[cont]!=0;cont++)
            printf(" %d ",vet[cont]);

        printf("\n");
        system("pause");
        system("cls");
        break;
    case 5:
        printf("\nDigite uma aresta: ");
        scanf("%d",&arestaA);
        vet = verticeInc(&g, arestaA);
        printf("\nVertices incidentes a aresta %d:",arestaA);

        for(cont=0;vet[cont]!=0;cont++)
            printf(" %d ",vet[cont]);
        printf("\n");
        system("pause");
        system("cls");
        break;
    case 6:
        printf("\nDigite um vertice: ");
        scanf("%d",&verticeV);
        num = grauVertice (&g, verticeV);
        printf("\nGrau do vertice %d: %d\n",verticeV,num);
        printf("\n");
        system("pause");
        system("cls");
        break;
    case 7:
        printf("\nDigite dois vertices: ");
        scanf("%d",&vertice1);
        scanf("%d",&vertice2);

        vet = verticeAdj (&g, vertice1);
        vet2 = verticeAdj (&g, vertice2);
        flag=0;
        for(cont=0,i=0;vet[cont]!=0 && vet2[i] !=0;cont++,i++){
            if(vet[cont]==vet2[i]){
                flag=1;
            }
        }
        if(flag==1)
            printf("\nOs vertices %d e %d sao adjacentes\n",vertice1,vertice2);
        else
            printf("\nOs vertices %d e %d nao sao adjacentes\n",vertice1,vertice2);
        system("pause");
        system("cls");
        break;
    case 8:
        printf("\nDigite uma aresta para ser trocado o peso: ");
        scanf("%d",&arestaA);
        printf("\nDigite o novo peso da aresta: ");
        scanf("%d",&peso);
        trocaPeso (&g, vertice1,  vertice2,  peso);

        printf("\n");
        system("pause");
        system("cls");
        break;
    case 9:
        printf("\nInforme os dois vertices a serem trocados: ");
        scanf("%d",&vertice1);
        scanf("%d",&vertice2);
        trocaVertice(&g, vertice1, vertice2);

        printf("\n");
        system("pause");
        system("cls");
        break;
    case 10:
        printf("\nDigite o vertice de origem: ");
        scanf("%d",& num_vertice);


        dijkstra(&g,num_vertice);

        printf("\n");
        system("pause");
        system("cls");
        break;
    case 11:
        printf("\nDigite o vertice de origem: ");
        scanf("%d",&ini);
        BuscaEmLargura(&g,ini);

        printf("\n");
        system("pause");
        system("cls");
        break;
    case 12:
        printf("\nDigite o vertice de origem: ");
        scanf("%d",&ini);
        BuscaEmProfundidade(&g,ini);
        printf("\n");
        system("pause");
        system("cls");
        break;

    case 13:
        imprimeGrafoLista(&g);
        printf("\n");
                system("pause");
        system("cls");
        break;
    case 14:
        imprimeGrafoMatrizInc(&g);
        printf("\n");
                system("pause");
        system("cls");
        break;
    case 15:
        imprimeGrafoMatrizAdj(&g);
        printf("\n");
                system("pause");
        system("cls");
        break;
     case 16:
        printf("\nGUILHERME MARX, PALOMA GOMES, TALITA SANTOS\n");
        system("pause");
        system("cls");
        break;
     case 17:
         printf("\nDigite dois vertices: ");
        scanf ("%d %d", &vertice1,&vertice2);
         caminhoMinimo(&g,vertice1,vertice2);
         system("pause");
         system("cls");
        break;
     case 18:
         goto ESCOLHANOVAMENTE;
        break;
        case 19:
        break;
    default:printf("\nDigite um numero valido! ");

    }

}
while (opcoes!=19);

system("pause");
return 0;
}


