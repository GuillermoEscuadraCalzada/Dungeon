#include "Dungeon\Dungeon.h"
Dungeon* Dungeon::ptr = nullptr;

/*Heurística: cada nodo con valor 1 es igual a 10, si ya no hay más nodos al rededor, es mayor a 100 y se regresa hasta donde tomo esa decisión.*/

Dungeon* Dungeon::GetPtr() {
    if(!ptr)
        ptr = new Dungeon();
    return ptr;
}

/*Setear el laberitno que el agente debe de buscar*/
void Dungeon::Setup() {
    try {
        cout << "Generando mazmorra\n";
        /*Se recorre una matriz de 7 dimensiones*/
        for(int i = 0; i < lines; i++) {
            for(int j = 0; j < columns; j++) {
                if (i == 0) {/*Primera fila del arreglo*/
                    if (j == 1) //Casilla [0][1] con numero 1
                    {
                        dungeon[i][j] = 1;
                        start = new Vector2(j, i);
                    }
                    else
                        dungeon[i][j] = 0; //Todos son cero a excepción de la casilla [0][1]
                }
                else if (i == 1) { //Fila 1
                    if (j > 0 && j < 4) //Elementos mayores a [0][0] y menores a [0][4] tienen valor de 1
                        dungeon[i][j] = 1;
                    else //los elementos tienen valor de 0
                        dungeon[i][j] = 0;
                }
                else if (i == 2) { //Fila 2
                    if (j > 2 && j < columns - 1) 
                        dungeon[i][j] = 1;
                    else                        
                        dungeon[i][j] = 0;
                }
                else if (i == 3) {
                    if (j >0 && j < 4 || j == 5) 
                        dungeon[i][j] = 1;
                    else
                        dungeon[i][j] = 0;                    
                }
                else if (i == 4) {
                    if (j ==1 ||j == 3)
                        dungeon[i][j] = 1;
                    else
                        dungeon[i][j] = 0;
                }
                else if (i == 5) {
                    if (j == 1 || j > 2 && j < columns-1)
                        dungeon[i][j] = 1;
                    else
                        dungeon[i][j] = 0;
                }
                else {
                    if (j == columns - 2) {
                        dungeon[i][j] = 1;
                        end = new Vector2(j, i);
                    }
                    else {
                        dungeon[i][j] = 0;
                    }
                }
            }
        }
        
        cout << endl;
    } catch(exception & e) {
        cout << "EXCEPTION CAUGHT: " << e.what() << endl;
    }
}

/*Se añaden los elementos de la matriz que tengan el número 1 al grafo.*/
void Dungeon::searchForStart()
{
    try {
        /*Iterar por toda la matriz e ir encontrando los que tengan el número 1*/
        for (int i = 0; i < lines; i++) {
            for (int j = 0; j < columns; j++) {
                Vector2* posStart = new Vector2(j, i);
                if (posStart->posX == start->posX && posStart->posY == start->posY) { //Encontrar el elemento start dentro de la matriz
                    posibilidades.InsertaNodo(new NodoG<int>(dungeon[i][j], j, i));
                    break;
                }
            }
            if (posibilidades.GetFirst())
                break;
            
        }
        posibilidades.PrintPath(posibilidades.GetAllNodes()); //Imprimir los nodos disponibles

    }
    catch (...) {

    }
}

