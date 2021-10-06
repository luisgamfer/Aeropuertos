#include "rutas.hpp"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

namespace bblProgII{

	// Constructor por defecto.
	// Inicializa la lista de Rutas a lista vacía
	Rutas::Rutas(){
        lista = NULL;

	}

	// Constructor de copia de Rutas.
	// Parámetros:
	//	- otro_objeto (E): objeto Rutas a copiar
	Rutas::Rutas(const Rutas &otro_objeto){

        lista = NULL; //Inicialmente hacemos que apunte a Null porque no sabemos donde apunta
        copiar_rutas(otro_objeto);


	}

	// Destructor de la clase
	Rutas::~Rutas(){

        borrar_rutas();
	}

	// Operador de asignación de Rutas
	// (Implementado on-line por el profesor)
	Rutas & Rutas::operator=(const Rutas &otro_objeto) {
		if (this != &otro_objeto) {
			borrar_rutas();
			copiar_rutas(otro_objeto);
		}

		return *this;
	}

	// Devuelve el número de rutas
	unsigned Rutas::num_rutas() const{

        Lista ptr = lista; //Puntero auxiliar que apunte a lista
        unsigned numero_rutas=0;


        while (ptr != NULL){

            numero_rutas++;
            ptr = ptr->sig;

        }

        return numero_rutas;

	}

	// Escribe por pantalla las Rutas actuales.
	// Formato de salida por pantalla:
	// <origen>, <destino>, <precio>, <duracion>, <linea_aerea>
	// Por ejemplo:
	// AER, KZN, 344, 151, Aerocondor
	// ASF, KZN, 232, 112, Aerocondor
	// ASF, MRV, 106, 84, Aerocondor
	// ...

	void Rutas::escribir_rutas() const{

        Lista ptr = lista; //Puntero que apunta a lista

        while (ptr != NULL){


            ptr->ruta.escribir_ruta();
            ptr = ptr->sig; //Avanzo el puntero
        }


	}

	// Consulta la ruta de la posición 'num' de
	// la lista de Rutas. Si num < num_rutas(),
	// devuelve la ruta correspondiente
	// y 'OK' a través de 'res'. Si no, devuelve
	// 'NO_EXISTE' a través de 'res'.
	// Parámetros:
	// 	- num (E): posición de la ruta a consultar
	//	- ruta (S): ruta de la posición 'num'
	//  - res (S): resultado de la operación
	void Rutas::consultar_ruta(unsigned num,
	                    Ruta &ruta,
	                    Resultado &res) const{

            unsigned nume_rutas = num_rutas(); //Consulto primero el numero de rutas que tiene la lista de rutas

            //Llamo al constructor por defecto

            ruta = Ruta();

            if (num < nume_rutas){

                Lista ptr = lista;//Que empiece en la lista
                unsigned posicion = 0; ///0 o 1
                while (ptr != NULL && posicion != num){

                    ptr = ptr->sig; //Deplazo el puntero
                    posicion++; //Sumo una posicion
                }

                //Saco al final la ruta donde se ha quedado el puntero
                //cout << ptr->ruta.consultar_origen() << ", " << ptr->ruta.consultar_destino() << ", " << ptr->ruta.consultar_precio() << ", " << ptr->ruta.consultar_duracion() << ", " << ptr->ruta.consultar_linea_aerea() <<endl;

               // ptr->ruta.escribir_ruta();
                ruta = ptr->ruta; ///Asigno la ruta a ptr
                res = OK;



                //ruta = Ruta();

            }else{
                res = NO_EXISTE;

            }


    }

	// Consulta las rutas con un determinado 'origen'
	// y 'destino'. Si existe/n alguna/s ruta/s con ese
	// 'origen' y 'destino' se devuelve/n a través de
	// 'rutas' y se devuelve 'OK' a través de 'res'. Si no,
	// se devuelve 'NO_EXISTE' a través de 'res'.
	// Parámetros:
	// 	- origen (E): aeropuerto de origen de la ruta
	// 	- destino (E): aeropuerto de destino de la ruta
	// 	- ruta (S): ruta encontrada
	// 	- res (S): resultado de la operación
	void Rutas::consultar_rutas(const std::string &origen,
	                     const std::string &destino,
	                     Rutas &rutas,
	                     Resultado &res) const{


	    Lista ptr = lista; //Puntero que apunte lista
        //rutas = Rutas(); ///Llamo al constructor
        rutas.borrar_rutas();

	    if (ptr != NULL){


            while (ptr != NULL){ //Puntero que me recorra todo la lista

                if (ptr->ruta.consultar_origen() == origen && ptr->ruta.consultar_destino()==destino){

                    rutas.insertar_final(ptr->ruta); //Inserto en la lista de rutas la ruta que esta apuntando el puntero
                    //res = OK;

                }
                ptr = ptr->sig; //Recorra
            }

            if (rutas.lista != NULL){

                res = OK;

            }else{

                res = NO_EXISTE;
            }



	    }
    }

