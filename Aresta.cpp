//#include <iostream>
#include "Aresta.h"
#include "No.h"

Aresta::Aresta() {}

Aresta::~Aresta() {
    delete proxima;
}

void Aresta::setProxima(Aresta *a) {
    proxima = a;
}

void Aresta::setPeso(float f) {
    pesoAresta = f;
}

//void Aresta::setNoAdj(int i) { //alterado
void Aresta::setNoAdj(No *no) {
    noAdj = no;
}

Aresta *Aresta::getProxima() {
    return proxima;
}

float Aresta::getPeso() {
    return pesoAresta;
}

No *Aresta::getNoAdj() { //alterado
    return noAdj;
}
