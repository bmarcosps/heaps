#ifndef HEAPBIN_H
#define HEAPBIN_H

#include "NoBin.h"


class HeapBin
{
    public:
        HeapBin();
        ~HeapBin();

        NoBin* getRaiz() { return raiz; }
        void setRaiz(NoBin* val) { raiz = val; }
        void link(NoBin* raiz1, NoBin* raiz2);
        NoBin* mergeHeaps(NoBin* raizH1, NoBin* raizH2);
        NoBin* uniao(NoBin* h1, NoBin* h2);
        void insere(int chave);
        void imprimeHeapConsole();
        void imprimeArvoreConsole(NoBin* r);
        void inverteListaFilhos(NoBin* h, NoBin** root);
        NoBin* removeMenor();

    //private:
        NoBin* raiz;
        int tamanho;
};

#endif // HEAPBIN_H
