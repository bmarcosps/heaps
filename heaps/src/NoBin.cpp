#include "NoBin.h"

NoBin::NoBin(int chave) {
    pai = NULL;
    filho = NULL;
    irmao = NULL;
    grau = 0;
    this->chave = chave;
}

NoBin::~NoBin()
{
    //dtor
}
