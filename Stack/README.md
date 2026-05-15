# Pilas — Repaso y Ejercicios

Este README contiene un listado de puntos clave para repasar antes del examen, seguido de ejercicios desafiantes (solo enunciados, sin soluciones) y varios pseudocódigos útiles.

---

## Puntos que repasar antes del examen

1. Definición de la estructura (`struct`) de nodo para pilas enlazadas
   - Cómo se genera el nodo
   - Uso del puntero siguiente

2. Creación de una pila usando punteros
   - Inicialización (pila nula = pila vacía)
   - Representación visual

3. Funciones básicas
   - `push`: agregar un elemento al tope
   - `pop`: quitar el tope y devolver el valor
   - `tope` (top): consultar el valor al tope sin quitarlo

4. Recorridos de la pila
   - Recorridos recursivos (sin modificar la pila)
   - Recorridos que vacían la pila (pop recursivo)

5. Búsqueda y eliminación de valores
   - Usando pila auxiliar
   - Con recursividad
   - Garantizar que la pila conserva el orden original

6. Manejo adecuado de memoria
   - Creación con `new`
   - Eliminación con `delete`
   - Limpieza total de la pila

7. Restaurar la pila tras procesamiento
   - Cómo usar una pila auxiliar para devolver los valores conservando el orden

8. Visualización y trazabilidad
   - Dibujar el contenido de la pila tras cada operación
   - Dry-runs a mano

9. Diferencias entre pilas y otras estructuras (colas, listas)
   - Cuándo usar cada una

---

## Ejercicios complejos de práctica (sin soluciones)

### 1. Intercambiar elementos según su paridad
Enunciado: Dada una pila, intercambia la posición de los elementos pares con los impares, respetando el orden relativo entre pares e impares.
Ejemplo: Para [3, 4, 7, 2, 6, 5] (tope a la izquierda) el resultado debe ser [4, 3, 2, 7, 5, 6].
Pista: Usa dos pilas auxiliares (`par`, `impar`), procesa la pila original y reconstruye.

---

### 2. Separar la pila en dos según el valor módulo 3
Enunciado: Dada una pila, separa los elementos que son múltiplos de 3 en una pila, y el resto en otra. Finalmente muestra ambas pilas.

---

### 3. Determinar si una pila es palíndromo
Enunciado: Implementa una función que determine si los valores en la pila (de cima a base) leen igual en ambos sentidos.
Pista: Usa una lista/array temporal y compara sin alterar el orden final de la pila.

---

### 4. Sumar los elementos de dos pilas en una nueva pila
Enunciado: Dadas dos pilas del mismo tamaño, crea una tercera cuya cima es la suma de las respectivas posiciones.

---

### 5. Invertir una pila usando solo funciones básicas
Enunciado: Reescribe la pila de forma que su cima sea su base original. No se permiten estructuras de datos persistentes extra aparte de variables temporales.

---

### 6. Eliminar todas las apariciones de un valor
Enunciado: Borra todas las apariciones de un número, sin perder el orden del resto de elementos.

---

### 7. Pasar el mayor elemento al fondo de la pila
Enunciado: Crea una función que coloque el mayor elemento de la pila en el fondo, sin usar estructuras permanentes extra (puedes usar recursividad o una pila auxiliar temporal).

---

### 8. (Bonus) Contar secuencias crecientes
Enunciado: Cuenta cuántas subsecuencias estrictamente crecientes consecutivas hay en la pila (de cima a base). Cada subsecuencia debe tener al menos dos elementos.

---

### 9. Duplicar valores mayores a un umbral
Enunciado: Dada una pila y un valor umbral X, duplica cada elemento cuyo valor sea mayor que X, manteniendo su posición relativa.
Ejemplo: Pila [2, 5, 3, 8, 1] con X=4 → resultado [2, 5, 5, 3, 8, 8, 1]

---

### 10. Verificar si la pila es simétrica en estructura
Enunciado: Determina si la cantidad de elementos en cada "nivel" de la pila es simétrica. (Nivel = número de nodos a la misma distancia del tope).

---

### 11. Combinar dos pilas intercaladas
Enunciado: Dadas dos pilas A y B, crea una tercera pila C que contenga los elementos intercalados (primero de A, luego de B, etc).
Ejemplo: A=[1,2,3], B=[4,5,6] (tope a izq) → C=[1,4,2,5,3,6]

---

### 12. Encontrar el k-ésimo elemento desde el tope
Enunciado: Implementa una función que devuelva el valor del k-ésimo elemento desde el tope, sin modificar la pila. Usa recursividad.

---

### 13. Eliminar elementos que están entre dos valores
Enunciado: Dada una pila, elimina todos los elementos cuyo valor esté entre dos números X e Y (incluidos).
Ejemplo: Pila [1,5,3,8,2,6], X=2, Y=5 → resultado [1,8,6]

---

### 14. Rotar la pila N posiciones
Enunciado: Gira la pila N posiciones hacia arriba. (El tope se convierte en N-ésimo elemento).
Ejemplo: Pila [1,2,3,4,5] rotada 2 → [3,4,5,1,2]

