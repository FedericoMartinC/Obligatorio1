#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/Cola.cpp"
#include "tads/MinHeap.cpp"
#include "tads/ListaDeAdyacenciaDir.cpp"
#include "tads/ListaDeAdyacenciaNoDir.cpp"

using namespace std;

void textoRec(int v,int* camino,string* misiones,string* ciudades){
    if(camino[v]==-1){
        cout<<ciudades[v];
    }else{
        textoRec(camino[v],camino,misiones,ciudades);
         cout<< " -> " << ciudades[v];
    }
}


int* dijkstra(ListaDeAdyacenciaNoDir * g, int desde,int* &camino){
    MinHeap * proximos = new MinHeap(g->getV() * g->getV());
    bool *visitado = new bool[g->getV() + 1]();
    int *costo = new int[g->getV() + 1]();
    int *vengo = new int[g->getV() + 1]();
    camino = new int [g->getV() + 1]();
    for (int v = 1; v <= g->getV(); v++)
    {
        visitado[v] = false;
        costo[v] = INT_MAX;
        vengo[v] = -1;
        camino[v] = -1;
    }
    costo[desde]=0;
    proximos->insertar(desde,0);
    while(!proximos->estaVacia())
    {
        int v=proximos->tope();
        proximos->eliminar(1);
        if(!visitado[v])
        {
            visitado[v] = true;
            NodoLista * ady=g->adyacentes(v);
            
            while(ady!=NULL)
            {
                if(!visitado[ady->destino] && costo[ady->destino] > costo[v] + ady->costo)
                {
                    costo[ady->destino]=costo[v]+ ady->costo;
                    vengo[ady->destino] = camino[ady->destino] = v;
                    proximos->insertar(ady->destino,costo[ady->destino]);
                }
                ady=ady->sig;
            }
        }
    }
    return costo;

}

int verticeConRecorridoMasCorto(ListaDeAdyacenciaDir * gDir,ListaDeAdyacenciaNoDir * gNoDir, int & idCiudadOrigen, Cola* &libres,string* misiones,string* ciudades,int* idCiudadDadoIdMision,int &tiempoTotal){
    int min=INT_MAX;
    int devuelvo;
    bool unaVez=false;
    int rep=0;
    int* camino;
    int* costoATodos=dijkstra(gNoDir,idCiudadOrigen,camino);
    int costo;
    while(rep!=libres->cantElem()+1){
        int v=libres->desencolar();
        costo=costoATodos[idCiudadDadoIdMision[v]];
        if(costo<min){
            if(unaVez){
                libres->encolar(devuelvo);
            }
            min=costo;
            devuelvo=v;
            unaVez=true;
        }else if(costo==min && v<devuelvo){
            libres->encolar(devuelvo);
            devuelvo=v;
        }else{
            libres->encolar(v);
        }
        rep++;
    }
    textoRec(idCiudadDadoIdMision[devuelvo],camino,misiones,ciudades);
    cout << " -> Mision: " << misiones[devuelvo] << " - " << ciudades[idCiudadDadoIdMision[devuelvo]] << " - Tiempo de viaje: " << min << endl;
    tiempoTotal=tiempoTotal+min;

    idCiudadOrigen=idCiudadDadoIdMision[devuelvo];
    return devuelvo;
}

void ordenTopologico(ListaDeAdyacenciaDir * gDir,ListaDeAdyacenciaNoDir * gNoDir,int idCiudadOrigen,string* misiones,string* ciudades,int* idCiudadDadoIdMision,int &tiempoTotal){
    int V=gDir->getV();
    int* gradoEntrada=new int[V+1]();
    Cola* proximos=new Cola();

    for(int i=1;i<=V;i++){
        Lista * ady=gDir->adyacentes(i);
        while(ady!=NULL){
            gradoEntrada[ady->destino]++;
            ady=ady->sig;
        }
    }

    for(int i=1;i<=V;i++){
        if(gradoEntrada[i]==0){
            proximos->encolar(i);
        }
    }

    while(!proximos->estaVacia()){

        int v=verticeConRecorridoMasCorto(gDir,gNoDir,idCiudadOrigen,proximos,misiones,ciudades,idCiudadDadoIdMision,tiempoTotal);


        Lista* ady=gDir->adyacentes(v);
        while(ady!=NULL){
            gradoEntrada[ady->destino]--;
            if(gradoEntrada[ady->destino]==0){
                proximos->encolar(ady->destino);
            }
            ady=ady->sig;
        }
    }
}

int main()
{
    int tiempoTotal;
    int M;
    cin >> M;
    string * misiones=new string[M+1]();
    int* idCiudadDadoIdMision= new int[M+1]();
    ListaDeAdyacenciaDir * gDir= new ListaDeAdyacenciaDir(M);
    for(int i=0;i<M;i++){
        int idMision;
        string Nombre_Mision;
        int idCiudad;
        cin >> idMision >> Nombre_Mision >> idCiudad;
        misiones[idMision]=Nombre_Mision;
        idCiudadDadoIdMision[idMision]=idCiudad;
        int idOtraMision;
        cin >> idOtraMision;
        while (idOtraMision!=0)
        {
            gDir->agregarRelacion(idMision,idOtraMision);
            cin >> idOtraMision;
        }
        
    }
    int C;
    int O;
    cin >> C;
    cin >> O;
    string * ciudades= new string[C+1];
    ListaDeAdyacenciaNoDir* gNoDir= new ListaDeAdyacenciaNoDir(C);
    for (int i=0;i<C;i++){
        int idCiudad;
        string Nombre_Ciudad;
        cin >> idCiudad >> Nombre_Ciudad;
        ciudades[idCiudad]=Nombre_Ciudad;

    }
    int E;
    cin >> E;
    for (int i=0;i<E;i++){
        int idCiudadOriginal;
        int idCiudadDestino;
        int tiempoDesplazamiento;
        cin >> idCiudadOriginal >> idCiudadDestino >> tiempoDesplazamiento;
        gNoDir->agregarRelacion(idCiudadOriginal,idCiudadDestino,tiempoDesplazamiento);
    }
    cout<< "Ciudad inicial: " << ciudades[O] << endl;
    ordenTopologico(gDir,gNoDir,O,misiones,ciudades,idCiudadDadoIdMision,tiempoTotal);
    cout<<"Misiones ejecutadas con exito."<<endl;
    cout << "Tiempo total de viaje: " << tiempoTotal<<endl;
    return 0;
}