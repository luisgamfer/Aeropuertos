#include "aeropuertos.hpp"
#include <iostream>
#include <string>
#include <array>

using namespace std;

namespace bblProgII{

	// Constructor por defecto
	// Inicializa la lista de aeropuertos a lista vac�a
	Aeropuertos::Aeropuertos(): n_aeropuertos(0){}

	// Constructor de copia de la clase
	Aeropuertos::Aeropuertos(const Aeropuertos &otro_objeto): n_aeropuertos(otro_objeto.n_aeropuertos), aeropuertos(otro_objeto.aeropuertos){}

	// Destructor del objeto
	Aeropuertos::~Aeropuertos(){}


	// Escribe por pantalla la cadena de caracteres
    // correspondiente al error.
    // Par�metros:
    // 		- res (E): c�digo de error
    void escribir_resultado(const Resultado &res){

        switch (res){

            case OK: cout << " --- OK." << endl;
                break;
            case FIC_ERROR: cout << " --- ERROR DE FICHERO. " << endl;
                break;
            case NO_EXISTE: cout << " --- NO EXISTE. " << endl;
                break;
            case YA_EXISTE: cout << " --- YA EXISTE. " << endl;
                break;
            default: cout << " --- CODIGO DE ERROR DESCONOCIDO." << endl;
        }
    }

	// Operador de asignaci�n de objetos Aeropuertos
	//(Implementado on-line por el profesor)
	// Par�metros:
	//	- otro_objeto (E): otro objeto de la clase Aeropuertos
	Aeropuertos & Aeropuertos::operator=(const Aeropuertos &otro_objeto) {
		if (this != &otro_objeto) {
			n_aeropuertos = otro_objeto.n_aeropuertos;
			aeropuertos = otro_objeto.aeropuertos;
		}
		return *this;
	}

	// Devuelve un objeto aeropuerto cuyo nombre se pasa
	// como par�metro. Si el aeropuerto est� en la lista
	// de Aeropuertos, se devuelve a trav�s del par�metro
	// 'aeropuerto' y se devuelve 'OK' a trav�s de 'res'.
	// Si el aeropuerto no existe en la lista de Aeropuertos,
	// se devuelve 'NO_EXISTE' a trav�s de 'res'.
	// Par�metros;
	//	- nombre (E): nombre del aeropuerto a consultar
	//	- aeropuerto (S): objeto Aeropuerto consultado
	//	- res (S): resultado de la operaci�n.
	void Aeropuertos::consultar_aeropuerto(const std::string &nombre,
	                          Aeropuerto &aeropuerto,
	                          Resultado &res) const{
        unsigned posicion;

        posicion = buscar_aeropuerto(nombre);

        if (posicion < n_aeropuertos){ //Eso es porque lo ha encontrado

            aeropuerto = aeropuertos[posicion];
            res = OK;

        }else{

            res = NO_EXISTE;


        }
    }

	// Escribe en pantalla la informaci�n de todos los
	// aeropuertos, en el formato:
	// <nombre>, <pais>, <latitud>, <longitud>
	// Por ejemplo:
	// FUE, Spain, 28.4527, -13.8638
	// VDE, Spain, 27.8148, -17.8871
	// SPC, Spain, 28.6265, -17.7556
	// LPA, Spain, 27.9319, -15.3866
	// ACE, Spain, 28.9455, -13.6052
	// ...
	void Aeropuertos::escribir_aeropuertos() const{

        for (int i = 0; i < n_aeropuertos; i++){


            cout << aeropuertos[i].consultar_nombre() << ", " << aeropuertos[i].consultar_pais() << ", " << aeropuertos[i].consultar_latitud() << ", " << aeropuertos[i].consultar_longitud() << endl;

        }
	}

	// Devuelve el n�mero de aropuertos de la
	// lista de Aeropuetos
	unsigned Aeropuertos::num_aeropuertos() const{

        return n_aeropuertos;


	}

	// Inserta un nuevo aeropuerto en la lista de
	// Aeropuertos. Si el aeropuerto no existe en la lista
	// actual de aeropuertos, se inserta al final de �sta y
	// se devuelve 'OK' a trav�s de 'res'. Si el aeropuerto
	// ya existe en la lista, no vuelve a insertarse y se
	// devuelve 'YA_EXISTE' a trav�s de 'res'.
	// Par�metros:
	//	- aeropuerto (E): un aeropuerto a insertar
	//	- res (E): resultado de la operaci�n
	void Aeropuertos::insertar_aeropuerto(const Aeropuerto &aeropuerto,
	                         Resultado &res){

	       unsigned posicion;
	       posicion = buscar_aeropuerto(aeropuerto.consultar_nombre());

	       if (posicion == n_aeropuertos){//Sintoma de que no existe

                aeropuertos[n_aeropuertos] = aeropuerto;
                n_aeropuertos++;
                res = OK;

	       }else{

                res = YA_EXISTE;

	       }
    }

