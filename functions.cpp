#pragma once

Cell* Cell::get_cell() {
    return this;
}

int Cell::getX() {
    return x;
}

int Cell::getY() {
    return y;
}

bool Cell::getLife() {
    return isLive;
}

void Cell::kill() {
    isLive = false;
}

void Cell::setXY(const int& x, const int& y) {
    this->x = x;
    this->y = y;
}

Cell::Cell(const int& x, const int& y) {
    this->x = x;
    this->y = y;
}


int Ship::get_direct() {
    return direct;
}

vector<Cell>& Ship::get_cells() {
    return cells;   
}

Ship::Ship() {
    
}

Ship::Ship(const int& m) {
    int iter = 0;
    direct = rand()%2;

    switch(m) {
        case 1:
            iter = 1;
            break;
        case 2:
            iter = 2;
            break;
        case 3:
            iter = 3;
            break;
        case 4:
            iter = 4;
            break;
    }

    for(int i = 0; i < iter; i++) {
        if(direct == 0) {
            cells.push_back(Cell(i + 1, 0));
        } else {
            cells.push_back(Cell(0, i + 1));
        }
    }
}

Ship::Ship(const Ship& obj) {
    direct = obj.direct;
    cells = obj.cells;
}

Ship::~Ship() {
    cells.clear();
}




int Player::get_cells_count() {
    return cells_count;
}

void Player::decrement_cells_count() {
    cells_count--;
}

char** Player::get_field() {
    return field;
}

vector<Ship> Player::get_ships() {
    return ships;
}

void Player::fill_ships_cells(Cell* obj) {
    ships_cells.push_back(obj);
}


void Player::update_field(Cell* obj, const string& player) {
    if(player == "human") {
        field[(*obj).getX()][(*obj).getY()] = ship.second;
    } else if(player == "computer") {
        field[(*obj).getX()][(*obj).getY()] = hidden_ship.second;
    }
}


int* Player::for_stroke_function(const int& x, const int& y) {
    int* arr = new int[2];
    arr[0] = x;
    arr[1] = y;
    return arr;
}


vector<int*> Player::stroke_destroyed(Ship& ship) {

    vector<int*> shooted;

    int cells_count = ship.get_cells().size();
    int startX = ship.get_cells()[0].getX();
    int startY = ship.get_cells()[0].getY();

    int loops_start = -1;

    if(ship.get_direct() == 0) {

        if(startX > 0) {
            field[startX - 1][startY] = shot.second;
            
            shooted.push_back(for_stroke_function(startX - 1, startY));

        } else {
            loops_start++;
        }

        if(startX + cells_count < 10) {
            field[startX + cells_count][startY] = shot.second;

            shooted.push_back(for_stroke_function(startX + cells_count, startY));

        } else {
            cells_count--;
        }

        for(int l = loops_start; l < cells_count + 1; l++) {
            if(startY > 0) {
                field[startX + l][startY - 1] = shot.second;

                shooted.push_back(for_stroke_function(startX + l, startY - 1));
            }
        }

        for(int l = loops_start; l < cells_count + 1; l++) {
            if(startY < 9) {
                field[startX + l][startY + 1] = shot.second;

                shooted.push_back(for_stroke_function(startX + l, startY + 1));
            }
        }

    } else if(ship.get_direct() == 1) {

        if(startY > 0) {
            field[startX][startY - 1] = shot.second;

            shooted.push_back(for_stroke_function(startX, startY - 1));

        } else {
            loops_start++;
        }

        if(startY + cells_count < 10) {
            field[startX][startY + cells_count] = shot.second;

            shooted.push_back(for_stroke_function(startX, startY + cells_count));

        } else {
            cells_count--;
        }

        for(int l = loops_start; l < cells_count + 1; l++) {
            if(startX > 0) {
                field[startX - 1][startY + l] = shot.second;

                shooted.push_back(for_stroke_function(startX - 1, startY + l));
            }
        }

        for(int l = loops_start; l < cells_count + 1; l++) {
            if(startX < 9) {
                field[startX + 1][startY + l] = shot.second;

                shooted.push_back(for_stroke_function(startX + 1, startY + l));
            }
        }
    }

    return shooted;
}


void Player::update_field(const string& player) {

    for(int i = 0; i < ships.size(); i++) {

        for(int j = 0; j < ships[i].get_cells().size(); j++) {

            Cell& cell = ships[i].get_cells()[j];

            if(cell.getLife() == true) {

                if(player == "human") {
                    field[cell.getX()][cell.getY()] = ship.second;
                } else if(player == "computer") {
                    field[cell.getX()][cell.getY()] = hidden_ship.second;
                }
                
            } else if(cell.getLife() == false) {
                field[cell.getX()][cell.getY()] = killed_ship.second;
            }
        }
    }
}

