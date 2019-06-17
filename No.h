#include <stdio.h>
#include <stdlib.h>

#ifndef NO_H
#define NO_H

#include "Aresta.h"

class No {
public:
    No();

    ~No();

    int getId();
    int getGrau();
    No *getProx();
    float getPeso();
    Aresta *getAresta();
    int getIndex(); // ADD
    int getGrauEntrada();

    void setId(int id);
    void setIndex(int ix);
    void setPeso(float f);
    void setProx(No *p);

    void insereAresta(Aresta *a);
    void imprimeListaNosAdj();// MOD

//    No *getNosAdj(); //SEM UTILIDADE POR ENQUANTO

    bool ehAdjacente(int id);
    void removeAdj(int id);

private:
    int Id;
    int index; // ADD
    float peso;
    Aresta *adj;
    No *prox;
    int grau;
    int grauEntrada;

};

#endif // NO_H
