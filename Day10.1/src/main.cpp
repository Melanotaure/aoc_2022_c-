#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include <vector>
#include <map>
#include <utility>
#include <stack>

#define input_file_name ("inputs.txt")

std::array<uint8_t, 40> sprite_position;
std::array<std::array<uint8_t, 40>, 6> CRT;
void move_srpite(int32_t prev, int32_t current);
void draw_pixel(uint32_t cycle);

int main()
{
    int32_t regX = 1;
    int32_t prev_regX = 1;
    move_srpite(prev_regX, regX);
 
    std::ifstream filestrm(input_file_name);
    if(filestrm.is_open())
    {
        std::string line;
        int32_t V;
        uint32_t cycle = 0;

        while(!filestrm.eof())
        {
            std::getline(filestrm, line);
            if (line == "noop")
            {
                cycle++;
                draw_pixel(cycle);
            }
            else
            {
                V = std::stoi(line.substr(5));
                cycle++;
                draw_pixel(cycle);
                cycle++;
                draw_pixel(cycle);
                prev_regX = regX;
                regX += V;
                move_srpite(prev_regX, regX);
            }
        }
    }
    else
    {
        std::cout << "Unable to open file: " << input_file_name << std::endl;
    }

    // Part 1
    std::cout << "PART 2" << std::endl;
    for (auto i = 0; i < 6; i++)
    {
        for (auto j = 0; j < 40; j++)
        {
            std::cout << ((CRT[i][j] == 0) ? ' ' : '#');
        }
        std::cout << std::endl;
    }

    return 0;
}

void move_srpite(int32_t prev, int32_t current)
{
    sprite_position[prev-1]    = 0;
    sprite_position[prev]      = 0;
    sprite_position[prev+1]    = 0;
    sprite_position[current-1] = 1;
    sprite_position[current]   = 1;
    sprite_position[current+1] = 1;
}

void draw_pixel(uint32_t cycle)
{
    cycle--;
    auto line = cycle / 40;
    auto row = cycle % 40;
    CRT[line][row] = sprite_position[row];
}