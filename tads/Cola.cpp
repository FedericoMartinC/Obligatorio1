#ifndef COLA
#define COLA
#include <cstring>
#include <string>
#include <iostream>
using namespace std;

class Cola
{
private:
    struct NodoListaInt {
        int dato;
        NodoListaInt* sig;
        NodoListaInt() : dato(0), sig(NULL) {}
        NodoListaInt(int d) : dato(d), sig(NULL) {}
    };
    NodoListaInt* ini;
    NodoListaInt* fin;
    int largo;

public:

    Cola(){
        this->ini=this->fin=NULL;
        this->largo=0;
    }

    void encolar(int d){
        NodoListaInt* nuevo= new NodoListaInt(d);
        if(estaVacia()){
            this->ini=this->fin=nuevo;
        }else{
            this->fin->sig=nuevo;
            this->fin= this->fin->sig;
        }
        this->largo++;
    }

    bool estaVacia(){
        return this->largo==0;
    }

    int desencolar(){
        int devuelvo=this->ini->dato;
        if(this->fin==this->ini){
            NodoListaInt* borro=this->ini;
            this->ini=this->fin=NULL;
            delete borro;
        }else{
            NodoListaInt* borro=this->ini;
            this->ini=this->ini->sig;
            delete borro;
        }
        this->largo--;
        return devuelvo;
    }

    int cantElem(){
        return this->largo;
    }
};

#endif