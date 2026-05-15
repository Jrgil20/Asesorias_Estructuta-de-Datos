#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<vector>
using namespace std;

struct Nodo {
    int dato;
    Nodo *siguiente;	
};

// Prototipos básicos
void push(Nodo *&, int);
void pop(Nodo *&, int &);
void mostrarPila(Nodo *, string titulo = "PILA");
bool estaVacia(Nodo *);
void limpiarPila(Nodo *&);
void copiarPila(Nodo *, Nodo *&);

// Prototipos de ejercicios
void ejercicio1_invertirPila();
void ejercicio2_eliminarValor();
void ejercicio3_mayorAlFondo();
void ejercicio4_contarPares();

int main() {
    int opcion;
    
    do {
        system("clear");
        cout << "\n╔══════════════════════════════════════════════╗\n";
        cout << "║    EJEMPLOS DE EJERCICIOS CON PILAS - C++    ║\n";
        cout << "╚══════════════════════════════════════════════╝\n\n";
        
        cout << "Selecciona un ejercicio para ver su ejecución:\n\n";
        cout << "1. 🔄 Invertir una pila (2 métodos)\n";
        cout << "2. ❌ Eliminar todas las apariciones de un valor\n";
        cout << "3. 🔽 Pasar el mayor elemento al fondo\n";
        cout << "4. 📊 Contar elementos pares e impares\n";
        cout << "5. ❌ Salir\n";
        cout << "\n➤ Opción: ";
        cin >> opcion;
        
        switch(opcion) {
            case 1: ejercicio1_invertirPila(); break;
            case 2: ejercicio2_eliminarValor(); break;
            case 3: ejercicio3_mayorAlFondo(); break;
            case 4: ejercicio4_contarPares(); break;
            case 5: cout << "\n👋 Hasta luego!\n\n"; break;
            default: cout << "\n❌ Opción no válida.\n";
        }
        
        if (opcion != 5) {
            cout << "\nPresiona cualquier tecla para continuar...";
            cin.ignore();
            getchar();
        }
    } while(opcion != 5);
    
    return 0;
}

// ═══════════════════════════════════════════════════════════════
// EJERCICIO 1: Invertir una pila
// ═══════════════════════════════════════════════════════════════

void ejercicio1_invertirPila() {
    system("clear");
    cout << "\n╔══════════════════════════════════════════════╗\n";
    cout << "║  EJERCICIO 1: INVERTIR UNA PILA (2 MÉTODOS)  ║\n";
    cout << "╚══════════════════════════════════════════════╝\n\n";
    
    // Crear pila original
    Nodo *pila = NULL;
    cout << "📝 Creando la pila original: [1, 2, 3, 4, 5]\n\n";
    push(pila, 5);
    push(pila, 4);
    push(pila, 3);
    push(pila, 2);
    push(pila, 1);
    
    cout << "Estado inicial:\n";
    mostrarPila(pila, "PILA ORIGINAL");
    
    // MÉTODO 1: Con pila auxiliar
    cout << "\n\n─────────────────────────────────────────────\n";
    cout << "MÉTODO 1: USANDO UNA PILA AUXILIAR\n";
    cout << "─────────────────────────────────────────────\n";
    cout << "Proceso:\n";
    cout << "1. Pop todos los elementos de pila original → auxiliar\n";
    cout << "2. Pop todos los elementos de auxiliar → pila original\n\n";
    
    Nodo *pila1 = NULL;
    copiarPila(pila, pila1);
    
    Nodo *auxiliar1 = NULL;
    int valor;
    
    cout << "Paso 1: Trasladando a auxiliar...\n";
    Nodo *temp = pila1;
    int paso = 1;
    while (temp != NULL) {
        cout << "  [Paso " << paso << "] Pop " << temp->dato << " de original\n";
        pop(pila1, valor);
        push(auxiliar1, valor);
        cout << "  [Paso " << paso << "] Push " << valor << " a auxiliar\n";
        temp = pila1;
        paso++;
    }
    
    mostrarPila(auxiliar1, "AUXILIAR (INVERTIDA)");
    
    cout << "\nPaso 2: Trasladando de regreso a original...\n";
    paso = 1;
    temp = auxiliar1;
    while (temp != NULL) {
        cout << "  [Paso " << paso << "] Pop " << temp->dato << " de auxiliar\n";
        pop(auxiliar1, valor);
        push(pila1, valor);
        cout << "  [Paso " << paso << "] Push " << valor << " a original\n";
        temp = auxiliar1;
        paso++;
    }
    
    cout << "\n✅ Resultado final (pila invertida):\n";
    mostrarPila(pila1, "PILA INVERTIDA");
    
    limpiarPila(pila1);
}

// ═══════════════════════════════════════════════════════════════
// EJERCICIO 2: Eliminar todas las apariciones de un valor
// ═══════════════════════════════════════════════════════════════

