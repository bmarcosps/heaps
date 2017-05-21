#ifndef NOBIN_H
#define NOBIN_H
#include <iostream>


class NoBin
{
    public:
        NoBin(int chave);
        ~NoBin();

        NoBin* getPai() { return pai; }
        void setPai(NoBin* val) { pai = val; }
        NoBin* getFilho() { return filho; }
        void setFilho(NoBin* val) { filho = val; }
        NoBin* getIrmao() { return irmao; }
        void setIrmao(NoBin* val) { irmao = val; }
        int getGrau() { return grau; }
        void setGrau(int val) { grau = val; }
        int getChave() { return chave; }
        void setChave(int val) { chave = val; }

    //private:
        NoBin* pai;
        NoBin* filho;
        NoBin* irmao;
        int grau;
        int chave;
};

#endif // NOBIN_H
