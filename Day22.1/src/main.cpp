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

struct Position
{
    Point point;
    Point direction;
};

std::vector<std::array<char, MAX>> terrain;

void find_start(Point& p);
void move_forward(Position& p, int32_t m);
void display_position(Position& p);
int32_t my_mod(int32_t dividend, int32_t divisor);

int main()
{
    Position me = {{0, 0}, {1, 0}};
    std::ifstream filestrm(input_file_name);
    if(filestrm.is_open())
    {
        std::string line;
        while(!filestrm.eof())
        {
            std::array<char, MAX> row;
            std::getline(filestrm, line);
            if (line[0] == ' ' || line[0] == '.' || line[0] == '#')
            {
                auto i = 0;
                while ((i < MAX) && (line[i] == ' ' || line[i] == '.' || line[i] == '#'))
                {
                    row[i] = line[i];
                    i++;
                }
                while (i < MAX) row[i++] = ' ';
                terrain.push_back(row);
            }
            else
            {
                find_start(me.point);
                for (auto i = 0; i < line.size(); i++)
                {
                    if (line[i] >= '0' && line[i] <= '9')
                    {
                        auto nb_mov = 0;
                        while (line[i] >= '0' && line[i] <= '9' && i < line.size())
                        {
                            nb_mov = 10*nb_mov + (line[i] - '0');
                            i++;
                        }
                        move_forward(me, nb_mov);
                    }
                    if (line[i] == 'R')
                    {
                        auto tmpx = -me.direction.second;
                        auto tmpy = me.direction.first;
                        me.direction.first = tmpx;
                        me.direction.second = tmpy;
                    }
                    else if (line[i] == 'L')
                    {
                        auto tmpx = me.direction.second;
                        auto tmpy = -me.direction.first;
                        me.direction.first = tmpx;
                        me.direction.second = tmpy;
                    }
                }
            }
        }
    }
    else
    {
        std::cout << "Unable to open file: " << input_file_name << std::endl;
    }

    auto password = 1000 * (me.point.second+1) + 4 * (me.point.first+1);
    if (me.direction.first == 1) password += 0;
    else if (me.direction.first == -1) password += 2;
    else if (me.direction.second == 1) password += 1;
    else if (me.direction.second == -1) password += 3;

    std::cout << "Final position: (" << me.point.first << ", " << me.point.second << ") and direction: (" << me.direction.first << ", " << me.direction.second << ")" << std::endl;
    // Part 1
    std::cout << "PART 2" << std::endl;
    std::cout <<"Password: " << password << std::endl;

    return 0;
}

void find_start(Point& p)
{
    auto i = 0;

    while (terrain[0][i] == ' ' && i < terrain[0].size())
    {
        i++;
    }

    p = std::make_pair(i, 0);
}

void move_forward(Position& p, int32_t m)
{
    auto dx = p.direction.first;
    auto dy = p.direction.second;

    for (auto d = 0; d < m; d++)
    {
        auto cdx = dx;
        auto cdy = dy;
        auto x = p.point.first + dx;
        auto y = p.point.second + dy;

        if (y < 0 && x >= 50 && x < 100 && dy == -1)
        {
            dy = 0; dx = 1;
            y = x + 100; x = 0;
        }
        else if (y < 0 && x >= 100 && x < 150 && dy == -1)
        {
            y = 199; x = x - 100;
        }
        else if (y < 100 && x >= 0 && x < 50 && dy == -1)
        {
            dy = 0; dx = 1;
            y = x + 50; x = 50;
        }
        else if (y >= 50 && x >= 100 && x < 150 && dy == 1)
        {
            dy = 0; dx = -1;
            y = x - 50; x = 99;
        }
        else if (y >= 150 && x >= 50 && x < 100 && dy == 1)
        {
            dy = 0; dx = -1;
            y = x + 100; x = 49;
        }
        else if (y >= 200 && x >= 0 && x < 50 && dy == 1)
        {
            y = 0; x = x + 100;
        }
        else if (x >= 150 && y >= 0 && y < 50 && dx == 1)
        {
            dx = -1;
            x = 99; y = 149 - y;
        }
        else if (x >= 100 && y >= 50 && y < 100 && dx == 1)
        {
            dx = 0; dy = -1;
            x = y + 50; y = 49;
        }
        else if (x >= 100 && y >= 100 && y < 150 && dx == 1)
        {
            dx = -1;
            x = 149; y = 149 - y;
        }
        else if (x >= 50 && y >= 150 && y < 200 && dx == 1)
        {
            dx = 0; dy = -1;
            x = y - 100; y = 149;
        }
        else if (x < 50 && y >= 0 && y < 50 && dx == -1)
        {
            dx = 1;
            x = 0; y = 149 - y;
        }
        else if (x < 50 && y >= 50 && y < 100 && dx == -1)
        {
            dx = 0; dy = 1;
            x = y - 50; y = 100;
        }
        else if (x < 0 && y >= 100 && y < 150 && dx == -1)
        {
            dx = 1;
            x = 50; y = 149 - y;
        }
        else if (x < 0 && y >= 150 && y < 200 && dx == -1)
        {
            dx = 0; dy = 1;
            x = y - 100; y = 0;
        }
        if (terrain[y][x] == '#')
        {
            p.direction.first = cdx;
            p.direction.second = cdy;
            return;
        }
        p.point.first = x;
        p.point.second = y;
    }
    p.direction.first = dx;
    p.direction.second = dy;
}

void display_position(Position& p)
{
    for (auto j = 0; j < terrain.size(); j++)
    {
        for (auto i = 0; i < terrain[j].size(); i++)
        {
            if (p.point.first == i && p.point.second == j)
            {
                if (p.direction.first == 1) std::cout << ">";
                else if (p.direction.first == -1) std::cout << "<";
                else if (p.direction.second == 1) std::cout << "v";
                else if (p.direction.second == -1) std::cout << "^";
            }
            else std::cout << terrain[j][i];
        }
        std::cout << std::endl;
    }
}

int32_t my_mod(int32_t dividend, int32_t divisor)
{
    auto x = dividend % divisor;
    if (x < 0) x = divisor + x;
    return x;
}