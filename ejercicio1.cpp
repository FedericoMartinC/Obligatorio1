#include <cstring>
#include <string>
#include <iostream>
#include "tads/avl.cpp"
using namespace std;

int main()
{
    int N;
    cin >> N;
    AVL<int> * arbol= new AVL<int>;
    for (int i=0; i<N; i++){
        string p1;
        cin >> p1;
        if(p1=="ADD"){
            int id=0;
            string p3;
            cin >> id >> p3;
            arbol->add(id,p3);
        }else if(p1=="FIND"){
            int id=0;
            cin >> id;
            cout << arbol->find(id) << endl;
        }else if(p1=="TOGGLE"){
            int id;
            cin >> id;
            bool existe= arbol->toggle(id);
            if(!existe){
                cout << "libro_no_encontrado" << endl;
            }
        }else{
            cout << arbol->getCount() << endl;
        }
    }
    return 0;
}