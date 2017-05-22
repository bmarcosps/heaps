#include <iostream>
#include <iomanip>

#include "AVL.h"
#include "Splay.h"
#define TESTE 123



int main(){
    AVL arv;
    testaAVL(&arv, TESTE);

    Splay arvore;
    testaSplay(&arvore, TESTE);
}