void Player::update_field(const int& x, const int& y) {
    field[x][y] = shot.second;
}


Ship& Player::find_ship(Cell* cell) {
    for(int i = 0; i < ships.size(); i++) {
        for(int j = 0; j < ships[i].get_cells().size(); j++) {
            if((*cell).getX() == ships[i].get_cells()[j].getX() && (*cell).getY() == ships[i].get_cells()[j].getY()) {
                return ships[i];
            }
        }
    }

    return ships[1];
}


bool Player::isDestroyed_ship(Ship& ship) {

    for(int i = 0; i < ship.get_cells().size(); i++) {
        if(ship.get_cells()[i].getLife() == true) {
            return false;
        }
    }

    return true;
}


tuple<int, Cell*> Player::check_hit(const int& x, const int& y) {
    for(int i = 0; i < ships_cells.size(); i++) {

        Cell& cell = (*ships_cells[i]);

        if(cell.getX() == x && cell.getY() == y) {
            if(cell.getLife() == true) {
                return {1, ships_cells[i]};
            } else {
                return {2, nullptr};
            }
        }
    }

    return {0, nullptr};
}


bool Player::check_place(const int& x, const int& y, const int& cells_count, const int& dir) {
    if(dir == 0) {

        if(x + cells_count > 10) {
            return false;
        }

        for(int i = -1; i < cells_count + 1; i++) {
            if(x + i != -1 && x + i != 10) {
                if(field[x + i][y] != empty_place.second) {
                    return false;
                }

                if(y != 0) {
                    if(field[x + i][y - 1] != empty_place.second) {
                        return false;
                    }
                }

                if(y != 9) {
                    if(field[x + i][y + 1] != empty_place.second) {
                        return false;
                    }
                }
            }
        }

    } else if(dir == 1) {

        if(y + cells_count > 10) {
            return false;
        }

        for(int i = -1; i < cells_count + 1; i++) {
            if(y + i != -1 && y + i != 10) {
                if(field[x][y + i] != empty_place.second) {
                    return false;
                }

                if(x != 0) {
                    if(field[x - 1][y + i] != empty_place.second) {
                        return false;
                    }
                }

                if(x != 9) {
                    if(field[x + 1][y + i] != empty_place.second) {
                        return false;
                    }
                }
            }
        }
    }
    
    return true;
}


Player::Player(const string& player) {
    for(int i = 0; i < 10; i++) {
        char* new_mas = new char[10];
        field[i] = new_mas;

        for(int j = 0; j < 10; j++) {
            field[i][j] = empty_place.second;
        }
    }

    vector<int*> free_coordinates;
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            int* arr = new int[2];
            arr[0] = i;
            arr[1] = j;
            free_coordinates.push_back(arr);
        }
    }

    for(int i = 0; i < ships.size(); i++) {
        
        int random = rand()%free_coordinates.size();
        int x = free_coordinates[random][0];
        int y = free_coordinates[random][1];
        delete[] free_coordinates[random];
        free_coordinates.erase(free_coordinates.begin() + random);

        while(!check_place(x, y, ships[i].get_cells().size(), ships[i].get_direct())) {

            random = rand()%free_coordinates.size();

            x = free_coordinates[random][0];
            y = free_coordinates[random][1];

            free_coordinates.erase(free_coordinates.begin() + random);
        }

        for(int j = 0; j < ships[i].get_cells().size(); j++) {
            if(ships[i].get_direct() == 0) {
                ships[i].get_cells()[j].setXY(x + j, y);
            } else {
                ships[i].get_cells()[j].setXY(x, y + j);
            }

            fill_ships_cells(ships[i].get_cells()[j].get_cell());

            if(player == "human") {
                update_field(ships[i].get_cells()[j].get_cell(), "human");
            } else if(player == "computer") {
                update_field(ships[i].get_cells()[j].get_cell(), "computer");
            }
        }
        
    }

    free_coordinates.clear();
}

Player::~Player() {
    for(int i = 0; i < 10; i++) {
        delete[] field[i];
    }

    delete[] field;

    ships.clear();
    ships_cells.clear();
}





