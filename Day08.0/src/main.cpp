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

std::vector<std::vector<uint8_t>> map;
bool is_visible(std::size_t x, std::size_t y);
uint32_t scenic_score(std::size_t x, std::size_t y);

int main()
{
    std::ifstream filestrm(input_file_name);
    if(filestrm.is_open())
    {
        std::string cmd;

        std::string line;
        auto i = 0;
        while(!filestrm.eof())
        {
            std::getline(filestrm, line);
            std::vector<uint8_t> hline;
            for (auto c : line)
            {
                hline.push_back(c);
            }
            map.push_back(hline);
        }
    }
    else
    {
        std::cout << "Unable to open file: " << input_file_name << std::endl;
    }

    // Part 1
    auto count = 0;
    for (auto i = 1; i< map.size()-1; i++)
    {
        for(auto j = 1; j < map[i].size()-1; j++)
        {
            if (is_visible(i, j)) count++;
        }
    }

    count += 2 * map.size();
    count += 2 * (map[0].size() - 2);
    std::cout << "PART 1" << std::endl;
    std::cout << "Result: " << count << std::endl << std::endl;

    // Part 2
    auto max = 0;
    for (auto i = 1; i< map.size()-1; i++)
    {
        for(auto j = 1; j < map[i].size()-1; j++)
        {
            auto vd = scenic_score(i, j);
            if (vd > max) max = vd;
        }
    }

    std::cout << "PART 2" << std::endl;
    std::cout << "Result: " << max << std::endl;

    return 0;
}

bool is_visible(std::size_t x, std::size_t y)
{
    // from left
    auto max = 0;
    for (auto j = 0; j < y; j++)
    {
        if (map[x][j] > max)
        {
            max = map[x][j];
        }
    }
    if (map[x][y] > max) return true;

    // from right
    max = 0;
    for (auto j = y+1; j < map[x].size(); j++)
    {
        if (map[x][j] > max)
        {
            max = map[x][j];
        }
    }
    if (map[x][y] > max) return true;

    // from top
    max = 0;
    for (auto i = 0; i < x; i++)
    {
        if (map[i][y] > max)
        {
            max = map[i][y];
        }
    }
    if (map[x][y] > max) return true;

    // from bottom
    max = 0;
    for (auto i = x+1; i < map.size(); i++)
    {
        if (map[i][y] > max)
        {
            max = map[i][y];
        }
    }
    if (map[x][y] > max) return true;

    return false;
}

uint32_t scenic_score(std::size_t x, std::size_t y)
{
    auto tree = map[x][y];

    // to the left
    auto cnt_left = 0;
    for (int32_t j = y-1; j >=0; j--)
    {
        cnt_left++;
        if (map[x][j] >= tree)
        {
            break;
        }
    }

    // to the right
    auto cnt_right = 0;
    for (auto j = y+1; j < map[x].size(); j++)
    {
        cnt_right++;
        if (map[x][j] >= tree)
        {
            break;
        }
    }

    // to the top
    auto cnt_top = 0;
    for (int32_t i = x-1; i >=0; i--)
    {
        cnt_top++;
        if (map[i][y] >= tree)
        {
            break;
        }
    }

    // to the bottom
    auto cnt_bottom = 0;
    for (auto i = x+1; i < map.size(); i++)
    {
        cnt_bottom++;
        if (map[i][y] >= tree)
        {
            break;
        }
    }

    auto score = cnt_left * cnt_right * cnt_top * cnt_bottom;

    return score;
}