	// Devuelve un objeto Rutas con la lista de rutas
	// cuyo aeropuerto de origen coincide con el que
	// se pasa como parámetro. Si existe al menos una
	// ruta con ese aeropuerto de origen, se devuelve
	// 'OK' a través de 'res'. Si no, se devuelve
	// 'NO_EXISTE' a través de 'res'.
	// Parámetros:
	//	- origen (E): aeropuerto de origen de la ruta
	// 	- rutas (S): lista de rutas con ese aeropuerto
	//				de origen.
	//	- res (S): resultado de la operación.
	void Rutas::consultar_rutas_origen(const std::string &origen,
	                            Rutas &rutas,
	                            Resultado &res) const{

	        if (lista != NULL){

                Lista ptr = lista; //Puntero auxiliar que apunte a la lista
                rutas.borrar_rutas(); //Borro las rutas que inicialmente pueda haber
                while (ptr != NULL){

                    if (ptr->ruta.consultar_origen() == origen){

                        rutas.insertar_final(ptr->ruta);//Inserto en la lista de rutas la ruta que apunta ptr
                        //res = OK;

                    }

                    ptr = ptr->sig;//Avance
                }

                if (rutas.lista != NULL){

                    res = OK;
                }else{

                    res = NO_EXISTE;
                }


	        }
    }
	// Devuelve un objeto Rutas con la lista de rutas
	// cuyo aeropuerto de destino coincide con el que
	// se pasa como parámetro. Si existe al menos una
	// ruta con ese aeropuerto de destino, se devuelve
	// 'OK' a través de 'res'. Si no, se devuelve
	// 'NO_EXISTE' a través de 'res'.
	// Parámetros:
	//	- destino (E): aeropuerto de destino de la ruta
	// 	- rutas (S): lista de rutas con ese aeropuerto
	//				de origen.
	//	- res (S): resultado de la operación.
	void Rutas::consultar_rutas_destino(const std::string &destino,
	                             Rutas &rutas,
	                             Resultado &res) const{

	     if (lista != NULL){

            Lista ptr = lista; //Puntero que apunte a lista
            rutas.borrar_rutas(); //Borro las rutas que inicialmente pueda haber
            while (ptr != NULL){

                if (ptr->ruta.consultar_destino() == destino){

                    rutas.insertar_final(ptr->ruta); //Inserto en las rutas la ruta que esta apuntando


                }

                ptr = ptr->sig;//Avanzo
            }

            if (rutas.lista != NULL){

                res = OK;

            }else{

                res = NO_EXISTE;
            }


	     }
    }

	// Consulta la lista de rutas que contienen,
	// ya sea como aeropuerto de origen o como aeropuerto de destino,
	// alguno de los 'aeropuertos' que se pasan como parámetro.
	// Si existe al menos una ruta con alguno de esos aeropuertos, se
	// devuelve 'OK' a través de 'res'. Si no, se devuelve 'NO_EXISTE'.
	// Parámetros:
	//	- aeropuertos (E): objeto Aeropuertos con la lista de aeropuertos
	//				cuyas rutas se quieren obtener.
	//	- rutas (S): lista de rutas que contienen esos aeropuertos
	//	- res (S): resultado de la operación
	// PRECONDICIÓN: aeropuertos.num_aeropuertos() > 0
	void Rutas::consultar_rutas_aeropuertos(const Aeropuertos &aeropuertos,
	                                 Rutas &rutas,
	                                 Resultado &res) const{

            rutas.lista = NULL; //Inicializo la lista de rutas
        if (aeropuertos.num_aeropuertos() >0){

            if (lista != NULL){//Si la lista de rutas no esta vacia

                Lista ptr = lista; //Puntero auxiliar que apunta a la lista

                    while (ptr != NULL){

                            Aeropuerto a;
                            Resultado res_origen, res_destino;

                            aeropuertos.consultar_aeropuerto(ptr->ruta.consultar_origen(),a,res_origen); //Consulto si aeropuerto de origen esta en el array de aeropuertos
                            aeropuertos.consultar_aeropuerto(ptr->ruta.consultar_destino(),a,res_destino); //Consulto si el aeropuerto de destino esta en el array de aeropuertos

                        if (res_origen == OK || res_destino == OK){


                            rutas.insertar_final(ptr->ruta);

                        }

                        ptr = ptr->sig;//Avance
                    }



                if (rutas.lista != NULL){

                    res = OK;
                }else{

                    res = NO_EXISTE;
                }


            }
        }
    }

