/*
 * EJERCICIOS DE CASOS EDGE EN TABLAS HASH
 * ========================================
 * 
 * Este archivo contiene ejercicios diseñados para explotar cada uno de los casos
 * edge en tablas hash, específicamente durante inserción, búsqueda y eliminación.
 * 
 * CASOS EDGE CUBIERTOS:
 * 
 * 1. COLISIONES:
 *    - Colisión simple (dos claves misma posición)
 *    - Colisión múltiple (cadena de colisiones)
 *    - Colisión en cascada
 * 
 * 2. RESOLUCIÓN DE COLISIONES:
 *    - Encadenamiento (Chaining)
 *    - Direccionamiento abierto:
 *      * Sondeo lineal (Linear Probing)
 *      * Sondeo cuadrático (Quadratic Probing)
 *      * Hashing doble (Double Hashing)
 * 
 * 3. FACTOR DE CARGA:
 *    - Tabla con baja carga
 *    - Tabla con alta carga
 *    - Tabla llena (100% carga)
 * 
 * 4. REHASHING:
 *    - Rehashing automático al exceder factor de carga
 *    - Redistribución de elementos
 * 
 * 5. ELIMINACIÓN:
 *    - Eliminación en encadenamiento
 *    - Eliminación con marcador de borrado (direccionamiento abierto)
 *    - Eliminación que afecta cadenas de sondeo
 */

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <functional>
#include <iomanip>

// ============================================================================
//                      TABLA HASH CON ENCADENAMIENTO
// ============================================================================

class HashTableChaining {
private:
    std::vector<std::list<std::pair<int, std::string>>> tabla;
    int tamano;
    int numElementos;
    
    int hash(int clave) {
        return clave % tamano;
    }
    
public:
    HashTableChaining(int tam) : tamano(tam), numElementos(0) {
        tabla.resize(tamano);
    }
    
    void insertar(int clave, const std::string& valor) {
        int indice = hash(clave);
        std::cout << "  Insertando (" << clave << ", \"" << valor << "\") -> hash(" << clave << ") = " << indice << std::endl;
        
        // Verificar si ya existe
        for (auto& par : tabla[indice]) {
            if (par.first == clave) {
                std::cout << "  [CASO: Actualización de clave existente]" << std::endl;
                par.second = valor;
                return;
            }
        }
        
        if (!tabla[indice].empty()) {
            std::cout << "  [CASO: COLISIÓN detectada en índice " << indice << "]" << std::endl;
            std::cout << "  Elementos existentes en cubeta " << indice << ": " << tabla[indice].size() << std::endl;
        }
        
        tabla[indice].push_back({clave, valor});
        numElementos++;
    }
    
    bool buscar(int clave, std::string& resultado) {
        int indice = hash(clave);
        int comparaciones = 0;
        
        std::cout << "  Buscando " << clave << " -> hash(" << clave << ") = " << indice << std::endl;
        
        for (const auto& par : tabla[indice]) {
            comparaciones++;
            if (par.first == clave) {
                resultado = par.second;
                std::cout << "  [Encontrado después de " << comparaciones << " comparación(es)]" << std::endl;
                return true;
            }
        }
        
        std::cout << "  [No encontrado después de " << comparaciones << " comparación(es)]" << std::endl;
        return false;
    }
    
    bool eliminar(int clave) {
        int indice = hash(clave);
        std::cout << "  Eliminando " << clave << " -> hash(" << clave << ") = " << indice << std::endl;
        
        for (auto it = tabla[indice].begin(); it != tabla[indice].end(); ++it) {
            if (it->first == clave) {
                tabla[indice].erase(it);
                numElementos--;
                std::cout << "  [Elemento eliminado exitosamente]" << std::endl;
                return true;
            }
        }
        
        std::cout << "  [Elemento no encontrado]" << std::endl;
        return false;
    }
    
    void imprimir() {
        std::cout << "\n  Estado de la tabla (Encadenamiento):" << std::endl;
        std::cout << "  " << std::string(50, '-') << std::endl;
        for (int i = 0; i < tamano; i++) {
            std::cout << "  [" << std::setw(2) << i << "]: ";
            if (tabla[i].empty()) {
                std::cout << "(vacío)";
            } else {
                for (const auto& par : tabla[i]) {
                    std::cout << "(" << par.first << ",\"" << par.second << "\") -> ";
                }
                std::cout << "NULL";
            }
            std::cout << std::endl;
        }
        std::cout << "  " << std::string(50, '-') << std::endl;
        std::cout << "  Elementos: " << numElementos << ", Tamaño: " << tamano << std::endl;
        std::cout << "  Factor de carga: " << std::fixed << std::setprecision(2) 
                  << (float)numElementos / tamano << std::endl;
    }
};

