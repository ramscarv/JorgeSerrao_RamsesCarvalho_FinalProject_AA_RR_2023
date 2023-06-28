#include <iostream>
#include <list>
#include<bits/stdc++.h>

#define MAX_VERTICES 10000

#define MAX_EDGES 10000000
int N_colors;

using namespace std;

// Uma classe que representa um grafo não direcionado
class Graph{
    int V;    // Num. de vertices
    list<int> *adj;    // Um vetor dinamico de lista de adjacencia
public:
    // Construtor e destrutor
    Graph(int V)   { this->V = V; adj = new list<int>[V]; }
    ~Graph()       { delete [] adj; }

    // funcao para add uma aresta ao grafo
    void addEdge(int v, int w);

    // Printa a coloração gulosa dos vertices greedy coloring of the vertices
    void greedyColoring();
};

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);  // Nota: o grafo não é derecionado
}

// Atribui cores (comecando em 0) para todos os vértices e imprime
// a atribuição de cores
void Graph::greedyColoring(){
    int result[V];

    // Atribui a primeira cor ao primeiro vértice
    result[0]  = 0;

    // Inicializa os vértices V-1 restantes como não atribuídos
    for (int u = 1; u < V; u++)
        result[u] = -1;  // nenhuma cor é atribuída a u

    // Um vetor temporario para armazenar as cores disponiveis. O valor True
    // de "available[cr]" seguinifica que a cor já está atribuida
    // a algum vertice vizinho.
    bool available[V];
    for (int cr = 0; cr < V; cr++)
        available[cr] = false;

    // Atribui cores aos vertices V-1 restantes.
    for (int u = 1; u < V; u++){
        // Processa todos os vértices adjacentes e marca suas cores
        // como indisponível
        list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (result[*i] != -1)
                available[result[*i]] = true;

        // Encontra a primeira cor disponivel
        int cr;
        for (cr = 0; cr < V; cr++)
            if (available[cr] == false)
                break;

        result[u] = cr; // Atribui a cor encontrada
        if (cr > N_colors)
            N_colors = cr;

        // Reseta os valores de volta para false pata a proxima iteracao
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (result[*i] != -1)
                available[result[*i]] = false;
    }

    /*// printa o resultado
    for (int u = 0; u < V; u++)
        cout << "Vertex " << u << " --->  Color "
             << result[u] << endl;*/
    cout << "Cores: " << N_colors << endl;
}
int main(){
    set<pair<int, int>> container;
	set<pair<int, int>>::iterator it;

	srand(time(NULL));

	int NUM; // Number of Vertices
	int NUMEDGE; // Number of Edges

	NUM = MAX_VERTICES;

	// Define the maximum number of edges of the graph
	// Since the most dense graph can have N*(N-1)/2 edges
	// where N = nnumber of vertices in the graph
    NUMEDGE = MAX_EDGES;
    Graph g(NUM);

    // First print the number of vertices and edges
    printf("%d %d\n", NUM, NUMEDGE);
    //pior caso
    for(int i  = 0; i < NUM; i++){
        for(int j  = i + 1; j < NUM; j++)
            g.addEdge(i, j);
    }
    
    cout << "Coloring of graph \n";
    g.greedyColoring();

    /*
    Graph g1(5);
    g1.addEdge(0, 1);
    g1.addEdge(0, 2);
    g1.addEdge(1, 2);
    g1.addEdge(1, 3);
    g1.addEdge(2, 3);
    g1.addEdge(3, 4);
    cout << "Coloring of graph 1 \n";
    g1.greedyColoring();

    Graph g2(5);
    g2.addEdge(0, 1);
    g2.addEdge(0, 2);
    g2.addEdge(1, 2);
    g2.addEdge(1, 4);
    g2.addEdge(2, 4);
    g2.addEdge(4, 3);
    cout << "\nColoring of graph 2 \n";
    g2.greedyColoring();
    */
    return 0;
}