	// Devuelve la ruta más barata (menor precio) del la lista de Rutas.
	// Si la lista está vacía, devuelve 'NO_EXISTE' a través
	// de 'RES'. Si no, devuelve OK.
	// Parámetros:
	//	- ruta (S): ruta más barata de la lista
	// 	- res (S: resultado de la operación
	void Rutas::consultar_mas_barata(Ruta &ruta, Resultado &res) const{

            if (lista != NULL){ //Si la lista no esta vacia

            Lista ptr = lista; //Puntero inicial lista;
            double mas_barata = ptr->ruta.consultar_precio(); //La mas barata al principio va a ser la primera;
            Lista ptr_barata = lista; //Inicialmente apunta a lista

            while (ptr != NULL){//Recorra toda la lista

                if (ptr->ruta.consultar_precio() < mas_barata){

                    mas_barata = ptr->ruta.consultar_precio();
                    ptr_barata = ptr; //El puntero de mas barata apunta a ptr;

                }

                ptr = ptr->sig; //Avance
            }

                ruta = ptr_barata->ruta;//La ruta del parametro es la ruta que apunta el ptr_barata;
                res = OK;

            }else{//Si la lista esta vacia

                res = NO_EXISTE;

            }
    }

	// Insertar nueva ruta al final de la lista de Rutas.
	// Si la ruta no existe (es decir, no hay una ruta
	// en la lista con los mismos atributos que ésta),
	// se inserta al final de la lista y se devuelve 'OK'
	// a través de 'res'. Si la ruta existe (hay una ruta
	// con los mismos aeropuertos de origen y destino), se
	// devuelve 'YA_EXISTE' a través de 'res'.
	// Parámetros:
	//	- ruta (E): ruta a insertar en la lista de Rutas.
	//	- res (S): resultado de la operación
	void Rutas::insertar_ruta(const Ruta &ruta, Resultado &res){


            Lista ptr = buscar_ruta(ruta);

            if (lista != NULL){//Lista no esta vacia

                if (ptr != NULL){//Existe la ruta

                    res = YA_EXISTE;


                }else{

                    insertar_final(ruta);
                    res = OK;

                }

            }else{//Si esta vacia

                insertar_final(ruta); //La inserto igual
            }



            }

	// Elimina la ruta que se pasa como parámetro de la
	// lista de Rutas.
	// Si la ruta existe, se elimina de la lista de Rutas
	// y se devuelve 'OK' a través de 'res'. Si no, se
	// devuelve 'NO_EXISTE' a través de 'res'.
	// Parámetros:
	//	- origen (E): aeropuerto de origen de la ruta
	//	- destino (E): aeropuerto de destino de la ruta
	//	- res (S): resultado de la operación
	void Rutas::eliminar_ruta(const Ruta &ruta,
	                   Resultado &res){

            res = NO_EXISTE;
	       if (lista != NULL){

	          if (lista->ruta == ruta){//Eliminamos el primer nodo

                Lista ptr = lista;
                lista = ptr->sig; //Apuntara a NULL
                delete ptr;
                res = OK;



	          }else{//Eliminamos nodo intermedio o ultimo

                Lista anterior, actual;
                anterior = lista;
                actual = anterior->sig;

                    while (actual != NULL && !(actual->ruta == ruta)){


                        anterior = actual;//Desplazo los punteros
                        actual = actual->sig;
                    }

                    if (actual != NULL){//Si no se ha salido por llegar al final

                        anterior ->sig = actual ->sig;
                        delete actual;
                        res = OK;

                    }

	          }
	       }
    }

