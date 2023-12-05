#include "SistemaBicing.hh"

void SistemaBicing::anadirBicicleta(const string& idBici, const string& idEstacion) {
    // Verificar si la bicicleta ya existe
    if (bicicletas.find(idBici) != bicicletas.end()) {
        cout << "error: la bici ya existe" << endl;
        return;
    }

    // Verificar si la estación existe
    auto estacion = estaciones.find(idEstacion);
    
    if (estacion == estaciones.end()) {
        cout << "error: la estacion no existe" << endl;
        return;
    }

    // Verificar si hay espacio en la estación para la nueva bicicleta
    if (estacion->second->getBicicletas().size() >= estacion->second->getCapacidad()) {
        cout << "error: la bici no cabe" << endl;
        return;
    }

    // Añadir la bicicleta a la estación y al sistema
    Bicicleta* nuevaBici = new Bicicleta(idBici);
    bicicletas[idBici] = nuevaBici;
    
    
    estacion->second->anadirBicicleta(nuevaBici);
}


void SistemaBicing::eliminarBicicleta(const string& idBici) {
    // Verificar si la bicicleta existe en el sistema
    auto itBici = bicicletas.find(idBici);
    if (itBici == bicicletas.end()) {
        cout << "error: la bici no existe" << endl;
        return;
    }

    // Si la bicicleta existe, obtener la estación donde está ubicada
    string estacionBici = obtenerEstacionDeBicicleta(idBici);
    if (!estacionBici.empty()) {
        // Suponiendo que Estacion tiene un método para quitar bicicletas
        estaciones[estacionBici]->quitarBicicleta(itBici->second);
    }

    // Eliminar la bicicleta del sistema y liberar la memoria
    delete itBici->second;
    bicicletas.erase(itBici);
}

void SistemaBicing::moverBicicleta(const string& idBici, const string& idEstacionDestino) {
    // Verificar si la bicicleta existe en el sistema
    auto itBici = bicicletas.find(idBici);
    if (itBici == bicicletas.end()) {
        cout << "error: la bici no existe" << endl;
        return;
    }

    // Verificar si la estación de destino existe
    auto itEstacionDestino = estaciones.find(idEstacionDestino);
    if (itEstacionDestino == estaciones.end()) {
        cout << "error: la estacion no existe" << endl;
        return;
    }
    // Verificar si hay espacio en la estación de destino
    if (itEstacionDestino->second->getBicicletas().size() >= itEstacionDestino->second->getCapacidad()) {
        cout << "error: la bici no cabe" << endl;
        return;
    }
    // Obtener la estación de origen de la bicicleta
    string estacionOrigen = obtenerEstacionDeBicicleta(idBici);
    if (estacionOrigen.empty() || estacionOrigen == idEstacionDestino) {
        cout << "error: la bici ya esta en el sitio" << endl;
        return;
    }



    // Mover la bicicleta de la estación de origen a la de destino
    estaciones[estacionOrigen]->quitarBicicleta(itBici->second);
   
    itEstacionDestino->second->anadirBicicleta(itBici->second);
    itBici->second->agregarViaje(estacionOrigen);
    itBici->second->agregarViaje(idEstacionDestino); 
}


vector<string> SistemaBicing::listarBicicletasEnEstacion(const string& idEstacion) {
    vector<string> listaBicicletas;
    if (estaciones.find(idEstacion) != estaciones.end()) {
        for (const auto& par : estaciones[idEstacion]->getBicicletas()) {
            listaBicicletas.push_back(par.first);
        }
    }
    return listaBicicletas;
}

void SistemaBicing::modificarCapacidadEstacion(const string& idEstacion, int nuevaCapacidad) {
    // Verificar si la estación existe
    auto itEstacion = estaciones.find(idEstacion);
    if (itEstacion == estaciones.end()) {
        cout << "error: la estacion no existe" << endl;
        return;
    }

    // Verificar si la nueva capacidad es menor que la cantidad actual de bicicletas en la estación
    if (itEstacion->second->getBicicletas().size() > nuevaCapacidad) {
        cout << "error: capacidad insuficiente" << endl;
        return;
    }

    // Establecer la nueva capacidad
    itEstacion->second->setCapacidad(nuevaCapacidad);
}


int SistemaBicing::calcularPlazasLibres() const {
    int totalPlazasLibres = 0;
    for (const auto& par : estaciones) {
        totalPlazasLibres += par.second->getCapacidad() - par.second->getBicicletas().size();
    }
    return totalPlazasLibres;
}

