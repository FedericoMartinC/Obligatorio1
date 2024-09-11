#ifndef HASH_CERRADO
#define HASH_CERRADO
#include <cassert>
#include <string>
#include <iostream>
using namespace std;

class HashCerrado
{
private:
    struct Nodo{
        int id;
        string titulo;
        bool habilitado;
        Nodo(int unId, string unTitulo): id(unId), titulo(unTitulo), habilitado(true) {}
    };
    Nodo** arr;
    int capacidad;
    int cantLibrosHa;
    int cantLibrosDes;
    
    int hash1(int id){
        return id;
    }

    int hash2(int id){;
        return  (id/2);
    }

    int getPosicion(int id ,int i){
        int n= this->hash1(id);
        int m=this->hash2(id);
        return abs(n + (i * m)) % capacidad;
    }

    void addRec(int i, string titulo, int id){
        int posAc= getPosicion(id,i);
        if (arr[posAc]==NULL){
            arr[posAc]=new Nodo(id,titulo);
            this->cantLibrosHa++;
        }else if (arr[posAc]->id==id){
            arr[posAc]->titulo=titulo;
            if(!arr[posAc]->habilitado){
                this->cantLibrosHa++;
                this->cantLibrosDes--;
                arr[posAc]->habilitado=true;
            }
        }else{
            addRec( i + 1 , titulo, id);
        }
    }

    string findRec(int i, int id){
        int posAc=getPosicion(id,i);
        if(arr[posAc]==NULL){
            return "libro_no_encontrado";
        }else if(arr[posAc]->id==id){
            if(arr[posAc]->habilitado){
                return arr[posAc]->titulo + " " + "H";
            }else{
                return arr[posAc]->titulo + " " + "D";
            }
        }else{
            return findRec(i + 1 , id);
        }
    }

    bool toggleRec(int i,int id){
        int posAc=getPosicion(id,i);
        if(arr[posAc]==NULL){
            return false;
        }
        else if(arr[posAc]->id==id){
            if(arr[posAc]->habilitado){
                this->cantLibrosDes++;
                this->cantLibrosHa--;
                arr[posAc]->habilitado=false;
            }else{
                this->cantLibrosDes--;
                this->cantLibrosHa++;
                arr[posAc]->habilitado=true;
            }
            return true;
        }else{
            return toggleRec(i + 1 ,id);
        }
    }

    string count(){
        return  to_string(this->cantLibrosDes+this->cantLibrosHa) + " " + to_string(this->cantLibrosHa) + " " + to_string(this->cantLibrosDes);
    }


public:
    HashCerrado(int _capacidad)
    {
        this->arr = new Nodo *[_capacidad]();
        for (int i = 0; i < _capacidad; i++)
        {
            arr[i] = NULL;
        }
        capacidad= _capacidad;
        this->cantLibrosDes=0;
        this->cantLibrosHa=0;
    }

    void add(int id, string titulo){
        this->addRec(0,titulo,id);
    }
    
    string find(int id){
        return this->findRec(0,id);
    }

    bool toggle (int id){
        return this->toggleRec(0, id);
    }

    string getCount(){
        return count();
    }
};
#endif