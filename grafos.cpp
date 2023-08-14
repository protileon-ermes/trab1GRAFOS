#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#define MAXSIZE 300000

struct Aresta {
    int inicio, fim;
    double peso;
};

struct Ponto {
    int x, y;
};

int pai[MAXSIZE];
Aresta arestas[MAXSIZE];
Ponto pontos[MAXSIZE];

//funcao para encontra o pai
int encontrarPai(int i) {
    return i == pai[i] ? i : encontrarPai(pai[i]);
}

double kruskal(int numArestas) {
    int i;
    int inicio, fim;
    double pesoTotal;

    for (i = 0, pesoTotal = 0; i < numArestas; ++i) {
        inicio = encontrarPai(arestas[i].inicio);
        fim = encontrarPai(arestas[i].fim);

        if (fim != inicio)
            pai[inicio] = pai[fim], pesoTotal += arestas[i].peso;
    }

    return pesoTotal;
}

// Funcao que calcula a distância Euclidiana entre dois pontos
double distancia(Ponto a, Ponto b) {
    return hypot(b.x - a.x, b.y - a.y);
}

// Funcao de comparação para ordenar as arestas com base em seus pesos
bool comparar(const Aresta &a, const Aresta &b) {
    return a.peso < b.peso;
}

int main() {
    int i, j, C, n, indiceAresta;
    std::cout << "insira a quantidade de casos teste";
    std::cin >> C;
    std::cout << "insira a quantidade de linhas";
    
    while (C--) {// Loop para cada caso de teste
        std::cin >> n;
            
            for (i = 0, indiceAresta = 0; i < n; ++i) {// Entrada dos pontos
            std::cout << "insira os pontos";
            std::cin >> pontos[i].x >> pontos[i].y;

            for (j = 0; j < i; ++j) { // cria arestas
                arestas[indiceAresta].inicio = j;
                arestas[indiceAresta].fim = i;
                arestas[indiceAresta].peso = distancia(pontos[j], pontos[i]) / 100.0;
                ++indiceAresta;
            }
        }

        std::sort(arestas, arestas + indiceAresta, comparar);// Ordenação das arestas pelo peso

        for (i = 0; i < n; ++i)// Inicialização da estrutura de conjuntos disjuntos

            pai[i] = i;

        printf("%.2lf\n", kruskal(indiceAresta));
    }

    return 0;
}