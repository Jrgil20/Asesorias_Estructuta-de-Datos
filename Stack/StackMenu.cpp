#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<string>
using namespace std;

struct Nodo {
    int dato;
    Nodo *siguiente;	
};

// Prototipos
void menu();
void push(Nodo *&, int);
void pop(Nodo *&, int &);
void mostrarPila(Nodo *, bool eliminar = false);
bool estaVacia(Nodo *);
int obtenerTamano(Nodo *);
void limpiarPila(Nodo *&);

int main() {
    menu();
    return 0;
}

void menu() {
    Nodo *pila = NULL;
    int opcion, dato;
    
    do {
        // Limpiar pantalla
        system("clear");
        
        cout << "\n";
        cout << "╔════════════════════════════════════════╗\n";
        cout << "║         .: GESTOR DE PILAS :.          ║\n";
        cout << "║     Estructura de Datos - Repaso       ║\n";
        cout << "╚════════════════════════════════════════╝\n\n";
        
        // Mostrar estado actual de la pila
        cout << "📦 ESTADO ACTUAL DE LA PILA:\n";
        cout << "─────────────────────────────\n";
        if (estaVacia(pila)) {
            cout << "   [PILA VACÍA]\n";
        } else {
            cout << "   Tamaño: " << obtenerTamano(pila) << " elemento(s)\n";
            cout << "   Contenido (de arriba a abajo):\n";
            mostrarPila(pila);
        }
        
        cout << "\n╔════════════════════════════════════════╗\n";
        cout << "║            .: MENÚ PRINCIPAL :.         ║\n";
        cout << "╚════════════════════════════════════════╝\n";
        cout << "1. ➕ Insertar un número en la pila\n";
        cout << "2. ➖ Extraer el tope de la pila\n";
        cout << "3. 👀 Ver todos los elementos\n";
        cout << "4. 🔄 Ver el tope sin extraer\n";
        cout << "5. 🗑️  Limpiar la pila completa\n";
        cout << "6. ❌ Salir\n";
        cout << "\n➤ Selecciona una opción: ";
        cin >> opcion;
        
        switch(opcion) {
            case 1: {
                cout << "\n📝 Ingresa el número a insertar: ";
                cin >> dato;
                push(pila, dato);
                cout << "\n✅ Número " << dato << " insertado correctamente en el tope.\n";
                
                // Mostrar visualización de la acción
                cout << "\n📊 Visualización después de la inserción:\n";
                mostrarPila(pila);
                
                cout << "\nPresiona cualquier tecla para continuar...";
                cin.ignore();
                getchar();
                break;
            }
            
            case 2: {
                if (estaVacia(pila)) {
                    cout << "\n❌ ERROR: La pila está vacía. No se puede extraer.\n";
                } else {
                    cout << "\n⏳ Extrayendo el elemento del tope...\n";
                    pop(pila, dato);
                    cout << "✅ Elemento " << dato << " extraído exitosamente.\n";
                    cout << "\n📊 Estado de la pila tras la extracción:\n";
                    mostrarPila(pila);
                }
                
                cout << "\nPresiona cualquier tecla para continuar...";
                cin.ignore();
                getchar();
                break;
            }
            
            case 3: {
                cout << "\n📋 RECORRIDO COMPLETO DE LA PILA (de tope a base):\n";
                cout << "═════════════════════════════════════════\n";
                if (estaVacia(pila)) {
                    cout << "   [PILA VACÍA]\n";
                } else {
                    int contador = 1;
                    Nodo *actual = pila;
                    while (actual != NULL) {
                        cout << "   Posición " << contador << " (tope): " << actual->dato << "\n";
                        actual = actual->siguiente;
                        contador++;
                    }
                }
                cout << "═════════════════════════════════════════\n";
                
                cout << "\nPresiona cualquier tecla para continuar...";
                cin.ignore();
                getchar();
                break;
            }
            
            case 4: {
                if (estaVacia(pila)) {
                    cout << "\n❌ ERROR: La pila está vacía. No hay tope.\n";
                } else {
                    cout << "\n👀 El tope actual de la pila es: " << pila->dato << "\n";
                    cout << "   (No se modificó la pila)\n";
                }
                
                cout << "\nPresiona cualquier tecla para continuar...";
                cin.ignore();
                getchar();
                break;
            }
            
            case 5: {
                if (estaVacia(pila)) {
                    cout << "\n⚠️  La pila ya está vacía.\n";
                } else {
                    cout << "\n🔄 Limpiando la pila...\n";
                    limpiarPila(pila);
                    cout << "✅ Pila completamente limpia y memoria liberada.\n";
                }
                
                cout << "\nPresiona cualquier tecla para continuar...";
                cin.ignore();
                getchar();
                break;
            }
            
            case 6: {
                cout << "\n👋 Limpiando memoria y saliendo...\n";
                limpiarPila(pila);
                cout << "✅ Hasta luego!\n\n";
                break;
            }
            
            default: {
                cout << "\n❌ Opción no válida. Intenta de nuevo.\n";
                cout << "\nPresiona cualquier tecla para continuar...";
                cin.ignore();
                getchar();
            }
        }
        
    } while(opcion != 6);
}

// Función para insertar (PUSH)
void push(Nodo *&pila, int n) {
    Nodo *nuevo_nodo = new Nodo();
    nuevo_nodo->dato = n;
    nuevo_nodo->siguiente = pila;
    pila = nuevo_nodo;
}

// Función para extraer (POP)
void pop(Nodo *&pila, int &n) {
    if (pila != NULL) {
        Nodo *aux = pila;
        n = aux->dato;
        pila = aux->siguiente;
        delete aux;
    }
}

// Función para mostrar la pila de forma visual y atractiva
void mostrarPila(Nodo *pila, bool eliminar) {
    if (pila == NULL) {
        cout << "   ┌─────────────┐\n";
        cout << "   │   VACÍA     │\n";
        cout << "   └─────────────┘\n";
        return;
    }
    
    cout << "   ┌───────────┐\n";
    Nodo *actual = pila;
    int contador = 0;
    
    while (actual != NULL) {
        cout << "   │ " << actual->dato << "         │ " << (contador == 0 ? "← TOPE" : "") << "\n";
        if (actual->siguiente != NULL) {
            cout << "   ├───────────┤\n";
        }
        actual = actual->siguiente;
        contador++;
    }
    
    cout << "   └───────────┘\n";
}

// Función para verificar si la pila está vacía
bool estaVacia(Nodo *pila) {
    return pila == NULL;
}

// Función para obtener el tamaño de la pila
int obtenerTamano(Nodo *pila) {
    int contador = 0;
    Nodo *actual = pila;
    while (actual != NULL) {
        contador++;
        actual = actual->siguiente;
    }
    return contador;
}

// Función para limpiar la pila completamente
void limpiarPila(Nodo *&pila) {
    while (pila != NULL) {
        Nodo *aux = pila;
        pila = pila->siguiente;
        delete aux;
    }
}
