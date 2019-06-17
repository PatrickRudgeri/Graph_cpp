#ifndef ARESTA_H
#define ARESTA_H

class No;

class Aresta {
public:
    Aresta();
    ~Aresta();

    void setProxima(Aresta *a);
    void setPeso(float f);
//    void setNoAdj(int i); //alterado
    void setNoAdj(No *no);

    Aresta *getProxima();
    float getPeso();
    No *getNoAdj(); //alterado

private:
//    int noAdj; //alterado
    No *noAdj;
    float pesoAresta;
    Aresta *proxima;
};

#endif // ARESTA_H
