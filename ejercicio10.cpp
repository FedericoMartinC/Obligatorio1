#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

bool esSolucion(int colActual,int colMax){
    return colActual==colMax;
}

bool esMejorSolucion(int cantFloresAct,int maxFlores){
    return cantFloresAct > maxFlores;
}

void aplicarMovimiento (int** jardin,int colActual,int &cantFloresAct,int posFila,int flor){
    jardin[posFila][colActual]=flor;
    cantFloresAct=cantFloresAct + 1;
}

void deshacerMovimiento (int** jardin,int colActual,int &cantFloresAct,int posFila,int flor){
    jardin[posFila][colActual]=-1;
    cantFloresAct=cantFloresAct - 1;
}

bool cooEsValida(int col, int fila, int colMAx){
    return col >= 0 && col < colMAx && fila >= 0 && fila < colMAx;
}

bool puedoAplicarMovimiento(int** jardin,int colActual,int posfila,int* restriccionesPorFlor,int FAct, int colMAx){
    int f= posfila;
    int c=colActual;
    if(jardin[f][c]!=-1){
        return false;
    }

    if(cooEsValida(f,c-1,colMAx) && jardin[f][c-1]==FAct){
        return false;
    }

    if(cooEsValida(f+1,c,colMAx) && jardin[f+1][c]==FAct){
        return false;
    }

    if(cooEsValida(f-1,c,colMAx) && jardin[f-1][c]==FAct){
        return false;
    }


    if(cooEsValida(f-1,c-1,colMAx) && jardin[f-1][c-1]==FAct){
        return false;
    }

    if(cooEsValida(f+1,c-1,colMAx) && jardin[f+1][c-1]==FAct){
        return false;
    }
    return true;
}

void maxFloresOpt(int &maxFlores,int &cantFloresAct,int** jardin,int colActual,int colMax, int* restriccionesPorFlor, int cantFlores,int** &mejorJardin,int filaAct){
    if(esSolucion(colActual,colMax) && esMejorSolucion(cantFloresAct,maxFlores)){
        maxFlores=cantFloresAct;
    }else if(!esSolucion(colActual,colMax)){
        bool entro=false;
        for (int FAct=0;FAct<cantFlores;FAct++){
            int restFila=restriccionesPorFlor[FAct];
            if(restFila==-1 || restFila==filaAct){
                if(puedoAplicarMovimiento(jardin,colActual,filaAct,restriccionesPorFlor,FAct,colMax)){
                    entro=true;
                    aplicarMovimiento(jardin, colActual,cantFloresAct,filaAct,FAct);
                    if(filaAct!=colMax-1){
                        maxFloresOpt(maxFlores,cantFloresAct,jardin,colActual,colMax,restriccionesPorFlor,cantFlores,mejorJardin,filaAct + 1);
                    }else{
                        maxFloresOpt(maxFlores,cantFloresAct,jardin,colActual + 1,colMax,restriccionesPorFlor,cantFlores,mejorJardin,0);
                    }
                    deshacerMovimiento(jardin, colActual,cantFloresAct,filaAct,FAct);
                }
            }
        }
        if(!entro){
            if(filaAct!=colMax-1){
                maxFloresOpt(maxFlores,cantFloresAct,jardin,colActual,colMax,restriccionesPorFlor,cantFlores,mejorJardin,filaAct + 1);
            }else{
                maxFloresOpt(maxFlores,cantFloresAct,jardin,colActual + 1,colMax,restriccionesPorFlor,cantFlores,mejorJardin,0);
            }
        }
    }
}


int main()
{
    int N;
    int cantF;
    cin >> N;
    cin >> cantF;
    int** jardin = new int*[N]();
    for(int i=0;i<N;i++){
        jardin[i]=new int[N]();
        for(int j=0;j<N;j++){
            jardin[i][j]=-1;
        }
    }
    int* restriccionesPorFlor= new int[cantF]();
    for(int i=0;i<cantF;i++){
        string flor;
        int fila;
        cin >> flor >> fila;
        restriccionesPorFlor[i]=fila;
    }

    int maxFlores=0;
    int cantFloresAct=0;
    int** mejorJardin=NULL;
    maxFloresOpt(maxFlores,cantFloresAct,jardin,0,N,restriccionesPorFlor,cantF,mejorJardin,0);
    cout << maxFlores;
    return 0;
}