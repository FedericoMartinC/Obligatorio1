#include <cstring>
#include <string>
#include <iostream>
#include "tads/MinHeapYHash.cpp"

using namespace std;

int main()
{
    int N;
    int O;
    cin >> N >> O;
    MinHeapYHash * pedidos= new MinHeapYHash(N);
    string op=" ";
    for(int i=0; i<O ; i++){
        cin >> op;
        if(op == "I"){
            int id;
            int prioridad;
            string paraLlevar;
            string items;
            cin >> id >> prioridad >> paraLlevar >> items;
            if(paraLlevar=="false"){
                pedidos->insertar(id , prioridad, false, items);
            }else{
                pedidos->insertar(id , prioridad, true, items);
            }
        }else if(op=="E"){
            int id;
            cin >> id;
            pedidos->eliminar(id);
        }else{
            int id;
            cin >> id;
            pedidos->cambiarParaLlevar(id);
        }
    }
    while (!pedidos->estaVacio())
    {
        cout << pedidos->tope() << endl;
    }
    
    return 0;
}