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
void move_head_tail(char dir, int32_t& hx, int32_t& hy, int32_t& tx, int32_t& ty, uint32_t dep);

int main()
{
    std::ifstream filestrm(input_file_name);
    if(filestrm.is_open())
    {
        char direction;
        uint32_t nb_mov;
        int32_t tx = 0;
        int32_t ty = 0;
        int32_t hx = 0;
        int32_t hy = 0;
        positions[std::make_pair(tx, ty)]++;

        while(filestrm >> direction >> nb_mov)
        {
            move_head_tail(direction, hx, hy, tx, ty, nb_mov);
        }
    }
    else
    {
        std::cout << "Unable to open file: " << input_file_name << std::endl;
    }

    // Part 1
    std::cout << "PART 1" << std::endl;
    std::cout << "Result: " << positions.size() << std::endl << std::endl;

    return 0;
}

void move_head_tail(char dir, int32_t& hx, int32_t& hy, int32_t& tx, int32_t& ty, uint32_t dep)
{
    for (auto i = 0; i < dep; i++)
    {
        switch (dir)
        {
            case 'R':
                hx++;
                break;
            case 'L':
                hx--;
                break;
            case 'U':
                hy++;
                break;
            case 'D':
                hy--;
                break;
        }

        auto dx = hx - tx;
        if (dx > 1)
        {
            tx = hx - 1;
            ty = hy;
        }
        else if (dx < -1)
        {
            tx = hx + 1;
            ty = hy;
        }
        
        auto dy = hy - ty;
        if (dy > 1)
        {
            ty = hy - 1;
            tx = hx;
        }
        else if (dy < -1)
        {
            ty = hy + 1;
            tx = hx;
        }

        positions[std::make_pair(tx, ty)]++;
    }
}