---

### 15. (Reto) Resolver Torres de Hanoi visualizando con pilas
Enunciado: Implementa el clásico problema de Torres de Hanoi usando tres pilas. Muestra visualmente cada movimiento de discos.

---

## Pseudocódigos útiles (no son soluciones completas, son guías)

1.

funcion invertir(pila):
    auxiliar = pila vacia

    mientras pila no esta vacia:
        valor = pop(pila)
        push(auxiliar, valor)

    // Ahora auxiliar tiene los elementos en orden inverso
    // Copiamos de auxiliar a pila para restaurar el nombre de la variable original
    mientras auxiliar no esta vacia:
        valor = pop(auxiliar)
        push(pila, valor)

2.

funcion invertir(pila):
    si pila está vacía:
        return

    valor = pop(pila)
    invertir(pila)
    insertarFondo(pila, valor)

funcion insertarFondo(pila, valor):
    si pila está vacía:
        push(pila, valor)
        return
    temp = pop(pila)
    insertarFondo(pila, valor)
    push(pila, temp)

3.

funcion mayorAlFondo(pila):
    si pila está vacía:
        return

    valor = pop(pila)
    mayorAlFondo(pila)

    // Al volver: si la pila está vacía o el tope es menor que valor, push valor.
    // Sino, comparar y dejar el mayor al fondo.
    si pila está vacía:
        push(pila, valor)
    sino:
        tope = pop(pila)
        si valor > tope:
            push(pila, tope)
            push(pila, valor)
        sino:
            push(pila, valor)
            push(pila, tope)

4.

funcion contarSecuenciasCrecientes(pila, contador, anterior, enSecuencia):
    si pila está vacía:
        return contador

    actual = pop(pila)
    si anterior != nulo y actual > anterior:
        enSecuencia = enSecuencia + 1
        // Si acabamos de tener una secuencia de al menos 2, cuenta una sola vez
        if enSecuencia == 2:
            contador = contador + 1
    else:
        enSecuencia = 1 // empezamos nueva secuencia

    contador = contarSecuenciasCrecientes(pila, contador, actual, enSecuencia)
    push(pila, actual)
    return contador

---

Si quieres, puedo:
- Añadir ejemplos de entrada/salida para cada ejercicio.
- Preparar soluciones comentadas (por ejercicio o por grupo).
- Implementar código C++ de referencia en Stack/.

Indica qué prefieres y lo hago a continuación.

---

## 📌 Archivos de Código C++ incluidos

### 1. **StackMenu.cpp** — Gestor interactivo de pilas
Programa con menú gráfico interactivo que permite:
- ➕ Insertar números
- ➖ Extraer del tope
- 👀 Visualizar la pila
- 🔄 Ver el tope sin extraer
- 🗑️ Limpiar completamente

**Compilación:**
```bash
g++ -o StackMenu StackMenu.cpp
./StackMenu
```

**Características:**
- Interfaz visual con caracteres especiales (┌─┐│└─┘)
- Muestra el estado de la pila en tiempo real
- Mensajes descriptivos paso a paso

---

### 2. **EjerciciosEjemplos.cpp** — Ejemplos de ejercicios resueltos
Contiene 4 ejercicios completos con visualización gráfica:

1. **Invertir una pila** (2 métodos)
   - Método 1: Con pila auxiliar
   - Método 2: Recursivo (en pseudocódigo en el README)

2. **Eliminar todas las apariciones de un valor**
   - Usa pila auxiliar
   - Muestra cada paso

3. **Pasar el mayor elemento al fondo**
   - Busca y extrae el máximo
   - Reconstruye con el mayor al fondo

4. **Contar elementos pares e impares**
   - Clasifica en dos pilas
   - Muestra estadísticas

**Compilación:**
```bash
g++ -o EjerciciosEjemplos EjerciciosEjemplos.cpp
./EjerciciosEjemplos
```

**Características:**
- Menú con selección de ejercicios
- Visualización paso a paso
- Diagramas ASCII para ver la pila
- Explicación del proceso

---

## 🎯 Cómo usar estos archivos

1. **Para repaso teórico:**
   - Lee el README.md completo (puntos + pseudocódigos)
   - Dibuja las pilas en papel mientras estudias

2. **Para ver funcionamiento:**
   - Ejecuta `StackMenu.cpp` para jugar interactivamente
   - Ejecuta `EjerciciosEjemplos.cpp` para ver soluciones visuales

3. **Para practicar:**
   - Implementa los ejercicios del 1 al 15 sin mirar las soluciones
   - Luego compara con las implementaciones en `EjerciciosEjemplos.cpp`

---

## 💡 Recomendaciones para el examen

✅ Asegúrate de:
- Entender la estructura del nodo (`struct`)
- Diferenciar push, pop y top
- Dominar el manejo de memoria (new/delete)
- Practicar recursividad con pilas
- Visualizar cada operación en papel

❌ Evita:
- Confundir push y pop
- Olvidar liberar memoria (memory leaks)
- Mezclar LIFO con FIFO (pila vs cola)
- No verificar pila vacía antes de pop
