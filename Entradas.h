//=====================================================
// File: Entradass.h
// Author: Carolina Herrera Martinez A01411547
// Evidencia 2
// Descripción:
// Este header se encarga de crear una clase para las 
// entradas de texto que se van leyendo de la bitacora
// para posteriormente ordenarlas y almacenarlas en 
// un queue
//=====================================================


#ifndef Entradas_h
#define Entradas_h
#include <string>
using namespace std;

class Entradas{
  public:
    Entradas(string, int, string, string,string);
    int JerarquiaDias(string, int, string);
    bool operator==(int);
    bool operator!=(int);
    bool operator<=(Entradas);
    bool operator>(int);
    friend ostream& operator<<(ostream&, Entradas);
  
  private:
    int dia, orden;
    string mes, hora, direccionIP, motivo;

};



Entradas::Entradas(string _mes, int _dia, string _hora, string _direccionIP, string _motivo){
    mes = _mes;
    dia = _dia;
    hora = _hora;
    direccionIP = _direccionIP;
    motivo = _motivo;
    orden = JerarquiaDias(mes, dia, hora);
}



bool Entradas::operator<=(Entradas v){
    if(orden <= v.orden)        return true;
    
    return false;
}

bool Entradas::operator>(int n){
    if(orden > n)        return true;

    return false;
}

bool Entradas::operator==(int n){
    if(orden == n)        return true;

    return false;
}

bool Entradas::operator!=(int n){
    if(orden != n)        return true;

    return false;
}

//o(1)
int Entradas::JerarquiaDias(string mes, int dia, string hora){
    if(mes == "Jun")        return 600 + dia;
    if(mes == "Jul")        return 700 + dia;
    if(mes == "Aug")        return 800 + dia;
    if(mes == "Sep")        return 900 + dia;
    if(mes == "Oct")        return 1000 + dia;
    return -1;
}




ostream& operator<<(ostream& ostr, Entradas v){
    ostr  << v.mes << ' ' << v.dia << ' ' << v.hora << ' ' << v.direccionIP << v.motivo;
    return ostr;
}

#endif
