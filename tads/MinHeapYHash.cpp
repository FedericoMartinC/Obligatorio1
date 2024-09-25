#ifndef MIN_HEAP_Y_HASH
#define MIN_HEAP_Y_HASH
#include <cstring>
#include <string>
#include <iostream>
#include "HashAbierto.cpp"
using namespace std;

class MinHeapYHash
{
private:
    struct datoCuadruple {
        int id;
        int prioridad;
        bool paraLLevar;
        string items;
        datoCuadruple(int unId, int unPrecio, bool esParaLlevar, string unosItmes): id(unId), prioridad(unPrecio), paraLLevar(esParaLlevar), items(unosItmes){}
    };
    int capacidad;
    int primerLibre;
    datoCuadruple** arr;
    HashAbierto * tablaHash;

    void cambio(int pos1, int pos2){
        datoCuadruple* aux = arr[pos1];
        arr[pos1]=arr[pos2];
        arr[pos2]=aux;
        
    }

    int padre(int i){
        return i / 2;
    }

    int hIzq(int i){
        return 2 * i;
    }

    int hDer(int i){
        return (2 * i ) + 1;
    }

    void subir(int pos){
        if(pos == 1){
            return;
        }else{
            int posPadre= padre(pos);
            if(arr[posPadre]->prioridad > arr[pos]->prioridad){
                tablaHash->cambiarPos(arr[posPadre]->id,pos);
                tablaHash->cambiarPos(arr[pos]->id,posPadre);
                cambio(pos,posPadre);
                subir(posPadre);
            }else if(arr[posPadre]->prioridad == arr[pos]->prioridad && !arr[posPadre]->paraLLevar && arr[pos]->paraLLevar){
                tablaHash->cambiarPos(arr[posPadre]->id,pos);
                tablaHash->cambiarPos(arr[pos]->id,posPadre);
                cambio(pos,posPadre);
                subir(posPadre);
            }else if(arr[posPadre]->prioridad == arr[pos]->prioridad && ((!arr[posPadre]->paraLLevar && !arr[pos]->paraLLevar) || (arr[posPadre]->paraLLevar && arr[pos]->paraLLevar))  &&  arr[posPadre]->id > arr[pos]->id){
                tablaHash->cambiarPos(arr[posPadre]->id,pos);
                tablaHash->cambiarPos(arr[pos]->id,posPadre);
                cambio(pos,posPadre);
                subir(posPadre);
            }
        }
    }

    void bajar (int pos){
        int posIzq= hIzq(pos);
        int posDer= hDer(pos);
        if(posIzq < primerLibre){
            int posMenor= posIzq;
            if(posDer < primerLibre){
                if(arr[posIzq]->prioridad > arr[posDer]->prioridad){
                    posMenor= posDer;
                }else if(arr[posIzq]->prioridad == arr[posDer]->prioridad && !arr[posIzq]->paraLLevar && arr[posDer]->paraLLevar){
                    posMenor= posDer;
                }else if(arr[posIzq]->prioridad == arr[posDer]->prioridad && ((!arr[posIzq]->paraLLevar && !arr[posDer]->paraLLevar) || (arr[posIzq]->paraLLevar && arr[posDer]->paraLLevar))  && arr[posIzq]->id > arr[posDer]->id){
                    posMenor= posDer;
                }
            }

            if(arr[pos]->prioridad > arr[posMenor]->prioridad){
                tablaHash->cambiarPos(arr[posMenor]->id,pos);
                tablaHash->cambiarPos(arr[pos]->id,posMenor);
                cambio(pos, posMenor);
                bajar(posMenor);
            }else if(arr[pos]->prioridad == arr[posMenor]->prioridad && !arr[pos]->paraLLevar && arr[posMenor]->paraLLevar){
                tablaHash->cambiarPos(arr[posMenor]->id,pos);
                tablaHash->cambiarPos(arr[pos]->id,posMenor);
                cambio(pos, posMenor);
                bajar(posMenor);
            }else if (arr[pos]->prioridad == arr[posMenor]->prioridad && ((!arr[pos]->paraLLevar && !arr[posMenor]->paraLLevar) || (arr[pos]->paraLLevar && arr[posMenor]->paraLLevar)) && arr[pos]->id > arr[posMenor]->id)
            {
                tablaHash->cambiarPos(arr[posMenor]->id,pos);
                tablaHash->cambiarPos(arr[pos]->id,posMenor);
                cambio(pos, posMenor);
                bajar(posMenor);
            }
            

        }
    }


public:
    MinHeapYHash(int N) {
        capacidad = N;
        primerLibre = 1;
        arr= new datoCuadruple*[capacidad+1]();
        for (int i=0; i <= capacidad; i++){
            arr[i]=NULL;
        }
        this->tablaHash= new HashAbierto((N*2));
    }

    void insertar(int id, int prioridad, bool esParaLlevar, string unosItems){
        datoCuadruple * nuevo= new datoCuadruple(id,prioridad,esParaLlevar, unosItems);
        arr[primerLibre]=nuevo;
        this->tablaHash->insert(id,primerLibre);
        primerLibre++;
        subir(primerLibre-1);
    }

    string tope(){
        string a;
        if(!arr[1]->paraLLevar){
            a=to_string(arr[1]->id) + " "+ to_string(arr[1]->prioridad)+" "+"false"+ " " + arr[1]->items;
        }else{
            a=to_string(arr[1]->id) + " "+ to_string(arr[1]->prioridad) + " " +"true"+ " " + arr[1]->items;
        }
        tablaHash->remove(arr[1]->id);
        tablaHash->cambiarPos(arr[primerLibre-1]->id,1);
        cambio(1,primerLibre-1);
        this->primerLibre--;
        bajar(1);
        return a;
    }

    void eliminar(int id){
        int pos=this->tablaHash->get(id,true);
        if(primerLibre-1!=pos){
            tablaHash->cambiarPos(arr[primerLibre-1]->id,pos);
        }
        cambio(pos,primerLibre-1);
        this->primerLibre--;
        subir(pos);
        bajar(pos);
    }

    void cambiarParaLlevar(int id){
        int pos=this->tablaHash->get(id,false);
        arr[pos]->paraLLevar=true;
        subir(pos);
        bajar(pos);
    }

    bool estaVacio(){
        return primerLibre==1;
    }

};
#endif