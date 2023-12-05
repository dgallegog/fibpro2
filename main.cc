#include "SistemaBicing.hh"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>  

bool isCommand(string comando) {
    if (comando == "alta_bici" || comando == "ab" || comando == "baja_bici" || comando == "bb" || comando == "estacion_bici" || comando == "eb" ||comando == "viajes_bici" || comando == "vb" || comando == "mover_bici" || comando == "mb" || comando == "bicis_estacion" || comando == "be" || comando == "modificar_capacidad" || comando == "mc" || comando == "plazas_libres" || comando == "pl" || comando == "subir_bicis" || comando == "sb" || comando == "asignar_estacion" || comando == "ae") {
        return true;
    }
    return false;
}
int main() {
    SistemaBicing bicing;
    string idEstacion;
    int capacidad;
    string linea;
    string comando;
    while (getline(cin, linea)) {
        if (linea == "#") {
            continue; // Ignorar las líneas con solo '#'
        }
        if (isCommand(linea)) {
            comando = linea;
            break; // Ignorar las líneas con solo '#'
        }
        stringstream ss(linea);
        string idEstacion;
        int capacidad;

        ss >> idEstacion >> capacidad;
        if (!idEstacion.empty() && ss) {
            bicing.anadirEstacion(idEstacion, capacidad);
        }
    }
    
    
    do  {
        if (comando == "alta_bici" || comando == "ab") {
            string idBici, idEstacion;
            cin >> idBici >> idEstacion;
            cout << "#" << "ab" << " " << idBici << " " << idEstacion << endl; 
           
            bicing.anadirBicicleta(idBici, idEstacion);
            
        } else if (comando == "baja_bici" || comando == "bb") {
            string idBici;
            cin >> idBici;
            cout << "#" << "bb" << " " << idBici << endl; 
            bicing.eliminarBicicleta(idBici);
        } else if (comando == "estacion_bici" || comando == "eb") {
            string idBici;
            cin >> idBici;
            cout << "#" << "eb" << " " << idBici << endl;
            cout << bicing.obtenerEstacionDeBicicleta(idBici) << endl;
        } else if (comando == "viajes_bici" || comando == "vb") {
            string idBici;
            cin >> idBici;
            cout << "#" << "vb" << " " << idBici << endl;
            vector<string> viajes = bicing.obtenerViajesBicicleta(idBici);
            bool ex = false;
            for (const auto& viaje : viajes) {
                if (ex) cout << " ";
                cout << viaje;
                ex = true;
            }
            if (ex) cout << endl;
        } else if (comando == "mover_bici" || comando == "mb") {
            string idBici, idEstacion;
            cin >> idBici >> idEstacion;
            cout << "#" << "mb" << " " << idBici << " " << idEstacion << endl; 
            bicing.moverBicicleta(idBici, idEstacion);
        } else if (comando == "bicis_estacion" || comando == "be") {
            string idEstacion;
            cin >> idEstacion;
            cout << "#" << "be" << " " << idEstacion << endl; 
            vector<string> bicis = bicing.obtenerBicicletasEnEstacion(idEstacion);
            for (const auto& bici : bicis) {
                cout << bici << endl;
            }
        } else if (comando == "modificar_capacidad" || comando == "mc") {
            string idEstacion;
            int nuevaCapacidad;
            cin >> idEstacion >> nuevaCapacidad;
            cout << "#" << "mc" << " " << idEstacion << " " << nuevaCapacidad << endl; 
            bicing.modificarCapacidadEstacion(idEstacion, nuevaCapacidad);
        } else if (comando == "plazas_libres" || comando == "pl") { 
            cout << "#" << "pl" << endl; 
            cout << bicing.obtenerPlazasLibres() << endl;
        } else if (comando == "subir_bicis" || comando == "sb") {
            cout << "#" << "sb" << endl; 
            bicing.subirBicicletas();
        } else if (comando == "asignar_estacion" || comando == "ae") {
            string idBici;
            cin >> idBici;
            cout << "#" << "ae" << " " << idBici << endl; 
            cout << bicing.asignarEstacionABicicleta(idBici) << endl;
        } else if (comando == "fin") {
            break;
        } 
    } while (cin >> comando);

    return 0;
}
