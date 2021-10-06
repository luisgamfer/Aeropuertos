
/******************************************************************************
 * main.cpp
 *
 * Main final del módulo Rutas.
 *
 * Alumno: Luis Francisco Gámez Fernández
 * Fecha:30/05/2018
 *****************************************************************************/

#include "ruta.hpp"
#include "aeropuerto.hpp"
#include "aeropuertos.hpp"
#include "rutas.hpp"
#include <iostream>
#include <string>
#include <cassert>

using namespace std;
using namespace bblProgII;

const string FIC_AEROPUERTOS = "localizacion.txt";
const string PAIS = "Spain";
const string FIC_PRECIOS = "precios.txt";

int main(){
    string origen,destino;
    Aeropuertos es;
    Rutas rs,aux;
    Resultado res;
    Ruta r;

    es.obtener_aeropuertos(FIC_AEROPUERTOS, PAIS, res);//Busco los aeropuertos españoles del fichero de aeropuertos y los almaceno en la lista de aeropuertos de es
    rs.obtener_rutas(FIC_PRECIOS,es,res); //Buscamos las rutas entre aeropuertos españoles

    while(true){

        cout << "Introduzca codigo del aeropuerto de origen: ";
        cin >>origen;
        cout << "Introduzca codigo del aeropuerto de destino: ";
        cin >> destino;
        cout << endl;

        cout << "Buscando vuelo de "<<origen<< " a " <<destino<< "..."<<endl;
        rs.obtener_itinerario(origen,destino,aux,res);

            if (res == OK){

        cout << "Itinerario encontrado..."<<endl;

        cout << endl;

        //rs.obtener_itinerario(origen,destino,aux,res); //Imprimo las rutas
        aux.consultar_ruta(0,r,res);

        cout << "---"<<endl;
        r.escribir_ruta();
        cout <<"---"<<endl;
        cout << endl;

        cout << "Generando billetes en fichero " <<origen<<"_"<<destino<<".txt..."<<endl;

        string fichero = origen + "_" + destino +".txt";

        aux.guardar_rutas(fichero,res);

            }else{ //En el caso de que no exista ninguna ruta

                cout << "No existe una ruta" << endl;

            }

    }
}
