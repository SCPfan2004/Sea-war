void Computer::fill_enemy_coords(const int& iterator) {
    if(iterator == 1) {

        if(enemy_coords[0][0] > 0) {
            int* arr = new int[2];
            arr[0] = enemy_coords[0][0] - 1;
            arr[1] = enemy_coords[0][1];
            enemy_coords.push_back(arr);
        }

        if(enemy_coords[0][0] < 9) {
            int* arr = new int[2];
            arr[0] = enemy_coords[0][0] + 1;
            arr[1] = enemy_coords[0][1];
            enemy_coords.push_back(arr);
        }

        if(enemy_coords[0][1] > 0) {
            int* arr = new int[2];
            arr[0] = enemy_coords[0][0];
            arr[1] = enemy_coords[0][1] - 1;
            enemy_coords.push_back(arr);
        }

        if(enemy_coords[0][1] < 9) {
            int* arr = new int[2];
            arr[0] = enemy_coords[0][0];
            arr[1] = enemy_coords[0][1] + 1;
            enemy_coords.push_back(arr);
        }

        enemy_coords_filter(1);

    } else if(iterator == 2) {

        enemy_coords.erase(enemy_coords.begin() + 1, enemy_coords.end() - 1);

        if(enemy_coords[0][0] != enemy_coords[1][0]) {
            enemy_direction = false;
        } else if(enemy_coords[0][1] != enemy_coords[1][1]) {
            enemy_direction = true;
        }


        if(enemy_coords[0][enemy_direction] > enemy_coords[1][enemy_direction]) {

            int* tmp = enemy_coords[1];
            enemy_coords[1] = enemy_coords[0];
            enemy_coords[0] = tmp;
        }

        if(enemy_coords[0][enemy_direction] >= 1) {

            int* arr = new int[2];
            arr[enemy_direction] = enemy_coords[0][enemy_direction] - 1;
            arr[!enemy_direction] = enemy_coords[0][!enemy_direction];
            enemy_coords.push_back(arr);
        }

        if(enemy_coords[1][enemy_direction] <= 8) {

            int* arr = new int[2];
            arr[enemy_direction] = enemy_coords[1][enemy_direction] + 1;
            arr[!enemy_direction] = enemy_coords[0][!enemy_direction];
            enemy_coords.push_back(arr);
        }


        if(enemy_coords.size() > 3) {
            enemy_coords_filter(2);
        }


    } else if(iterator == 3) {

        if(enemy_coords.size() == 4) {
            delete[] enemy_coords[2];
            enemy_coords.erase(enemy_coords.begin() + 2);
        }


        for(int i = 0; i < enemy_coords.size(); i++) {
            for(int j = 0; j < enemy_coords.size() - 1; j++) {
                if(enemy_coords[j][enemy_direction] > enemy_coords[j + 1][enemy_direction]) {
                    int* tmp = enemy_coords[j];
                    enemy_coords[j] = enemy_coords[j + 1];
                    enemy_coords[j + 1] = tmp;
                }
            }
        }


        delete[] enemy_coords[1];
        enemy_coords.erase(enemy_coords.begin() + 1);

        if(enemy_coords[0][enemy_direction] >= 1) {

            int* arr = new int[2];
            arr[enemy_direction] = enemy_coords[0][enemy_direction] - 1;
            arr[!enemy_direction] = enemy_coords[0][!enemy_direction];
            enemy_coords.push_back(arr);
        }

        if(enemy_coords[1][enemy_direction] <= 8) {

            int* arr = new int[2];
            arr[enemy_direction] = enemy_coords[1][enemy_direction] + 1;
            arr[!enemy_direction] = enemy_coords[0][!enemy_direction];
            enemy_coords.push_back(arr);
        }


        delete[] enemy_coords[0];
        delete[] enemy_coords[1];

        enemy_coords.erase(enemy_coords.begin(), enemy_coords.begin() + 2);
        enemy_coords_filter(0);

    }
}



tuple<int, int> Computer::shoot() {
    int x;
    int y;

    if(iterator == 0) {
        int random = rand() % for_shoots.size();
        x = for_shoots[random][0];
        y = for_shoots[random][1];

    } else if(iterator == 1) {

        int random = 1 + (rand() % (enemy_coords.size() - 1));;
        
        x = enemy_coords[random][0];
        y = enemy_coords[random][1];

        delete[] enemy_coords[random];
        enemy_coords.erase(enemy_coords.begin() + random);

    } else if(iterator == 2) {

        int random = 2 + (rand() % (enemy_coords.size() - 2));
        x = enemy_coords[random][0];
        y = enemy_coords[random][1];

        delete[] enemy_coords[random];
        enemy_coords.erase(enemy_coords.begin() + random);

    } else if(iterator == 3) {

        int random = rand() % enemy_coords.size();
        x = enemy_coords[random][0];
        y = enemy_coords[random][1];

        delete[] enemy_coords[random];
        enemy_coords.erase(enemy_coords.begin() + random);

    }

    return {x, y};
}