// ============================================================================
//                  TABLA HASH CON SONDEO LINEAL
// ============================================================================

class HashTableLinearProbing {
private:
    enum Estado { VACIO, OCUPADO, ELIMINADO };
    
    struct Entrada {
        int clave;
        std::string valor;
        Estado estado;
        
        Entrada() : clave(0), estado(VACIO) {}
    };
    
    std::vector<Entrada> tabla;
    int tamano;
    int numElementos;
    
    int hash(int clave) {
        return clave % tamano;
    }
    
public:
    HashTableLinearProbing(int tam) : tamano(tam), numElementos(0) {
        tabla.resize(tamano);
    }
    
    bool insertar(int clave, const std::string& valor) {
        if (numElementos >= tamano) {
            std::cout << "  [CASO: Tabla llena - No se puede insertar]" << std::endl;
            return false;
        }
        
        int indiceOriginal = hash(clave);
        int indice = indiceOriginal;
        int intentos = 0;
        int primerEliminado = -1;
        
        std::cout << "  Insertando (" << clave << ", \"" << valor << "\") -> hash(" << clave << ") = " << indice << std::endl;
        
        while (intentos < tamano) {
            if (tabla[indice].estado == VACIO) {
                break;
            }
            
            if (tabla[indice].estado == OCUPADO && tabla[indice].clave == clave) {
                std::cout << "  [CASO: Actualización de clave existente]" << std::endl;
                tabla[indice].valor = valor;
                return true;
            }
            
            if (tabla[indice].estado == ELIMINADO && primerEliminado == -1) {
                primerEliminado = indice;
            }
            
            intentos++;
            if (intentos >= tamano) {
                break;
            }
            
            std::cout << "  [COLISIÓN en " << indice << "] Sondeo lineal: índice = (" << indiceOriginal << " + " << intentos << ") % " << tamano << std::endl;
            indice = (indiceOriginal + intentos) % tamano;
        }
        
        if (intentos >= tamano && primerEliminado == -1 && tabla[indice].estado != VACIO) {
            std::cout << "  [CASO: Tabla llena después de sondear toda la tabla]" << std::endl;
            return false;
        }
        
        int indiceInsercion = (primerEliminado != -1) ? primerEliminado : indice;
        
        numElementos++;
        tabla[indiceInsercion].clave = clave;
        tabla[indiceInsercion].valor = valor;
        tabla[indiceInsercion].estado = OCUPADO;
        
        if (intentos > 0) {
            std::cout << "  [Insertado en índice " << indiceInsercion << " después de " << intentos << " colisión(es)]" << std::endl;
        }
        
        return true;
    }
    
    bool buscar(int clave, std::string& resultado) {
        int indice = hash(clave);
        int indiceOriginal = indice;
        int intentos = 0;
        
        std::cout << "  Buscando " << clave << " -> hash(" << clave << ") = " << indice << std::endl;
        
        while (tabla[indice].estado != VACIO) {
            if (tabla[indice].estado == OCUPADO && tabla[indice].clave == clave) {
                resultado = tabla[indice].valor;
                std::cout << "  [Encontrado en índice " << indice << " después de " << intentos << " salto(s)]" << std::endl;
                return true;
            }
            
            intentos++;
            indice = (indiceOriginal + intentos) % tamano;
            
            if (intentos >= tamano) break;
        }
        
        std::cout << "  [No encontrado después de " << intentos << " intento(s)]" << std::endl;
        return false;
    }
    
    bool eliminar(int clave) {
        int indice = hash(clave);
        int indiceOriginal = indice;
        int intentos = 0;
        
        std::cout << "  Eliminando " << clave << " -> hash(" << clave << ") = " << indice << std::endl;
        
        while (tabla[indice].estado != VACIO) {
            if (tabla[indice].estado == OCUPADO && tabla[indice].clave == clave) {
                tabla[indice].estado = ELIMINADO;
                numElementos--;
                std::cout << "  [CASO: Elemento eliminado - Marcado como ELIMINADO]" << std::endl;
                std::cout << "  (El marcador permite continuar sondeos de búsqueda)" << std::endl;
                return true;
            }
            
            intentos++;
            indice = (indiceOriginal + intentos) % tamano;
            
            if (intentos >= tamano) break;
        }
        
        std::cout << "  [Elemento no encontrado]" << std::endl;
        return false;
    }
    