	// Elimina todas las rutas de la lista de Rutas que
	// contengan ese aeropuerto como aeropuerto de origen
	// o destino de la ruta. Si se ha eliminado al menos
	// una ruta con ese aeropuerto, se devuelve 'OK' a
	// través de 'res'. Si no, se devuelve 'NO_EXISTE'.
	// Parámetros:
	//	- aeropuerto (E): aeropuerto cuyas rutas se eliminan
	//	- res (S): resultado de la operación
	void Rutas::eliminar_rutas_aeropuerto(const std::string aeropuerto,
	                               Resultado &res){

            res = NO_EXISTE;
	        if (lista != NULL){//Si la lista no esta vacia


                    Lista ptr = lista;

                    while (ptr != NULL){

                        if (ptr->ruta.consultar_origen()==aeropuerto || ptr->ruta.consultar_destino() == aeropuerto){

                            eliminar_ruta(ptr->ruta, res); //Le paso el puntero que apunta a la ruta que quiero borrar
                            res = OK;

                        }


                        ptr = ptr->sig;
                    }
            }

    }

	// Elimina todas las rutas que contienen como 'origen'
	// el aeropuerto cuyo nombre se pasa como parámetro.
	// Si se ha eliminado al menos una ruta con ese aeropuerto
	// de origen, se devuelve 'OK' a través de 'res'. Si no,
	// se devuelve 'NO_EXISTE' a través de 'res'.
	// Parámetros:
	//	- origen (E): aeropuerto de origen de las rutas a
	//			eliminar.
	//	- res (S): resultado de la operación.
	void Rutas::eliminar_rutas_origen(const std::string &origen,
	                           Resultado &res){

                res = NO_EXISTE;

                if (lista != NULL){//Si la lista no esta vacia

                            Lista ptr = lista; //Puntero auxiliar que me recorra la lista

                            while (ptr != NULL){


                                if (ptr->ruta.consultar_origen() == origen){


                                    eliminar_ruta(ptr->ruta,res);
                                    res = OK;

                                }


                                ptr = ptr->sig;
                            }
                }


    }

	// Elimina todas las rutas que contienen como 'destino'
	// el aeropuerto cuyo nombre se pasa como parámetro.
	// Si se ha eliminado al menos una ruta con ese aeropuerto
	// de destino, se devuelve 'OK' a través de 'res'. Si no,
	// se devuelve 'NO_EXISTE' a través de 'res'.
	// Parámetros:
	//	- destino (E): aeropuerto de destino de las rutas a
	//			eliminar.
	//	- res (S): resultado de la operación.
	void Rutas::eliminar_rutas_destino(const std::string &destino,
	                            Resultado &res){

	            res = NO_EXISTE;

                        Lista ptr = lista; //Puntero auxiliar que apunte a lista
                    if (lista != NULL){
                        while (ptr != NULL){

                            if (ptr->ruta.consultar_destino() == destino){

                                eliminar_ruta(ptr->ruta, res);
                                res = OK;

                            }

                            ptr = ptr->sig;
                        }
                    }
    }

