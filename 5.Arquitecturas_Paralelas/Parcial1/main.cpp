#include <iostream>
#include <string>
#include <chrono>
#include <cmath>
#include "simulacion.h"
#include "utilidades.h"

int main(int argc, char* argv[]) {
    // Parámetros del sistema físico
    double masa = 1.0;            // kg
    double omega_0 = 2.0;        // Frecuencia natural (rad/s)
    double k = masa * omega_0 * omega_0;  // N/m
    double F0 = 1.0;             // N
    double omega_ext = omega_0;   // Frecuencia de la fuerza externa

    // Parámetros de simulación
    double dt = 0.01;            // Paso de tiempo (s)
    double tiempo_total = 5.0;  // Tiempo total (s)
    int num_pasos = static_cast<int>(tiempo_total / dt);

    // Condiciones iniciales
    double x0 = 1.0;             // Posición inicial (m)
    double v0 = 0.0;             // Velocidad inicial (m/s)

    // Valores de gamma
    double valores_gamma[] = {0.5, 1.0, 2.0};

    // Ejecutar simulación para cada valor de gamma
    for (double gamma : valores_gamma) {
        std::string nombre_archivo = "datos_" + std::to_string(gamma) + ".csv";
        std::string nombre_archivo_h = "datos_h_" + std::to_string(gamma) + ".csv";

        auto inicio = std::chrono::high_resolution_clock::now();

        // Simular solución forzada
        simular_oscilador(nombre_archivo, masa, k, gamma/2.0, F0, omega_ext, 
                         x0, v0, dt, num_pasos, true);

        // Simular solución homogénea (F0 = 0)
        simular_oscilador(nombre_archivo_h, masa, k, gamma/2.0, 0.0, omega_ext, 
                         x0, v0, dt, num_pasos, false);

        auto fin = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duracion = fin - inicio;

        // Calcular tiempo de transición
        double tiempo_transicion = 1.0 / gamma;

        std::cout << "Simulación para gamma = " << gamma << " completada en " 
                  << duracion.count() << " segundos." << std::endl;
        std::cout << "Tiempo de transición (1/γ) = " << tiempo_transicion 
                  << " segundos" << std::endl;
        std::cout << "Resultados guardados en: " << nombre_archivo << " y " 
                  << nombre_archivo_h << std::endl;
    }

    return 0;
}