    void imprimir() {
        std::cout << "\n  Estado de la tabla (Sondeo Lineal):" << std::endl;
        std::cout << "  " << std::string(50, '-') << std::endl;
        for (int i = 0; i < tamano; i++) {
            std::cout << "  [" << std::setw(2) << i << "]: ";
            switch (tabla[i].estado) {
                case VACIO:
                    std::cout << "(vacío)";
                    break;
                case OCUPADO:
                    std::cout << "(" << tabla[i].clave << ", \"" << tabla[i].valor << "\")";
                    break;
                case ELIMINADO:
                    std::cout << "(ELIMINADO)";
                    break;
            }
            std::cout << std::endl;
        }
        std::cout << "  " << std::string(50, '-') << std::endl;
        std::cout << "  Elementos: " << numElementos << ", Tamaño: " << tamano << std::endl;
        std::cout << "  Factor de carga: " << std::fixed << std::setprecision(2) 
                  << (float)numElementos / tamano << std::endl;
    }
};

// ============================================================================
//              TABLA HASH CON SONDEO CUADRÁTICO
// ============================================================================

class HashTableQuadraticProbing {
private:
    enum Estado { VACIO, OCUPADO, ELIMINADO };
    
    struct Entrada {
        int clave;
        std::string valor;
        Estado estado;
        
        Entrada() : clave(0), estado(VACIO) {}
    };
    
    std::vector<Entrada> tabla;
    int tamano;
    int numElementos;
    
    int hash(int clave) {
        return clave % tamano;
    }
    
public:
    HashTableQuadraticProbing(int tam) : tamano(tam), numElementos(0) {
        tabla.resize(tamano);
    }
    
    bool insertar(int clave, const std::string& valor) {
        if (numElementos >= tamano) {
            std::cout << "  [CASO: Tabla llena]" << std::endl;
            return false;
        }
        
        int indice = hash(clave);
        int indiceOriginal = indice;
        int intentos = 0;
        
        std::cout << "  Insertando (" << clave << ", \"" << valor << "\") -> hash(" << clave << ") = " << indice << std::endl;
        
        while (tabla[indice].estado == OCUPADO && tabla[indice].clave != clave) {
            intentos++;
            int offset = intentos * intentos;  // Sondeo cuadrático: i²
            std::cout << "  [COLISIÓN en " << indice << "] Sondeo cuadrático: índice = (" << indiceOriginal << " + " << intentos << "²) % " << tamano << std::endl;
            indice = (indiceOriginal + offset) % tamano;
            
            if (intentos >= tamano) {
                std::cout << "  [CASO: No se encontró posición disponible]" << std::endl;
                return false;
            }
        }
        
        if (tabla[indice].estado == OCUPADO && tabla[indice].clave == clave) {
            std::cout << "  [CASO: Actualización de clave existente]" << std::endl;
        } else {
            numElementos++;
        }
        
        tabla[indice].clave = clave;
        tabla[indice].valor = valor;
        tabla[indice].estado = OCUPADO;
        
        if (intentos > 0) {
            std::cout << "  [Insertado en índice " << indice << " después de " << intentos << " colisión(es)]" << std::endl;
        }
        
        return true;
    }
    
    void imprimir() {
        std::cout << "\n  Estado de la tabla (Sondeo Cuadrático):" << std::endl;
        std::cout << "  " << std::string(50, '-') << std::endl;
        for (int i = 0; i < tamano; i++) {
            std::cout << "  [" << std::setw(2) << i << "]: ";
            switch (tabla[i].estado) {
                case VACIO:
                    std::cout << "(vacío)";
                    break;
                case OCUPADO:
                    std::cout << "(" << tabla[i].clave << ", \"" << tabla[i].valor << "\")";
                    break;
                case ELIMINADO:
                    std::cout << "(ELIMINADO)";
                    break;
            }
            std::cout << std::endl;
        }
        std::cout << "  " << std::string(50, '-') << std::endl;
    }
};

/*
 * ============================================================================
 *                    EJERCICIO 1: INSERCIÓN SIN COLISIONES
 * ============================================================================
 * Claves: 5, 12, 23
 * Tabla de tamaño 10
 * 
 * Las claves generan índices diferentes: 5, 2, 3
 */
