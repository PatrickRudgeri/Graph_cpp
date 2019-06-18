#include "Grafo.h"
#include <iostream>

using namespace std;

Grafo::Grafo() {
    grau = 0;
    ordem = 0;
    ListaNo = new No;
    direcionado = false;
    ponderadoAr = false;
    ponderadoNo = false;
    simples = false;
}

Grafo::~Grafo() {
    //fixme bug no destrutor
//    No *p;
//    while (p != NULL) {
//        p = ListaNo->getProx();
//        delete ListaNo;
//        ListaNo = p;
//    }
}

int Grafo::getOrdem() {
    return ordem;
}

int Grafo::getGrau() {
    return grau;
}

No *Grafo::getListaNo() {
    return ListaNo;
}

void Grafo::setDirecionado(bool b) {
    direcionado = b;
}

void Grafo::setPonderadoNo(bool b) {
    ponderadoNo = b;
}

void Grafo::setPonderadoAr(bool b) {
    ponderadoAr = b;
}

void Grafo::setSimples(bool b) {
    simples = b;
}

void Grafo::adicionaNo(No *p, int peso) {
    No *q = ListaNo;
    float f;
    if (ponderadoNo) {
//        cout << "Digite o valor do noh " << p->getId() << ": ";
//        cin >> f;
//        cout << endl;
        p->setPeso(peso);
    }
    if (ordem == 0) {
        q->setProx(p);
        ordem++;
        return;
    }
    while (q->getProx() != NULL) {
        if (q->getId() == p->getId() && q != ListaNo) {
            cout << "Ja existe um noh no grafo com este Id." << endl;
            return;
        }
        q = q->getProx();
    }
    if (q->getId() != p->getId()) {
        q->setProx(p);
        ordem++;
    } else {
        cout << "Ja existe um noh no grafo com este Id." << endl;
    }
}

//void Grafo::adicionaAresta(No *p, int i, int peso) { //MOD
void Grafo::adicionaAresta(No *p, No *no, int peso) {
    Aresta *a = new Aresta;
    int i = no->getId(); // ADD

    a->setNoAdj(no);
    a->setProxima(NULL);
    No *q = ListaNo;
    bool b = false;
    while (q->getProx() != NULL) {
        if (q->getId() == i) {
            b = true;
            break;
        }
        q = q->getProx();
    }
    if (q->getId() == i) {
        b = true;
    }
    if (!b) {
        cout << "Erro: nao existe noh com o Id especificado." << endl;
        return;
    }
    if (ponderadoAr) {
        a->setPeso(peso);
    }
    if (!simples) {
        p->insereAresta(a);
    } else {
        if (p->ehAdjacente(i)) {
            cout << "Erro: tentativa de adicionar multiplas arestas entre um mesmo par de nohs em um grafo simples."
                 << endl;
            return;
        } else {
            p->insereAresta(a);
        }
    }
    if (!direcionado && p->getId() != i) {
        No *q = ListaNo;
        while (q->getId() != i) {
            q = q->getProx();
        }
        Aresta *d = new Aresta;
        d->setProxima(NULL);
        d->setPeso(a->getPeso());
        d->setNoAdj(p);// MOD
        q->insereAresta(d);
    }
}

void Grafo::imprime() {
    No *p = ListaNo->getProx();
    int k;
    while (p != NULL) {
        k = p->getId();
        cout << k << " -> ";
        p->imprimeListaNosAdj(); // era ListaNosAdj()
        p = p->getProx();
    }
    delete p; // ADD
}


bool Grafo::estaNoGrafo(int id) {
    No *q = ListaNo;
    while (q != NULL) {
        if (q->getId() == id) {
            return true;
        }
        q = q->getProx(); // ADD
    }
    return false;
}

void Grafo::removeNo(int id) {
    if (!estaNoGrafo(id)) {
        cout << "Erro: o noh em questao nao estah no grafo." << endl;
        return;
    }
    No *q = ListaNo;
    No *p;
    while (q->getId() != id) {
        p = q;
        q = q->getProx();
    }
    p->setProx(q->getProx());
    delete q;
}

void Grafo::removeAresta(int i, int adjacente) {
    if (!estaNoGrafo(i)) {
        cout << "Erro: o noh em questao nao estah no grafo." << endl;
        return;
    }
    No *p = ListaNo;
    while (p->getId() != i) {
        p = p->getProx();
    }
    p->removeAdj(adjacente);
}

