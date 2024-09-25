#ifndef MIN_HEAP
#define MIN_HEAP
#include <cstring>
#include <string>
#include <iostream>
using namespace std;

class MinHeap
{
private:
    struct datoDoble {
        int id;
        int precio;
        datoDoble(int unId, int unPrecio): id(unId), precio(unPrecio){}
    };
    int capacidad;
    int primerLibre;
    datoDoble** arr;

    void cambio(int pos1, int pos2){
        datoDoble* aux = arr[pos1];
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
            if(arr[posPadre]->precio > arr[pos]->precio){
                cambio(pos,posPadre);
                subir(posPadre);
            }else if(arr[posPadre]->precio == arr[pos]->precio && arr[posPadre]->id < arr[pos]->id){
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
                if(arr[posIzq]->precio > arr[posDer]->precio){
                    posMenor= posDer;
                }else if(arr[posIzq]->precio == arr[posDer]->precio && arr[posIzq]->id < arr[posDer]->id){
                    posMenor= posDer;
                }
            }

            if(arr[pos]->precio > arr[posMenor]->precio){
                cambio(pos, posMenor);
                bajar(posMenor);
            }else if(arr[pos]->precio == arr[posMenor]->precio && arr[pos]->id < arr[posMenor]->id){
                cambio(pos, posMenor);
                bajar(posMenor);
            }   

        }
    }


public:
    MinHeap(int _capacidad) {
        capacidad = _capacidad;
        primerLibre = 1;
        arr= new datoDoble*[capacidad+1]();
        for (int i=0; i <= capacidad; i++){
            arr[i]=NULL;
        }
    }

    void insertar(int id, int precio){
        datoDoble * nuevo= new datoDoble(id,precio);
        arr[primerLibre]=nuevo;
        primerLibre++;
        subir(primerLibre-1);
    }

    int tope(){
        return arr[1]->id;
    }

    void eliminar(int pos){
        cambio(pos,primerLibre-1);
        primerLibre--;
        subir(pos);
        bajar(pos);
    }

    void cambiarPrecio(int pos, int precio){
        arr[pos]->precio=precio;
        subir(pos);
    }



};
#endif