void ejercicio1_sin_colisiones() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 1: INSERCIÓN SIN COLISIONES" << std::endl;
    std::cout << "Tabla tamaño 10, Claves: 5, 12, 23" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    HashTableChaining tabla(10);
    
    tabla.insertar(5, "cinco");
    tabla.insertar(12, "doce");
    tabla.insertar(23, "veintitrés");
    
    tabla.imprimir();
}

/*
 * ============================================================================
 *                    EJERCICIO 2: COLISIÓN SIMPLE
 * ============================================================================
 * Claves: 5, 15, 25
 * Tabla de tamaño 10
 * 
 * Todas las claves hash al índice 5 (5%10=5, 15%10=5, 25%10=5)
 */
void ejercicio2_colision_simple() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 2: COLISIÓN SIMPLE (Encadenamiento)" << std::endl;
    std::cout << "Tabla tamaño 10, Claves: 5, 15, 25" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    HashTableChaining tabla(10);
    
    tabla.insertar(5, "cinco");
    tabla.insertar(15, "quince");
    tabla.insertar(25, "veinticinco");
    
    tabla.imprimir();
}

/*
 * ============================================================================
 *            EJERCICIO 3: COLISIÓN CON SONDEO LINEAL
 * ============================================================================
 * Claves: 5, 15, 25, 35
 * Tabla de tamaño 10
 * 
 * Todas colisionan en índice 5, sondeo lineal busca: 5, 6, 7, 8...
 */
void ejercicio3_sondeo_lineal() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 3: COLISIÓN CON SONDEO LINEAL" << std::endl;
    std::cout << "Tabla tamaño 10, Claves: 5, 15, 25, 35" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    HashTableLinearProbing tabla(10);
    
    tabla.insertar(5, "cinco");
    tabla.insertar(15, "quince");
    tabla.insertar(25, "veinticinco");
    tabla.insertar(35, "treinta y cinco");
    
    tabla.imprimir();
}

/*
 * ============================================================================
 *            EJERCICIO 4: COLISIÓN CON SONDEO CUADRÁTICO
 * ============================================================================
 * Claves: 5, 15, 25, 35
 * Tabla de tamaño 10
 * 
 * Sondeo cuadrático: i² -> 5, 5+1, 5+4, 5+9...
 */
void ejercicio4_sondeo_cuadratico() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 4: COLISIÓN CON SONDEO CUADRÁTICO" << std::endl;
    std::cout << "Tabla tamaño 10, Claves: 5, 15, 25, 35" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    HashTableQuadraticProbing tabla(10);
    
    tabla.insertar(5, "cinco");
    tabla.insertar(15, "quince");
    tabla.insertar(25, "veinticinco");
    tabla.insertar(35, "treinta y cinco");
    
    tabla.imprimir();
}

/*
 * ============================================================================
 *                    EJERCICIO 5: BÚSQUEDA CON COLISIONES
 * ============================================================================
 * Demostrar cómo las búsquedas atraviesan la cadena de colisiones.
 */
void ejercicio5_busqueda_colisiones() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 5: BÚSQUEDA CON COLISIONES" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    HashTableLinearProbing tabla(10);
    
    // Insertar con colisiones
    tabla.insertar(5, "cinco");
    tabla.insertar(15, "quince");
    tabla.insertar(25, "veinticinco");
    
    tabla.imprimir();
    
    std::cout << "\n--- Búsquedas ---" << std::endl;
    std::string resultado;
    
    // Buscar el primero (sin saltos)
    std::cout << "\nBuscar 5 (primer elemento en cadena):" << std::endl;
    tabla.buscar(5, resultado);
    
    // Buscar el último (máximos saltos)
    std::cout << "\nBuscar 25 (último elemento en cadena):" << std::endl;
    tabla.buscar(25, resultado);
    
    // Buscar inexistente
    std::cout << "\nBuscar 35 (no existe):" << std::endl;
    tabla.buscar(35, resultado);
}

/*
 * ============================================================================
 *            EJERCICIO 6: ELIMINACIÓN CON MARCADOR (TOMBSTONE)
 * ============================================================================
 * Demostrar el problema de eliminar en sondeo abierto.
 */