void Grafo::limpaGrafo() {
    No *p = ListaNo;
    No *q = ListaNo;
    while (p != NULL) {
        while (q != NULL) {
            if (p->ehAdjacente(q->getId())) {
                p->removeAdj(q->getId());
            }
            q = q->getProx();
        }
        p = p->getProx();
        q = ListaNo;
    }
}

Grafo *Grafo::getComplementar() {
    Grafo *G = new Grafo;
    /*if(simples==false)
    {
        cout << "Erro: um grafo precisa ser simples para que seu complementar esteja bem definido." << endl;
        exit(1);
    }*/
    if (ListaNo->getProx() == NULL) {
        return G;
    }
    No *p = ListaNo->getProx();
    No *q = p;
    while (p != NULL) {
        G->adicionaNoAux(p);
        p = p->getProx();
    }
    p = ListaNo->getProx();
    while (p != NULL) {
        while (q != NULL) {
            if (!p->ehAdjacente(q->getId()) && p != q) {
//                G->adicionaArestaAux(p->getId(), q->getId()); // MOD
                G->adicionaArestaAux(p, q);
            }
            q = q->getProx();
        }
        p = p->getProx();
        if (!direcionado) {
            q = p;
        } else {
            q = ListaNo->getProx();
        }
    }
    return G;
}

void Grafo::adicionaNoAux(No *t) {
    No *q = ListaNo;
    No *p = new No;
    float f;
    p->setId(t->getId());
    p->setPeso(t->getPeso());
    p->setProx(NULL);
    if (ponderadoNo) {
        cout << "Digite o valor do noh " << p->getId() << ": ";
        cin >> f;
        cout << endl;
        p->setPeso(f);
    }
    if (ordem == 0) {
        q->setProx(p);
        ordem++;
        return;
    }
    while (q->getProx() != NULL) {
        if (q->getId() == p->getId() && q != ListaNo) {
            cout << "Ja existe um noh no grafo com este Id." << endl;
            return;
        }
        q = q->getProx();
    }
    if (q->getId() != p->getId()) {
        q->setProx(p);
        ordem++;
    } else {
        cout << "Ja existe um noh no grafo com este Id." << endl;
    }
}

//void Grafo::adicionaArestaAux(int j, int i) {// MOD
void Grafo::adicionaArestaAux(No *j, No *i) {
    Aresta *a = new Aresta;

    a->setNoAdj(i);
    a->setProxima(NULL);

    No *q = ListaNo;
    No *p = ListaNo;

    bool b = false;

    while (q->getProx() != NULL) {
        if (q->getId() == i->getId()) {
            b = true;
            break;
        }
        q = q->getProx();
    }
    if (q->getId() == i->getId()) {
        b = true;
    }
    if (!b) {
        cout << "Erro: nao existe noh com o Id especificado." << endl;
        return;
    }
    b = false;
    while (p->getProx() != NULL) {
        if (p->getId() == j->getId()) {
            b = true;
            break;
        }
        p = p->getProx();
    }
    if (p->getId() == j->getId()) {
        b = true;
    }
    if (!b) {
        cout << "Erro: nao existe noh com o Id especificado." << endl;
        return;
    }
    if (ponderadoAr) {
        float f;
        cout << "Digite o peso da aresta: ";
        cin >> f;
        a->setPeso(f);
    }
    if (!simples) {
        p->insereAresta(a);
    } else {
        if (p->ehAdjacente(i->getId())) {
            cout << "Erro: tentativa de adicionar multiplas arestas entre um mesmo par de nohs em um grafo simples."
                 << endl;
            return;
        } else {
            p->insereAresta(a);
        }
    }
    if (!direcionado && p->getId() != i->getId()) {
        No *q = ListaNo;
        while (q->getId() != i->getId()) {
            q = q->getProx();
        }
        Aresta *d = new Aresta;
        d->setProxima(NULL);
        d->setPeso(a->getPeso());
        d->setNoAdj(p); // MOD
        q->insereAresta(d);
    }
}

