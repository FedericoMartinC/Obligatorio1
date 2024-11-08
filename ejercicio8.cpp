#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include <cmath>

using namespace std;

struct datoTriple{
    int ejeX;
    int ejeY;
    int poblacion;
};

double distancia(int inicio,int final, datoTriple** puntos){
    return (double)((double)sqrt(pow(puntos[final]->ejeX-puntos[inicio]->ejeX,2)+pow(puntos[final]->ejeY-puntos[inicio]->ejeY,2)))+(double)(abs(puntos[final]->poblacion-puntos[inicio]->poblacion))/(max(puntos[final]->poblacion,puntos[inicio]->poblacion));
}

double distanciaEjeX(int inicio,int final, datoTriple** puntos){
    return abs(puntos[final]->ejeX-puntos[inicio]->ejeX);
}

double distanciaEjeY(int inicio,int final, datoTriple** puntos){
    return abs(puntos[final]->ejeY-puntos[inicio]->ejeY);
}

int* minDeDist(int* izq, int* der, datoTriple** puntos){
    double distIzq=distancia(izq[0],izq[1],puntos);
    double distDer=distancia(der[0],der[1],puntos);

    if(distIzq<distDer){
        return izq;
    }else if(distIzq>distDer){
        return der;
    }else{
        int pobIzq=puntos[izq[0]]->poblacion+puntos[izq[1]]->poblacion;
        int pobDer=puntos[der[0]]->poblacion+puntos[der[1]]->poblacion;
        if(pobIzq>pobDer){
            return izq;
        }else{
            return der;
        }
    }
}

int* intercalarEsp(int* izq, int* der, int inicio,int mitad, int final,datoTriple**  puntos){
    int tamIzq=(mitad+1)-inicio;
    int tamDer=(final+1)-(mitad+1);
    int* devuelvo= new int[tamIzq+tamDer];
    
    int i = 0, j = 0, k = 0;
    while (i < tamIzq && j < tamDer) {
        if (puntos[izq[i]]->ejeY < puntos[der[j]]->ejeY) {
            devuelvo[k++] = izq[i++];
        } else {
            devuelvo[k++] = der[j++];
        }
    }
    while (i < tamIzq) {
        devuelvo[k++] = izq[i++];
    }

    while (j < tamDer) {
        devuelvo[k++] = der[j++];
    }

    return devuelvo;
}

int* mergeSortEsp(int*  posPuntos, int inicio, int final,datoTriple**  puntos){
    if(inicio==final){
        int* aux = new int[1];
        aux[0] = posPuntos[inicio];
        return aux;
    }

    int mitad = (final+inicio)/2;

    int* izq= mergeSortEsp(posPuntos,inicio,mitad,puntos);
    int* der= mergeSortEsp(posPuntos,mitad+1,final,puntos);

    return intercalarEsp(izq,der,inicio,mitad,final,puntos);
}

datoTriple** intercalar(datoTriple** izq, datoTriple** der, int inicio,int mitad, int final){
    int tamIzq=(mitad+1)-inicio;
    int tamDer=(final+1)-(mitad+1);
    datoTriple** devuelvo= new datoTriple*[tamIzq+tamDer];

    int i = 0, j = 0, k = 0;
    while (i < tamIzq && j < tamDer) {
        if (izq[i]->ejeX < der[j]->ejeX) {
            devuelvo[k++] = izq[i++];
        } else {
            devuelvo[k++] = der[j++];
        }
    }

    while (i < tamIzq) {
        devuelvo[k++] = izq[i++];
    }

    while (j < tamDer) {
        devuelvo[k++] = der[j++];
    }

    return devuelvo;
}

datoTriple** mergeSort(datoTriple**  puntos, int inicio, int final){
    if(inicio==final){
        datoTriple** aux = new datoTriple*[1];
        aux[0] = puntos[inicio];
        return aux;
    }

    int mitad = (final+inicio)/2;
    datoTriple** izq= mergeSort(puntos,inicio,mitad);
    datoTriple** der= mergeSort(puntos,mitad+1,final);

    return intercalar(izq,der,inicio,mitad,final);
}