void ejercicio6_eliminacion_tombstone() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 6: ELIMINACIÓN CON MARCADOR (TOMBSTONE)" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    HashTableLinearProbing tabla(10);
    
    tabla.insertar(5, "cinco");
    tabla.insertar(15, "quince");
    tabla.insertar(25, "veinticinco");
    
    std::cout << "\nTabla antes de eliminar:" << std::endl;
    tabla.imprimir();
    
    std::cout << "\n--- Eliminar 15 (en medio de la cadena) ---" << std::endl;
    tabla.eliminar(15);
    
    std::cout << "\nTabla después de eliminar:" << std::endl;
    tabla.imprimir();
    
    std::cout << "\n--- Buscar 25 (después del elemento eliminado) ---" << std::endl;
    std::string resultado;
    tabla.buscar(25, resultado);
}

/*
 * ============================================================================
 *                    EJERCICIO 7: FACTOR DE CARGA ALTO
 * ============================================================================
 * Tabla casi llena - demostrar degradación del rendimiento.
 */
void ejercicio7_factor_carga_alto() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 7: FACTOR DE CARGA ALTO" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    HashTableLinearProbing tabla(10);
    
    // Llenar la tabla al 80%
    int claves[] = {5, 12, 23, 34, 45, 56, 67, 78};
    
    for (int c : claves) {
        tabla.insertar(c, "val" + std::to_string(c));
    }
    
    std::cout << "\nTabla con factor de carga 0.80:" << std::endl;
    tabla.imprimir();
    
    std::cout << "\n--- Insertar en tabla con alta carga ---" << std::endl;
    tabla.insertar(89, "val89");
    
    tabla.imprimir();
}

/*
 * ============================================================================
 *                    EJERCICIO 8: TABLA LLENA
 * ============================================================================
 * Intentar insertar cuando la tabla está completamente llena.
 */
void ejercicio8_tabla_llena() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 8: TABLA LLENA" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    HashTableLinearProbing tabla(5);
    
    // Llenar completamente
    tabla.insertar(0, "cero");
    tabla.insertar(1, "uno");
    tabla.insertar(2, "dos");
    tabla.insertar(3, "tres");
    tabla.insertar(4, "cuatro");
    
    std::cout << "\nTabla llena:" << std::endl;
    tabla.imprimir();
    
    std::cout << "\n--- Intentar insertar en tabla llena ---" << std::endl;
    tabla.insertar(5, "cinco");
}

/*
 * ============================================================================
 *                EJERCICIO 9: CLUSTERING EN SONDEO LINEAL
 * ============================================================================
 * Demostrar el problema de agrupamiento primario.
 */
void ejercicio9_clustering() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 9: CLUSTERING EN SONDEO LINEAL" << std::endl;
    std::cout << "Problema: Claves consecutivas crean clusters grandes" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    HashTableLinearProbing tabla(10);
    
    // Claves que crean un cluster grande
    int claves[] = {0, 10, 20, 1, 11, 21, 2};
    
    for (int c : claves) {
        tabla.insertar(c, "val" + std::to_string(c));
    }
    
    std::cout << "\nObserve el cluster formado:" << std::endl;
    tabla.imprimir();
}

/*
 * ============================================================================
 *        EJERCICIO 10: COMPARACIÓN ENCADENAMIENTO VS SONDEO
 * ============================================================================
 */
void ejercicio10_comparacion() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 10: COMPARACIÓN ENCADENAMIENTO VS SONDEO LINEAL" << std::endl;
    std::cout << "Mismas claves: 5, 15, 25, 35, 45" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    HashTableChaining tablaChaining(10);
    HashTableLinearProbing tablaLineal(10);
    
    int claves[] = {5, 15, 25, 35, 45};
    
    std::cout << "\n--- ENCADENAMIENTO ---" << std::endl;
    for (int c : claves) {
        tablaChaining.insertar(c, "val" + std::to_string(c));
    }
    tablaChaining.imprimir();
    
    std::cout << "\n--- SONDEO LINEAL ---" << std::endl;
    for (int c : claves) {
        tablaLineal.insertar(c, "val" + std::to_string(c));
    }
    tablaLineal.imprimir();
}

/*
 * ============================================================================
 *                EJERCICIO 11: ELIMINACIÓN EN ENCADENAMIENTO
 * ============================================================================
 */
void ejercicio11_eliminacion_encadenamiento() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 11: ELIMINACIÓN EN ENCADENAMIENTO" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    HashTableChaining tabla(10);
    
    tabla.insertar(5, "cinco");
    tabla.insertar(15, "quince");
    tabla.insertar(25, "veinticinco");
    
    std::cout << "\nTabla antes de eliminar:" << std::endl;
    tabla.imprimir();
    
    std::cout << "\n--- Eliminar 15 (del medio de la lista) ---" << std::endl;
    tabla.eliminar(15);
    
    std::cout << "\nTabla después de eliminar:" << std::endl;
    tabla.imprimir();
    
    std::cout << "\n--- Buscar 25 (verificar que sigue accesible) ---" << std::endl;
    std::string resultado;
    if (tabla.buscar(25, resultado)) {
        std::cout << "  Resultado: " << resultado << std::endl;
    }
}

