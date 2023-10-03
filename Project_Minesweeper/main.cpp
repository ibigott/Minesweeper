#include "iostream"
#include "fstream"
#include <SFML/Graphics.hpp>
#include <random>
#include <ctime>

using namespace std;

class Random {

    static mt19937 random;

public:

    static int Number(int min, int max);
};

mt19937  Random::random(timelocal(0));

int Random::Number(int min, int max) {

    std::uniform_int_distribution<int> dist(min, max);
    return dist(random);
}

struct mine_counter {

    sf::Sprite negative_sign;
    sf::Sprite first_digit;
    sf::Sprite second_digit;
    sf::Sprite third_digit;
    int flags_left;
    string s_flags_left;
    char c_first_digit = '0';
    char c_second_digit = '0';
    char c_third_digit = '0';
};

struct tile {

    sf::Sprite cover;
    sf::Sprite icon;
    sf::Sprite flag;
    int mine_status = 0;
    int nearby_bombs = 0;
    bool is_revealed = false;
    bool debugged = false;
    bool flagged = false;
    tile* neighbors[8];
    vector<tile*> update;
};

void CheckNeighbors(tile &input) {

    for (int i = 0; i < 8; i++) {

        if (input.neighbors[i] != nullptr) {

            if (input.neighbors[i]->mine_status == 1) {

                input.nearby_bombs++;
            }
        }
    }
}

void Click(tile *input, mine_counter &counter) {

    if (input->is_revealed || input->flagged) {

    }

    else {

        if (input->nearby_bombs > 0) {

            input->is_revealed = true;
        }

        else {

            input->is_revealed = true;

            for (int i = 0; i < input->update.size(); i++) {

                if (input->update[i]->nearby_bombs == 0) {

                    Click(input->update[i], counter);
                }

                else {

                    input->update[i]->is_revealed = true;
                }
            }
        }

    }
}

