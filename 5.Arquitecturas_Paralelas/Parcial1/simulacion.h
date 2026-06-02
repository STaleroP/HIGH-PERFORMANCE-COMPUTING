
#ifndef SIMULACION_H
#define SIMULACION_H

#include <string>
#include <fstream>
#include <cmath>
#include <iostream>
#include "utilidades.h"

/**
 * Simula un oscilador armónico amortiguado forzado usando el método de Euler-Cromer
 * 
 * @param nombre_archivo Nombre del archivo donde se guardarán los resultados
 * @param masa Masa del oscilador (kg)
 * @param k Constante elástica del resorte (N/m)
 * @param gamma Coeficiente de amortiguamiento (kg/s)
 * @param F0 Amplitud de la fuerza externa (N)
 * @param omega_ext Frecuencia angular de la fuerza externa (rad/s)
 * @param x0 Posición inicial (m)
 * @param v0 Velocidad inicial (m/s)
 * @param dt Paso de tiempo (s)
 * @param num_pasos Número de pasos de tiempo a simular
 * @param forzado true si es solución forzada, false si es homogénea
 */
inline void simular_oscilador(const std::string& nombre_archivo, 
                             double masa, double k, double frecuencia, double F0, double omega_ext,
                             double x0, double v0, double dt, int num_pasos, bool forzado) {

    // Preparar archivo de salida
    std::ofstream archivo;
    if (!abrir_archivo(archivo, nombre_archivo)) {
        std::cerr << "Error al abrir el archivo: " << nombre_archivo << std::endl;
        return;
    }

    // Escribir encabezado
    archivo << "tiempo,posicion,velocidad,regimen\n";

    // Variables para almacenar el estado del sistema
    double x = x0;
    double v = v0;
    double t = 0.0;

    double gamma = 2 * frecuencia;
    double tiempo_transicion = 1.0 / gamma;

    // Constantes auxiliares para optimización
    const double inv_masa = 1.0 / masa;  // Inversa de la masa
    const double gamma_masa = gamma * inv_masa;  // γ/m
    const double k_masa = k * inv_masa;  // k/m
    const double F0_masa = F0 * inv_masa;  // F₀/m

    // Método de Euler-Cromer
    for (int i = 0; i < num_pasos; ++i) {
        // Determinar régimen
        std::string regimen = (t < tiempo_transicion) ? "transitorio" : "estacionario";
        
        // Guardar estado actual
        archivo << t << "," << x << "," << v << "," << regimen << "\n";

        // Calcular la fuerza externa en este instante (0 si es homogénea)
        double fuerza_externa = forzado ? F0_masa * cos(omega_ext * t) : 0.0;

        // Actualizar velocidad (Euler)
        v += dt * (-gamma_masa * v - k_masa * x + fuerza_externa);

        // Actualizar posición (Cromer)
        x += dt * v;

        // Avanzar el tiempo
        t += dt;
    }

    // Cerrar el archivo
    archivo.close();
}

#endif // SIMULACION_H
