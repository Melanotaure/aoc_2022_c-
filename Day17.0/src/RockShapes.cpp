#include <iostream>
#include "../Inc/RockShape.hpp"

void RockChamber::add_rock(RockShape* rock)
{
    this->rock = rock;
    find_the_highest();
    int64_t delta = (highest_point.second + 3 + rock->height);
    if (!shaft.empty()) delta -= shaft.size();

    std::vector<uint8_t> line = {0,0,0,0,0,0,0};
    for (auto i = 0; i < delta; i++)
    {
        shaft.emplace_back(line);
    }
    rock->move_rock(std::make_pair(2, (highest_point.second + 3)));
    for (auto&& p : rock->shape)
    {
        shaft[p.second][p.first] = 2;
    }
}

void RockChamber::jet_effect(char jet)
{
    // The jet effect first
    if (jet == '>')
    {
        for (auto&& p : rock->shape)
        {
            if (p.first + 1 >= shaft[0].size()) return;
            if (shaft[p.second][p.first+1] == 1) return;
        }
        erase_rock();
        rock->move_rock(std::make_pair(1,0));
        draw_rock(2);
    }
    else if (jet == '<')
    {
        for (auto&& p : rock->shape)
        {
            if (p.first - 1 < 0) return;
            if (shaft[p.second][p.first-1] == 1) return;
        }
        erase_rock();
        rock->move_rock(std::make_pair(-1,0));
        draw_rock(2);
    }
    else return;
}

bool RockChamber::move_rock_down()
{
    // Check if obstacle down
    for (auto&& p : rock->shape)
    {
        if ((p.second - 1) < 0 || shaft[p.second-1][p.first] == 1)
        {
            draw_rock(1);
            return false;
        }
    }
    // Rock can go down
    // Update rock in shaft
    erase_rock();
    rock->move_rock(std::make_pair(0,-1));
    draw_rock(2);

    return true;
}

void RockChamber::erase_rock()
{
    for (auto p : rock->shape)
    {
        shaft[p.second][p.first] = 0;
    }
}

void RockChamber::draw_rock(uint8_t movement)
{
    for (auto p : rock->shape)
    {
        shaft[p.second][p.first] = movement;
    }
}

void RockChamber::find_the_highest()
{
    if (!shaft.empty())
    {
        for (uint64_t y  = shaft.size() -1; y >= 0; y--)
        {
            for (uint64_t x = 0; x < shaft[0].size(); x++)
            {
                if (shaft[y][x] == 1)
                {
                    highest_point = std::make_pair(x, y+1);
                    return;
                }
            }
        }
    }
    highest_point = std::make_pair(0, 0);
}