#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include <vector>
#include <map>
#include <utility>
#include <stack>
#include <algorithm>

#define input_file_name ("inputs.txt")
#define MAX 150

using Point = std::pair<int32_t, int32_t>;

struct Elf
{
    Point cpos;
    Point ppos;
};

struct Direction
{
    char name;
    Point d1;
    Point front;
    Point d2;
};

std::vector<Elf> elves;
std::vector<Direction> directions;
std::map<Point, int32_t> terrain;

void init_directions();
bool do_one_round(uint32_t current_direction);
void display_map();
void display_elves();
bool can_mov(Elf& elf, uint32_t direction);
int32_t find_empty_spaces();

int main()
{
    init_directions();

    std::ifstream filestrm(input_file_name);
    if(filestrm.is_open())
    {
        auto j = 0;
        std::string line;
        while(!filestrm.eof())
        {
            auto i = 0;
            std::getline(filestrm, line);
            for (auto c : line)
            {
                if (c == '#')
                {
                    Elf one_elf;
                    one_elf.cpos = std::make_pair(i, j);
                    one_elf.ppos = std::make_pair(i, j);
                    elves.emplace_back(one_elf);
                    terrain[one_elf.cpos] = -1;
                }
                else
                {
                    terrain[std::make_pair(i,j)] = 0;
                }
                i++;
            }
            j++;
        }
    }
    else
    {
        std::cout << "Unable to open file: " << input_file_name << std::endl;
    }

    for (auto round = 0; round < 10; round++)
    {
        do_one_round(round % directions.size());
    }

    // Part 1
    std::cout << "PART 1" << std::endl;
    std::cout << "Empty tiles: " << find_empty_spaces() << std::endl;

    return 0;
}

void init_directions()
{
    Direction dir;
    // North
    dir.name = 'N';
    dir.d1.first = -1;
    dir.d1.second = -1;
    dir.front.first = 0;
    dir.front.second = -1;
    dir.d2.first = 1;
    dir.d2.second = -1;
    directions.emplace_back(dir);
    // South
    dir.name = 'S';
    dir.d1.first = 1;
    dir.d1.second = 1;
    dir.front.first = 0;
    dir.front.second = 1;
    dir.d2.first = -1;
    dir.d2.second = 1;
    directions.emplace_back(dir);
    // West
    dir.name = 'W';
    dir.d1.first = -1;
    dir.d1.second = 1;
    dir.front.first = -1;
    dir.front.second = 0;
    dir.d2.first = -1;
    dir.d2.second = -1;
    directions.emplace_back(dir);
    // East
    dir.name = 'E';
    dir.d1.first = 1;
    dir.d1.second = -1;
    dir.front.first = 1;
    dir.front.second = 0;
    dir.d2.first = 1;
    dir.d2.second = 1;
    directions.emplace_back(dir);
}

bool do_one_round(uint32_t current_direction)
{
    bool no_mov = true;
    for (auto i = 0; i < elves.size(); i++)
    {
        auto res = can_mov(elves[i], current_direction);
        no_mov = no_mov && !res;
    }
    if (no_mov)
    {
        std::cout << "no move" << std::endl;
        return false;
    }

    for (auto i = 0; i < elves.size(); i++)
    {
        if (terrain[elves[i].cpos] > 1)
        {
            elves[i].cpos = elves[i].ppos;
        }
        else
        {
            terrain[elves[i].ppos] = 0;
            terrain[elves[i].cpos] = -1;
            elves[i].ppos = elves[i].cpos;
        }
    }

    for (auto [p, v] : terrain)
    {
        if (v > 0) terrain[p] = 0;
    }

    return true;
}

void display_map()
{
    for (auto j = 0; j < 12; j++)
    {
        for (auto i = 0; i < 14; i++)
        {
            std::cout << ((terrain.at(std::make_pair(i,j)) == -1) ? '#' : '.');
        }
        std::cout << std::endl;
    }
}

void display_elves()
{
    for (auto elf : elves)
    {
        std::cout << "(" << elf.cpos.first << ", " << elf.cpos.second << ")" << std::endl;
    }
}

bool can_mov(Elf& elf, uint32_t direction)
{
    bool can_mov = false;
    auto x = elf.cpos.first;
    auto y = elf.cpos.second;
    auto N = std::make_pair(x, y-1);
    auto S = std::make_pair(x, y+1);
    auto E = std::make_pair(x+1, y);
    auto W = std::make_pair(x-1, y);
    auto NW = std::make_pair(x-1, y-1);
    auto NE = std::make_pair(x+1, y-1);
    auto SE = std::make_pair(x+1, y+1);
    auto SW = std::make_pair(x-1, y+1);
    can_mov = terrain[N] != -1 && terrain[NE] != -1 &&
              terrain[E] != -1 && terrain[SE] != -1 &&
              terrain[S] != -1 && terrain[SW] != -1 &&
              terrain[W] != -1 && terrain[NW] != -1;
    if (can_mov) return false;

    for (auto d = 0; d < directions.size(); d++)
    {
        auto d1x = elf.cpos.first + directions[(d + direction) % directions.size()].d1.first;
        auto d1y = elf.cpos.second + directions[(d + direction) % directions.size()].d1.second;
        auto d2x = elf.cpos.first + directions[(d + direction) % directions.size()].d2.first;
        auto d2y = elf.cpos.second + directions[(d + direction) % directions.size()].d2.second;
        auto fx = elf.cpos.first + directions[(d + direction) % directions.size()].front.first;
        auto fy = elf.cpos.second + directions[(d + direction) % directions.size()].front.second;

        if (terrain[std::make_pair(d1x,d1y)] != -1 && terrain[std::make_pair(d2x,d2y)] != -1 && terrain[std::make_pair(fx,fy)] != -1)
        {
            elf.cpos = std::make_pair(fx, fy);
            terrain[elf.cpos]++;
            return true;
        }
    }
    //return false;
}

int32_t find_empty_spaces()
{
    // first let's find the smallest rectangle
    // wrapping all the elves
    int32_t minx = elves[0].cpos.first;
    int32_t miny = elves[0].cpos.second;
    int32_t maxx = elves[0].cpos.first;
    int32_t maxy = elves[0].cpos.second;

    for (auto& elf : elves)
    {
        auto x = elf.cpos.first;
        auto y = elf.cpos.second;

        minx = ((x < minx) ? x : minx);
        miny = ((y < miny) ? y : miny);
        maxx = ((x > maxx) ? x : maxx);
        maxy = ((y > maxy) ? y : maxy);
    }

    auto count = (maxx - minx +1) * (maxy - miny +1) - (int32_t)elves.size();
    return count;
}