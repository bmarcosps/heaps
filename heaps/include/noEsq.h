#ifndef NOESQ_H
#define NOESQ_H

#include <iostream>
class NoEsq
{
    public:
        NoEsq(int chave);
        ~NoEsq();

        NoEsq* getDir() { return dir; }
        void setDir(NoEsq* val) { dir = val; }
        NoEsq* getEsq() { return esq; }
        void setEsq(NoEsq* val) { esq = val; }
        int getDist() { return dist; }
        void setDist(int val) { dist = val; }
        int getChave() { return chave; }
        void setChave(int val) { chave = val; }

    protected:

    private:
        NoEsq* dir; // filho a direita
        NoEsq* esq; // dilho a esquerda
        int dist; // menor comprimento do no a null
        int chave;
};

#endif // NOESQ_H
