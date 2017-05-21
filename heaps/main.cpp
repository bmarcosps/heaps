#include <iostream>

#include "heapEsq.h"
#include "HeapBin.h"

int main()
{
    /*
    HeapEsq* H = new HeapEsq();
    H->insere(20);
    H->insere(3);
    H->insere(15);
    H->insere(21);
    H->insere(2);
    H->insere(10);
    H->insere(9);
    H->insere(1);

    H->removeMaiorPrioridade();
    H->removeMaiorPrioridade();
   // if(H->getRaiz() == NULL)
    //std::cout << "aaaaa";
    H->imprimeArvore();
    */

    HeapBin H;
    H.insere(20);
    H.insere(50);
    H.insere(2);
    H.insere(25);
    H.insere(10);
    H.insere(11);
    H.insere(28);
    H.insere(3);

    H.removeMenor();
    H.imprimeHeapConsole();
    H.removeMenor();

    H.imprimeHeapConsole();

    return 0;
}