int* menoresADirDer(int* posDist,int mitad, int final,datoTriple** puntos, int & ultArr){
    int* devuelvo = new int[(final+2)-mitad]();
    bool mayor=false;
    int pos=mitad+1;
    double dist=distancia(posDist[0],posDist[1],puntos);
    while(pos<=final && !mayor){
        double distAct=distanciaEjeX(mitad,pos,puntos);
        if(distAct<=dist){
            devuelvo[++ultArr]=pos;
        }else if(distAct==dist){
            int poblAct=puntos[mitad]->poblacion+puntos[pos]->poblacion;
            int pob=puntos[posDist[0]]->poblacion+puntos[posDist[1]]->poblacion;
            if(poblAct>pob){
                ultArr=ultArr+1;
                devuelvo[ultArr]=pos;
            }else{
                mayor=true;
            }
        }else{
            mayor=true;
        }
        pos++;
    }
    
    if(ultArr>=0){
        int* devuelvoOrdenado=mergeSortEsp(devuelvo,0,ultArr,puntos);
        return devuelvoOrdenado;
    }else{
        return devuelvo;
    }
}

int* menoresADirIzq(int* posDist,int inicio, int mitad,datoTriple** puntos, int& ultArr){
    int* devuelvo = new int[(mitad+1)-inicio]();
    bool mayor=false;
    int pos=mitad-1;
    ultArr=ultArr+1;
    devuelvo[ultArr]=mitad;
    double dist=distancia(posDist[0],posDist[1],puntos);
    while(pos>=inicio && !mayor){
        double distAct=distanciaEjeX(pos,mitad,puntos);
        if(distAct<=dist){
            ultArr=ultArr+1;
            devuelvo[ultArr]=pos;
        }else if(distAct==dist){
            int poblAct=puntos[mitad]->poblacion+puntos[pos]->poblacion;
            int pob=puntos[posDist[0]]->poblacion+puntos[posDist[1]]->poblacion;
            if(poblAct>pob){
                ultArr=ultArr+1;
                devuelvo[ultArr]=pos;
            }else{
                mayor=true;
            }
        }else{
            mayor=true;
        }
        pos--;
    }
    if(ultArr>=0){
        int* devuelvoOrdenado=mergeSortEsp(devuelvo,0,ultArr,puntos);
        return devuelvoOrdenado;
    }else{
        return devuelvo;
    }
}

int* nomFun(int* posDistMin,int inicio, int mitad, int final,datoTriple** puntos){
    int ultArrDer=-1;
    int ultArrIzq=-1;
    int* puntosMenorDistanciaLadoDer= menoresADirDer(posDistMin,mitad,final,puntos,ultArrDer);
    int* puntosMenorDistanciaLadoIzq= menoresADirIzq(posDistMin,inicio,mitad,puntos,ultArrIzq);

    double distMin=distancia(posDistMin[0],posDistMin[1],puntos);
    int* devuelvo= posDistMin;

    int posActArrIzq=0;
    while(posActArrIzq<=ultArrIzq){
        int posActArrDer=0;
        bool menorDistanciaEjeY=true;
        while(posActArrDer<=ultArrDer && menorDistanciaEjeY){
            double distAct=distancia(puntosMenorDistanciaLadoIzq[posActArrIzq],puntosMenorDistanciaLadoDer[posActArrDer],puntos);
            /*if(distanciaEjeY(puntosMenorDistanciaLadoIzq[posActArrIzq],puntosMenorDistanciaLadoDer[posActArrDer],puntos) > distMin ){
               cout << distanciaEjeY(puntosMenorDistanciaLadoIzq[posActArrIzq],puntosMenorDistanciaLadoDer[posActArrDer],puntos) <<" "<< distMin <<endl; 
                cout << puntos[puntosMenorDistanciaLadoIzq[posActArrIzq]]->ejeX <<" "<< puntos[puntosMenorDistanciaLadoDer[posActArrDer]]->ejeX
                menorDistanciaEjeY=false;
            }else*/ if(distAct<distMin){
                distMin=distAct;
                devuelvo[0]=puntosMenorDistanciaLadoIzq[posActArrIzq];
                devuelvo[1]=puntosMenorDistanciaLadoDer[posActArrDer];
            } if(distAct==distMin){
                int poblAct=puntos[puntosMenorDistanciaLadoIzq[posActArrIzq]]->poblacion+puntos[puntosMenorDistanciaLadoDer[posActArrDer]]->poblacion;
                int pob=puntos[devuelvo[0]]->poblacion+puntos[devuelvo[1]]->poblacion;
                if(poblAct>pob){
                    distMin=distAct;
                    devuelvo[0]=puntosMenorDistanciaLadoIzq[posActArrIzq];
                    devuelvo[1]=puntosMenorDistanciaLadoDer[posActArrDer];
                }
            }
            posActArrDer++;
        }
        posActArrIzq++;
    }
    return devuelvo;
}