	// Lee de 'fichero' la lista de rutas correspondientes
	// a los 'aeropuertos' que se pasan como parámetro y
	// las inserta al final de la lista de rutas actual.
	// Si la lista de 'aeropuertos' es vacía, lee todas
	// las rutas del fichero y las inserta en la lista
	// de Rutas actual. Si el fichero ha podido abrirse
	// correctamente para lectura, devuelve 'OK' a través
	// de 'res'. Si no, devuelve 'FIC_ERROR'.
	//
	// El formato de fichero de entrada es el siguiente:
	// <origen>,<destino>,<precio>,<duracion>,<linea_aerea>
	// Por ejemplo:
	// AER,KZN,344,151,Aerocondor
	// ASF,KZN,232,112,Aerocondor
	// ASF,MRV,106,84,Aerocondor
	// ...
	// (obsérvese que no hay espacios tras los campos)
	//
	// Parámetros:
	//	- fichero (E): nombre del fichero de lectura.
	// 	- aeropuertos (E): objeto de tipo Aeropuertos con la
	//			lista de aeropuertos para los que obtener rutas.
	//	- res (S): resultado de la operación.
	void Rutas::obtener_rutas(const std::string &fichero,
	                   const Aeropuertos &aeropuertos,
	                   Resultado &res){

        ifstream f_ent;
        f_ent.open(fichero);
        string origen,destino,linea_aerea;
        double precio;
        unsigned duracion;
        Resultado res_insert, res_origen, res_destino;
        Aeropuerto a; //Aeropuerto auxiliar que me va a ayudar

        if (f_ent.fail()){

            res = FIC_ERROR;

        }else{//Si se ha abierto correctamente

            res = OK;

            if (aeropuertos.num_aeropuertos() == 0){//Si la lista de aeropuertos esta vacia

                            ///LEO ORIGEN POR ADELANTADO
                           getline(f_ent, origen,',');

                    while (!f_ent.eof()){//Mientras que no sea fin de fichero

                           ///LEO DESTINO
                           getline(f_ent,destino,',');

                           ///LEO PRECIO
                           //getline(f_ent,precio,',');
                           f_ent >> precio;
                           f_ent.ignore();

                           ///LEO DURACION
                           //getline(f_ent,duracion,',');
                           f_ent >> duracion;
                           f_ent.ignore();
                           ///LEO LINEA AEREA
                           getline(f_ent,linea_aerea,'\n');

                           insertar_ruta(Ruta(origen,destino,precio,duracion,linea_aerea), res_insert); //Inserto el aeropuerto


                            //Leo el siguiente
                            ///LEO ORIGEN
                           getline(f_ent, origen,',');
                    }



            }else{//Si la lista de aeropuertos no esta vacia

                            ///LEO ORIGEN POR ADELANTADO
                           getline(f_ent, origen,',');

                    while (!f_ent.eof()){//Mientras que no sea fin de fichero

                           ///LEO DESTINO
                           getline(f_ent,destino,',');

                           ///LEO PRECIO
                           //getline(f_ent,precio,',');
                           f_ent >> precio;
                           f_ent.ignore();

                           ///LEO DURACION
                           //getline(f_ent,duracion,',');
                           f_ent >> duracion;
                           f_ent.ignore();


                           ///LEO LINEA AEREA
                           getline(f_ent,linea_aerea,'\n');

                           aeropuertos.consultar_aeropuerto(origen,a, res_origen);//Busco en el array de aeropuertos si estan el origen y el destino leidos
                           aeropuertos.consultar_aeropuerto(destino,a,res_destino);

                           if (res_origen == OK && res_destino == OK){//Es decir, tanto el aeropuerto de origen como el de destino existe

                                insertar_ruta(Ruta(origen,destino,precio,duracion,linea_aerea), res_insert); //Lo inserto


                           }

                            //Leo el siguiente
                            ///LEO ORIGEN
                           getline(f_ent, origen,',');
                    }
            }
        }

        f_ent.close(); //Cierro el fichero
    }

	// Guarda en fichero todas las Rutas. El formato
	// de salida coincide con el de entrada (véase
	// la función miembro obtener_rutas). Si el fichero
	// puede abrirse correctamente para escritura,
	// se guardan en él las rutas y se devuelve 'OK' a
	// través de 'res'. Si no, se devuelve 'FIC_ERROR'.
	// Parámetros:
	//	- fichero (E): nombre del fichero de salida
	// 	- res (S): resultado de la operación.
	void Rutas::guardar_rutas(const std::string &fichero,
	                   Resultado &res) const{

	        ofstream f_sal;
	        f_sal.open(fichero);

	        if (f_sal.fail()){

                res = FIC_ERROR;

	        }else{

                Lista ptr = lista;

                while (ptr != NULL){


                    f_sal << ptr->ruta.consultar_origen()<< "," << ptr->ruta.consultar_destino() << "," << ptr->ruta.consultar_precio() << "," << ptr->ruta.consultar_duracion() << "," << ptr->ruta.consultar_linea_aerea() << endl;

                    ptr = ptr->sig;
                }

                    res = OK;

	        }
                f_sal.close();

    }

