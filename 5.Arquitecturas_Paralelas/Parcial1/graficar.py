
#!/usr/bin/env python3
import pandas as pd
import matplotlib.pyplot as plt
import glob
import os

def graficar_datos(archivo_forzado, archivo_homogeneo):
    # Cargar datos
    df_f = pd.read_csv(archivo_forzado)
    df_h = pd.read_csv(archivo_homogeneo)
    
    # Obtener gamma del nombre del archivo
    gamma = float(archivo_forzado.split('_')[1].split('.')[0])
    
    # Crear gráfica
    plt.figure(figsize=(12, 8))
    
    # Graficar solución forzada
    plt.plot(df_f['tiempo'], df_f['posicion'], 'b-', label='Solución forzada', linewidth=1.5)
    
    # Graficar solución homogénea
    plt.plot(df_h['tiempo'], df_h['posicion'], 'r--', label='Solución homogénea', linewidth=1.5)
    
    # Marcar regímenes y tiempo de transición usando las etiquetas del CSV
    transitorio = df_f[df_f['regimen'] == 'transitorio']
    estacionario = df_f[df_f['regimen'] == 'estacionario']
    
    if not transitorio.empty and not estacionario.empty:
        t_trans = transitorio['tiempo'].iloc[-1]
        plt.axvline(x=t_trans, color='g', linestyle=':', 
                    label=f'Transición (t = {t_trans:.2f}s)')
        
        # Agregar texto indicando los regímenes
        ymin, ymax = plt.ylim()
        plt.text(t_trans/2, ymax*0.9, 'Régimen\nTransitorio', 
                 horizontalalignment='center')
        plt.text(t_trans*1.5, ymax*0.9, 'Régimen\nEstacionario', 
                 horizontalalignment='center')
    
    # Personalizar gráfica
    plt.title(f'Oscilador Amortiguado (γ = {gamma:.1f})')
    plt.xlabel('Tiempo (s)')
    plt.ylabel('Posición (m)')
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.legend()
    
    # Guardar
    nombre_grafica = f"grafica_gamma_{gamma}.png"
    plt.savefig(nombre_grafica, dpi=300, bbox_inches='tight')
    print(f"Gráfica guardada como: {nombre_grafica}")
    plt.close()

def main():
    # Buscar archivos de datos
    archivos_forzados = sorted(glob.glob("datos_[0-9]*.csv"))
    
    if not archivos_forzados:
        print("No se encontraron archivos de datos")
        return
    
    print(f"Procesando {len(archivos_forzados)} casos...")
    
    # Graficar cada caso
    for archivo_f in archivos_forzados:
        archivo_h = f"datos_h_{archivo_f.split('_')[1]}"
        if os.path.exists(archivo_h):
            print(f"Procesando γ = {archivo_f.split('_')[1].split('.')[0]}...")
            graficar_datos(archivo_f, archivo_h)

if __name__ == "__main__":
    main()
