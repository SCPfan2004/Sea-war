#pragma once

HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
const int map_size = 10;
const string map_word = "RESPUBLIKA";

const pair<char, char> empty_place = {' ', '0'};
const pair<char, char> ship = {'x', '1'};
const pair<char, char> hidden_ship = {' ', '2'};
const pair<char, char> shot = {'*', '3'};
const pair<char, char> killed_ship = {'#', '4'};

class Cell {
    int x;
    int y;
    bool isLive = true;

public:
    Cell* get_cell();
    int getX();
    int getY();
    void setXY(const int&, const int&);
    bool getLife();
    void kill();
    Cell(const int&, const int&);
};


class Ship {
protected:
    int direct;
    vector<Cell> cells;

public:

    vector<Cell>& get_cells();
    int get_direct();
    Ship();
    Ship(const int&);
    Ship(const Ship&);
    ~Ship();
};


// Player template -------------------------------------->
class Player {

protected:
    char** field = new char*[map_size];

    int cells_count = 20;
    vector<Ship> ships {Ship(4), Ship(3), Ship(3), Ship(2), Ship(2), Ship(2), Ship(1), Ship(1), Ship(1), Ship(1)};
    vector<Cell*> ships_cells;

public:

    int get_cells_count();
    void decrement_cells_count();
    tuple<int, Cell*> check_hit(const int&, const int&);
    char** get_field();
    vector<Ship> get_ships();
    Ship& find_ship(Cell*);
    bool isDestroyed_ship(Ship&);
    vector<int*> stroke_destroyed(Ship& ship);
    void update_field(const string&);
    void update_field(const int&, const int&);
    int* for_stroke_function(const int&, const int&);
    Player(const string&);
    ~Player();

private:
    bool check_place(const int&, const int&, const int&, const int&);
    void update_field(Cell*, const string&);
    void fill_ships_cells(Cell*);
};


// First player (human) -------------------------------------->
class Human : public Player {

public:

    tuple<int, int> shoot();

    Human() : Player("human") {}

private:

    bool validator(const string&);

};


// Second player (computer) -------------------------------------->
class Computer : public Player {
    vector<int*> for_shoots;
    vector<int*> enemy_coords;
    int iterator = 0;
    bool enemy_direction; //true = 1, false = 0

public:

    tuple<int, int> shoot();
    void fill_enemy_coords(const int&);
    void add_enemy_coords(const int&, const int&);
    int get_iterator();
    void increase_iterator();
    void clear_enemy();
    void delete_from_for_shoots(const int&, const int&);

    Computer() : Player("computer") {
        for(int i = 0; i < map_size; i++) {
            for(int j = 0; j < map_size; j++) {
                int* arr = new int[2];
                arr[0] = i;
                arr[1] = j;
                for_shoots.push_back(arr);
            }
        }
    }

private:

    void enemy_coords_filter(const int&);

};


class Game {
    Human player1;
    Computer player2;
public:
    void start();

private:
    void print_fields();
    void print_computer_field();
    void computer_turn();
    void human_turn();
};


#include "functions.cpp"