bool Human::validator(const string& str) {
    if(str.length() < 2 || str.length() > 3) {
        return false;
    }
    

    bool flag = false;
    for(int i = 0; i < map_word.length(); i++) {
        if(toupper(str[0]) == map_word[i]) {
            flag = true;
            break;
        }
    }

    if(flag == false) {
        return false;
    }


    if(str.length() == 3) {

        if(str[1] != '1') {
            return false;
        }

        if(str[2] != '0') {
            return false;
        }

    } else {

        if(str[1] == '0') {
            return false;
        }

        if(isdigit(str[1]) == false) {
            return false;
        }

    }

    return true;
}

tuple<int, int> Human::shoot() {
    string coords = "1";

    cout << "PLEASE, ENTER COORDINATES: ";
    cin >> coords;

    while(validator(coords) == false) {
        cout << "PLEASE, CORRECT CORRECT COORDINATES: ";
        cin >> coords;    
    }

    int x;
    int y;

    if(coords.length() == 3) {
        x = 9;
    } else {
        x = int(coords[1]) - 49;
    }

    for(int i = 0; i < map_word.length(); i++) {
        if(toupper(coords[0]) == map_word[i]) {
            y = i;
        }
    }

    return {x, y};
}




#include "computer_shoot.cpp"




void Computer::add_enemy_coords(const int& x, const int& y) {
    int* arr = new int[2];
    arr[0] = x;
    arr[1] = y;
    enemy_coords.push_back(arr);
}


int Computer::get_iterator() {
    return iterator;
}


void Computer::increase_iterator() {
    iterator++;
}


void Computer::clear_enemy() {
    iterator = 0;
    
    if(enemy_coords.size() > 0) {
        for(int i = 0; i < enemy_coords.size(); i++) {
            delete[] enemy_coords[i];
        }

        enemy_coords.clear();
    }
}


void Computer::delete_from_for_shoots(const int& x, const int& y) {
    for(int i = 0; i < for_shoots.size(); i++) {
        if(for_shoots[i][0] == x && for_shoots[i][1] == y) { 
            delete[] for_shoots[i];
            for_shoots.erase(for_shoots.begin() + i);
            break;
        }
    }
}


void Computer::enemy_coords_filter(const int& start_index) {
    for(int i = start_index; i < enemy_coords.size(); i++) {

        bool flag = true;
        for(int j = 0; j < for_shoots.size(); j++) {
            if(enemy_coords[i][0] == for_shoots[j][0] && enemy_coords[i][1] == for_shoots[j][1]) {
                flag = false;
                break;
            }
        }

        if(flag) {
            enemy_coords.erase(enemy_coords.begin() + i);
            i--;
        }
    }
}






void Game::print_fields() {
    for(int i = 0; i < map_size + 1; i++) {
        for(int o = 0; o < 2; o++) {
            for(int j = 0; j < map_word.length() + 1; j++) {

                if(i == 0 && j == 0) {
                    cout << empty_place.first;

                } else if(i == 0 && j > 0) {
                    SetConsoleTextAttribute(handle, 14);
                    cout << map_word[j - 1];

                } else if(i > 0 && j == 0) {
                    SetConsoleTextAttribute(handle, 13);
                    cout << i;

                } else {
                    if(o == 0) {
                        if(player1.get_field()[i - 1][j - 1] == ship.second) {
                            SetConsoleTextAttribute(handle, 9);
                            cout << ship.first;
                        } else if(player1.get_field()[i - 1][j - 1] == killed_ship.second) {
                            SetConsoleTextAttribute(handle, 4);
                            cout << killed_ship.first;
                        } else if(player1.get_field()[i - 1][j - 1] == shot.second) {
                            SetConsoleTextAttribute(handle, 8);
                            cout << shot.first;
                        } else {
                            cout << empty_place.first;
                        }

                    } else  if(o == 1){
                        if(player2.get_field()[i - 1][j - 1] == hidden_ship.second) {
                            SetConsoleTextAttribute(handle, 10);
                            cout << hidden_ship.first;
                        } else if(player2.get_field()[i - 1][j - 1] == killed_ship.second) {
                            SetConsoleTextAttribute(handle, 4);
                            cout << killed_ship.first;
                        } else if(player2.get_field()[i - 1][j - 1] == shot.second) {
                            SetConsoleTextAttribute(handle, 8);
                            cout << shot.first;
                        } else {
                            cout << empty_place.first;
                        }
                    }
                }

                if(i == 10 && j == 0) {
                    cout << empty_place.first;
                } else {
                    cout << empty_place.first << empty_place.first;
                }
            }

            cout << "\t";
        }

        cout << "\n";
    }

    SetConsoleTextAttribute(handle, 15);
}


