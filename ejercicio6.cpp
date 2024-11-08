#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/ListaDeAdyacenciaNoDir.cpp"
#include "tads/MinHeap.cpp"

using namespace std;

void hacerTextoRec(int v,int* vengo,string* ciudad){
    if(vengo[v]==-1){
        cout<<ciudad[v];
    }else{
        hacerTextoRec(vengo[v],vengo,ciudad);
        cout<< " -> " << ciudad[v];
    }
}


int dijkstra(ListaDeAdyacenciaNoDir * &g, int desde,int hasta,int* &camino){
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

    int devuevlo=costo[hasta];
    while(hasta != -1)
    {
        if(vengo[hasta] != -1){
            g->duplicarCosto(hasta,vengo[hasta]);
        }
        hasta = vengo[hasta];
    }
    return devuevlo;

}

int main()
{
    int N;
    cin >> N;
    string* ciudades= new string[N+1];
    ListaDeAdyacenciaNoDir * grafoABC= new ListaDeAdyacenciaNoDir(N);
    ListaDeAdyacenciaNoDir * grafoBAC= new ListaDeAdyacenciaNoDir(N);
    for(int i=0;i<N;i++){
        int id;
        string ciudad;
        cin >> id >> ciudad;
        ciudades[id]=ciudad;
    }
    int inicio;
    int d_e;
    int r_e;
    int i_r;
    cin >> inicio >> d_e >> r_e >> i_r;
    int E;
    cin >> E;
    for(int i=0; i<E;i++){
        int idOrigen;
        int idDestino;
        int costo;
        cin >> idOrigen >> idDestino >> costo;
        grafoABC->agregarRelacion(idOrigen,idDestino,costo);
        grafoBAC->agregarRelacion(idOrigen,idDestino,costo);
    }

    int* arrI_A;
    int* arrA_B;
    int* arrB_C;
    int I_A=dijkstra(grafoABC,inicio,d_e,arrI_A);
    int A_B=dijkstra(grafoABC,d_e,r_e,arrA_B);
    int B_C=dijkstra(grafoABC,r_e,i_r,arrB_C);

    int* arrI_B;
    int* arrB_A;
    int* arrA_C;
    int I_B=dijkstra(grafoBAC,inicio,r_e,arrI_B);
    int B_A=dijkstra(grafoBAC,r_e,d_e,arrB_A);
    int A_C=dijkstra(grafoBAC,d_e,i_r,arrA_C);

    int ABC=I_A+A_B+B_C;
    int BAC=I_B+B_A+A_C;
    if(ABC<=BAC){
        cout << "BE11, la mejor ruta es Desactivar la Entidad, buscar equipo y punto de extraccion con un costo de "<<ABC<<endl;
        cout << "La otra opcion tiene un costo de "<<BAC<<endl;
        cout << "Paso 1: ";
        hacerTextoRec(d_e,arrI_A,ciudades);
        cout <<" -> Desactivar la Entidad"<<endl<< "Paso 2: ";
        hacerTextoRec(r_e,arrA_B,ciudades);
        cout <<" -> Buscar equipo"<<endl<< "Paso 3: ";
        hacerTextoRec(i_r,arrB_C,ciudades);
        cout <<" -> Ir a Punto de extraccion"<<endl;
    }else{
        cout << "BE11, la mejor ruta es buscar equipo, Desactivar la Entidad y punto de extraccion con un costo de "<<BAC<<endl;
        cout <<"La otra opcion tiene un costo de "<<ABC<<endl;
        cout << "Paso 1: ";
        hacerTextoRec(r_e,arrI_B,ciudades);
        cout <<" -> Buscar equipo"<<endl<< "Paso 2: ";
        hacerTextoRec(d_e,arrB_A,ciudades);
        cout <<" -> Desactivar la Entidad"<<endl<< "Paso 3: ";
        hacerTextoRec(i_r,arrA_C,ciudades);
        cout <<" -> Ir a Punto de extraccion"<<endl;
    }
    return 0;
}