#include <iostream>
#include "No.h"
#include "Aresta.h"
#include "Grafo.h"

using namespace std;


int main() {
    Grafo G, *Comp;
    No *N;

    int n = 6; //ADD
    int *nos = new int[n]{100, 20, 30, 50, 60, 35};//ADD

    N = new No[n];
//    G.setPonderadoAr(true);
    G.setDirecionado(true);

    //Nós
    for (int i = 0; i < n; i++) {
        N[i].setId(nos[i]);
        N[i].setIndex(i);
        G.adicionaNo(&N[i]);
    }

    //Arestas

    G.adicionaAresta(&N[0], &N[1]);
    G.adicionaAresta(&N[1], &N[2]);
    G.adicionaAresta(&N[2], &N[3]);
    G.adicionaAresta(&N[3], &N[0]);
    G.adicionaAresta(&N[2], &N[4]);
    G.adicionaAresta(&N[4], &N[5]);
    G.adicionaAresta(&N[5], &N[4]);

    G.imprime();

//    cout << "\n\nCaminhamento em profundidade :\n";
//    for (int j = 0; j < n; ++j)
//        G.caminhamentoProfundidade(nos, &N[0]);
//
    cout << "\n\nCaminhamento em largura :\n";
    for (int j = 0; j < n; ++j)
        G.caminhamentoLargura(N, nos, &N[j]);


    //    cout << (G.existeCaminho(&N[1], &N[10]) ? "Existe" : "Não Existe");

//    cout << "\n";
//    G.compConexas(nos, N) ;
//
//    cout << "\n";
//    G.compFortConexas(nos, N);

//    cout << "\n";
//    G.ordenacaoTopologica(nos, &N[0]);

//    Comp = G.getComplementar();
//    Comp->imprime();
    return 0;
}
