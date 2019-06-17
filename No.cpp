#include <iostream>
#include "No.h"
//#include "Aresta.h"

using namespace std;

No::No() {
    adj = NULL;
    grau = 0;
    grauEntrada = 0;
    peso = 1;
    prox = NULL;
}

No::~No() {
    //fixme: bug no destrutor
//    Aresta *a = adj;
//    while (a != NULL) {
//        a = adj->getProxima();
//        delete adj;
//        adj = a;
//    }
//    delete prox;
}

int No::getId() {
    return Id;
}

int No::getGrau() {
    return grau;
}

No *No::getProx() {
    return prox;
}

Aresta *No::getAresta() {
    return adj;
}

int No::getGrauEntrada() {
    return grauEntrada;
}

void No::insereAresta(Aresta *a) {
    Aresta *b = adj;
    if (adj == NULL) {
        adj = a;
        grau++;
    } else {
        while (b->getProxima() != NULL) {
            b = b->getProxima();
        }
        b->setProxima(a);
        grau++;
    }
}

void No::setId(int id) {
    Id = id;
}

void No::setPeso(float f) {
    peso = f;
}

void No::setProx(No *p) {
    prox = p;
}

void No::imprimeListaNosAdj() {
    Aresta *p = adj;
    No *k;
    while (p != NULL) {
        k = p->getNoAdj();
        cout << k->getId() << " ";
        p = p->getProxima();
    }
    cout << endl;
    delete p;
}

//No *No::getNosAdj() {
//    Aresta *p = adj;
//    No *k = NULL;
//    k = p->getNoAdj();
//    while (p != NULL) {
//        k = p->getNoAdj();
//        // do something w/ k
//        p = p->getProxima();
//    }
//    delete p;
//    delete k;// ADD
//}

bool No::ehAdjacente(int id) {
    Aresta *a = adj;
    while (a->getProxima() != NULL) {
        if (a->getNoAdj()->getId() == id) { //MOD
            return true;
        }
    }
    return a->getNoAdj()->getId() == id;
}

void No::removeAdj(int id) {
    if (!ehAdjacente(id)) {
        cout << "Erro: a aresta que voce estah tentando remover nao existe." << endl;
        return;
    }
    Aresta *a = adj;
    Aresta *b;
    while (a->getNoAdj()->getId() != id) {//MOD
        b = a;
        a = a->getProxima();
    }
    b->setProxima(a->getProxima());
    delete a;
}

float No::getPeso() {
    return peso;
}

void No::setIndex(int ix) {
    index = ix;
}

int No::getIndex() {
    return index;
}

