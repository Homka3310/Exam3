#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <conio.h>

using std::vector;
using std::cout;

const unsigned short SIZE = 4;

vector<int> in_game_map(SIZE);
vector<vector<int>> game_map(SIZE, in_game_map);

vector<int> in_right_map(SIZE);
vector<vector<int>> right_map(SIZE, in_right_map);

struct coordinate
{
    unsigned x;
    unsigned y;
} zero;

void create_right_map()
{
    unsigned right_value = 1;
    for (unsigned i = 0; i < SIZE; i++)
    {
        for (unsigned j = 0; j < SIZE; j++)
            right_map[i][j] = right_value++;
    }
    right_map[SIZE - 1][SIZE - 1] = 0;
}

void create_game_map()
{
    unsigned limit = SIZE * SIZE;
    vector<int> temporary;
    for (unsigned i = 0; i < limit; i++)
        temporary.push_back(i);

    int value;
    for (unsigned i = 0; i < SIZE; i++)
    {
        for (unsigned j = 0; j < SIZE; j++)
        {
            value = rand() % limit--;
            game_map[i][j] = temporary[value];
            if (temporary[value] == 0)
            {
                zero.x = j;
                zero.y = i;
            }
            temporary.erase(temporary.begin() + value);
        }
    }
}

bool check_map()
{
    if (game_map == right_map)
        return true;
    return false;
}

void up_move()
{
    if (zero.y < SIZE - 1)
    {
        game_map[zero.y][zero.x] = game_map[zero.y + 1][zero.x];
        zero.y++;
        game_map[zero.y][zero.x] = 0;
    }
}

void down_move()
{
    if (zero.y > 0)
    {
        game_map[zero.y][zero.x] = game_map[zero.y - 1][zero.x];
        zero.y--;
        game_map[zero.y][zero.x] = 0;
    }
}

void right_move()
{
    if (zero.x > 0)
    {
        game_map[zero.y][zero.x] = game_map[zero.y][zero.x - 1];
        zero.x--;
        game_map[zero.y][zero.x] = 0;
    }
}

void left_move()
{
    if (zero.x < SIZE - 1)
    {
        game_map[zero.y][zero.x] = game_map[zero.y][zero.x + 1];
        zero.x++;
        game_map[zero.y][zero.x] = 0;
    }
}

void get_direction()
{
    int move = static_cast<int> (_getch());
    switch (move)
    {
    case 72:
    {
        up_move(); break;
    }
    case 80:
    {
        down_move(); break;
    }
    case 77:
    {
        right_move(); break;
    }
    case 75:
    {
        left_move(); break;
    }
    default:
    {
        get_direction();
    }
    }
}
void screen()
{
    system("cls");
    for (unsigned i = 0; i < SIZE; i++)
    {
        for (unsigned j = 0; j < SIZE; j++)
        {
            if (game_map[i][j] != 0)
                cout << std::setw(2) << std::setfill('0') << game_map[i][j] << ' ';
            else
                cout << "** ";
        }
        cout << '\n';
    }
}

int main()
{
    srand(static_cast<int>(time(NULL)));

    create_right_map();
    do
    {
        create_game_map();
    } while (check_map());

    do
    {
        screen();
        get_direction();
    } while (!check_map());

    cout << "You win! Game over!";
    _getch();
}