/*Obtiene la posición actual del jugador y lo mueve a ese lugar*/
bool Dungeon::searchNextPos(Vector2* pos, NodoG<int>* busqueda)
{
    try {
        dungeon[busqueda->position->posY][busqueda->position->posX] = -1;
        std::this_thread::sleep_for(std::chrono::milliseconds(60* 50));
        Print();

        //Pregunta si la suma de las posiciones de los elementos al rededor del nodo son igual al valor de end

        /*Pregunta si la posición en frente de la actual es menor al número total de columnas (7) para no preguntar fuera del rango en el eje x. También pregunta si en la matriz el valor es igual a 1*/
        if (pos->posX + 1 < columns && dungeon[pos->posY][pos->posX + 1] == 1) {
            NodoG<int>* derecha = new NodoG<int>(dungeon[pos->posY][pos->posX + 1], pos->posX + 1, pos->posY); //Crea un nodo con la posición siguiente al nodo búsqueda [y][x + 1]
            if (derecha->position->posX == end->posX && derecha->position->posY == end->posY) { //Pregunta si el nodo tiene la misma posición al vector end
                busqueda->position = end; //Actualiza la posición aquí
                dungeon[busqueda->position->posY][busqueda->position->posX] = -1; //Cambia el valor de la matriz a -1
                Print(); //Imprime
                return true; //Regresa verdadero
            } if (checarHijos(derecha) > 0) { //Checa si hay hijos en la casilla derecha
                busqueda->l.Add(derecha); //Añade el valor a la lista del nodo búsqueda
                busqueda->cost += 10; //Aumenta el costo en 10
            }else { //No tiene hijos válidos a la derecha
                busqueda->cost += 25; //Aumenta el costo en 25
            }

        } else { //No tiene el valor de 1, es una pared o ya fue visitado
            busqueda->cost += 25; //Aumenta el costo en 25
        }
        /*Pregunta si la posición atrás de la actual es mayor o igual a cero para preguntar que está dentro de la matriz por la parte izquierda. También pregunta si en la matriz el valor es igual a 1*/
        if (pos->posX - 1 >= 0 && dungeon[pos->posY][pos->posX - 1] == 1) { 
            NodoG<int>* izquierda = new NodoG<int>(dungeon[pos->posY][pos->posX - 1], pos->posX - 1, pos->posY); //Crea un nodo con la posición atrás al nodo búsqueda [y][x - 1]
            if (izquierda->position->posX == end->posX && izquierda->position->posY == end->posY) {
                busqueda->position = end;
                dungeon[busqueda->position->posY][busqueda->position->posX] = -1;
                Print();
                return true;
            } if (checarHijos(izquierda) > 0) {
                busqueda->l.Add(izquierda);
                busqueda->cost += 10;
            }else{
                busqueda->cost += 25;
            }
        } else { //No tiene el valor de 1, es una pared o ya fue visitado
            busqueda->cost += 25;
        }
        /*Pregunta si la posición abajo de la actual es mayor a la cantidad total de líneas (7) y que no se ha salido del arreglo. También pregunta si en la matriz el valor es igual a 1*/
        if (pos->posY + 1 < lines && dungeon[pos->posY + 1][pos->posX] == 1) { //Preguntar si hay alguien debajo
            NodoG<int>* abajo = new NodoG<int>(dungeon[pos->posY+ 1][pos->posX], pos->posX, pos->posY + 1); //Crea un nodo con la posición abajo al nodo búsqueda [y + 1][x]
            if (abajo->position->posX == end->posX && abajo->position->posY == end->posY) {
                busqueda->position = end; //Actualiza la posición
                dungeon[busqueda->position->posY][busqueda->position->posX] = -1;
                Print();
                return true;
            } if (checarHijos(abajo) > 0) {
                busqueda->l.Add(abajo);
                busqueda->cost += 10;
            }else{
               
                busqueda->cost += 25;
            }
        } else {//No tiene el valor de 1, es una pared o ya fue visitado
            busqueda->cost += 25;
        }
        /*Pregunta si la posición arriba de la actual es mayor a cero y que no se ha salido del arreglo. También pregunta si en la matriz el valor es igual a 1*/
        if (pos->posY - 1 >= 0 && dungeon[pos->posY - 1][pos->posX] == 1) {
            NodoG<int>* arriba = new NodoG<int>(dungeon[pos->posY + 1][pos->posX], pos->posX, pos->posY - 1); //Crea un nodo con la posición de arriba al nodo búsqueda [y - 1][x]
            if (arriba->position->posX == end->posX && arriba->position->posY == end->posY) {
                busqueda->position = end;
                dungeon[busqueda->position->posY][busqueda->position->posX] = -1;
                Print();
                return true;
            } if (checarHijos(arriba) > 0) {
                busqueda->l.Add(arriba);
                busqueda->cost += 10;
            } else {
                busqueda->cost += 25;
            }
        } else { //No tiene el valor de 1, es una pared o ya fue visitado
            busqueda->cost += 25;
        }

        if (busqueda->cost >= 100 || !busqueda->l.first) {
            cout << "Llegue a un punto muerto, tendre que darme la vuelta\nEstoy en la posicion ["<<pos->posY<<"]["<<pos->posX<<"]\n";
            return false;
        }
        
        busqueda->l.Print(); //Imprime todos los hijos del nodo actual
        NodoT<NodoG<int>*>* iterador = busqueda->l.first;
        while (iterador != nullptr) {
            if (searchNextPos(iterador->value->position, iterador->value)) {
                busqueda->position = iterador->value->position;
            }
            iterador = iterador->next;
        }
    }
    catch (...) {
        cout << "Algo salio mal!\n";
    }
}

