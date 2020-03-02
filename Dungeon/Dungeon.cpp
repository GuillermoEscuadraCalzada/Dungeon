#include "Dungeon\Dungeon.h"
Dungeon* Dungeon::ptr = nullptr;

Dungeon* Dungeon::GetPtr() {
    if(!ptr)
        ptr = new Dungeon();
    return ptr;
}

void Dungeon::Setup() {
    try {
        for(int i = 0; i < lines; i++) {
            for(int j = 0; j < columns; j++) {
                if(i == 0 || i == lines - 1)
                    dungeon[i][j] = 0;
                else if(j > 0 && j < columns - 1)
                    dungeon[i][j] = 1;
            }
        }
    } catch(exception & e) {
        cout << "EXCEPTION CAUGHT: " << e.what() << endl;
    }
}

void Dungeon::Update() {
    try {

    } catch(exception & e) {
        cout << "EXCEPTION CAUGHT: " << e.what() << endl;
    }
}

void Dungeon::Init() {
    try {
        Setup();
        Print();
    } catch(exception & e) {
        cout << "EXCEPTION CAUGHT: " << e.what() << endl;
    }
}

void Dungeon::Print() {
    try {
        for(int i = 0; i < lines; i++) {
            for(int j = 0; j < columns; j++) {
                cout << dungeon[i][j];
            }
            cout << endl;
        }
    } catch(exception & e) {
        cout << "EXCEPTION CAUGHT: " << e.what() << endl;
    }
}

Dungeon::Dungeon() {
}

Dungeon::~Dungeon() {
}

