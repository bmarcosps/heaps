#include "noEsq.h"

NoEsq::NoEsq(int chave)
{
    dir = NULL;
    esq = NULL;
    this->chave = chave;
    this->dist = 0;
}

NoEsq::~NoEsq()
{
    //dtor
}
