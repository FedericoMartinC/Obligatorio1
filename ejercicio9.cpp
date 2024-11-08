#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

void mochila(int cantJu,int presupuesto, int maxJuEx, int cantJuNec, int* valoraciones,int* salarios,int* extranjeros,int* posOnceInicial){
    int ****tab=new int***[cantJu+1]();
    for(int i=0; i<= cantJu+1;i++){
        tab[i]=new int**[presupuesto+1]();
        for(int j=0;j<=presupuesto;j++){
            tab[i][j]=new int*[maxJuEx+1]();
            for(int k=0;k<=maxJuEx;k++){
                tab[i][j][k]=new int[cantJuNec+1]();
            }
        }
    }

    for(int jugAct=1;jugAct<=cantJu;jugAct++){
        int valoracionJug = valoraciones[jugAct - 1];
        int salarioJug = salarios[jugAct - 1];
        int extraJug = extranjeros[jugAct - 1];
        int onceJug = posOnceInicial[jugAct - 1];
        for(int capSalarioAct=0;capSalarioAct<=presupuesto;capSalarioAct++){

            for(int capExtraJugAct=0;capExtraJugAct<=maxJuEx;capExtraJugAct++){

                for(int capOnceJugAct=0;capOnceJugAct<=cantJuNec;capOnceJugAct++){

                    if(salarioJug>capSalarioAct || extraJug>capExtraJugAct || onceJug > capOnceJugAct){
                        tab[jugAct][capSalarioAct][capExtraJugAct][capOnceJugAct]=tab[jugAct-1][capSalarioAct][capExtraJugAct][capOnceJugAct];
                    }else{
                        int valorDeNoUsarJug = tab[jugAct-1][capSalarioAct][capExtraJugAct][capOnceJugAct];
                        int valorDeUsarJug= valoracionJug+tab[jugAct-1][capSalarioAct-salarioJug][capExtraJugAct-extraJug][capOnceJugAct-onceJug];
                        if(valorDeUsarJug>=valorDeNoUsarJug){
                            tab[jugAct][capSalarioAct][capExtraJugAct][capOnceJugAct]=valorDeUsarJug;
                        }else{
                            tab[jugAct][capSalarioAct][capExtraJugAct][capOnceJugAct]=valorDeNoUsarJug;
                        }
                    }
                }
            }
        }
    }




    int valoracion= tab[cantJu][presupuesto][maxJuEx][cantJuNec];
    cout << (valoracion/11);
}

int main()
{
    int N;
    cin >> N;
    int* valoraciones=new int[N]();
    int* salarios=new int[N]();
    int* extranjeros= new int[N]();
    int* posOnceInicial=new int[N]();
    for(int i=0;i<N;i++){
        int ritmo;
        int tiro;
        int pase;
        int regate;
        int defensa;
        int fisico;
        cin >> ritmo >> tiro >> pase >> regate >> defensa >> fisico;
        int valoracion=(ritmo+tiro+pase+regate+defensa+fisico)/6;
        string ff;
        cin >> ff;
        if (ff=="Lesionado"){
            valoracion=0;
        }else if(ff=="Mala"){
            valoracion=valoracion-5;
        }else if(ff=="Buena"){
            valoracion=valoracion+5;
        }

        int salario;
        string extranjero;
        string confianza;
        cin >> salario>> extranjero >> confianza;

        if(confianza=="Alta"){
            valoracion=valoracion+5;
        }else if(confianza=="Baja"){
            valoracion=valoracion-5;
        }
        valoraciones[i]=valoracion;
        salarios[i]=salario;
        posOnceInicial[i]=1;
        if(extranjero=="Si"){
            extranjeros[i]=1;
        }else{
            extranjeros[i]=0;
        }
    }
    int presupuesto;
    int cantJuEx;
    cin >> presupuesto >> cantJuEx;
    mochila(N,presupuesto,cantJuEx,11,valoraciones,salarios,extranjeros,posOnceInicial);
    return 0;
}