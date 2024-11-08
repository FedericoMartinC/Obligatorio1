#ifndef LISTA_DE_ADYACENCIA_DIR
#define LISTA_DE_ADYACENCIA_DIR
#include <cstring>
#include <string>
#include <iostream>
using namespace std;

struct Lista {
    int destino;
    Lista* sig;
};

class ListaDeAdyacenciaDir
{
private:

    Lista** arr; 
    int vertices;

public:

    ListaDeAdyacenciaDir(int cantV){
        arr= new Lista*[cantV+1]();
        for(int i=0; i<=cantV ; i++){
            arr[i]=NULL;
        }
        this->vertices=cantV;
    }

    void agregarRelacion(int origen, int destino){
        Lista* nuevo = new Lista;
        nuevo->destino=destino;
        nuevo->sig=arr[origen];
        arr[origen]=nuevo;
    }

    int getV(){
        return vertices;
    }

    Lista* adyacentes(int v){
        return arr[v];
    }
};

#endif