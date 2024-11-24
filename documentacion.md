# DOCUMENTACIÓN
Hecho por: Federico Martín Cortázar (311721)

| PROBLEMA | RESULTADO |
|----------|-----------|
| 1        | Completo  |
| 2        | Completo  |
| 3        | Completo  |
| 4        | Completo  |
| 5        | Completo  |
| 6        | Completo  |
| 7        | Completo  |
| 8        | Completo  |
| 9        | Completo  |
| 10       | Completo  |


## EJERCICIO 1
Para hallar la solución del ejercicio 1 cree un árbol AVL donde los elementos se insertan según su ID, a su vez dicho árbol lleva la cuenta de cuantos libros están habilitados y cuantos no. El orden de las operaciones de inserción, búsqueda, y actualización de estado se realicen en tiempo O(log N) siendo N la cantidad de nodos ya que a medida que se llega a un nuevo nodo preguntas si tu ID es mayor, menor o igual, si es igual haces la operación que tengas que hacer, en otro caso vas a la derecha o a la izquierda dependiendo de si tu ID es mayor o menor y el orden de la operación COUNT es $O(1)pc$  ya que al tener la cantidad de libros habilitados y cuantos no se accede siempre en $O(1)pc$ , y para tener el total solo hay que sumar estos dos números.
Para hacer este ejercicio tome la implementación de AVL dada en clase.

## EJERCICIO 2
Para hallar la solución del ejercicio 2 cree una tabla de hash con hashing cerrado y con una resolución de colisiones mediante doble hash, Además tiene la cantidad de libros habilitados y la cantidad de libros deshabilitados y cuál es el tamaño del array. El orden para las operaciones de inserción, búsqueda y actualización de estado es $O(1)cp$ ya que es este el orden que tiene la tabla de hash para estas funciones y el orden de la operación COUNT es de $O(1)pc$ ya que al tener la cantidad de libros habilitados y cuantos no se accede siempre en $O(1)pc$ , y para tener el total solo hay que sumar estos dos números.
Para hacer este ejercicio tome lo que dimos en clase de hash abierto y lo pase a hash cerrado.

## EJERCICIO 3
Para hallar la solución de este ejercicio utilice un min heap ya que te pide que ordenes los objetos de menor a mayor dependiendo de ciertos criterios, dicho min heap guarda un id y un precio en cada posición del array. El orden de esta solución es de $O(N logN)pc$ siendo $N$ la cantidad de datos ya que insertamos $N$ datos y la función de insertar en un heap tiene $O(logN)pc$.
Para hacer este ejercicio tome lo que dimos en clase sobre heap y lo modifique a lo que se pide.

## EJERCICIO 4
Para hallar la solución de este ejercicio utilice un min heap con una tabla de hash con hashing abierto ya que te pide que ordenes los objetos de menor a mayor dependiendo de ciertos criterios y se puede cambiar algunos valores de un dato ya ingresado, por lo que necesito la tabla para guardar la posición de los datos en el array para acceder en $O(1)cp$, dicho min heap guarda un id, una prioridad, si es para llevar y que tiene el pedido en cada posición del array. El orden de esta solución es de $O(N logN)cp$ siendo $N$ la cantidad de elementos  ya que insertamos $N$ datos y la función de insertar en un heap tiene $O(logN)pc$ y el orden es de $O(N2)pc$ si la tabla de hash tiene una función de hash mala por lo que tiene un $O(N)$ y se ingresan $N$ veces $C$ por lo que hay que aplicar $N$ veces la tabla de hash para encontrar la posición en el array.

## EJERCICIO 5


## EJERCICIO 6

## EJERCICIO 7

## EJERCICIO 8

## EJERCICIO 9

## EJERCICIO 10
