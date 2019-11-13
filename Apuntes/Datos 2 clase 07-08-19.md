**Tema: Administración de memoria**

A nivel de proceso (Programa en ejecución):

- La memoria para un proceso tiene una estructura bien definida.
- Esta estructura puede variar según el compilador (el compilador define la estructura).

- Para el lenguaje C/C++, la estructura tiene a ser:

- Memory Layout: Parámetros de línea de comando (argumentos) y variables de ambiente (variables de sólo lectura).

**#Insertar lo que falta#**

**Pointer/Puntero**

- Tipo de dato
  - `int * aPtr = (int *) malloc(sizeof(int))`
  - `Persona *p = new Persona();`
  - Todos los punteros son del mismo tamaño.
    - 32 bits -> 4 bytes
    - 64 bits -> 8 bytes
  - Operaciones:
    - Referenciador (&): Se le aplica a una variable y devuelve la dirección.
    - Desreferenciador (*): Se le aplica a un pointer y devuelve el valor apuntado.
  - Se les pone tipo para detectar errores en tiempo de compilación.
  - Un puntero sin inicializar tiene un valor conocido como **Bad Value.** 



