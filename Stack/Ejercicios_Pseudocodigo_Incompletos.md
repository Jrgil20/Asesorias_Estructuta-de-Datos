# Ejercicios de Pseudocódigo Incompletos — Pilas

Este documento contiene pseudocódigos **con partes faltantes** que debes completar. Los huecos incluyen condiciones, retornos, inicializaciones y lógica central.

---

## EJERCICIO 1: Verificar si la pila está vacía

```
funcion estaVacia(pila):
    __________________ // ¿Qué condición verifica si está vacía?
        return true
    __________________ 
        return false
```

**Pista:** Compara la pila con algo.

---

## EJERCICIO 2: Insertar un elemento (PUSH)

```
funcion push(pila, valor):
    nuevo_nodo = crear nuevo Nodo()
    nuevo_nodo.dato = __________________
    nuevo_nodo.siguiente = __________________
    pila = nuevo_nodo
```

**Pista:** El dato va al nodo, y el siguiente apunta a...

---

## EJERCICIO 3: Extraer un elemento (POP)

```
funcion pop(pila, valor):
    si pila está vacía:
        __________________ // ¿Qué haces si no hay qué extraer?
    
    auxiliar = pila
    valor = __________________
    pila = __________________
    delete auxiliar
```

**Pista:** Necesitas guardar algo, avanzar el puntero y liberar memoria.

---

## EJERCICIO 4: Obtener el tope sin modificar

```
funcion tope(pila):
    si __________________:
        return -1 // o un error
    
    __________________ pila->dato
```

**Pista:** Verifica si está vacía y devuelve qué cosa.

---

## EJERCICIO 5: Contar elementos en la pila

```
funcion contarElementos(pila):
    contador = 0
    actual = pila
    
    mientras __________________:
        contador = contador + 1
        actual = __________________
    
    __________________ contador
```

**Pista:** ¿Cuándo dejas de contar? ¿A dónde avanzas?

---

## EJERCICIO 6: Buscar un valor en la pila

```
funcion buscar(pila, valor):
    actual = pila
    
    mientras actual != NULL:
        si __________________:
            __________________ true
        actual = actual->siguiente
    
    __________________ false
```

**Pista:** ¿Qué comparas? ¿Cuándo encontraste lo que buscas?

---

## EJERCICIO 7: Mostrar todos los elementos recursivamente

```
funcion mostrarRecursivo(pila):
    si __________________:
        return
    
    __________________ pila->dato  // mostrar el dato
    mostrarRecursivo(pila->siguiente)
```

**Pista:** Verifica vacío, luego imprime, luego avanzas.

---

## EJERCICIO 8: Invertir pila (método 1 con auxiliar)

```
funcion invertir(pila):
    auxiliar = pila vacía
    
    mientras pila no está vacía:
        valor = pop(pila)
        __________________ 
    
    mientras auxiliar no está vacía:
        valor = pop(auxiliar)
        __________________
```

**Pista:** Push y pop, pero en orden diferente.

---

## EJERCICIO 9: Invertir pila (método 2 recursivo)

```
funcion invertirRecursivo(pila):
    si __________________:
        return
    
    valor = pop(pila)
    invertirRecursivo(pila)
    insertarFondo(pila, valor)

funcion insertarFondo(pila, valor):
    si __________________:
        push(pila, valor)
        return
    
    temp = pop(pila)
    insertarFondo(pila, valor)
    __________________
```

**Pista:** Base: pila vacía. Recursión: extrae, recorre, inserta.

---

## EJERCICIO 10: Limpiar completamente la pila

```
funcion limpiar(pila):
    mientras pila != NULL:
        auxiliar = __________________
        pila = __________________
        delete __________________
```

**Pista:** Guarda, avanza, borra.

---

## EJERCICIO 11: Copiar una pila a otra

