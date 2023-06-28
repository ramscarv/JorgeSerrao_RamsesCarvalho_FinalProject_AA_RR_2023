#include <stdbool.h>
#include <stdio.h>
#include<bits/stdc++.h>
// numbero de vertices no grafo
#define V 10
#define E 50
void printa_solucao(int color[]);

// checa se o grafo colorido é seguro ou não
bool ehSeguro(bool graph[V][V], int color[]){
    // checa por todas os vertices
    for (int line = 0; line < V; line++)
        for (int column = line + 1; column < V; column++)
            if (graph[line][column] && color[column] == color[line])
                return false;
    return true;
}

/* Esta função resolve o problema de colorir com m cores usando recursao.
   Retorna falso se as m cores não podem ser atribuidas,
  snão retorna verdadeiro e printa
  otherwise, return true and prints as
  atribuições de cores em todos os vertices.
  assignments of colours to all vertices.*/
bool graphColoring(bool graph[V][V], int m, int index, int color[V]){
    //printf("1");
    // Se o indice atual chegar no fim
    if (index == V) {
        // se colorir é seguro
        if (ehSeguro(graph, color)) {
            // Printa a solucao
            printa_solucao(color);
            return true;
        }
        return false;
    }

    // Atribui cada cor de 1 até m
    for (int counter = 1; counter <= m; counter++) {
        color[index] = counter;

        // Recorrencia do resto dos vertices
        if (graphColoring(graph, m, index + 1, color))
            return true;

        color[index] = 0;
    }

    return false;
}

/* Funcao para printar a solucao */
void printa_solucao(int color[]){
    printf("A solucao existe:"
           " A seguir estão as cores atribuidas \n");
    for (int i = 0; i < V; i++)
        printf(" %d ", color[i]);
    printf("\n");
}


int main(){
    /* Criando o grafo a seguir e
       testando se é colorivel com m cores
      (0)---(1)
       |   / |
       |  /  |
       | /   |
      (3)---(2)
    */
    /*bool graph[V][V] = {
        { 1, 1, 0, 1 },
        { 1, 1, 1, 1 },
        { 0, 1, 1, 1 },
        { 1, 1, 1, 1 },
    };*/
    bool graph[V][V];

    for(int i = 0; i < V; i++)
        for(int j = 0; j < V; j++){
            graph[i][j] = 0;
            if (i == j)
                graph[i][j] = 1;
        }
    for(int i = 0; i < E; i++){
        int a = rand() % (V - 1);
        int b = rand() % (V - 1);
        graph[a][b] = 1;
        graph[b][a] = 1;
    }
    int m = V; // Numero de cores

    // Inicializa todos os valores como 0.
    // Esta inicializacao eh necessaria para o
    // funcionamento correto do ehSeguro()
    int color[m];
    for (int i = 0; i < m; i++)
        color[i] = 0;

    if (!graphColoring(graph, m, 0, color))
        printf("Solucao nao existe");

    return 0;
}
