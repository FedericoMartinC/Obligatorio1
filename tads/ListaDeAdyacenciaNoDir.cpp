#ifndef LISTA_DE_ADYACENCIA_NO_DIR
#define LISTA_DE_ADYACENCIA_NO_DIR
#include <cstring>
#include <string>
#include <iostream>
using namespace std;

struct NodoLista {
    int destino;
    int costo;
    NodoLista* sig;
};

class ListaDeAdyacenciaNoDir
{
private:

    NodoLista** arr; 
    int vertices;

    void duplicarCostoRec(NodoLista *&l,int destino){
        if(l->destino==destino){
            l->costo=l->costo*2;
        }else{
            duplicarCostoRec(l->sig,destino);
        }
    }

public:

    ListaDeAdyacenciaNoDir(int cantV){
        arr= new NodoLista*[cantV+1]();
        for(int i=0; i<=cantV ; i++){
            arr[i]=NULL;
        }
        this->vertices=cantV;
    }

    void agregarRelacion(int origen, int destino, int costo){
        NodoLista* nuevo = new NodoLista;
        nuevo->destino=destino;
        nuevo->costo=costo;
        nuevo->sig=arr[origen];
        arr[origen]=nuevo;

        NodoLista* nuevo2 = new NodoLista;
        nuevo2->destino=origen;
        nuevo2->costo=costo;
        nuevo2->sig=arr[destino];
        arr[destino]=nuevo2;
    }

    int getV(){
        return vertices;
    }

    NodoLista* adyacentes(int v){
        return arr[v];
    }

    void duplicarCosto(int v,int destino){
        this->duplicarCostoRec(this->arr[v],destino);
        this->duplicarCostoRec(this->arr[destino],v);
    }
};

#endif