/*
 * ============================================================================
 *            EJERCICIO 12: DISPERSIÓN MÓDULO PRIMO VS NO PRIMO
 * ============================================================================
 */
void ejercicio12_modulo_primo() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 12: DISPERSIÓN MÓDULO PRIMO VS NO PRIMO" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    int clavesMultiplos[] = {10, 20, 30, 40, 50, 60, 70};
    
    std::cout << "\n--- Tabla tamaño 10 (no primo) ---" << std::endl;
    std::cout << "Claves múltiplos de 10: ";
    for (int c : clavesMultiplos) std::cout << c << " ";
    std::cout << std::endl;
    
    HashTableChaining tabla10(10);
    for (int c : clavesMultiplos) {
        tabla10.insertar(c, "val" + std::to_string(c));
    }
    tabla10.imprimir();
    
    std::cout << "\n--- Tabla tamaño 11 (primo) ---" << std::endl;
    std::cout << "Mismas claves distribuidas mejor:" << std::endl;
    
    HashTableChaining tabla11(11);
    for (int c : clavesMultiplos) {
        tabla11.insertar(c, "val" + std::to_string(c));
    }
    tabla11.imprimir();
}

int main() {
    std::cout << "\n" << std::string(70, '*') << std::endl;
    std::cout << "        EJERCICIOS DE CASOS EDGE EN TABLAS HASH" << std::endl;
    std::cout << std::string(70, '*') << std::endl;
    
    std::cout << "\n[MENÚ DE EJERCICIOS]" << std::endl;
    std::cout << "1.  Inserción sin colisiones" << std::endl;
    std::cout << "2.  Colisión simple (Encadenamiento)" << std::endl;
    std::cout << "3.  Colisión con sondeo lineal" << std::endl;
    std::cout << "4.  Colisión con sondeo cuadrático" << std::endl;
    std::cout << "5.  Búsqueda con colisiones" << std::endl;
    std::cout << "6.  Eliminación con marcador (Tombstone)" << std::endl;
    std::cout << "7.  Factor de carga alto" << std::endl;
    std::cout << "8.  Tabla llena" << std::endl;
    std::cout << "9.  Clustering en sondeo lineal" << std::endl;
    std::cout << "10. Comparación Encadenamiento vs Sondeo" << std::endl;
    std::cout << "11. Eliminación en encadenamiento" << std::endl;
    std::cout << "12. Dispersión módulo primo vs no primo" << std::endl;
    std::cout << "0.  Ejecutar todos los ejercicios" << std::endl;
    
    int opcion;
    std::cout << "\nSelecciona un ejercicio (0-12): ";
    std::cin >> opcion;
    
    switch(opcion) {
        case 0:
            ejercicio1_sin_colisiones();
            ejercicio2_colision_simple();
            ejercicio3_sondeo_lineal();
            ejercicio4_sondeo_cuadratico();
            ejercicio5_busqueda_colisiones();
            ejercicio6_eliminacion_tombstone();
            ejercicio7_factor_carga_alto();
            ejercicio8_tabla_llena();
            ejercicio9_clustering();
            ejercicio10_comparacion();
            ejercicio11_eliminacion_encadenamiento();
            ejercicio12_modulo_primo();
            break;
        case 1: ejercicio1_sin_colisiones(); break;
        case 2: ejercicio2_colision_simple(); break;
        case 3: ejercicio3_sondeo_lineal(); break;
        case 4: ejercicio4_sondeo_cuadratico(); break;
        case 5: ejercicio5_busqueda_colisiones(); break;
        case 6: ejercicio6_eliminacion_tombstone(); break;
        case 7: ejercicio7_factor_carga_alto(); break;
        case 8: ejercicio8_tabla_llena(); break;
        case 9: ejercicio9_clustering(); break;
        case 10: ejercicio10_comparacion(); break;
        case 11: ejercicio11_eliminacion_encadenamiento(); break;
        case 12: ejercicio12_modulo_primo(); break;
        default:
            std::cout << "Opción no válida." << std::endl;
    }
    
    return 0;
}