int* distanciaMinimaDeTres(datoTriple** puntos,int inicio, int final){
    double min=INT_MAX;
    int* devuelvo= new int[2]();

    for(int i=inicio; i<=final;i++){
        for(int j=i+1;j<=final;j++){
            double dist=distancia(i,j,puntos);
            if(dist<min){
                min=dist;
                devuelvo[0]=i;
                devuelvo[1]=j;
            }else if(min!=INT_MAX && dist==min){
                int pobAct=puntos[i]->poblacion+puntos[j]->poblacion;
                int pob=puntos[devuelvo[0]]->poblacion+puntos[devuelvo[1]]->poblacion;
                if(pobAct>pob){
                    min=dist;
                    devuelvo[0]=i;
                    devuelvo[1]=j;
                }
            }
        }
    }
    
    return devuelvo;
}

int* distanciaMinimaDeDos(datoTriple** puntos,int inicio, int final){
    int* devuelvo=new int[2]();
    devuelvo[0]=inicio;
    devuelvo[1]=final;
    return devuelvo;
}

int* distanciaMinima(datoTriple** puntos,int inicio, int final){
    if((final+1)-inicio==3){
        return distanciaMinimaDeTres(puntos,inicio,final);
    }else if ((final+1)-inicio==2){
        return distanciaMinimaDeDos(puntos,inicio,final);
    }
    
    int mitad=(final+inicio)/2;

    int* distanciaMinimaIzq=distanciaMinima(puntos,inicio,mitad);
    int* distanciaMinimaDer=distanciaMinima(puntos,mitad+1,final);

    return nomFun(minDeDist(distanciaMinimaIzq,distanciaMinimaDer,puntos),inicio,mitad,final,puntos);
}

int main()
{
    int N;
    cin >> N;
    datoTriple** puntos= new datoTriple*[N]();
    for(int i=0;i<N;i++){
        int coorX;
        int coorY;
        int pob;
        cin >> coorX >> coorY >> pob;
        datoTriple* nuevo=new datoTriple();
        nuevo->ejeX=coorX;
        nuevo->ejeY=coorY;
        nuevo->poblacion=pob;
        puntos[i]=nuevo;
    }

    datoTriple** puntosOrdenados=mergeSort(puntos,0,N-1);

    int* aux=distanciaMinima(puntosOrdenados,0,N-1);

    if(puntosOrdenados[aux[0]]->ejeX<puntosOrdenados[aux[1]]->ejeX){
        cout << puntosOrdenados[aux[0]]->ejeX <<" "<<puntosOrdenados[aux[0]]->ejeY <<" "<<puntosOrdenados[aux[0]]->poblacion<<endl;
        cout << puntosOrdenados[aux[1]]->ejeX <<" "<<puntosOrdenados[aux[1]]->ejeY <<" "<<puntosOrdenados[aux[1]]->poblacion<<endl;
    }else if(puntosOrdenados[aux[0]]->ejeX>puntosOrdenados[aux[1]]->ejeX){
        cout << puntosOrdenados[aux[1]]->ejeX <<" "<<puntosOrdenados[aux[1]]->ejeY <<" "<<puntosOrdenados[aux[1]]->poblacion<<endl;
        cout << puntosOrdenados[aux[0]]->ejeX <<" "<<puntosOrdenados[aux[0]]->ejeY <<" "<<puntosOrdenados[aux[0]]->poblacion<<endl;
    }else{
        if(puntosOrdenados[aux[0]]->ejeY<puntosOrdenados[aux[1]]->ejeY){
            cout << puntosOrdenados[aux[0]]->ejeX <<" "<<puntosOrdenados[aux[0]]->ejeY <<" "<<puntosOrdenados[aux[0]]->poblacion<<endl;
            cout << puntosOrdenados[aux[1]]->ejeX <<" "<<puntosOrdenados[aux[1]]->ejeY <<" "<<puntosOrdenados[aux[1]]->poblacion<<endl;
        }else{
             cout << puntosOrdenados[aux[1]]->ejeX <<" "<<puntosOrdenados[aux[1]]->ejeY <<" "<<puntosOrdenados[aux[1]]->poblacion<<endl;
            cout << puntosOrdenados[aux[0]]->ejeX <<" "<<puntosOrdenados[aux[0]]->ejeY <<" "<<puntosOrdenados[aux[0]]->poblacion<<endl;
        }
    }



    return 0;
}