// Continuación de la implementación de la clase SistemaBicing

vector<string> SistemaBicing::obtenerBicicletasEnEstacion(const string& idEstacion) {
    vector<string> idsBicicletas;

    // Verificar si la estación existe en el sistema
    auto itEstacion = estaciones.find(idEstacion);
    if (itEstacion == estaciones.end()) {
        cout << "error: la estacion no existe" << endl;
        return idsBicicletas; // Retorna un vector vacío
    }

    // Si la estación existe, obtener las bicicletas en esa estación
    auto bicicletasEnEstacion = itEstacion->second->getBicicletas();
    for (const auto& bici : bicicletasEnEstacion) {
        idsBicicletas.push_back(bici.first);
    }

    return idsBicicletas;
}

int SistemaBicing::obtenerPlazasLibres() const {
    int totalPlazasLibres = 0;
    for (const auto& estacion : estaciones) {
        int capacidad = estacion.second->getCapacidad();
        int bicisEnEstacion = estacion.second->getBicicletas().size();
        totalPlazasLibres += capacidad - bicisEnEstacion;
    }
    return totalPlazasLibres;
}

void SistemaBicing::subirBicicletas() {
    // Identificar estaciones con exceso y falta de bicicletas
    vector<string> estacionesConExceso, estacionesConEspacio;
    for (const auto& estacion : estaciones) {
        int capacidad = estacion.second->getCapacidad();
        int cantidadBicis = estacion.second->getBicicletas().size();
        if (cantidadBicis > capacidad / 2) {
            estacionesConExceso.push_back(estacion.first);
        } else if (cantidadBicis < capacidad / 2) {
            estacionesConEspacio.push_back(estacion.first);
        }
    }

    // Mover bicicletas de estaciones con exceso a estaciones con espacio
    for (const auto& idEstacionConExceso : estacionesConExceso) {
        auto& bicisEnEstacionExceso = estaciones[idEstacionConExceso]->getBicicletas();
        for (const auto& idBici : bicisEnEstacionExceso) {
            for (const auto& idEstacionConEspacio : estacionesConEspacio) {
                if (estaciones[idEstacionConEspacio]->getBicicletas().size() < estaciones[idEstacionConEspacio]->getCapacidad()) {
                    moverBicicleta(idBici.first, idEstacionConEspacio);
                    break; // Rompe el bucle después de mover una bicicleta
                }
            }
        }
    }
}


string SistemaBicing::asignarEstacionABicicleta(const string& idBici) {
    // Implementación específica para asignar una estación a una bicicleta
    // Ejemplo simple: encontrar la primera estación con espacio disponible
    for (const auto& estacion : estaciones) {
        if (estacion.second->getCapacidad() > estacion.second->getBicicletas().size()) {
            estaciones[estacion.first]->anadirBicicleta(new Bicicleta(idBici));
            bicicletas[idBici] = new Bicicleta(idBici);
            return estacion.first;
        }
    }
    return "";
}
string SistemaBicing::obtenerEstacionDeBicicleta(const string& idBici) {
    // Primero verificar si la bicicleta existe en el sistema
    if (bicicletas.find(idBici) == bicicletas.end()) {
        return "error: la bici no existe"; // Retorna un error si la bicicleta no existe
    }

    // Recorrer todas las estaciones buscando la bicicleta
    for (const auto& estacion : estaciones) {
        const auto& bicisEnEstacion = estacion.second->getBicicletas();
        if (bicisEnEstacion.find(idBici) != bicisEnEstacion.end()) {
            return estacion.first; // Retorna el identificador de la estación donde se encontró la bicicleta
        }
    }

    return ""; // Retorna un string vacío si la bicicleta no se encuentra en ninguna estación
}


vector<string> SistemaBicing::obtenerViajesBicicleta(const string& idBici) {
    // Implementación de ejemplo
    if (bicicletas.find(idBici) == bicicletas.end()) {
        cout << "error: la bici no existe" << endl; // Retorna si la bicicleta no existe
        return vector<string>();
    }
  
    return bicicletas[idBici]->getViajes();
    
   
}

void SistemaBicing::anadirEstacion(const string& idEstacion, int capacidad) {
    if (estaciones.find(idEstacion) == estaciones.end()) {
        estaciones[idEstacion] = new Estacion(idEstacion, capacidad);
    } else {
        return;
    }
}

// Final de la implementación de la clase SistemaBicing

