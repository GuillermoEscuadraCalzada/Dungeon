#include <iostream>
#include "Dungeon/Dungeon.h"

int main() {
    Dungeon* dungeon = Dungeon::GetPtr();
    dungeon->Init();
    std::cout << "Hello World!\n";
}