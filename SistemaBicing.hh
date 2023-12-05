#ifndef SISTEMABICING_HH
#define SISTEMABICING_HH

#include <map>
#include <iostream>
#include <vector>
#include "Estacion.hh"
#include "Bicicleta.hh"
using namespace std;

class SistemaBicing {
    map<string, Estacion*> estaciones;
    map<string, Bicicleta*> bicicletas;

public:
    // Añade una nueva bicicleta al sistema
    // Pre: idBici e idEstacion son strings válidos y la estación existe en el sistema
    // Post: La bicicleta se añade al sistema y a la estación especificada
    void anadirBicicleta(const string& idBici, const string& idEstacion);

    // Elimina una bicicleta del sistema
    // Pre: idBici es un string válido y la bicicleta existe en el sistema
    // Post: La bicicleta se elimina del sistema y de la estación donde estaba
    void eliminarBicicleta(const string& idBici);

    // Obtiene la estación donde se encuentra una bicicleta
    // Pre: idBici es un string válido y la bicicleta existe en el sistema
    // Post: Retorna el identificador de la estación donde está la bicicleta
    string obtenerEstacionDeBicicleta(const string& idBici);

    // Obtiene los viajes realizados por una bicicleta
    // Pre: idBici es un string válido y la bicicleta existe en el sistema
    // Post: Retorna una lista de identificadores de estaciones visitadas por la bicicleta
    vector<string> obtenerViajesBicicleta(const string& idBici);

        // Continuación de la clase SistemaBicing

    // Mueve una bicicleta de su estación actual a otra
    // Pre: idBici e idEstacionDestino son strings válidos, la bicicleta y ambas estaciones existen en el sistema
    // Post: La bicicleta se mueve a la estación de destino
    void moverBicicleta(const string& idBici, const string& idEstacionDestino);

    // Lista las bicicletas presentes en una estación específica
    // Pre: idEstacion es un string válido y la estación existe en el sistema
    // Post: Retorna una lista de identificadores de bicicletas en la estación especificada
    vector<string> listarBicicletasEnEstacion(const string& idEstacion);

    // Modifica la capacidad de una estación específica
    // Pre: idEstacion es un string válido, la estación existe en el sistema y la nueva capacidad es válida
    // Post: Cambia la capacidad de la estación a la nueva capacidad especificada
    void modificarCapacidadEstacion(const string& idEstacion, int nuevaCapacidad);

    // Calcula el total de plazas libres en todas las estaciones del sistema
    // Pre: -
    // Post: Retorna el total de plazas libres en el sistema
    int calcularPlazasLibres() const;

    // Sube bicicletas hacia la primera estación
    // Pre: -
    // Post: Realiza la operación de subir bicicletas según la lógica del sistema
    void subirBicicletas();

    // Asigna una estación a una bicicleta según los criterios del sistema
    // Pre: idBici es un string válido y la bicicleta no existe en el sistema
    // Post: La bicicleta se asigna a una estación y se retorna el identificador de esa estación
    string asignarEstacionABicicleta(const string& idBici);
    
    // Obtiene las bicicletas presentes en una estación específica
    // Pre: idEstacion es un string válido y la estación existe en el sistema
    // Post: Retorna una lista de identificadores de bicicletas en la estación especificada
    vector<string> obtenerBicicletasEnEstacion(const string& idEstacion);

    // Añade una estacion de tamaño especificado
    // Pre: idEstacion es un string válido y la estación no existe en el sistema
    // Post: Se añade estacion
    void anadirEstacion(const string& idEstacion, int capacidad);




    // Calcula el total de plazas libres en todas las estaciones del sistema
    // Pre: -
    // Post: Retorna el total de plazas libres en todas las estaciones del sistema
    int obtenerPlazasLibres() const;
};

#endif // SISTEMABICING_HH