/*Se decide checar los hijos del nodo en el que se está iteradndo, así se pregunta la cantidad de hijos encontrados en ese momento. Si no hay ningún hijo se regresa un cero y se le pone
 *un valor grande a la etiqueta del nodo "padre"
 *@param[NodoG<int>* nodoHijo] el nodo al que se le pregunta cuántos hijos tiene*/
int Dungeon::checarHijos(NodoG<int>* nodoHijo)
{
    int counter = 0; //Se crea un contador desde cero
    if (nodoHijo->position->posX + 1 < columns && dungeon[nodoHijo->position->posY][nodoHijo->position->posX + 1] == 1) { //Se pregunta si hay un número a la derecha y qué numero tiene, si es uno es aceptado
        counter++; //Aumenta el contador
    }
    if (nodoHijo->position->posX - 1 < columns && dungeon[nodoHijo->position->posY][nodoHijo->position->posX - 1] == 1) { //Se pregunta si hay un número a la izquierda y si tiene el valor de 1
        counter++; //Aumenta el contador
    }if (nodoHijo->position->posY + 1 < columns && dungeon[nodoHijo->position->posY +  1][nodoHijo->position->posX] == 1) { //Se pregunta si hay un número abajo y si tiene el valor de 1
        counter++; //Aumenta el contador
    }if (nodoHijo->position->posY - 1 < columns && dungeon[nodoHijo->position->posY - 1][nodoHijo->position->posX] == 1) { //Se pregunta si hay un número arriba y si tiene el valor de 1
        counter++; //Aumenta el contador
    }
    return counter; //Regresa el contador
}

/*Se actualiza constantemente las decisiones del agente*/
void Dungeon::Update() {
    try {
        while (!isOnEnd) { //Avanza hasta que el número se encuentra dentro de la posición End
            if (searchNextPos(posibilidades.GetFirst()->position,  posibilidades.GetFirst()))
                isOnEnd = !isOnEnd;
            //Print();
        }
    } catch(exception & e) {
        cout << "EXCEPTION CAUGHT: " << e.what() << endl;
    }
}

/*Se inicializa el laberinto y se imprime*/
void Dungeon::Init() {
    try {
        Setup();
        Print();
        searchForStart();
    } catch(exception & e) {
        cout << "EXCEPTION CAUGHT: " << e.what() << endl;
    }
}

/*Impresión del laberinto*/
void Dungeon::Print() {
    try {
        /*Recorrer la matriz de 7 x 7 e imprimir cada uno de sus elementos*/
        for(int i = 0; i < lines; i++) { 
            for(int j = 0; j < columns; j++) {
                cout << dungeon[i][j] <<"\t";
            }
            cout << endl << endl;
        }
        cout << endl;

    } catch(exception & e) {
        cout << "EXCEPTION CAUGHT: " << e.what() << endl;
    }
}

Dungeon::Dungeon() {
}

Dungeon::~Dungeon() {
}