```
funcion copiar(pilaOrigen, pilaDestino):
    si pilaOrigen == NULL:
        return
    
    __________________ // recursión hacia el final
    push(pilaDestino, pilaOrigen->dato)
```

**Pista:** Llama recursivo primero, luego inserta.

---

## EJERCICIO 12: Eliminar todas las apariciones de un valor

```
funcion eliminarValor(pila, valorAEliminar):
    auxiliar = pila vacía
    
    mientras pila no está vacía:
        valor = pop(pila)
        si __________________:
            __________________  // solo si NO es igual
        else:
            continue  // salta al siguiente
    
    mientras auxiliar no está vacía:
        valor = pop(auxiliar)
        push(pila, valor)
```

**Pista:** ¿Qué condición evita insertar el valor que buscas eliminar?

---

## EJERCICIO 13: Encontrar el mayor elemento

```
funcion encontrarMayor(pila):
    si __________________:
        return -1  // pila vacía
    
    mayor = pila->dato
    actual = pila->siguiente
    
    mientras __________________:
        si actual->dato > mayor:
            __________________
        actual = actual->siguiente
    
    __________________ mayor
```

**Pista:** Compara cada elemento con el mayor que has visto.

---

## EJERCICIO 14: Sumar todos los elementos

```
funcion sumarElementos(pila):
    si __________________:
        return 0
    
    valor = pop(pila)
    suma = valor + sumarElementos(pila)
    push(pila, valor)
    
    __________________ suma
```

**Pista:** Recursión: base es pila vacía, suma parcial + resto.

---

## EJERCICIO 15: Contar elementos pares

```
funcion contarPares(pila):
    si __________________:
        return 0
    
    valor = pop(pila)
    
    contador = contarPares(pila)  // cuenta el resto recursivo
    
    si __________________:  // ¿Es par?
        contador = contador + 1
    
    push(pila, valor)
    __________________ contador
```

**Pista:** Modulo 2 te ayuda con la paridad.

---

## EJERCICIO 16: Pasar el mayor elemento al fondo

```
funcion mayorAlFondo(pila):
    si __________________:
        return
    
    valor = pop(pila)
    mayorAlFondo(pila)
    
    si pila está vacía:
        push(pila, valor)
    else:
        tope = pop(pila)
        si __________________:  // ¿Es valor mayor que tope?
            push(pila, tope)
            push(pila, valor)
        else:
            push(pila, valor)
            __________________
```

**Pista:** Compara y decide quién va primero.

---

## EJERCICIO 17: Verificar si es palíndromo

```
funcion esPalindromo(pila):
    if pila == NULL:
        return true
    
    cola = convertirACola(pila)  // convierte pila a cola
    
    mientras pila no está vacía y cola no está vacía:
        val_pila = pop(pila)
        val_cola = dequeue(cola)
        
        si __________________:  // ¿Son diferentes?
            __________________
    
    __________________ true
```

**Pista:** Compara de ambos lados.

---

## EJERCICIO 18: Intercalar dos pilas

```
funcion intercalar(pila1, pila2, pilaResultado):
    mientras __________________ and __________________:
        valor1 = pop(pila1)
        valor2 = pop(pila2)
        
        push(pilaResultado, valor1)
        push(pilaResultado, valor2)
    
    // Vacía lo que quede
    mientras pila1 no está vacía:
        __________________
    
    mientras pila2 no está vacía:
        valor = pop(pila2)
        __________________
```

**Pista:** Ambas tienen elementos para intercalar. Luego completa el resto.

---

## EJERCICIO 19: Rotación de N posiciones

```
funcion rotar(pila, n):
    para i = 1 hasta n:
        si pila está vacía:
            __________________
        
        valor = pop(pila)
        // Necesitas insertar al fondo...
        insertarFondo(pila, valor)

funcion insertarFondo(pila, valor):
    si __________________:
        push(pila, valor)
        return
    
    temp = pop(pila)
    insertarFondo(pila, valor)
    __________________
```

