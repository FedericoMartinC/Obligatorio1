#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/HashCerrado.cpp"

using namespace std;

int main()
{
    int N;
    cin >> N;
    HashCerrado * tabla= new HashCerrado(N);
    for (int i=0; i<N; i++){
        string p1;
        cin >> p1;
        if(p1=="ADD"){
            int id=0;
            string p3;
            cin >> id >> p3;
            tabla->add(id,p3);
        }else if(p1=="FIND"){
            int id=0;
            cin >> id;
            cout << tabla->find(id) << endl;
        }else if(p1=="TOGGLE"){
            int id;
            cin >> id;
            bool existe= tabla->toggle(id);
            if(!existe){
                cout << "libro_no_encontrado" << endl;
            }
        }else{
            cout << tabla->getCount() << endl;
        }
    }
    return 0;
}