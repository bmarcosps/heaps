#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED

#include <iostream>
#include <iomanip>

typedef struct NoAVL{
    struct NoAVL* dir = NULL;
    struct NoAVL* esq = NULL;
    int chave;
    int fb = 0;
} NoAVL;

typedef struct AVL{
    NoAVL* raiz = NULL;
    int n = 0;
} AVL;

void insereABB(AVL* arvore, int val){
    NoAVL* novo = new NoAVL;
    novo->chave = val;

    if(arvore->raiz == NULL){
        arvore->raiz = novo;
    } else {
        NoAVL* aux1 = arvore->raiz;
        NoAVL* aux2 = NULL;
        while(aux1 != NULL){
            aux2 = aux1;
            if(val > aux1->chave){
                aux1 = aux1->dir;
            } else {
                aux1 = aux1->esq;
            }
        }

        if(val > aux2->chave){
            aux2->dir = novo;
        } else {
            aux2->esq = novo;
        }
    }
    arvore->n++;
//    return aux2;
}

int altura(NoAVL* p){
    if(p == NULL){
        return 0;
    } else {
        int dir = altura(p->dir);
        int esq = altura(p->esq);

        p->fb = dir-esq;
        if(dir > esq){
            return 1 + dir;
        } else {
            return 1 + esq;
        }
    }
}

int calculaFB(NoAVL* p){
    p->fb = altura(p->dir) - altura(p->esq);
    return p->fb;
}

///rotacao esquerda
NoAVL* rotacaoRR(NoAVL* p){
    NoAVL* aux = p->dir;
    p->dir = aux->esq;
    aux->esq = p;
    return aux;
}

///rotacao direita
NoAVL* rotacaoLL(NoAVL* p){
    NoAVL* aux = p->esq;
    p->esq = aux->dir;
    aux->dir = p;
    return aux;
}

NoAVL* rotacaoRL(NoAVL* p){
    NoAVL* aux = rotacaoLL(p->dir);
    p->dir = aux;
    return rotacaoRR(p);
}

NoAVL* rotacaoLR(NoAVL* p){
    NoAVL* aux = rotacaoRR(p->esq);
    p->esq = aux;
    return rotacaoLL(p);
}

NoAVL* corrige(NoAVL* p){
    if(p != NULL){
        p->dir = corrige(p->dir);
        p->esq = corrige(p->esq);

        int fb = calculaFB(p);
        if(fb > 1){
            if(p->dir->fb > 0){
                p = rotacaoRR(p);
            } else {
                p = rotacaoRL(p);
            }
        } else if( fb < -1) {
            if(p->esq->fb < 0){
                p = rotacaoLL(p);//LL
            } else {
                p = rotacaoLR(p); //LR
            }
        }
    }
    return p;
}

void insere(AVL* arvore, int val){
    insereABB(arvore, val);
    arvore->raiz = corrige(arvore->raiz);
    altura(arvore->raiz);
}

NoAVL* novoInsere(NoAVL* p, int val){

    if(p == NULL){
        NoAVL* novo = new NoAVL;
        novo->chave = val;
        return novo;
    } else {
        if(val > p->chave){
            p->dir = novoInsere(p->dir, val);
        } else {
            p->esq = novoInsere(p->esq, val);
        }

        int fb = calculaFB(p);
        if(fb > 1){
            if(p->dir->fb > 0){
                p = rotacaoRR(p);
            } else {
                p = rotacaoRL(p);
            }
        } else if( fb < -1) {
            if(p->esq->fb < 0){
                p = rotacaoLL(p);//LL
            } else {
                p = rotacaoLR(p); //LR
            }
        }
    }
    return p;
}


NoAVL* auxDeletaABB(NoAVL* p){
    NoAVL* aux;
    NoAVL* auxPai;
    ///caso 1: no folha
    if(p->dir == NULL && p->esq == NULL){
        delete p;
        return NULL;
    ///caso 2: 1 filho a esquerda
    } else if(p->dir == NULL && p->esq != NULL){
        aux = p->esq;
        delete p;
        return aux;
    ///caso 3: 1 filho a direita
    } else if(p->dir != NULL && p->esq == NULL){
        aux = p->dir;
        delete p;
        return aux;
    ///caso 4: 2 filhos -> acha o maior da subarvore esquerda
    } else {
        ///caso 4.1: se o maior é o proprio filho
        if(p->esq->dir == NULL){
            aux = p->esq;
            aux->dir =p->dir;
            p->esq =aux->esq;
            delete p;
            return aux;
        ///caso 4.1: senão busca o maior percorrendo à direita
        } else {
            auxPai = p;
            aux = p->esq;
            while(aux->dir != NULL){
                auxPai = aux;
                aux = aux->dir;
            }

            if(aux->esq == NULL){
                auxPai->dir =NULL;
            } else {
                auxPai->dir =aux->esq;
            }

            aux->dir =p->dir;
            aux->esq =p->esq;

            delete p;
            return aux;
        }
    }
}

NoAVL* deletaABB(AVL* arv, int chave){
    NoAVL* aux1 = arv->raiz;
    NoAVL* aux2 = NULL;

    if(aux1->chave == chave){
        arv->raiz = auxDeletaABB(aux1);
        return arv->raiz;
    }

    bool dir = false;

    while(aux1 != NULL && aux1->chave != chave){
        aux2 = aux1;
        if(chave < aux1->chave){
            dir = false;
            aux1 = aux1->esq;
        } else if(chave > aux1->chave){
            dir = true;
            aux1 = aux1->dir;
        }
    }

    if(aux1 != NULL){
        if(dir){
            aux2->dir =auxDeletaABB(aux1);
        } else {
            aux2->esq =auxDeletaABB(aux1);
        }
    }


    return arv->raiz;
}

void deleta(AVL* arvore, int val){
    deletaABB(arvore, val);
    arvore->raiz = corrige(arvore->raiz);
    altura(arvore->raiz);
}

NoAVL* busca(AVL* arvore, int valor){
    if(arvore->raiz != NULL){
        NoAVL* aux1 = arvore->raiz;
        NoAVL* aux2 = NULL;
        while(aux1 != NULL){
            aux2 = aux1;
            if(valor == aux1->chave){
                return aux1;
            }else if(valor > aux1->chave){
                aux1 = aux1->dir;
            } else {
                aux1 = aux1->esq;
            }
        }
        return NULL;
    }
}

void imprime(NoAVL* p, int indent){
    if (p != NULL) {
        imprime(p->dir, indent + 4);
        if (indent > 0)
            std::cout <<std::setw(indent) << " ";
        std::cout << p->chave << " | "<< p->fb << std::endl;
        imprime(p->esq, indent + 4);
    }
}

void testaAVL(AVL* arvore, int TESTE){

    for(int i = 0; i < TESTE; i++){
        int random = rand() % 300;
        std::cout << "Inserindo " << random << std::endl;
        arvore->raiz = novoInsere(arvore->raiz, random);

    }
    imprime(arvore->raiz, 0);
}


#endif // AVL_H_INCLUDED