void Grafo::ordenarCaminhos(int *nos, int *vet, int low, int high) {
    int pivo, aux, aux2, i, j, meio;

    i = low;
    j = high;

    meio = ((i + j) / 2);
    pivo = vet[meio];

    do {
        while (vet[i] < pivo)
            i = i + 1;
        while (vet[j] > pivo)
            j = j - 1;

        if (i <= j) {
            aux = vet[i];
            vet[i] = vet[j];
            vet[j] = aux;

            //espelhando ordenação nos IDs dos Nós
            aux2 = nos[i];
            nos[i] = nos[j];
            nos[j] = aux2;

            i = i + 1;
            j = j - 1;
        }
    } while (j > i);

    if (low < j)
        ordenarCaminhos(nos, vet, low, j);
    if (i < high)
        ordenarCaminhos(nos, vet, i, high);

}

////-----------------------------------------------

int *Grafo::caminhamentoLargura(No *N, int *nos, No *ini, bool imprimir) {
    int v, cnt = 0, IF = 0, FF = 0, k;

    const int n = this->getOrdem();

    int *visitados = new int[n];
    int *fila = new int[n];
    int *nosAux = new int[n];

    copy(nos, nos + n, nosAux); //fazendo uma cópia do vetor nos para nosAux

    for (int v = 0; v < n; v++) visitados[v] = -1;

    visitados[ini->getIndex()] = cnt++;
    fila[FF++] = ini->getIndex(); // nó inicial na fila

    while (IF != FF) {
        v = fila[IF++];
        for (Aresta *a = N[v].getAresta(); a != NULL; a = a->getProxima()) {
            k = a->getNoAdj()->getIndex();
            if (visitados[k] == -1) {
                visitados[k] = cnt++;
                fila[FF++] = k;
            }
        }
    }
    ordenarCaminhos(nosAux, visitados, 0, n - 1);

    if (imprimir) {
        cout << ini->getId() << " : ";
        for (int i = 0; i < n; i++) {
            if (visitados[i] != -1) {
                cout << nosAux[i] << " ";
            }
        }
        cout << endl;
    }
    delete[] fila;
    delete[] visitados;
    return nosAux;

}

////-----------------------------------------------

static int contP;

void Grafo::caminhamentoProfundidadeAux(No *ini, int *visitados) {
    int i;
    int v = ini->getIndex();
    visitados[v] = contP++;

    for (Aresta *a = ini->getAresta(); a != NULL; a = a->getProxima()) {
        i = a->getNoAdj()->getIndex();

        // Se o nó adj ainda não foi visitado, então irá visita-lo
        if (visitados[i] == -1) {
            caminhamentoProfundidadeAux(a->getNoAdj(), visitados);
        }

    }
}

int *Grafo::caminhamentoProfundidade(int *nos, No *ini, bool imprimir) {
    const int n = this->getOrdem();

    int *visitados = new int[n];
    int *nosAux = new int[n];

    copy(nos, nos + n, nosAux); //fazendo uma cópia do vetor nos para nosAux
    contP = 0; //inicializando contador

    // definindo todos os nós como não visitados
    for (int v = 0; v < n; v++)
        visitados[v] = -1;

    caminhamentoProfundidadeAux(ini, visitados);

    ordenarCaminhos(nosAux, visitados, 0, n - 1);

    if (imprimir) {
        cout << ini->getId() << " : ";
        for (int i = 0; i < n; i++) {
            if (visitados[i] != -1) {
                cout << nosAux[i] << " ";
            }
        }
        cout << endl;
    }
    delete[] visitados;
    return nosAux;
}

//----------------------------------------------
//EXTRA
void Grafo::existeCaminhoAux(No *ini, No *fim, int *visitados) {
    int i;
    int v = ini->getIndex();
    visitados[v] = 1;

    for (Aresta *a = ini->getAresta(); a != NULL; a = a->getProxima()) {
        i = a->getNoAdj()->getIndex();

        // Conseguiu encontrar o No fim
        if (visitados[fim->getIndex()] == 1)
            return;

        // Se o nó adj ainda não foi visitado, então irá visita-lo
        if (visitados[i] == 0) {
            existeCaminhoAux(a->getNoAdj(), fim, visitados);
        }

    }
}

