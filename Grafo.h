#ifndef GRAFO_H
#define GRAFO_H

#include "No.h"

//class No;

class Grafo {
public:
    Grafo();

    ~Grafo();

    int getOrdem();
    int getGrau();
    No *getListaNo();
    void adicionaNo(No *p, int peso = 1);

//    void adicionaAresta(No *p, int i, int peso = 1); //MOD
    void adicionaAresta(No *p, No *no, int peso = 1);

    void imprime();
    void setDirecionado(bool b);
    void setPonderadoNo(bool b);
    void setPonderadoAr(bool b);
    void setSimples(bool b);
    bool estaNoGrafo(int id);
    Grafo *getComplementar();
    void removeNo(int id);
    void removeAresta(int id, int adjacente);
    void limpaGrafo();

    int *caminhamentoProfundidade(int *nos, No *ini, bool imprimir = true); //ADD
    bool existeCaminho(No *ini, No *fim); //ADD
    int *caminhamentoLargura(No *N, int *nos, No *ini, bool imprimir = true); //ADD

    int compConexas(int *nos, No *N); //ADD
    int compFortConexas(int *nos, No *N); //ADD

    void floyd();

    //int *ordenacaoTopologica(int *nos, No *ini); // ADD

    /*
    No* buscaNo(int id);
    No* GulosoKruskal();
    No* maiorGrau();
    No* menorPeso();
    */
private:
    No *ListaNo;
    int ordem;
    int grau;
    bool direcionado;
    bool ponderadoNo;
    bool ponderadoAr;
    bool simples;

    void adicionaNoAux(No *t);

    void adicionaArestaAux(No *j, No *i);

    void existeCaminhoAux(No *ini, No *fim, int *visitados); //ADD
    void caminhamentoProfundidadeAux(No *ini, int *visitados); //ADD
    void compConexasAux(int *cc, No *v, int cp);//ADD
    void compFortConexasAux(int *sc, No *vn); //ADD
    //(quicksort)
    void ordenarCaminhos(int *nos, int *vet, int low, int high); //ADD

    float **listToMatAdj();
    void printSolucaoFloyd(float **dist);


//    void OrdenaListaNo(No* t);
//    bool auxGuloso(No* p);
//    void removeNoGuloso(int i);
};

#endif // GRAFO_H
