#include "heapEsq.h"

HeapEsq::HeapEsq()
{
    this->raiz = NULL;
}

HeapEsq::~HeapEsq()
{
    //dtor
}

int min(int a, int b){
    return (a<b? a:b);
}

int HeapEsq::dist(NoEsq* p){
    int distancia = 0;
    if(p == NULL) distancia =  0;
    else distancia = 1 + min(dist(p->getDir()), dist(p->getDir()));

    if (p!= NULL) p->setDist(distancia);
    return distancia;
}

NoEsq* HeapEsq::uniao(NoEsq* H1, NoEsq* H2){
    if(H1 == NULL) return H2;
    if(H2 == NULL) return H1;

    if(H1->getChave() > H2->getChave()){ //troca H1 e H2
        //return uniao(H2, H1);
        NoEsq* aux = H1;
        H1 = H2;
        H2 = aux;
    }

    H1->setDir(uniao(H1->getDir(), H2));

    int distEsq = dist(H1->getEsq());
    int distDir = dist(H1->getDir());

    if(distEsq < distDir){
        NoEsq* aux = H1->getEsq();
        H1->setEsq(H1->getDir());
        H1->setDir(aux);
    }
    return H1;
}


void HeapEsq::insere(int chave){
    if(raiz == NULL){
        NoEsq* novo = new NoEsq(chave);
        raiz = novo;
    } else {
        //HeapEsq* novaHeap = new HeapEsq();
        //novaHeap->insere(chave);

        NoEsq* raizH = new NoEsq(chave);
        NoEsq* novaRaiz = uniao(this->raiz, raizH);
        dist(novaRaiz);

        this->raiz = novaRaiz;
    }
}



NoEsq* HeapEsq::removeMaiorPrioridade(){
    if(raiz != NULL){
        NoEsq* x = raiz;

        //HeapEsq* novaHeap = new HeapEsq();
        //novaHeap->setRaiz(raiz->getEsq());
        //raiz = raiz->getDir();

        raiz = uniao(raiz->getDir(), raiz->getEsq());
        return x;

    }
}



void HeapEsq::imprimeArvore(){
    imprime(raiz, 0);
}
void HeapEsq::imprime(NoEsq* p, int indent){

    if (p != NULL)
    {
        imprime(p->getDir(), indent + 4);
        if (indent > 0)
            std::cout <<std::setw(indent) << " ";
        std::cout << p->getChave() << " | "<< p->getDist() << std::endl;
        imprime(p->getEsq(), indent + 4);
    }

}