void Game::print_computer_field() {
    for(int i = 0; i < map_size + 1; i++) {

        for(int j = 0; j < map_word.length() + 1; j++) {

                if(i == 0 && j == 0) {
                    cout << empty_place.first;

                } else if(i == 0 && j > 0) {
                    SetConsoleTextAttribute(handle, 14);
                    cout << map_word[j - 1];

                } else if(i > 0 && j == 0) {
                    SetConsoleTextAttribute(handle, 13);
                    cout << i;

                } else {

                    if(player2.get_field()[i - 1][j - 1] == hidden_ship.second) {
                        SetConsoleTextAttribute(handle, 10);
                        cout << ship.first;
                    } else if(player2.get_field()[i - 1][j - 1] == killed_ship.second) {
                        SetConsoleTextAttribute(handle, 4);
                        cout << killed_ship.first;
                    } else if(player2.get_field()[i - 1][j - 1] == shot.second) {
                        SetConsoleTextAttribute(handle, 8);
                        cout << shot.first;
                    } else {
                        cout << empty_place.first;
                    }
                }

            if(i == 10 && j == 0) {
                cout << empty_place.first;
            } else {
                cout << empty_place.first << empty_place.first;
            }
        }

        cout << "\n";
    }

    SetConsoleTextAttribute(handle, 15);
}


void Game::human_turn() {
    cout << "YOUR TURN:\n";
    print_fields();

    while(player2.get_cells_count() > 0) {

        int x;
        int y;
        tie(x, y) = player1.shoot();


        auto [isHited, hited_cell] = player2.check_hit(x, y);

        if(isHited == 0) {
            player2.update_field(x, y);
            
            system("cls");
            cout << "YOUR TURN:\n";
            print_fields();
            cout << "MISS...\n";

            Sleep(1500);
            system("cls");
            break;

        } else if(isHited == 1) {
            (*hited_cell).kill();
            player2.decrement_cells_count();
            player2.update_field("computer");

            Ship& ship = player2.find_ship(hited_cell);

            if(player2.isDestroyed_ship(ship)) {
                player2.stroke_destroyed(ship);

                system("cls");
                cout << "YOUR TURN:\n";
                print_fields();
                cout << "YOU DESTROYED THE SHIP!!!\n";

            } else {
                system("cls");
                cout << "YOUR TURN:\n";
                print_fields();
                cout << "PENETRATION!\n";
            }

        } else if(isHited == 2) {
            system("cls");
            cout << "YOUR TURN:\n";
            print_fields();
            cout << "DON'T HIT DESTOYED SHIPS, IT IS USELESS\n";
            Sleep(2500);
            system("cls");
            break;
        }
    }
}

void Game::computer_turn() {
    cout << "COMPUTER TURN...\n";
    print_fields();
    Sleep(1500);

    while(player1.get_cells_count() > 0) {

        int x;
        int y;
        tie(x, y) = player2.shoot();

        player2.delete_from_for_shoots(x, y);

        auto [isHited, hited_cell] = player1.check_hit(x, y);

        if(isHited == 0) { 
            player1.update_field(x, y);

            system("cls");
            cout << "COMPUTER TURN...\n";
            print_fields();
            Sleep(1000);
            system("cls");
            break;

        } else if(isHited == 1) {
            (*hited_cell).kill();
            player1.decrement_cells_count();
            player1.update_field("human");

            Ship& ship = player1.find_ship(hited_cell);

            if(player1.isDestroyed_ship(ship)) {
                vector<int*> shooted = player1.stroke_destroyed(ship);

                for(int i = 0; i < shooted.size(); i++) {
                    player2.delete_from_for_shoots(shooted[i][0], shooted[i][1]);
                }

                player2.clear_enemy();

                system("cls");
                cout << "COMPUTER TURN...\n";
                print_fields();
                cout << "YOUR SHIP DESTROYED!!!\n";

                Sleep(1500);

            } else {
                player2.add_enemy_coords(x, y);
                player2.increase_iterator();
                player2.fill_enemy_coords(player2.get_iterator());

                system("cls");
                cout << "COMPUTER TURN...\n";
                print_fields();

                Sleep(1000);
            }
        }
    }
}


void Game::start() {

    while(player1.get_cells_count() > 0 && player2.get_cells_count() > 0) {
        human_turn();

        if(player2.get_cells_count() > 0) {
            computer_turn();
        }
    }

    if(player1.get_cells_count() > 0) {
        cout << "\nEEEEEEAH!!! YOU WIN!";

    } else if(player2.get_cells_count() > 0) {
        cout << "\nDEFEAT :(\n\nRIVAL MAP: \n";
        print_computer_field(); 
    }
}