	// Modifica, en la la lista actual de Aeropuertos,
	// la informaci�n del aeropuerto que se
	// pasa como par�metro. Si el aeropuerto existe en
	// la lista actual de Aeropuertos, se modifica su
	// informaci�n, sustituy�ndola por la contenida
	// en el par�metro 'aeropuerto' (es decir, asignando
	// el objeto que se pasa como par�metro al objeto
	// correspondiente contenido en la lista) y se devuelve
	// 'OK' a trav�s de 'res'. Si el aeropuerto no existe,
	// se devuelve 'NO_EXISTE' a trav�s de 'res'.
	// Par�metros:
	//	- aeropuerto (E): aeropuerto a modificar
	//	- res (S): resultado de la operaci�n
	void Aeropuertos::modificar_aeropuerto(const Aeropuerto &aeropuerto,
	                          Resultado &res){

	    unsigned posicion;
	    posicion = buscar_aeropuerto(aeropuerto.consultar_nombre());

	    if (posicion < n_aeropuertos){//Sintoma de que existe

            aeropuertos[posicion] = aeropuerto;
            res = OK;

	    }else{

            res = NO_EXISTE;

	    }
    }

	// Elimina un aeropuerto de la lista de Aeropuertos.
	// Si el aeropuerto cuyo nombre se pasa como par�metro
	// existe en la lista, se elimina de �sta y se devuelve
	// 'OK' a trav�s de 'res'. Si no existe, se devuelve
	// 'NO_EXISTE' a trav�s de 'res'.
	// Par�metros:
	// 	- nombre (E): nombre del aeropuerto a eliminar
	// 	- res (S): resultado de la operaci�n
	void Aeropuertos::eliminar_aeropuerto(const std::string &nombre,
	                         Resultado &res){

	     unsigned posicion;
	     posicion = buscar_aeropuerto(nombre);

	     if (posicion == n_aeropuertos){//Sintoma de que no existe


            res = NO_EXISTE;

	     }else{//Existe y est� en la posici�n "posicion"

            cerrar_hueco(posicion);
            n_aeropuertos--;

	     }

    }

