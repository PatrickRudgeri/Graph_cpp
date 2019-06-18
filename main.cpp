#include <iostream>
#include "No.h"
#include "Aresta.h"
#include "Grafo.h"

using namespace std;


int main() {
    Grafo G, *Comp;
    No *N;

    const int n = 6;
    int *nos = new int[n]{100, 101, 102, 103, 104, 105};

    N = new No[n];

    G.setPonderadoAr(true);
    G.setDirecionado(true);

    //Nós
    for (int i = 0; i < n; i++) {
        N[i].setId(nos[i]);
        N[i].setIndex(i);
        G.adicionaNo(&N[i]);
    }

    //Arestas

    G.adicionaAresta(&N[0], &N[1], 5); //(100, 101)
    G.adicionaAresta(&N[0], &N[3], 1); //(100, 103)
    G.adicionaAresta(&N[1], &N[2], 3); //(101, 102)
    G.adicionaAresta(&N[2], &N[3], 2); //(102, 103)
    G.adicionaAresta(&N[3], &N[1], 10); //(103, 101)
    G.adicionaAresta(&N[3], &N[4], 9); //(103, 104)
    G.adicionaAresta(&N[4], &N[2], 8); //(104, 102)
    G.adicionaAresta(&N[4], &N[5], 4); //(104, 105)
    G.adicionaAresta(&N[5], &N[0], 7); //(105, 100)

    G.floyd();


//    G.imprime();

//    cout << "\n\nCaminhamento em profundidade :\n";
//    for (int j = 0; j < n; ++j)
//        G.caminhamentoProfundidade(nos, &N[0]);
//
//    cout << "\n\nCaminhamento em largura :\n";
//    for (int j = 0; j < n; ++j)
//        G.caminhamentoLargura(N, nos, &N[j]);


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