bool Grafo::existeCaminho(No *ini, No *fim) {
    cout << "ini: id-" << ini->getId() << " [" << ini->getIndex() << "] -> id-" << fim->getId() << " ["
         << fim->getIndex() << "]" << endl;

    // Este vetor visitados é um mapeamento do vetor N declarado em main.cpp,
    // é utilizado como vetor de flag quando os nós são visitados
    int *visitados = new int[this->getOrdem()];

    // definindo todos os nós como não visitados
    for (int v = 0; v < this->getOrdem(); v++) {
        visitados[v] = 0;
    }

    existeCaminhoAux(ini, fim, visitados);

    /*
    // para visualizar quais nós foram visitados antes de atingir o nó fim(caso este seja alcançável)
    for (int i = 0; i < this->getOrdem(); i++) {
        cout << visitados[i] << " ";
    }
    cout << endl;*/

    // Retorna true se tiver um caminho disponível entre nó inicial e nó fim
    return visitados[fim->getIndex()] != 0;
}

//-----------------------------------------------

//static int contCC;

void Grafo::compConexasAux(int *cc, No *v, int cp) {
    int i;
//    int v = ini->getIndex();
    cc[v->getIndex()] = cp;

    for (Aresta *a = v->getAresta(); a != NULL; a = a->getProxima()) {
        i = a->getNoAdj()->getIndex();

        if (cc[i] == -1) {
            compConexasAux(cc, a->getNoAdj(), cp);
        }

    }
}

int Grafo::compConexas(int *nos, No *N) {
    int cp = 0;

    if (this->direcionado) {
        cout << "ERRO(compConexas): Estah funcao so estah disponivel para grafos não direcionados" << endl;
        return -1;
    }

    const int n = this->getOrdem();
    int *cc = new int[n];

    for (int v = 0; v < n; v++)
        cc[v] = -1;

    for (int v = 0; v < n; v++) {
        if (cc[v] == -1)
            compConexasAux(cc, &N[v], cp++);
    }

    //---visualização

    cout << cp << (cp == 1 ? " Componente conexa" : " Componentes conexas") << "\n";

    for (int j = 0; j < cp; j++) {
        cout << "COMP." << j << " : ";
        for (int i = 0; i < n; i++) {
            if (cc[i] == j)
                cout << nos[i] << " ";
        }
        cout << "\n";
    }
    //---

    delete[] cc;

    return cp;
//
}

//----------------------------------------------

// TODO: ajustar tamanho p/ dinâmico
static int pre[10000], lo[10000];
static int pilha[10000];
static int C, cnt, k;

void Grafo::compFortConexasAux(int *sc, No *vn) {
    const int v = vn->getIndex();

    pre[v] = cnt++;
    pilha[C++] = v;
    lo[v] = pre[v];

    for (Aresta *a = vn->getAresta(); a != NULL; a = a->getProxima()) {
        int w = a->getNoAdj()->getIndex();

        if (pre[w] == -1) {
            compFortConexasAux(sc, a->getNoAdj());
            if (lo[w] < lo[v])
                lo[v] = lo[w];
        } else if (pre[w] < pre[v] && sc[w] == -1) {
            if (pre[w] < lo[v])
                lo[v] = pre[w];
        }
    }
    if (lo[v] == pre[v]) {
        int u;
        do {
            u = pilha[--C];
            sc[u] = k;
        } while (u != v);
        k++;
    }
}

//-----------------------------------------------

int Grafo::compFortConexas(int *nos, No *N) {
    if (!this->direcionado) {
        cout << "ERRO(compFortConexas): Nao eh possivel executar essa funcao com grafos não direcionados\n";
        return -1;
    }
    C = cnt = k = 0;

    const int n = this->getOrdem();
    int *sc = new int[n];

    for (int v = 0; v < n; v++)
        pre[v] = sc[v] = -1;

    for (int v = 0; v < n; v++) {
        if (pre[v] == -1)
            compFortConexasAux(sc, &N[v]);
    }

    //---visualização
    cout << k << (k == 1 ? " Comp. fortemente conexa" : " Comps. fortemente conexas") << "\n";

    for (int j = 0; j < k; j++) {
        cout << "COMP." << j << " : ";
        for (int i = 0; i < n; i++) {
            if (sc[i] == j)
                cout << nos[i] << " ";
        }
        cout << "\n";
    }
    //----------------

    delete[] sc;
    return k;
}









