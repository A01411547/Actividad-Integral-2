//=====================================================
// File: main.cpp 
// Author: Carolina Herrera Martinez A01411547
// Evidencia 2
// Descripción:
// Este programa analiza la bitacora de acceso de un gym
// y ordena los datos por mes. 
// después, almacena los datos ordenados en una Fila (Queue)
// para poder guardar todo en un archivo que se le entrega
// al usuario
//=====================================================


#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include "Entradas.h"
using namespace std;

struct informacion{
  int dia, mes;
  string IP,  error;
};




//o(n)

void guardarQueue(queue<Entradas*> q, string nomFile) {
  ofstream file(nomFile);
  int tamanio = q.size();
  for (int i = 0; i < tamanio - 1; i++) {
    file << *q.front() << endl; 
    q.pop();  }

    file << *q.front();
    file.close();

}


//o(n)   (El vector es de uso temporal, abajo está la
// implementación del queue)
void llenarVector(vector<Entradas*> &v){
    string mes, hora, direccionIP, razon;
    int dia;    
    ifstream file("bitacora.txt");
    while(file >> mes >> dia >> hora >> direccionIP){
        getline(file, razon);
        v.push_back(new Entradas(mes, dia, hora, direccionIP, razon));
    } 
     file.close();  
}

//o(1)
int Orden(string mes, int dia){
    if(mes == "Jun")
        return 600 + dia;
    if(mes == "Jul")
        return 700 + dia;
    if(mes == "Aug")
        return 800 + dia;
    if(mes == "Sep")
        return 900 + dia;
    if(mes == "Oct")
        return 1000 + dia;
    
    return -1;
} 

//o(n)
void juntar(vector<Entradas*> &v, vector<Entradas*> &mov, int ini, int fin){
    int med = (ini + fin) / 2;
    int i = ini;
    int j = med+1;
    int k = ini;

    while(i <= med && j <= fin)
        if(*v[i] <= *v[j])    mov[k++] = v[i++];
        else
            mov[k++] = v[j++];
    
    while(i <= med)        mov[k++] = v[i++];
    
    while(j <= fin)        mov[k++] = v[j++];
    
    for(int z = ini; z <= fin; z++)        v[z] = mov[z];
}
//o(nlog2 n)
void MergeSort(vector<Entradas*> &v, vector<Entradas*> &mov, int ini, int fin){
    int med;

    if(ini < fin){
        med = (ini + fin) / 2;
        MergeSort(v, mov, ini, med);
        MergeSort(v, mov, med+1, fin);
        juntar(v, mov, ini, fin);
    }
}
//o(log n)
int busquedaBinaria(vector<Entradas*> v, int llave, bool inicio){
    int tamanio = v.size(), ini = 0, fin = tamanio - 1,  med;
    
    while (ini <= fin){
        med = (ini + fin) / 2;
        if (*v[med] == llave){
            if(inicio){
                if(med == 0 || *v[med-1] != llave)
                  return med;
                fin = med - 1;
            } else{
                if(med == tamanio-1 || *v[med+1] != llave)
                    return med;
                ini = med + 1;
            }
        } else if(*v[med] > llave)
            fin = med - 1;
        else
            ini = med + 1;
    }  
    return -1; 
}
//o(logn)
void busqueda(vector<Entradas*> v, string mesInicial, string mesFinal, int diaInicial, int diaFinal){
    int ini = Orden(mesInicial, diaInicial), posInicial;
    int fin = Orden(mesFinal, diaFinal), posFinal;
    posInicial = busquedaBinaria(v, ini, true);
    posFinal = busquedaBinaria(v, fin, false);
    cout << endl;
    
    if(posInicial == -1)
        cout << "La fecha " << mesInicial << ' ' << diaInicial << " no ha sido encontrada." << endl;
    else if(posFinal == -1)
        cout << "La fecha " << mesFinal << ' ' << diaFinal << " no ha sido encontrada." << endl;
    else
        for(int i = posInicial; i<=posFinal; i++)   cout <<  *v[i] << endl;
}



int main(){
    std::queue<Entradas*> q; //queue principal de datos
    vector<Entradas*> A; //vector temporal de orden
    llenarVector(A);
    int tamanio = A.size();
    vector<Entradas*> mov(tamanio);
    MergeSort(A, mov, 0, tamanio-1);
       

    int diaInicial, diaFinal;
    diaInicial = 1;
    diaFinal = 30;

    string mesInicial, mesFinal, nombreArchivoNuevo;
        
    cout << endl << "Hecho por: Carolina Herrera Mtz. A01411547 Evidencia 2" << endl;
    cout << "====================================================" << endl;
    cout << "Bienvend@ al sistema de ingresos del gimnasio RUSH Fitness! " << endl;
    cout << "====================================================" << endl;
    cout << "Introduce El mes inicial para la consulta. Meses disponibles: " << endl;
    cout << endl << "Jun Jul Aug Sep Oct "<<endl;
    cout<< ": " ;
              
        cin >> mesInicial ;

    cout << "Introduce el mes final de busqueda en el mismo formato de antes " << endl; 
    cout << ": ";
    cin >> mesFinal;

    busqueda(A, mesInicial, mesFinal, diaInicial, diaFinal);

    for (const auto& e: A)
     q.push(e);

    cout << endl << "Introduce el nombre del archivo a generar con la bitacora ordenada: ";
    cin >> nombreArchivoNuevo;
    guardarQueue(q, nombreArchivoNuevo);      
    
    
    return 0;
}




