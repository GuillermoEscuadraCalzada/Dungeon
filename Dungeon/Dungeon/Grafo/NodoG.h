#pragma once
#include "ListaS.h"

class Vector2 {
public:
	int posY;
	int posX;
	Vector2(int x, int y) : posX(x), posY(y) {};
		~Vector2() {}
};


template <class T>
class NodoG
{
public:
	bool visited = false;
	T nodoData; // Esto guarda el objeto deseado
	ListaS<NodoG<T>*> l; // esto guarda los apuntadores a los hijos
	NodoG<T>* previous; //Para saber de donde vengo
	int cost; //Cuanto me costó llegar aquí
	int Bidilvl; //De cual busqueda soy
	int Danger; //De cual busqueda soy
	int x;
	int y;
	int valorDePosicion;
	Vector2* position;
	NodoG<T>(T dat) : nodoData(dat) {}

	/*Este nodo recibe un elemento a guardar y recibe una posición dentro de la matriz
	 *@param[T dat] el valor que se le quiere guardar dependiendo del template
	 *@param[int x] el valor en x dentro de la matriz
	 *@param[int y] el valor en y dentro de la matriz*/
	NodoG<T>(T dat, int x, int y) : nodoData(dat) { 
		position = new Vector2(x, y); 
		valorDePosicion = 10;
	}
	//NodoG<T>(T dat, int x, int y) : nodoData(dat), x(x), y(y) {}
	NodoG<T>(T dat, int d) : nodoData(dat), Danger(d) {}
	NodoG<T>(const NodoG<T> &n) : nodoData(n.nodoData) 
	{
		std::cout << "Se está creando copia\n";
	}
};