	// Guarda todas las rutas en el `fichero` cuyo nombre
	// se pasa como parámetro de entrada. (El formato
	// de salida está destinado a generar los billetes
	// correspondientes a un itinerario con escalas
	// entre un aeropuerto de origen--el origen de la
	// primera ruta--y otro de destino--el destino de
	// la última ruta.)
	// Finalmente, escribe en el fichero la suma de los
	// costes totales de todas las rutas que se han
	// escrito en él, el número de rutas - 1 (es
	// decir, las escalas que hay que hacer entre
	// el primer aeropuerto y el último) y la duración
	// total de todos los vuelos.
	//
	// Formato de salida:
	// (ojo, incluye los tres guiones antes y después)
	//
	// ---
	// Flight: <origen> to <destino>
	// Carrier: <linea_aerea>
	// Duration: <duracion> minutes
	// Cost: <precio> euros
	// ---
	// .. (se repite tantas veces como rutas haya)
	// ---
	// Total Cost: <precio total> euros
	// ---
	// Number of Stops: <numero rutas - 1>
	// ---
	// Total Flight Duration: <duracion> minutes
	// ---
	//
	// Si no se puede abrir el fichero, se devuelve
	// `FIC_ERROR` a través de `res`. Si no, se
	// devuelve `Ok`.
	// Parámetros:
	//		- fichero (E): nombre del fichero de salida
	//		- res (S): resultado de la operación
	void Rutas::guardar_billetes(const std::string &fichero,
	                      Resultado &res){

            ofstream f_sal;
            f_sal.open(fichero);

            if (f_sal.fail()){

                res = FIC_ERROR;

            }else{

                Lista ptr = lista;
                double sum_precio = 0;
                unsigned numero_rutas = num_rutas();
                unsigned duracion = 0;
                while (ptr != NULL){

                    f_sal << "---"<< endl;
                    f_sal << "Flight: " << ptr->ruta.consultar_origen() << " to " << ptr->ruta.consultar_destino() << endl;
                    f_sal << "Carrier: " << ptr->ruta.consultar_linea_aerea() << endl;
                    f_sal << "Duration: " << ptr->ruta.consultar_duracion() << " minutes" << endl;
                    f_sal << "Cost: " << ptr->ruta.consultar_precio() << " euros" << endl;
                    f_sal << "---" << endl;

                    sum_precio += ptr->ruta.consultar_precio();
                    duracion += ptr->ruta.consultar_duracion();

                    ptr = ptr->sig;//Avance
                }

                    f_sal << "Total cost: " << sum_precio << " euros" << endl;
                    f_sal << "---" << endl;
                    f_sal << "Number of Stops: " << numero_rutas -1 << endl;
                    f_sal << "---" << endl;
                    f_sal << "Total flight duration: " << duracion << " minutes" << endl;
                    f_sal << "---" << endl;

                    res = OK;
            }

            f_sal.close();
    }

