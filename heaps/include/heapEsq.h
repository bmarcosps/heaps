#ifndef HEAPESQ_H
#define HEAPESQ_H

#include "noEsq.h"
#include <iomanip>

class HeapEsq
{
    public:
        HeapEsq();
        ~HeapEsq();
        NoEsq* getRaiz() { return raiz; }
        int dist(NoEsq* p);
        void insere(int chave);
        NoEsq* removeMaiorPrioridade();
        NoEsq* uniao(NoEsq* H1, NoEsq* H2);

        void imprimeArvore();
        void imprime(NoEsq* p, int indent);

    private:
        NoEsq* raiz;
};

#endif // HEAPESQ_H
