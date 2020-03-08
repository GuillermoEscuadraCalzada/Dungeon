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
bool Dungeon::searchNextPos(Vector2* pos)
{
    try {
        //Pregunta si la suma de las posiciones de los elementos al rededor del nodo son igual al valor de end
        if (new Vector2(pos->posX + 1, pos->posY ) == end || new Vector2(pos->posX - 1, pos->posY) == end || new Vector2(pos->posX, pos->posY + 1) == end || new Vector2(pos->posX , pos->posY - 1) == end) { 
            return true;
        }
        /*Pregunta si la posición en frente de la actual es menor al número total de columnas (7) para no preguntar fuera del rango en el eje x. También pregunta si en la matriz el valor es igual a 1*/
        if (pos->posX + 1 < columns && dungeon[pos->posY][pos->posX + 1] == 1) {
            posibilidades.GetFirst()->l.Add(new NodoG<int>(dungeon[pos->posY][pos->posX + 1], pos->posY, pos->posX + 1));

        }
        /*Pregunta si la posición atrás de la actual es mayor o igual a cero para preguntar que está dentro de la matriz por la parte izquierda. También pregunta si en la matriz el valor es igual a 1*/
        if (pos->posX - 1 >= 0 && dungeon[pos->posY][pos->posX - 1] == 1) { 
            posibilidades.GetFirst()->l.Add(new NodoG<int>(dungeon[pos->posY][pos->posX - 1], pos->posY, pos->posX - 1));
        }
        /*Pregunta si la posición abajo de la actual es mayor a la cantidad total de líneas (7) y que no se ha salido del arreglo. También pregunta si en la matriz el valor es igual a 1*/
        if (pos->posY + 1 < lines && dungeon[pos->posY + 1][pos->posX] == 1) { //Preguntar si hay alguien debajo
            posibilidades.GetFirst()->l.Add(new NodoG<int>(dungeon[pos->posY + 1][pos->posX], pos->posY + 1, pos->posX));
        }
        /*Pregunta si la posición arriba de la actual es mayor a cero y que no se ha salido del arreglo. También pregunta si en la matriz el valor es igual a 1*/
        if (pos->posY - 1 >= 0 && dungeon[pos->posY - 1][pos->posX] == 1) {
            posibilidades.GetFirst()->l.Add(new NodoG<int>(dungeon[pos->posY - 1][pos->posX], pos->posY - 1, pos->posX));
        }
        posibilidades.GetFirst()->l.Print(); //Imprime todos los hijos del nodo actual
        NodoT<NodoG<int>*>* iterador = posibilidades.GetFirst()->l.first;
        while (iterador != nullptr) {
            dungeon[posibilidades.GetFirst()->position->posY][posibilidades.GetFirst()->position->posX] = -1;

            posibilidades.GetFirst()->position = iterador->value->position;
            iterador = iterador->next;
        }
        return false;
    }
    catch (...) {
        cout << "Algo salio mal!\n";
    }
}

/*Se actualiza constantemente las decisiones del agente*/
void Dungeon::Update() {
    try {
        while (!isOnEnd) {
            if (searchNextPos(posibilidades.GetFirst()->position));
            isOnEnd = !isOnEnd;
            Print();
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
                cout << dungeon[i][j] <<" ";
            }
            cout << endl;
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