void ejercicio2_eliminarValor() {
    system("clear");
    cout << "\n╔══════════════════════════════════════════════╗\n";
    cout << "║  EJERCICIO 2: ELIMINAR UN VALOR ESPECÍFICO    ║\n";
    cout << "╚══════════════════════════════════════════════╝\n\n";
    
    // Crear pila original
    Nodo *pila = NULL;
    cout << "📝 Creando pila: [3, 5, 2, 5, 4, 5, 1]\n";
    cout << "🎯 Valor a eliminar: 5\n\n";
    
    push(pila, 1);
    push(pila, 5);
    push(pila, 4);
    push(pila, 5);
    push(pila, 2);
    push(pila, 5);
    push(pila, 3);
    
    cout << "Estado inicial:\n";
    mostrarPila(pila, "PILA ORIGINAL");
    
    // Proceso de eliminación
    cout << "\n─────────────────────────────────────────────\n";
    cout << "PROCESO DE ELIMINACIÓN CON PILA AUXILIAR\n";
    cout << "─────────────────────────────────────────────\n";
    
    Nodo *auxiliar = NULL;
    int valor;
    int contador_eliminados = 0;
    int paso = 1;
    
    cout << "Paso 1: Trasladando elementos (sin el 5)...\n";
    while (!estaVacia(pila)) {
        pop(pila, valor);
        cout << "  [" << paso << "] Pop " << valor;
        if (valor != 5) {
            cout << " → Se guarda en auxiliar\n";
            push(auxiliar, valor);
        } else {
            cout << " → ❌ SE ELIMINA (coincide con 5)\n";
            contador_eliminados++;
        }
        paso++;
    }
    
    cout << "\n✅ Se eliminaron " << contador_eliminados << " apariciones de 5.\n";
    cout << "\nPaso 2: Devolviendo a la pila original...\n";
    paso = 1;
    while (!estaVacia(auxiliar)) {
        pop(auxiliar, valor);
        cout << "  [" << paso << "] Pop " << valor << " de auxiliar → Push a original\n";
        push(pila, valor);
        paso++;
    }
    
    cout << "\n✅ Resultado final:\n";
    mostrarPila(pila, "PILA SIN 5");
    
    limpiarPila(pila);
}

// ═══════════════════════════════════════════════════════════════
// EJERCICIO 3: Pasar el mayor elemento al fondo
// ═══════════════════════════════════════════════════════════════

void ejercicio3_mayorAlFondo() {
    system("clear");
    cout << "\n╔══════════════════════════════════════════════╗\n";
    cout << "║  EJERCICIO 3: PASAR EL MAYOR AL FONDO        ║\n";
    cout << "╚══════════════════════════════════════════════╝\n\n";
    
    // Crear pila original
    Nodo *pila = NULL;
    cout << "📝 Creando pila: [3, 7, 2, 9, 1]\n\n";
    
    push(pila, 1);
    push(pila, 9);
    push(pila, 2);
    push(pila, 7);
    push(pila, 3);
    
    cout << "Estado inicial:\n";
    mostrarPila(pila, "PILA ORIGINAL");
    
    cout << "\n─────────────────────────────────────────────\n";
    cout << "BUSCANDO EL MAYOR Y MOVIÉNDOLO AL FONDO\n";
    cout << "─────────────────────────────────────────────\n";
    
    // Encontrar el mayor
    Nodo *temp = pila;
    int mayor = temp->dato;
    cout << "\n🔍 Buscando el elemento mayor:\n";
    int paso = 1;
    while (temp != NULL) {
        cout << "   [Paso " << paso << "] Revisando: " << temp->dato;
        if (temp->dato > mayor) {
            mayor = temp->dato;
            cout << " ← ✅ Es el mayor hasta ahora!";
        }
        cout << "\n";
        temp = temp->siguiente;
        paso++;
    }
    
    cout << "\n🏆 El mayor elemento es: " << mayor << "\n";
    
    // Extraer el mayor
    cout << "\n📤 Extrayendo el mayor de la pila...\n";
    Nodo *auxiliar = NULL;
    int valor;
    while (!estaVacia(pila)) {
        pop(pila, valor);
        cout << "   Pop: " << valor;
        if (valor != mayor) {
            push(auxiliar, valor);
            cout << " (guardado en auxiliar)\n";
        } else {
            cout << " (este es el mayor, lo guardaremos para el final)\n";
        }
    }
    
    // Devolver a la pila
    cout << "\n📥 Devolviendo elementos a la pila (el mayor irá al fondo)...\n";
    paso = 1;
    while (!estaVacia(auxiliar)) {
        pop(auxiliar, valor);
        cout << "   [" << paso << "] Push " << valor << "\n";
        push(pila, valor);
        paso++;
    }
    
    // Poner el mayor al final
    cout << "   [" << paso << "] Push " << mayor << " (AL FONDO)\n";
    push(pila, mayor);
    
    cout << "\n✅ Resultado final:\n";
    mostrarPila(pila, "MAYOR AL FONDO");
    
    limpiarPila(pila);
}

