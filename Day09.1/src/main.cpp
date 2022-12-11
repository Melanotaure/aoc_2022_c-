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

std::map<std::pair<int32_t, int32_t>, uint32_t> positions;
std::vector<std::pair<int32_t, int32_t>> knots;
void move_head_tail(char dir, uint32_t dep);

int main()
{
    for (auto i = 0; i < 10; i++)
    {
        knots.push_back(std::make_pair(0, 0));
    }
    positions[std::make_pair(0, 0)]++;

    std::ifstream filestrm(input_file_name);
    if(filestrm.is_open())
    {
        char direction;
        uint32_t nb_mov;

        while(filestrm >> direction >> nb_mov)
        {
            move_head_tail(direction, nb_mov);
        }
    }
    else
    {
        std::cout << "Unable to open file: " << input_file_name << std::endl;
    }

    // Part 2
    std::cout << "PART 2" << std::endl;
    std::cout << "Result: " << positions.size() << std::endl << std::endl;

    return 0;
}

void move_head_tail(char dir, uint32_t dep)
{
    for (auto i = 0; i < dep; i++)
    {
        switch (dir)
        {
            case 'R':
                knots[0].first++;
                break;
            case 'L':
                knots[0].first--;
                break;
            case 'U':
                knots[0].second++;
                break;
            case 'D':
                knots[0].second--;
                break;
        }

        for (auto j = 0; j < 9; j++)
        {
            auto dx = knots[j].first - knots[j+1].first;
            auto dy = knots[j].second - knots[j+1].second;

            if (std::abs(dx) > 1 || std::abs(dy) > 1)
            {
                if (dx == 0) knots[j+1].second += dy/2;
                else if (dy == 0) knots[j+1].first += dx/2;
                else
                {
                    knots[j+1].first += (dx > 0) ? 1 : (-1);
                    knots[j+1].second += (dy > 0) ? 1 : (-1); 
                }
            }
        }
        positions[knots[9]]++;
    }
}