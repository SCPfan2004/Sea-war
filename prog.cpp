#include <iostream>
#include <windows.h>
#include <ctime>
#include <vector>
#include <map>
using namespace std;

#include "header.h"


int main() {
    SetConsoleTextAttribute(handle, 15);
    srand(time(0));
    Game game;
    game.start();
}