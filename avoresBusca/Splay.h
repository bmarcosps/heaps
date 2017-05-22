#ifndef SPLAY_H_INCLUDED
#define SPLAY_H_INCLUDED

typedef struct NoSplay{
    struct NoSplay* dir = NULL;
    struct NoSplay* esq = NULL;
    struct NoSplay* pai = NULL;
    int chave;
} NoSplay;

typedef struct Splay{
    NoSplay* raiz = NULL;

} Splay;

NoSplay* avo(NoSplay* p){
    if(p->pai == NULL){
        return NULL;
    } else {
        return p->pai->pai;
    }
}

NoSplay* direita(NoSplay* p){
    NoSplay* aux = p->esq;
    if(aux->dir != NULL){
        aux->dir->pai = p;
    }
    p->esq = aux->dir;
    aux->dir = p;

    aux->pai = p->pai;
    if(p->pai != NULL){
        if(p->pai->dir == p) p->pai->dir = aux;
        else p->pai->esq = aux;
    }
    p->pai = aux;

    return aux;
}

NoSplay* esquerda(NoSplay* p){
    NoSplay* aux = p->dir;
    if(aux->esq != NULL){
        aux->esq->pai = p;
    }
    p->dir = aux->esq;
    aux->esq = p;

    aux->pai = p->pai;
    if(p->pai != NULL){
        if(p->pai->dir == p) p->pai->dir = aux;
        else p->pai->esq = aux;
    }
    p->pai = aux;

    return aux;
}

NoSplay* zigZig(NoSplay* p){
    NoSplay* aux = direita(p->pai);
    aux = direita(p);
    return aux;
}

NoSplay* zagZag(NoSplay* p){
    NoSplay* aux = esquerda(p->pai);
    aux = esquerda(p);
    return aux;
}

NoSplay* zigZag(NoSplay* p){
    NoSplay* pai = p->pai;

    NoSplay* aux = direita(p);
    pai->dir = aux;
    aux->pai = pai;

    aux = esquerda(pai);

    return aux;
}

NoSplay* zagZig(NoSplay* p){
    NoSplay* pai = p->pai;

    NoSplay* aux = esquerda(p);
    pai->esq = aux;
    aux->pai = pai;
    aux = direita(pai);

    return aux;
}


NoSplay* splay(NoSplay* p){
    NoSplay* aux = p;
    if(p != NULL){
        if(p->pai == NULL){
            return p;
        }
        NoSplay* avoP = avo(p);
        ///pai é raiz
        if(avoP == NULL){
            if(p->pai->esq == p){
                return splay(direita(p->pai));
            } else {
                return splay(esquerda(p->pai));
            }
        } else {
            if(avoP->dir == p->pai && p->pai->dir == p) return splay(zagZag(p->pai));//esq esq
            if(avoP->dir == p->pai && p->pai->esq == p) return splay(zigZag(p->pai));//dir esq
            if(avoP->esq == p->pai && p->pai->esq == p) return splay(zigZig(p->pai));//dir dir
            if(avoP->esq == p->pai && p->pai->dir == p) return splay(zagZig(p->pai));//esq dir

        }
    }
}

NoSplay* busca(Splay* arvore, int valor){
    if(arvore->raiz != NULL){
        NoSplay* aux1 = arvore->raiz;
        NoSplay* aux2 = NULL;
        while(aux1 != NULL){
            aux2 = aux1;
            if(valor == aux1->chave){
                arvore->raiz = splay(aux1);
                return arvore->raiz;
            }else if(valor > aux1->chave){
                aux1 = aux1->dir;
            } else {
                aux1 = aux1->esq;
            }
        }
        arvore->raiz = splay(aux2);
        return arvore->raiz;
    }
}

void insere(Splay* arvore, int valor){
    NoSplay* novo = new NoSplay;
    novo->chave = valor;

    if(arvore->raiz == NULL){
        arvore->raiz = novo;
    } else {
        NoSplay* aux = arvore->raiz;
        NoSplay* pai;
        while(aux!=NULL){
            pai = aux;
            if(aux->chave < valor) aux = aux->dir;
            else aux = aux->esq;
        }
        novo->pai = pai;
        if(valor > pai->chave) pai->dir = novo;
        else pai->esq = novo;
    }
    arvore->raiz = splay(novo);
}

NoSplay* auxDeletaABB(NoSplay* p){
    NoSplay* aux;
    NoSplay* auxPai;
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

NoSplay* deleta(Splay* arv, int chave){
    NoSplay* aux1 = arv->raiz;
    NoSplay* aux2 = NULL;

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

    arv->raiz = splay(aux2);

    return arv->raiz;
}

void imprime(NoSplay* p, int indent){
    if (p != NULL)
    {
        imprime(p->dir, indent + 4);
        if (indent > 0)
            std::cout <<std::setw(indent) << " ";
        std::cout << p->chave << std::endl;
        imprime(p->esq, indent + 4);
    }
}

void testaSplay(Splay* arvore, int TESTE){
    for(int i = 0; i < TESTE; i++){
        int random = rand() % 300;
        std::cout << "Inserindo " << random << std::endl;
        insere(arvore, random);
    }
//    std::cout << "Removendo 17" << std::endl;
//    deleta(arvore, 17);
//    std::cout << "Removendo 14" << std::endl;
//    deleta(arvore, 14);
    imprime(arvore->raiz, 0);
}



#endif // SPLAY_H_INCLUDED