//----------------------------------------------

// ordenação topológica
// TODO: Falta implementar



////-----------------------------------------

const int INF = INT32_MAX;

float **Grafo::listToMatAdj() {
    int i,j;

    float **G = new float *[ordem];

    for (i = 0; i < ordem; i++) {
        G[i] = new float[ordem];

//        Atribuindo INF para a distancia entre todos os pares, exceto p/ diagonal
        for (int j = 0; j < ordem; ++j) {
            G[i][j] = (float) (i == j ? 0 : INF);
        }
    }

    No * nos = ListaNo->getProx();

    for (i=0; i < ordem; i++) {
        j = 0;
        Aresta *a = nos[i].getAresta();

        while(a != NULL) {
            j = a->getNoAdj()->getIndex();

            G[i][j] = a->getPeso();
            a = a->getProxima();
        }
    }

//    for (int l = 0; l < ordem; ++l) {
//        for (int m = 0; m < ordem; ++m) {
//            cout << G[l][m] << " ";
//        }
//        cout << endl;
//    }
    return G;
}

// TODO: falta verificar ciclos negativos
void Grafo::floyd() {
    int i, j, k;

    if(!direcionado){
        cerr << "Grafo não direcionado! Floyd deve ser aplicado apenas em digrafos";
        return;
    }

    float **dist = listToMatAdj();

    for (k = 0; k < ordem; k++) {
        for (i = 0; i < ordem; i++) {
            for (j = 0; j < ordem; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
    printSolucaoFloyd(dist);
}

void Grafo::printSolucaoFloyd(float **dist) {
    for (int i = 0; i < ordem; i++)
    {
        for (int j = 0; j < ordem; j++)
        {
            if (dist[i][j] == INF)
                printf("%4s", "INF");
            else
                printf("%3.f ", dist[i][j]);
        }
        cout << "\n";
    }
}



/*
 *
No* Grafo::maiorGrau()
{
    No* p=ListaNo;
    No* q=ListaNo;
    while(p!=NULL)
    {
        if(p->getGrau()>q->getGrau())
        {
            q=p;
        }
        p=p->getProx();
    }
    return q;
}

No* Grafo::menorPeso()
{
    No* p=ListaNo;
    No* q=ListaNo;
    while(p!=NULL)
    {
        if(p->getPeso()<q->getPeso())
        {
            q=p;
        }
        p=p->getProx();
    }
    return q;
}


No* Grafo::GulosoKruskal()
{
    Grafo* G=new Grafo;
    No* p=ListaNo->getProx();
    No* q=ListaNo->getProx();
    No* Sol = new No;
    while(p!=NULL)
    {
        G->adicionaNoAux(p);
        p=p->getProx();
    }
    p = ListaNo->getProx();
    while(p!=NULL)
    {
        while(q!=NULL)
        {
            if(p->ehAdjacente(q->getId())==true)
            {
                G->adicionaArestaAux(p->getId(),q->getId());
            }
            q=q->getProx();
        }
        p=p->getProx();
        if(direcionado==false)
        {
            q=p;
        }
        else
        {
            q=ListaNo->getProx();
        }
    }

    while(auxGuloso(Sol)!=true)
    {
        p=G->menorPeso();
        q=Sol;
        while(q->getProx()!=NULL)
        {
            q=q->getProx();
        }
        q->setProx(p);
        G->removeNoGuloso(p->getId());
    }
    return Sol;
}

bool Grafo::auxGuloso(No* p)
{
    No* t=p;
    No* q=ListaNo->getProx();
    while(q!=NULL)
    {
        while(t!=NULL)
        {
            if(q->ehAdjacente(t->getId())==true)
            {
                break;
            }
            else
            {
                if(t->getProx()==NULL)
                {
                    return false;
                }
                t=t->getProx();
            }
        }
        t=p;
        q=q->getProx();
    }
    return true;
}

void Grafo::removeNoGuloso(int i)
{
    if(estaNoGrafo(i)==false)
    {
        cout << "Erro: o noh em questao nao estah no grafo." << endl;
        return;
    }
    No* q=ListaNo;
    No* p;
    while(q->getId()!=i)
    {
        p=q;
        q=q->getProx();
    }
    p->setProx(q->getProx());
    return;
}

*/