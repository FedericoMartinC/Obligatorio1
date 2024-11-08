#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

bool nomFun(int valorMaximo, int *tiempoCancion, int cantAlumnos, int tamArray, int **&lugarDeCancionPorAlumno, int & maxLocal)
{
    maxLocal=0;
    int posInicio = 1;
    int posEnArray = 1;
    int alumno = 1;
    int suma = 0;
    while (posEnArray <= tamArray && alumno <= cantAlumnos)
    {
        if (posEnArray == tamArray && suma + tiempoCancion[posEnArray] < valorMaximo)
        {
            suma = suma + tiempoCancion[posEnArray];
            lugarDeCancionPorAlumno[alumno][0] = posInicio;
            lugarDeCancionPorAlumno[alumno][1] = posEnArray;
            lugarDeCancionPorAlumno[alumno][2] = suma;
            if(suma>maxLocal){
                maxLocal=suma;
            }
        }
        else if (suma + tiempoCancion[posEnArray] < valorMaximo)
        {
            suma = suma + tiempoCancion[posEnArray];
        }
        else if (posInicio == posEnArray)
        {
            return false;
        }
        else
        {
            lugarDeCancionPorAlumno[alumno][0] = posInicio;
            lugarDeCancionPorAlumno[alumno][1] = posEnArray - 1;
            lugarDeCancionPorAlumno[alumno][2] = suma;
            if(suma>maxLocal){
                maxLocal=suma;
            }
            suma = tiempoCancion[posEnArray];
            if (suma > valorMaximo)
            {
                return false;
            }
            alumno++;
            posInicio = posEnArray;
        }
        posEnArray++;
    }
    if (alumno > cantAlumnos || posEnArray <= tamArray)
    {
        return false;
    }
    else
    {
        return true;
    }
}

int maxTiempo(int *tiempoCanciones, int tam)
{
    int devuelvo = 0;
    for (int i = 1; i <= tam; i++)
    {
        devuelvo = devuelvo + tiempoCanciones[i];
    }
    return devuelvo;
}

int minTiempo(int *tiempoCanciones, int tam)
{
    int min = INT_MAX;
    for (int i = 1; i <= tam; i++)
    {
        if (tiempoCanciones[i] < min)
        {
            min = tiempoCanciones[i];
        }
    }
    return min;
}

void tiempoMinimo(int *tiempoCanciones, int cantAlumnos, int tamArray, int **&lugarDeCancionPorAlumno,int & maxTiempoEscuchando)
{
    int maxDeTiempo = maxTiempo(tiempoCanciones, tamArray);
    int minDeTiempo = minTiempo(tiempoCanciones, tamArray);
    int mitad = 0;
    bool termine = false;
    int **aux = new int *[cantAlumnos + 1];
    for (int i = 1; i <= cantAlumnos; i++)
    {
        aux[i] = new int[3];
        for (int j = 0; j < 3; j++)
        {
            aux[i][j] = -1;
        }
    }
    int mitadMenor = INT_MAX;
    int maxLocal;
    while (!termine)
    {
        if (mitad == (maxDeTiempo + minDeTiempo) / 2)
        {
            termine = true;
        }
        else
        {
            mitad = (maxDeTiempo + minDeTiempo) / 2;
        }

        if (nomFun(mitad, tiempoCanciones, cantAlumnos, tamArray, aux, maxLocal))
        {
            if (mitad < mitadMenor)
            {
                for (int i = 1; i <= cantAlumnos; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        lugarDeCancionPorAlumno[i][j] = aux[i][j];
                    }
                }
                maxTiempoEscuchando=maxLocal;
                mitadMenor = mitad;
            }
            maxDeTiempo = mitad;
        }
        else
        {
            minDeTiempo = mitad;
        }
        for (int i = 1; i <= cantAlumnos; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                aux[i][j]=-1;
            }
        }
    }
}

int main()
{
    int N;
    cin >> N;
    int *tiempoDeCanciones = new int[N + 1]();
    for (int i = 1; i <= N; i++)
    {
        int tiempoCancion;
        cin >> tiempoCancion;
        tiempoDeCanciones[i] = tiempoCancion;
    }
    int cantAlumnos;
    cin >> cantAlumnos;
    int **lugarDeCancionPorAlumno = new int *[cantAlumnos + 1];
    for (int i = 1; i <= cantAlumnos; i++)
    {
        lugarDeCancionPorAlumno[i] = new int[3];
        for (int j = 0; j < 3; j++)
        {
            lugarDeCancionPorAlumno[i][j] = -1;
        }
    }
    int maxTiempoEscuchando=0;
    tiempoMinimo(tiempoDeCanciones, cantAlumnos, N, lugarDeCancionPorAlumno,maxTiempoEscuchando);
    for (int i = 1; i <= cantAlumnos; i++)
    {
        if (lugarDeCancionPorAlumno[i][0] != -1)
        {
            cout << lugarDeCancionPorAlumno[i][2] << " ";
            for (int j = 0; j < 2; j++)
            {
                cout << lugarDeCancionPorAlumno[i][j] << " ";
            }
            cout << endl;
        }
    }
    cout<<maxTiempoEscuchando<<endl;
    return 0;
}