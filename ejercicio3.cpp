#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/MinHeap.cpp"
#include "tads/HashAbierto.cpp"

using namespace std;

int main()
{
    int N;
    cin >> N;
    bool* salio= new bool[N+1]();
    MinHeap * obj= new MinHeap(N);
    for(int i=0;i<N;i++){
        int id;
        int precio;
        cin >> id >> precio;
        obj->insertar(id,precio);
    }
    int k;
    cin >> k;
    int a=0;
    while(a!=k){
        int id=obj->tope();
        if(!salio[id]){
            cout << obj->tope() << endl;
            salio[id]=true;
            a++;
        }
        obj->eliminar(1);
    }
    return 0;
}