#ifndef DUNGEON_H
#define DUNGEON_H
#include <iostream>
#include <chrono>
#include <thread>
#include "Grafo/Grafo.h"
using namespace std;

class Dungeon {

public:
	static Dungeon* GetPtr();
	void Update();
	void Init();
	void Print();
private:
	const static int lines = 7;
	const static int columns = 7;
	int dungeon[lines][columns];
	Vector2* start, * end;
	Grafo<int> posibilidades;
	void Setup();
	void searchForStart();
	bool searchNextPos(Vector2* pos, NodoG<int>* nodoBusqueda);
	int checarHijos(NodoG<int>* nodoHijo);
	bool isOnEnd = false;
	Dungeon();
	~Dungeon();
	static Dungeon* ptr;
};

#endif // !DUNGEON_H
