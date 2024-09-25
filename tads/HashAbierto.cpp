#ifndef HASH_ABIERTO
#define HASH_ABIERTO
#include <cstring>
#include <string>
#include <iostream>
using namespace std;

class HashAbierto 
{
private:
    struct NodoLista
    {
        int id;
        int pos;
        NodoLista *sig;
        NodoLista(int unId, int unaPos) : id(unId), pos(unaPos), sig(NULL) {}
    };

    NodoLista **arr;

    int buckets;

    int getBucket(int id)
    {
        return (id % this->buckets);
    }

    void insertIni(NodoLista *&nodoPtr, int id, int pos)
    {
        NodoLista* nuevo=new NodoLista(id,pos);
        nuevo->sig=nodoPtr;
        nodoPtr=nuevo;
    }

    int getRec(NodoLista *nodoPtr, int id , bool eliminar)
    {
        if (nodoPtr->id == id)
        {
            //cout << nodoPtr->pos << " " <<id <<endl;
            int a=nodoPtr->pos;
            if(eliminar){
                NodoLista *toDelete = nodoPtr;
                nodoPtr = nodoPtr->sig;
                delete toDelete;
            }
            return a;
        }
        else
        {
            return getRec(nodoPtr->sig, id,eliminar);
        }
    }

    void removeRec(NodoLista *&nodoPtr, int id)
    {
        if (nodoPtr->id == id)
        {
            NodoLista *toDelete = nodoPtr;
            nodoPtr = nodoPtr->sig;
            delete toDelete;
        }
        else
        {
            removeRec(nodoPtr->sig, id);
        }
    }

    void recorrerListaRec(NodoLista* &l, int id, int pos){
        if(l!=NULL){
            if(l->id==id){
                //if (id==2){
                //    cout << id << " " << l->pos << " " << pos << endl;
                //}
                l->pos=pos;
            }else{
                recorrerListaRec(l->sig,id,pos);
            }
        }else{
            return;
        }
    }

public:
    HashAbierto(int capInicial)
    {
        arr = new NodoLista *[capInicial]();
        for (int i = 0; i < capInicial; i++)
        {
            arr[i] = NULL;
        }
        buckets = capInicial;
    }

    void insert(int id, int pos)
    {
        int bucket = this->getBucket(id);
        this->insertIni(arr[bucket], id, pos);
    }

    int get(int id,bool eliminar)
    {
        int bucket = this->getBucket(id);
        return this->getRec(arr[bucket], id, eliminar);
    }

    void remove(int id)
    {
        int bucket = this->getBucket(id);
        this->removeRec(arr[bucket], id);
    }

    void cambiarPos(int id,int pos){
        int bucket= this->getBucket(id);
        this->recorrerListaRec(arr[bucket], id, pos);
    }
};
#endif