#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <fstream>
#include <string>
#include <iostream>

/**
 * Abre un archivo de salida con el nombre especificado
 * 
 * @param archivo Referencia al objeto ofstream que se abrirá
 * @param nombre_archivo Nombre del archivo a abrir
 * @return true si el archivo se abrió correctamente, false en caso contrario
 */
inline bool abrir_archivo(std::ofstream& archivo, const std::string& nombre_archivo) {
    archivo.open(nombre_archivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << nombre_archivo << std::endl;
        return false;
    }
    return true;
}

#endif // UTILIDADES_H