	// Lee de fichero una lista de aeropuertos
	// correspondiente al 'pais' que se
	// pasa como par�metro y los
	// inserta en la lista actual de Aeropuertos.
	// Si el pa�s es "cualquiera", lee todos los
	// aeropuertos del fichero.
	//
	// El formato de entrada es el siguiente:
	// <nombre>,<pais>,<latitud>,<longitud>
	// Por ejemplo (n�tese que no hay espacios de
	// sepraci�n entres los campos, solo comas):
	// GKA,Papua New Guinea,-6.081689,145.391881
	// MAG,Papua New Guinea,-5.207083,145.7887
	// HGU,Papua New Guinea,-5.826789,144.295861
	// LAE,Papua New Guinea,-6.569828,146.726242
	// POM,Papua New Guinea,-9.443383,147.22005
	// WWK,Papua New Guinea,-3.583828,143.669186
	// UAK,Greenland,61.160517,-45.425978
	// GOH,Greenland,64.190922,-51.678064
	// SFJ,Greenland,67.016969,-50.689325
	// THU,Greenland,76.531203,-68.703161
	//	...
	// Si el fichero puede abrirse para lectura correcta-
	// mente, se devuelve 'OK', a trav�s de 'res'. Si no,
	// se devuelve 'FIC_ERROR' a trav�s de 'res'.
	// Par�metros:
	// 	- fichero (E): nombre del fichero de entrada
	// 	- res (S): resultado de la operaci�n
	void Aeropuertos::obtener_aeropuertos(const std::string &fichero,
	                         const std::string &pais,
	                         Resultado &res){

	      ifstream f_ent;
	      f_ent.open(fichero);
	      string cadena;
	      double latitud, longitud;


	      if (f_ent.fail()){//Si falla

            res = FIC_ERROR;

	      }else{
	          if (pais == "cualquiera"){

                    n_aeropuertos = 0;

                    ///-----LEO EL NOMBRE DEL AEROPUERTO (POR ADELANTADO)
                    getline(f_ent, cadena, ',');
                    aeropuertos[n_aeropuertos].asignar_nombre(cadena);

                    while (!f_ent.eof() && n_aeropuertos < MAX_AEROPUERTOS){


                    ///----LEO EL PAIS-------

                    getline(f_ent, cadena, ',');
                    aeropuertos[n_aeropuertos].asignar_pais(cadena);

                    ///----LEO LATITUD-------

                    f_ent>> latitud;
                    f_ent.ignore();

                    aeropuertos[n_aeropuertos].asignar_latitud(latitud);

                    ///----LEO LONGITUD-----
                    f_ent>>longitud;
                    f_ent.ignore();

                    aeropuertos[n_aeropuertos].asignar_longitud(longitud);

                    n_aeropuertos++;

                    if (n_aeropuertos < MAX_AEROPUERTOS){

                    ///LEO EL NOMBRE DEL AEROPUERTO
                    getline(f_ent, cadena, ',');
                    aeropuertos[n_aeropuertos].asignar_nombre(cadena);
                    }

                    }
                    res = OK;


	          }else{//Si el aeropuerto que introducimos no es "cualquiera"
                    //cout << "Entra aqui " << endl;
                    n_aeropuertos = 0;

                    ///-----LEO EL NOMBRE DEL AEROPUERTO (POR ADELANTADO)
                    getline(f_ent, cadena, ',');
                    //cout << "El primer aeropuerto que se encuentra es: " << cadena << endl;
                    aeropuertos[n_aeropuertos].asignar_nombre(cadena);

                    while (!f_ent.eof() && n_aeropuertos < MAX_AEROPUERTOS){


                    ///----LEO EL PAIS-------

                    getline(f_ent, cadena, ',');
                    aeropuertos[n_aeropuertos].asignar_pais(cadena);


                    ///----LEO LATITUD-------

                    f_ent>> latitud;

                    aeropuertos[n_aeropuertos].asignar_latitud(latitud);
                    f_ent.ignore();


                    ///----LEO LONGITUD-----
                    f_ent>>longitud;


                    aeropuertos[n_aeropuertos].asignar_longitud(longitud);

                    f_ent.ignore();


                        if (pais == aeropuertos[n_aeropuertos].consultar_pais()){
                           // cout << "Es espa�ol" << endl;
                           // cout << "Aeropuerto que se mete en la posicion "<< n_aeropuertos  << " es: " <<aeropuertos[n_aeropuertos].consultar_nombre() << endl;
                            n_aeropuertos++;

                        }

                        if (n_aeropuertos < MAX_AEROPUERTOS){
                    ///LEO EL NOMBRE DEL AEROPUERTO
                    getline(f_ent, cadena, ',');
                    aeropuertos[n_aeropuertos].asignar_nombre(cadena);
                        }

                    }

                    res = OK;

	          }

	      }
            f_ent.close();
    }

	// Guarda en fichero la lista de Aeropuertos. El
	// formato de salida coincide con el de entrada
	// (v�ase la funci�n obtener_aeropuertos). Si
	// el fichero puede abrirse, se guardan en �l
	// los aeropuertos de la lista actual y se devuelve
	// 'OK' a trav�s de 'res'. Si no, se devuelve
	// 'FIC_ERROR' a trav�s de 'res'.
	// Par�metros:
	// 	- fichero (E): nombre del fichero de entrada
	// 	- res (S): resultado de la operaci�n
	void Aeropuertos::guardar_aeropuertos(const std::string &fichero,
	                         Resultado &res){

	           ofstream f_sal;
	           f_sal.open(fichero);

	           if (!f_sal.fail()){

	           for (int i = 0; i < n_aeropuertos; i++){


                        f_sal << aeropuertos[i].consultar_nombre() << "," << aeropuertos[i].consultar_pais() << "," << aeropuertos[i].consultar_latitud() << "," << aeropuertos[i].consultar_longitud() << endl;


	           }
                    res = OK;

	           }else{

                    res = FIC_ERROR;

	           }







    }

	// Operadores sobrecargados (implementados on-line por
	// el profesor).
	bool Aeropuertos::operator==(const Aeropuertos &otro_objeto) const {
		bool iguales = (n_aeropuertos == otro_objeto.n_aeropuertos);

		unsigned i = 0;

		while (iguales && i < n_aeropuertos) {
			unsigned pos = otro_objeto.buscar_aeropuerto(aeropuertos[i].consultar_nombre());
			iguales = (aeropuertos[i] == otro_objeto.aeropuertos[pos]);
			i++;
		}

		return iguales;
	}

    unsigned Aeropuertos::buscar_aeropuerto(const string &nombre) const{

		unsigned i = 0;
        while (i < n_aeropuertos && nombre != aeropuertos[i].consultar_nombre()){


           i++;

        }

        return i;

    }

    void Aeropuertos::cerrar_hueco (unsigned posicion){

        for (unsigned pos = posicion; pos < n_aeropuertos; pos++){

            aeropuertos[pos] = aeropuertos [pos+1];


        }
    }
}