	// (EJERCICIO DE INVESTIGACIÓN)
	//
	// -- OPCIÓN A - FÁCIL (Y MÍNIMA EXIGIDA)
	// Dado un aeropuerto de 'origen ' y un aeropuerto
	// de 'destino', devuelve la ruta más barata de entre
	// las diferentes rutas existentes entre esos dos
	// aeropuertos. Si existe una ruta entre esos dos
	// aeropuertos, se devuelve insertada en 'itinerario'
	// (como única ruta de la lista) y 'OK' a través de
	// 'res'. Si no existe, se devuelve un 'itinerario'
	// vacío y 'NO_EXISTE' a través de 'res'.
	// --------------------------------------------------
	//
	// ---OPCIÓN B - DIFÍCIL (Y MUCHO MEJOR Y OPCIONAL)
	// Obtener itinerario.
	// Dado un aeropuerto de 'origen' y un aeropuerto
	// de 'destino', devuelve la lista de rutas para llegar,
	// haciendo escalas si es necesario, desde el aeropuerto de 'origen'
	// al aeropuerto de 'destino'. Para ello, se deberá emplear
	// el algoritmo de Dijkstra para calcular, si existe,
	// el itinerario DE MENOR PRECIO entre el aeropuerto de 'origen' y el de
	// 'destino', haciendo escalas, si es preciso, en diferentes aeropuertos.
	// (https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm#Algorithm)
	// Si existe el itinerario, ya sea de una sola ruta (sin escalas entre
	// aeropuertos) o de varias rutas (con escalas entre aeropuertos),
	// se devuelve en el parámetro 'rutas' y se devuelve 'OK' a través
	// de 'res'. Si no existe el itinerario, se devuelve 'NO_EXISTE'
	// a través de 'res'.
	//
	// Parámetros:
	//	- origen (E): aeropuerto de origen
	//	- destino (E): aeropuerto de destino
	//	- rutas (S): itinerario (rutas) entre origen y destino
	// 	- res (S): resultado de la operación
	void Rutas::obtener_itinerario(const std::string &origen,
	                        const std::string &destino,
	                        Rutas &itinerario,
	                        Resultado &res) const{

	///METODO 1
	//Rutas rutas; //Lista de rutas auxiliar que va a contener todas las rutas del origen y del destino
    Rutas rutas = Rutas();
	rutas.lista = NULL; //Inicializo
    Resultado res1;
	Lista ptr_aux = lista;


	while (ptr_aux != NULL){

        if (ptr_aux->ruta.consultar_origen() == origen && ptr_aux->ruta.consultar_destino() == destino){

            rutas.insertar_ruta(ptr_aux->ruta,res1); //Si existe la ruta de origen y destino que yo quiero la inserta

        }

        ptr_aux = ptr_aux->sig; //Avanzo
	}

	if (rutas.lista != NULL){//Si minimo se ha insertado una

            Lista ptr = rutas.lista; //Puntero auxiliar que apunte a la lista de rutas que tienen origen y destino
            Lista ptr_barato = ptr; //Puntero auxiliar que me va a decir donde esta la mas barata al principio apunta al primero

            res = OK; //Si minimo se ha insertado una ruta es porque ya hay alguna barata

            while (ptr != NULL){


                if (ptr->sig != NULL && (ptr->sig->ruta.consultar_precio() < ptr->ruta.consultar_precio())){

                    ptr_barato = ptr->sig;


                }

                ptr = ptr->sig;

            }

        itinerario.lista=ptr_barato;
        itinerario.lista->sig = NULL;

    }else{ //Si no se ha insertado en "rutas" ninguna ruta es porque no va a haber ninguna ruta barata

            res = NO_EXISTE;
        }


}


	// Operadores sobrecargados.
	// Operador de comparación de igualdad (==).
	// (Implementado on-line por el profesor)
	bool Rutas::operator==(const Rutas &otro_objeto) {
		bool iguales = (num_rutas() == otro_objeto.num_rutas());
		Lista ptr1 = lista, ptr2 = otro_objeto.lista;

		while (iguales && ptr1 != nullptr && ptr1->ruta == ptr2->ruta) {
			ptr1 = ptr1->sig;
			ptr2 = ptr2->sig;
		}

		return iguales;
	}



	// Borra todas las rutas de la lista de Rutas
	// Postcondición: lista == nullptr
	void Rutas::borrar_rutas(){

	    Lista ptr;
	    while (lista != NULL){

            ptr = lista;
            lista = lista->sig;
            delete ptr;

	    }

	}

	// Copia la lista de rutas del objeto que se pasa como parámetro
	// al final de la lista de rutas actual
	void Rutas::copiar_rutas(const Rutas &otro_objeto){


        Lista ptr=lista; //Declaro un ptr auxiliar

        while (ptr->sig != NULL){

            ptr = ptr->sig;

        }

        ptr->sig = otro_objeto.lista; //Anexa el final de la lista original con el principio de la que se pasa como parametro


	}


		void Rutas::insertar_final(const Ruta &ruta){

                Lista ptr = new Nodo;
                ptr->ruta = ruta;
                ptr->sig = NULL;

                if (lista == NULL){//Si no tiene nodos

                    lista = ptr;


                }else{

                    Lista actual = lista;

                    while (actual->sig != NULL){

                        actual = actual->sig;

                    }

                    actual->sig = ptr;

                }
		}


		Rutas::Lista Rutas::buscar_ruta(const Ruta &ruta)const{ //SI LO HA ENCONTRADO DEVOLVERA UN PUNTERO APUNTANDO AL NODO Y SI NO DEVOLVERA NULL

            Lista ptr = lista; //Puntero inicial que apunta a lista


            while (ptr != NULL && !(ptr->ruta == ruta)){


                ptr = ptr->sig;


            }

            return ptr;

		}
}
