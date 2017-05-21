#include "HeapBin.h"

HeapBin::HeapBin(){
    raiz = NULL;
}

HeapBin::~HeapBin(){
    //dtor
}

void HeapBin::inverteListaFilhos(NoBin* h, NoBin** root){
    h->pai = NULL;
    if(h->irmao != NULL){
        inverteListaFilhos(h->irmao, root);
        (h->irmao)->irmao = h;
    } else {
        (*root) = h;
    }
}

NoBin* HeapBin::removeMenor(){
    NoBin* aux = raiz;
    NoBin* menor = aux;
    NoBin* ant = NULL;
    while(aux->irmao != NULL){
        if(aux->irmao->chave < menor->chave){
            ant = aux;
            menor = aux->irmao;
        }
        aux = aux->irmao;
    }
    aux->irmao = menor->irmao;
    NoBin* raizInvertida;
    inverteListaFilhos(menor->filho, &raizInvertida);
    menor->filho->irmao = NULL;

    if(ant == NULL){
        raiz = menor->irmao;
    } else {
        ant->irmao = menor->irmao;
    }

    raiz = uniao(raiz, raizInvertida);
}

void HeapBin::link(NoBin* raiz1, NoBin* raiz2){
    raiz1->irmao = raiz2->filho;
    raiz1->pai = raiz2;
    raiz2->filho = raiz1;
    raiz2->grau++;
    //std::cout << raiz1->chave << " " << raiz2->chave << std::endl;
}

NoBin* HeapBin::mergeHeaps(NoBin* raizH1, NoBin* raizH2){
    if(raizH1 == NULL) return raizH2;
    if(raizH2 == NULL) return raizH1;

    NoBin* h;
    if(raizH1->grau < raizH2->grau){
        h = raizH1;
        raizH1 = raizH1->irmao;
    } else {
        h = raizH2;
        raizH2 = raizH2->irmao;
    }

    NoBin* aux = h;
    while(raizH1 != NULL && raizH2 != NULL){
        if(raizH1->grau < raizH2->grau){
            aux->irmao = raizH1;
            raizH1 = raizH1->irmao;
        } else {
            aux->irmao = raizH2;
            raizH2 = raizH2->irmao;
        }
        aux = aux->irmao;
    }
    if(raizH1 == NULL){
        aux->irmao = raizH2;
    }else {
        aux->irmao = raizH1;
    }

//    while(raizH1 != NULL){
//        aux->irmao = raizH1;
//        raizH1 = raizH1->irmao;
//        aux = aux->irmao;
//    }
//    while(raizH2 != NULL){
//        aux->irmao = raizH2;
//        raizH2 = raizH2->irmao;
//        aux = aux->irmao;
//    }

    return h;
}

NoBin* HeapBin::uniao(NoBin* h1, NoBin* h2){
    if(h1 == NULL) return h2;
    if(h2 == NULL) return h1;

    NoBin* auxRaiz = mergeHeaps(h1, h2);
    //imprimeArvoreConsole(auxRaiz);
//    /std::cout << std::endl;

    //std::cout << auxRaiz->irmao->chave << std::endl;

    NoBin* ant = NULL;
    NoBin* atual = auxRaiz;
    NoBin* prox = auxRaiz->irmao;

    while(prox != NULL){
        ///CASO 1 E 2: arvores com grau diferente ou 3 com grau igual
        if((atual->grau != prox->grau) || (prox->irmao != NULL && prox->grau == prox->irmao->grau)){
            ant = atual;
            atual = prox;
        } else if(atual->chave < prox->chave){ ///CASO 3: arvores com mesmo grau
            atual->irmao = prox->irmao;
            link(prox, atual);
        } else { ///CASO 3: arvores com mesmo grau
            if(ant == NULL){
                auxRaiz = prox;
            } else {
                ant->irmao = prox;
            }
            //std::cout << "aaaaaaaaaaa";
            link(atual, prox);
            //std::cout << atual->chave << " " << prox->filho->chave << std::endl;
            atual = prox;
        }
        prox = atual->irmao;

   // imprimeArvoreConsole(auxRaiz);

    }
    return auxRaiz;
}

void HeapBin::insere(int chave){
    NoBin* aux = new NoBin(chave);

    if(raiz == NULL)
        raiz = aux;
    else {
        raiz = uniao(raiz, aux);
    }
}

void HeapBin::imprimeHeapConsole(){
    NoBin* aux = raiz;
    std::cout << "Iniciando impressao do Heap...";
    while(aux!=NULL){
        std::cout << std::endl << "-> Arvore de k = " << aux->getGrau() << std::endl << "--> " << aux->getChave() << " ";
        imprimeArvoreConsole(aux->getFilho());
        aux = aux->getIrmao();
    }
    std::cout << std::endl << "Fim da impressao." << std::endl;
}

// Imprime a arvore binomial de raiz r
void HeapBin::imprimeArvoreConsole(NoBin* r){
    if(r == NULL) return;
    std::cout << r->getChave() << " ";
    imprimeArvoreConsole(r->getFilho());
    imprimeArvoreConsole(r->getIrmao());
}
