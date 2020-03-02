#ifndef DUNGEON_H
#define DUNGEON_H
#include <iostream>
using namespace std;
class Dungeon {

public:
	static Dungeon* GetPtr();
	const static int lines = 7;
	const static int columns = 7;
	int dungeon[lines][columns];

	void Setup();
	void Update();
	void Init();
	void Print();
private:
	Dungeon();
	~Dungeon();
	static Dungeon* ptr;
};

#endif // !DUNGEON_H