// ═══════════════════════════════════════════════════════════════
// EJERCICIO 4: Contar elementos pares e impares
// ═══════════════════════════════════════════════════════════════

void ejercicio4_contarPares() {
    system("clear");
    cout << "\n╔══════════════════════════════════════════════╗\n";
    cout << "║  EJERCICIO 4: CONTAR PARES E IMPARES         ║\n";
    cout << "╚══════════════════════════════════════════════╝\n\n";
    
    // Crear pila original
    Nodo *pila = NULL;
    cout << "📝 Creando pila: [1, 2, 3, 4, 5, 6, 7, 8]\n\n";
    
    int numeros[] = {8, 7, 6, 5, 4, 3, 2, 1};
    for (int i = 0; i < 8; i++) {
        push(pila, numeros[i]);
    }
    
    cout << "Estado inicial:\n";
    mostrarPila(pila, "PILA ORIGINAL");
    
    cout << "\n─────────────────────────────────────────────\n";
    cout << "CLASIFICANDO PARES E IMPARES\n";
    cout << "─────────────────────────────────────────────\n";
    
    Nodo *pila_pares = NULL;
    Nodo *pila_impares = NULL;
    int valor;
    int paso = 1;
    
    cout << "\nProcesando elementos:\n";
    while (!estaVacia(pila)) {
        pop(pila, valor);
        cout << "   [Paso " << paso << "] Pop " << valor;
        
        if (valor % 2 == 0) {
            cout << " → PAR ✅ (guardado en pila_pares)\n";
            push(pila_pares, valor);
        } else {
            cout << " → IMPAR ❌ (guardado en pila_impares)\n";
            push(pila_impares, valor);
        }
        paso++;
    }
    
    cout << "\n═══════════════════════════════════════════════\n";
    cout << "RESULTADO FINAL:\n";
    cout << "═══════════════════════════════════════════════\n\n";
    
    // Mostrar pilas
    mostrarPila(pila_pares, "PILA PARES");
    cout << "\n";
    mostrarPila(pila_impares, "PILA IMPARES");
    
    // Contar
    int count_pares = 0, count_impares = 0;
    Nodo *temp = pila_pares;
    while (temp != NULL) {
        count_pares++;
        temp = temp->siguiente;
    }
    temp = pila_impares;
    while (temp != NULL) {
        count_impares++;
        temp = temp->siguiente;
    }
    
    cout << "\n📊 ESTADÍSTICAS:\n";
    cout << "   Total de pares: " << count_pares << "\n";
    cout << "   Total de impares: " << count_impares << "\n";
    cout << "   Total de elementos: " << (count_pares + count_impares) << "\n";
    
    limpiarPila(pila_pares);
    limpiarPila(pila_impares);
}

// ═══════════════════════════════════════════════════════════════
// FUNCIONES AUXILIARES
// ═══════════════════════════════════════════════════════════════

void push(Nodo *&pila, int n) {
    Nodo *nuevo_nodo = new Nodo();
    nuevo_nodo->dato = n;
    nuevo_nodo->siguiente = pila;
    pila = nuevo_nodo;
}

void pop(Nodo *&pila, int &n) {
    if (pila != NULL) {
        Nodo *aux = pila;
        n = aux->dato;
        pila = aux->siguiente;
        delete aux;
    }
}

bool estaVacia(Nodo *pila) {
    return pila == NULL;
}

void limpiarPila(Nodo *&pila) {
    while (pila != NULL) {
        Nodo *aux = pila;
        pila = pila->siguiente;
        delete aux;
    }
}

void copiarPila(Nodo *origen, Nodo *&destino) {
    if (origen == NULL) return;
    copiarPila(origen->siguiente, destino);
    push(destino, origen->dato);
}

void mostrarPila(Nodo *pila, string titulo) {
    cout << "\n┌─ " << titulo << " ─┐\n";
    
    if (pila == NULL) {
        cout << "│  [VACÍA]  │\n";
    } else {
        cout << "│ ┌─────┐   │\n";
        int contador = 0;
        Nodo *actual = pila;
        
        while (actual != NULL) {
            cout << "│ │ " << (actual->dato < 10 ? " " : "") << actual->dato << "  │";
            if (contador == 0) cout << " ← TOPE";
            cout << "\n";
            
            if (actual->siguiente != NULL) {
                cout << "│ ├─────┤   │\n";
            }
            
            actual = actual->siguiente;
            contador++;
        }
        
        cout << "│ └─────┘   │\n";
    }
    
    cout << "└───────────┘\n";
}