int main() {

    string input;
    int width;
    int height;
    int config_count;
    bool debug_on = false;
    bool play = true;
    int main_count = 0;

    fstream open("/Users/ignatius/Desktop/Project_Minesweeper/boards/config.cfg");

    while (open.good()) {

        getline(open, input);
        width = stoi(input);
        getline(open, input);
        height = stoi(input);
        getline(open, input);
        config_count = stoi(input);
    }

    sf::Texture mine;
    mine.loadFromFile("/Users/ignatius/Desktop/Project_Minesweeper/images/mine.png");
    sf::Texture number_1;
    number_1.loadFromFile("/Users/ignatius/Desktop/Project_Minesweeper/images/number_1.png");
    sf::Texture number_2;
    number_2.loadFromFile("/Users/ignatius/Desktop/Project_Minesweeper/images/number_2.png");
    sf::Texture number_3;
    number_3.loadFromFile("/Users/ignatius/Desktop/Project_Minesweeper/images/number_3.png");
    sf::Texture number_4;
    number_4.loadFromFile("/Users/ignatius/Desktop/Project_Minesweeper/images/number_4.png");
    sf::Texture number_5;
    number_5.loadFromFile("/Users/ignatius/Desktop/Project_Minesweeper/images/number_5.png");
    sf::Texture number_6;
    number_6.loadFromFile("/Users/ignatius/Desktop/Project_Minesweeper/images/number_6.png");
    sf::Texture number_7;
    number_7.loadFromFile("/Users/ignatius/Desktop/Project_Minesweeper/images/number_7.png");
    sf::Texture number_8;
    number_8.loadFromFile("/Users/ignatius/Desktop/Project_Minesweeper/images/number_8.png");
    sf::Texture debug;
    debug.loadFromFile("/Users/ignatius/Desktop/Project_Minesweeper/images/debug.png");
    sf::Texture digits;
    digits.loadFromFile("/Users/ignatius/Desktop/Project_Minesweeper/images/digits.png");
    sf::Texture face_happy;
    face_happy.loadFromFile("/Users/ignatius/Desktop/Project_Minesweeper/images/face_happy.png");
    sf::Texture face_lose;
    face_lose.loadFromFile("/Users/ignatius/Desktop/Project_Minesweeper/images/face_lose.png");
    sf::Texture face_win;
    face_win.loadFromFile("/Users/ignatius/Desktop/Project_Minesweeper/images/face_win.png");
    sf::Texture flag;
    flag.loadFromFile("/Users/ignatius/Desktop/Project_Minesweeper/images/flag.png");
    sf::Texture test_1;
    test_1.loadFromFile("/Users/ignatius/Desktop/Project_Minesweeper/images/test_1.png");
    sf::Texture test_2;
    test_2.loadFromFile("/Users/ignatius/Desktop/Project_Minesweeper/images/test_2.png");
    sf::Texture test_3;
    test_3.loadFromFile("/Users/ignatius/Desktop/Project_Minesweeper/images/test_3.png");
    sf::Texture tile_hidden;
    tile_hidden.loadFromFile("/Users/ignatius/Desktop/Project_Minesweeper/images/tile_hidden.png");
    sf::Texture tile_revealed;
    tile_revealed.loadFromFile("/Users/ignatius/Desktop/Project_Minesweeper/images/tile_revealed.png");

    tile game[height][width];
    mine_counter counter;

    main_count = config_count;
    counter.flags_left = config_count;

    for (int i = 0; i < height; i++) {

        for (int j = 0; j < width; j++) {

            for (int k = 0; k < 8; k++) {

                game[i][j].neighbors[k] = nullptr;
            }
        }
    }

    for (int i = 0; i < height; i++) {

        for (int j = 0; j < width; j++) {

            if ((i == 0) && (j == 0)) {

                game[i][j].neighbors[4] = &game[i][j + 1];
                game[i][j].neighbors[6] = &game[i + 1][j];
                game[i][j].neighbors[7] = &game[i + 1][j + 1];
            }

            else if ((i == 0) && (j == width - 1)) {

                game[i][j].neighbors[3] = &game[i][j - 1];
                game[i][j].neighbors[5] = &game[i + 1][j - 1];
                game[i][j].neighbors[6] = &game[i + 1][j];
            }

            else if ((i == height - 1) && (j == 0)) {

                game[i][j].neighbors[1] = &game[i - 1][j];
                game[i][j].neighbors[2] = &game[i - 1][j + 1];
                game[i][j].neighbors[4] = &game[i][j + 1];
            }

            else if ((i == height - 1) && (j == width - 1)) {

                game[i][j].neighbors[0] = &game[i - 1][j - 1];
                game[i][j].neighbors[1] = &game[i - 1][j];
                game[i][j].neighbors[3] = &game[i][j - 1];
            }

            else if (i == 0) {

                game[i][j].neighbors[3] = &game[i][j - 1];
                game[i][j].neighbors[4] = &game[i][j + 1];
                game[i][j].neighbors[5] = &game[i + 1][j - 1];
                game[i][j].neighbors[6] = &game[i + 1][j];
                game[i][j].neighbors[7] = &game[i + 1][j + 1];
            }

            else if (i == height - 1) {

                game[i][j].neighbors[0] = &game[i - 1][j - 1];
                game[i][j].neighbors[1] = &game[i - 1][j];
                game[i][j].neighbors[2] = &game[i - 1][j + 1];
                game[i][j].neighbors[3] = &game[i][j - 1];
                game[i][j].neighbors[4] = &game[i][j + 1];
            }

            else if (j == 0) {

                game[i][j].neighbors[1] = &game[i - 1][j];
                game[i][j].neighbors[2] = &game[i - 1][j + 1];
                game[i][j].neighbors[4] = &game[i][j + 1];
                game[i][j].neighbors[6] = &game[i + 1][j];
                game[i][j].neighbors[7] = &game[i + 1][j + 1];
            }

            else if (j == width - 1) {

                game[i][j].neighbors[0] = &game[i - 1][j - 1];
                game[i][j].neighbors[1] = &game[i - 1][j];
                game[i][j].neighbors[3] = &game[i][j - 1];
                game[i][j].neighbors[5] = &game[i + 1][j - 1];
                game[i][j].neighbors[6] = &game[i + 1][j];
            }

            else {

                game[i][j].neighbors[0] = &game[i - 1][j - 1];
                game[i][j].neighbors[1] = &game[i - 1][j];
                game[i][j].neighbors[2] = &game[i - 1][j + 1];
                game[i][j].neighbors[3] = &game[i][j - 1];
                game[i][j].neighbors[4] = &game[i][j + 1];
                game[i][j].neighbors[5] = &game[i + 1][j - 1];
                game[i][j].neighbors[6] = &game[i + 1][j];
                game[i][j].neighbors[7] = &game[i + 1][j + 1];
            }
        }
    }

    for (int i = 0; i < height; i++) {

        for (int j = 0; j < width; j++) {

            for (int k = 0; k < 8; k++) {

                if (game[i][j].neighbors[k] != nullptr) {

                    game[i][j].update.push_back(game[i][j].neighbors[k]);
                }
            }
        }
    }

    for (int i = 0; i < height; i++) {

        for (int j = 0; j < width; j++) {

            game[i][j].cover.setTexture(tile_hidden);
            game[i][j].cover.setPosition(sf::Vector2f((float) j * 32.0f, (float) i * 32.0f));
            game[i][j].icon.setPosition(sf::Vector2f((float) j * 32.0f, (float) i * 32.0f));
            game[i][j].flag.setPosition(sf::Vector2f((float) j * 32.0f, (float) i * 32.0f));
        }
    }

    counter.negative_sign.setPosition(sf::Vector2f(0.0f, (float) height * 32.0f));
    counter.negative_sign.setTexture(digits);
    counter.negative_sign.setTextureRect(sf::IntRect(21 * 10, 0, 21, 32));

    counter.first_digit.setPosition(sf::Vector2f(32.0f, (float) height * 32.0f));
    counter.first_digit.setTexture(digits);

    counter.second_digit.setPosition(sf::Vector2f(64.0f, (float) height * 32.0f));
    counter.second_digit.setTexture(digits);

    counter.third_digit.setPosition(sf::Vector2f(96.0f, (float) height * 32.0f));
    counter.third_digit.setTexture(digits);

    sf::Sprite game_status;
    game_status.setTexture(face_happy);
    game_status.setPosition(sf::Vector2f(((float) width / 2.0f) * 32.0f - 32, (float) height * 32.0f));
    sf::Sprite debug_button;
    debug_button.setTexture(debug);
    debug_button.setPosition(sf::Vector2f(((float) width / 2.0f) * 32.0f + 96.0f, (float) height * 32.0f));
    sf::Sprite test1_button;
    test1_button.setTexture(test_1);
    test1_button.setPosition(sf::Vector2f(((float) width / 2.0f) * 32.0f + 160.0f, (float) height * 32.0f));
    sf::Sprite test2_button;
    test2_button.setTexture(test_2);
    test2_button.setPosition(sf::Vector2f(((float) width / 2.0f) * 32.0f + 224.0f, (float) height * 32.0f));
    sf::Sprite test3_button;
    test3_button.setTexture(test_3);
    test3_button.setPosition(sf::Vector2f(((float) width / 2.0f) * 32.0f + 288.0f, (float) height * 32.0f));

    for (int i = 0; i < config_count;) {

        int x = Random::Number(0, width - 1);
        int y = Random::Number(0, height - 1);

        if (game[y][x].mine_status == 0) {

            game[y][x].mine_status = 1;
            i++;
        }
    }

    for (int i = 0; i < height; i++) {

        for (int j = 0; j < width; j++) {

            CheckNeighbors(game[i][j]);

            if (game[i][j].mine_status == 1) {

                game[i][j].icon.setTexture(mine);
            }

            else {

                if (game[i][j].nearby_bombs == 1) {

                    game[i][j].icon.setTexture(number_1);
                }

                if (game[i][j].nearby_bombs == 2) {

                    game[i][j].icon.setTexture(number_2);
                }

                if (game[i][j].nearby_bombs == 3) {

                    game[i][j].icon.setTexture(number_3);
                }

                if (game[i][j].nearby_bombs == 4) {

                    game[i][j].icon.setTexture(number_4);
                }

                if (game[i][j].nearby_bombs == 5) {

                    game[i][j].icon.setTexture(number_5);
                }

                if (game[i][j].nearby_bombs == 6) {

                    game[i][j].icon.setTexture(number_6);
                }

                if (game[i][j].nearby_bombs == 7) {

                    game[i][j].icon.setTexture(number_7);
                }

                if (game[i][j].nearby_bombs == 8) {

                    game[i][j].icon.setTexture(number_8);
                }
            }
        }
    }

    sf::RenderWindow window(sf::VideoMode(width * 32, (height * 32) + 100), "Minesweeper");

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();

            sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            sf::FloatRect reset = game_status.getGlobalBounds();
            sf::FloatRect debug = debug_button.getGlobalBounds();
            sf::FloatRect test1 = test1_button.getGlobalBounds();
            sf::FloatRect test2 = test2_button.getGlobalBounds();
            sf::FloatRect test3 = test3_button.getGlobalBounds();


            if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {

                int x = sf::Mouse::getPosition(window).x / 32;
                int y = sf::Mouse::getPosition(window).y / 32;

                if (((x >= 0) && (x < width)) && ((y >= 0) && (y < height)) && play) {

                    if (!game[y][x].flagged) {

                        if (game[y][x].mine_status == 0) {

                            Click(&game[y][x], counter);
                        }

                        else {

                            game[y][x].is_revealed = true;
                        }

                        for (int i = 0; i < height; i++) {

                            for (int j = 0; j < width; j++) {

                                if (game[y][x].mine_status == 1) {

                                    if (game[i][j].mine_status == 1) {

                                        game[i][j].is_revealed = true;
                                        game[i][j].cover.setTexture(tile_revealed);
                                        game_status.setTexture(face_lose);
                                        debug_on = false;
                                        play = false;
                                    }
                                }

                                else {

                                    if (game[i][j].is_revealed) {

                                        game[i][j].cover.setTexture(tile_revealed);
                                    }
                                }
                            }
                        }

                        int sum = 0;

                        for (int i = 0; i < height; i++) {

                            for (int j = 0; j < width; j++) {

                                if (game[i][j].is_revealed && game[i][j].mine_status == 0) {

                                    sum++;
                                }
                            }
                        }

                        if (sum == height * width - main_count) {

                            game_status.setTexture(face_win);
                            play = false;
                            counter.flags_left = 0;

                            for (int i = 0; i < height; i++) {

                                for (int j = 0; j < width; j++) {

                                    if (game[i][j].mine_status == 1) {

                                        game[i][j].flagged = true;
                                    }
                                }
                            }
                        }
                    }
                }

                else if (reset.contains(mouse)) {

                    for (int i = 0; i < height; i++) {

                        for (int j = 0; j < width; j++) {

                            game[i][j].cover.setTexture(tile_hidden);
                            game[i][j].icon.setTexture(tile_revealed);
                            game[i][j].is_revealed = false;
                            game[i][j].nearby_bombs = 0;
                            game[i][j].mine_status = 0;
                            game[i][j].debugged = false;
                            game_status.setTexture(face_happy);
                            play = true;

                            if (game[i][j].flagged) {

                                counter.flags_left++;
                                game[i][j].flagged = false;
                            }
                        }
                    }

                    main_count = config_count;
                    counter.flags_left = main_count;

                    for (int i = 0; i < config_count;) {

                        int x = Random::Number(0, width - 1);
                        int y = Random::Number(0, height - 1);

                        if (game[y][x].mine_status == 0) {

                            game[y][x].mine_status = 1;
                            i++;
                        }
                    }

                    for (int i = 0; i < height; i++) {

                        for (int j = 0; j < width; j++) {

                            CheckNeighbors(game[i][j]);

                            if (game[i][j].mine_status == 1) {

                                game[i][j].icon.setTexture(mine);
                            }

                            else {

                                if (game[i][j].nearby_bombs == 1) {

                                    game[i][j].icon.setTexture(number_1);
                                }

                                if (game[i][j].nearby_bombs == 2) {

                                    game[i][j].icon.setTexture(number_2);
                                }

                                if (game[i][j].nearby_bombs == 3) {

                                    game[i][j].icon.setTexture(number_3);
                                }

                                if (game[i][j].nearby_bombs == 4) {

                                    game[i][j].icon.setTexture(number_4);
                                }

                                if (game[i][j].nearby_bombs == 5) {

                                    game[i][j].icon.setTexture(number_5);
                                }

                                if (game[i][j].nearby_bombs == 6) {

                                    game[i][j].icon.setTexture(number_6);
                                }

                                if (game[i][j].nearby_bombs == 7) {

                                    game[i][j].icon.setTexture(number_7);
                                }

                                if (game[i][j].nearby_bombs == 8) {

                                    game[i][j].icon.setTexture(number_8);
                                }
                            }
                        }
                    }

                    if (debug_on) {

                        for (int i = 0; i < height; i++) {

                            for (int j = 0; j < width; j++) {

                                if (game[i][j].mine_status == 1) {

                                    game[i][j].debugged = true;
                                }
                            }
                        }
                    }
                }

                else if (debug.contains(mouse)) {

                    for (int i = 0; i < height; i++) {

                        for (int j = 0; j < width; j++) {

                            if (game[i][j].debugged) {

                                debug_on = false;
                                game[i][j].debugged = false;
                            }

                            else if ((game[i][j].mine_status == 1) && (!game[i][j].is_revealed) && play) {

                                debug_on = true;
                                game[i][j].debugged = true;
                            }
                        }
                    }
                }

                else if (test1.contains(mouse)) {

                    string name = "/Users/ignatius/Desktop/Project_Minesweeper/boards/testboard1.brd";
                    fstream file(name);

                    int h = 0;
                    string temp;
                    string num;

                    int test1_count = 0;

                    for (int i = 0; i < height; i++) {

                        for (int j = 0; j < width; j++) {

                            game[i][j].cover.setTexture(tile_hidden);
                            game[i][j].icon.setTexture(tile_revealed);
                            game[i][j].is_revealed = false;
                            game[i][j].nearby_bombs = 0;
                            game[i][j].mine_status = 0;
                            game[i][j].debugged = false;
                            game_status.setTexture(face_happy);
                            play = true;

                            if (game[i][j].flagged) {

                                counter.flags_left++;
                                game[i][j].flagged = false;
                            }
                        }
                    }

                    while (file.good()) {

                        file >> temp;

                        for (int i = 0; i < width; i++) {

                            num = temp[i];
                            game[h][i].mine_status = stoi(num);
                        }

                        h++;
                    }

                    for (int i = 0; i < height; i++) {

                        for (int j = 0; j < width; j++) {

                            if (game[i][j].mine_status == 1) {

                                test1_count++;
                            }
                        }
                    }

                    main_count = test1_count;
                    counter.flags_left = main_count;

                    for (int i = 0; i < height; i++) {

                        for (int j = 0; j < width; j++) {

                            CheckNeighbors(game[i][j]);

                            if (game[i][j].mine_status == 1) {

                                game[i][j].icon.setTexture(mine);
                            }

                            else {

                                if (game[i][j].nearby_bombs == 1) {

                                    game[i][j].icon.setTexture(number_1);
                                }

                                if (game[i][j].nearby_bombs == 2) {

                                    game[i][j].icon.setTexture(number_2);
                                }

                                if (game[i][j].nearby_bombs == 3) {

                                    game[i][j].icon.setTexture(number_3);
                                }

                                if (game[i][j].nearby_bombs == 4) {

                                    game[i][j].icon.setTexture(number_4);
                                }

                                if (game[i][j].nearby_bombs == 5) {

                                    game[i][j].icon.setTexture(number_5);
                                }

                                if (game[i][j].nearby_bombs == 6) {

                                    game[i][j].icon.setTexture(number_6);
                                }

                                if (game[i][j].nearby_bombs == 7) {

                                    game[i][j].icon.setTexture(number_7);
                                }

                                if (game[i][j].nearby_bombs == 8) {

                                    game[i][j].icon.setTexture(number_8);
                                }
                            }
                        }
                    }

                    if (debug_on) {

                        for (int i = 0; i < height; i++) {

                            for (int j = 0; j < width; j++) {

                                if (game[i][j].mine_status == 1) {

                                    game[i][j].debugged = true;
                                }
                            }
                        }
                    }
                }

                else if (test2.contains(mouse)) {

                    string name = "/Users/ignatius/Desktop/Project_Minesweeper/boards/testboard2.brd";
                    fstream file(name);

                    int h = 0;
                    string temp;
                    string num;

                    int test1_count = 0;

                    for (int i = 0; i < height; i++) {

                        for (int j = 0; j < width; j++) {

                            game[i][j].cover.setTexture(tile_hidden);
                            game[i][j].icon.setTexture(tile_revealed);
                            game[i][j].is_revealed = false;
                            game[i][j].nearby_bombs = 0;
                            game[i][j].mine_status = 0;
                            game[i][j].debugged = false;
                            game_status.setTexture(face_happy);
                            play = true;

                            if (game[i][j].flagged) {

                                counter.flags_left++;
                                game[i][j].flagged = false;
                            }
                        }
                    }

                    while (file.good()) {

                        file >> temp;

                        for (int i = 0; i < width; i++) {

                            num = temp[i];
                            game[h][i].mine_status = stoi(num);
                        }

                        h++;
                    }

                    for (int i = 0; i < height; i++) {

                        for (int j = 0; j < width; j++) {

                            if (game[i][j].mine_status == 1) {

                                test1_count++;
                            }
                        }
                    }

                    main_count = test1_count;
                    counter.flags_left = main_count;

                    for (int i = 0; i < height; i++) {

                        for (int j = 0; j < width; j++) {

                            CheckNeighbors(game[i][j]);

                            if (game[i][j].mine_status == 1) {

                                game[i][j].icon.setTexture(mine);
                            }

                            else {

                                if (game[i][j].nearby_bombs == 1) {

                                    game[i][j].icon.setTexture(number_1);
                                }

                                if (game[i][j].nearby_bombs == 2) {

                                    game[i][j].icon.setTexture(number_2);
                                }

                                if (game[i][j].nearby_bombs == 3) {

                                    game[i][j].icon.setTexture(number_3);
                                }

                                if (game[i][j].nearby_bombs == 4) {

                                    game[i][j].icon.setTexture(number_4);
                                }

                                if (game[i][j].nearby_bombs == 5) {

                                    game[i][j].icon.setTexture(number_5);
                                }

                                if (game[i][j].nearby_bombs == 6) {

                                    game[i][j].icon.setTexture(number_6);
                                }

                                if (game[i][j].nearby_bombs == 7) {

                                    game[i][j].icon.setTexture(number_7);
                                }

                                if (game[i][j].nearby_bombs == 8) {

                                    game[i][j].icon.setTexture(number_8);
                                }
                            }
                        }
                    }

                    if (debug_on) {

                        for (int i = 0; i < height; i++) {

                            for (int j = 0; j < width; j++) {

                                if (game[i][j].mine_status == 1) {

                                    game[i][j].debugged = true;
                                }
                            }
                        }
                    }
                }

                else if (test3.contains(mouse)) {

                    string name = "/Users/ignatius/Desktop/Project_Minesweeper/boards/testboard3.brd";
                    fstream file(name);

                    int h = 0;
                    string temp;
                    string num;

                    int test1_count = 0;

                    for (int i = 0; i < height; i++) {

                        for (int j = 0; j < width; j++) {

                            game[i][j].cover.setTexture(tile_hidden);
                            game[i][j].icon.setTexture(tile_revealed);
                            game[i][j].is_revealed = false;
                            game[i][j].nearby_bombs = 0;
                            game[i][j].mine_status = 0;
                            game[i][j].debugged = false;
                            game_status.setTexture(face_happy);
                            play = true;

                            if (game[i][j].flagged) {

                                counter.flags_left++;
                                game[i][j].flagged = false;
                            }
                        }
                    }

                    while (file.good()) {

                        file >> temp;

                        for (int i = 0; i < width; i++) {

                            num = temp[i];
                            game[h][i].mine_status = stoi(num);
                        }

                        h++;
                    }

                    for (int i = 0; i < height; i++) {

                        for (int j = 0; j < width; j++) {

                            if (game[i][j].mine_status == 1) {

                                test1_count++;
                            }
                        }
                    }

                    main_count = test1_count;
                    counter.flags_left = main_count;

                    for (int i = 0; i < height; i++) {

                        for (int j = 0; j < width; j++) {

                            CheckNeighbors(game[i][j]);

                            if (game[i][j].mine_status == 1) {

                                game[i][j].icon.setTexture(mine);
                            }

                            else {

                                if (game[i][j].nearby_bombs == 1) {

                                    game[i][j].icon.setTexture(number_1);
                                }

                                if (game[i][j].nearby_bombs == 2) {

                                    game[i][j].icon.setTexture(number_2);
                                }

                                if (game[i][j].nearby_bombs == 3) {

                                    game[i][j].icon.setTexture(number_3);
                                }

                                if (game[i][j].nearby_bombs == 4) {

                                    game[i][j].icon.setTexture(number_4);
                                }

                                if (game[i][j].nearby_bombs == 5) {

                                    game[i][j].icon.setTexture(number_5);
                                }

                                if (game[i][j].nearby_bombs == 6) {

                                    game[i][j].icon.setTexture(number_6);
                                }

                                if (game[i][j].nearby_bombs == 7) {

                                    game[i][j].icon.setTexture(number_7);
                                }

                                if (game[i][j].nearby_bombs == 8) {

                                    game[i][j].icon.setTexture(number_8);
                                }
                            }
                        }
                    }

                    if (debug_on) {

                        for (int i = 0; i < height; i++) {

                            for (int j = 0; j < width; j++) {

                                if (game[i][j].mine_status == 1) {

                                    game[i][j].debugged = true;
                                }
                            }
                        }
                    }
                }
            }

            if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right) {

                int x = sf::Mouse::getPosition(window).x / 32;
                int y = sf::Mouse::getPosition(window).y / 32;

                if (((x >= 0) && (x < width)) && ((y >= 0) && (y < height)) && play) {

                    if (!game[y][x].is_revealed) {

                        if (!game[y][x].flagged) {

                            counter.flags_left--;
                            game[y][x].flagged = true;
                        }

                        else {

                            counter.flags_left++;
                            game[y][x].flagged = false;
                        }
                    }
                }
            }
        }

        window.clear();

        window.draw(game_status);
        window.draw(debug_button);
        window.draw(test1_button);
        window.draw(test2_button);
        window.draw(test3_button);

        counter.s_flags_left = to_string(counter.flags_left);

        if (counter.s_flags_left.length() == 4) {

            counter.c_first_digit = counter.s_flags_left[1];
            counter.c_second_digit = counter.s_flags_left[2];
            counter.c_third_digit = counter.s_flags_left[3];

            window.draw(counter.negative_sign);
            counter.first_digit.setTextureRect(sf::IntRect(21 * int(counter.c_first_digit - '0'), 0, 21, 32));
            window.draw(counter.first_digit);
            counter.second_digit.setTextureRect(sf::IntRect(21 * int(counter.c_second_digit - '0'), 0, 21, 32));
            window.draw(counter.second_digit);
            counter.third_digit.setTextureRect(sf::IntRect(21 * int(counter.c_third_digit - '0'), 0, 21, 32));
            window.draw(counter.third_digit);
        }

        else if (counter.s_flags_left.length() == 3) {

            if (counter.flags_left > 0) {

                counter.c_first_digit = counter.s_flags_left[0];
                counter.c_second_digit = counter.s_flags_left[1];
                counter.c_third_digit = counter.s_flags_left[2];

                counter.first_digit.setTextureRect(sf::IntRect(21 * int(counter.c_first_digit - '0'), 0, 21, 32));
                window.draw(counter.first_digit);
                counter.second_digit.setTextureRect(sf::IntRect(21 * int(counter.c_second_digit - '0'), 0, 21, 32));
                window.draw(counter.second_digit);
                counter.third_digit.setTextureRect(sf::IntRect(21 * int(counter.c_third_digit - '0'), 0, 21, 32));
                window.draw(counter.third_digit);
            }

            else {

                counter.c_second_digit = counter.s_flags_left[1];
                counter.c_third_digit = counter.s_flags_left[2];

                window.draw(counter.negative_sign);
                counter.first_digit.setTextureRect(sf::IntRect(21 * 0, 0, 21, 32));
                window.draw(counter.first_digit);
                counter.second_digit.setTextureRect(sf::IntRect(21 * int(counter.c_second_digit - '0'), 0, 21, 32));
                window.draw(counter.second_digit);
                counter.third_digit.setTextureRect(sf::IntRect(21 * int(counter.c_third_digit - '0'), 0, 21, 32));
                window.draw(counter.third_digit);
            }
        }

        else if (counter.s_flags_left.length() == 2) {

            if (counter.flags_left > 0) {

                counter.c_second_digit = counter.s_flags_left[0];
                counter.c_third_digit = counter.s_flags_left[1];

                counter.first_digit.setTextureRect(sf::IntRect(21 * 0, 0, 21, 32));
                window.draw(counter.first_digit);
                counter.second_digit.setTextureRect(sf::IntRect(21 * int(counter.c_second_digit - '0'), 0, 21, 32));
                window.draw(counter.second_digit);
                counter.third_digit.setTextureRect(sf::IntRect(21 * int(counter.c_third_digit - '0'), 0, 21, 32));
                window.draw(counter.third_digit);
            }

            else {

                counter.c_third_digit = counter.s_flags_left[1];

                window.draw(counter.negative_sign);
                counter.first_digit.setTextureRect(sf::IntRect(21 * 0, 0, 21, 32));
                window.draw(counter.first_digit);
                counter.second_digit.setTextureRect(sf::IntRect(21 * 0, 0, 21, 32));
                window.draw(counter.second_digit);
                counter.third_digit.setTextureRect(sf::IntRect(21 * int(counter.c_third_digit - '0'), 0, 21, 32));
                window.draw(counter.third_digit);
            }
        }

        else if (counter.s_flags_left.length() == 1) {

            counter.c_third_digit = counter.s_flags_left[0];

            counter.first_digit.setTextureRect(sf::IntRect(21 * 0, 0, 21, 32));
            window.draw(counter.first_digit);
            counter.second_digit.setTextureRect(sf::IntRect(21 * 0, 0, 21, 32));
            window.draw(counter.second_digit);
            counter.third_digit.setTextureRect(sf::IntRect(21 * int(counter.c_third_digit - '0'), 0, 21, 32));
            window.draw(counter.third_digit);
        }

        for (int i = 0; i < height; i++) {

            for (int j = 0; j < width; j++) {

                window.draw(game[i][j].cover);

                if (game[i][j].is_revealed) {

                    window.draw(game[i][j].icon);
                }

                else if (game[i][j].debugged) {

                    window.draw(game[i][j].icon);
                }

                else {

                    if (game[i][j].flagged) {

                        game[i][j].flag.setTexture(flag);
                        window.draw(game[i][j].flag);
                    }
                }
            }
        }

        window.display();
    }

    return 0;
}