**Pista:** Mueve un elemento al fondo, N veces.

---

## EJERCICIO 20: Torres de Hanoi (simplificado)

```
funcion hanoi(n, origen, destino, auxiliar):
    si __________________:  // caso base
        valor = pop(origen)
        push(destino, valor)
        mostrar movimiento
        return
    
    hanoi(n-1, origen, auxiliar, destino)
    
    valor = pop(origen)
    push(destino, valor)
    mostrar movimiento
    
    __________________  // llamada recursiva final
```

**Pista:** Mueve n-1, mueve el disco grande, mueve n-1 al destino.

---

## 📝 Cómo usar este documento

1. **Copia cada pseudocódigo** en tu libreta o editor de texto
2. **Llena los huecos** (representados por `__________`)
3. **Verifica con el README.md** si tu respuesta es correcta
4. **Intenta implementar en C++** después de completar el pseudocódigo

---

## 🎯 Soluciones (desplázate para ver después de intentar)

<details>
<summary>EJERCICIO 1: Verificar si está vacía</summary>

```
funcion estaVacia(pila):
    si pila == NULL
        return true
    else
        return false
```
</details>

<details>
<summary>EJERCICIO 2: Push</summary>

```
funcion push(pila, valor):
    nuevo_nodo = crear nuevo Nodo()
    nuevo_nodo.dato = valor
    nuevo_nodo.siguiente = pila
    pila = nuevo_nodo
```
</details>

<details>
<summary>EJERCICIO 3: Pop</summary>

```
funcion pop(pila, valor):
    si pila está vacía:
        return  // o mostrar error
    
    auxiliar = pila
    valor = auxiliar.dato
    pila = auxiliar.siguiente
    delete auxiliar
```
</details>

<details>
<summary>EJERCICIO 4: Obtener tope</summary>

```
funcion tope(pila):
    si pila == NULL:
        return -1
    
    return pila->dato
```
</details>

<details>
<summary>EJERCICIO 5: Contar elementos</summary>

```
funcion contarElementos(pila):
    contador = 0
    actual = pila
    
    mientras actual != NULL:
        contador = contador + 1
        actual = actual->siguiente
    
    return contador
```
</details>

<details>
<summary>EJERCICIO 6: Buscar valor</summary>

```
funcion buscar(pila, valor):
    actual = pila
    
    mientras actual != NULL:
        si actual->dato == valor:
            return true
        actual = actual->siguiente
    
    return false
```
</details>

<details>
<summary>EJERCICIO 7: Mostrar recursivo</summary>

```
funcion mostrarRecursivo(pila):
    si pila == NULL:
        return
    
    print(pila->dato)
    mostrarRecursivo(pila->siguiente)
```
</details>

<details>
<summary>EJERCICIO 8: Invertir (auxiliar)</summary>

```
funcion invertir(pila):
    auxiliar = pila vacía
    
    mientras pila no está vacía:
        valor = pop(pila)
        push(auxiliar, valor)
    
    mientras auxiliar no está vacía:
        valor = pop(auxiliar)
        push(pila, valor)
```
</details>

<details>
<summary>EJERCICIO 9: Invertir recursivo</summary>

```
funcion invertirRecursivo(pila):
    si pila == NULL:
        return
    
    valor = pop(pila)
    invertirRecursivo(pila)
    insertarFondo(pila, valor)

funcion insertarFondo(pila, valor):
    si pila == NULL:
        push(pila, valor)
        return
    
    temp = pop(pila)
    insertarFondo(pila, valor)
    push(pila, temp)
```
</details>

<details>
<summary>EJERCICIO 10: Limpiar</summary>

```
funcion limpiar(pila):
    mientras pila != NULL:
        auxiliar = pila
        pila = pila->siguiente
        delete auxiliar
```
</details>

---

¡Ánimo! Completa estos ejercicios antes de mirar las soluciones. 💪
