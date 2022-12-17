#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include <vector>
#include <map>
#include <utility>
#include <deque>
#include <algorithm>

#define input_file_name ("inputs.txt")

using point = std::pair<int32_t, int32_t>;

struct Position
{
    Position(point p, uint32_t step): p(p), steps(step) {};
    point p;
    uint32_t steps;
};

std::vector<std::vector<char>> my_map;
std::deque<Position> history;
std::map<point, int> visited;

int main()
{
    point start;
    point end;

    std::ifstream filestrm(input_file_name);
    if(filestrm.is_open())
    {
        std::string line;
        auto y = 0;
        while(!filestrm.eof())
        {
            std::getline(filestrm, line);
            std::vector<char> hline;
            auto x = 0;
            for (auto c : line)
            {
                if (c == 'S')
                {
                    start = std::make_pair(x, y);
                    c = 'a';
                }
                if (c == 'E')
                {
                    end = std::make_pair(x, y);
                    c = 'z';
                }
                hline.emplace_back(c);
                x++;
            }
            my_map.push_back(hline);
            y++;
        }
    }
    else
    {
        std::cout << "Unable to open file: " << input_file_name << std::endl;
    }

    // Part 2
    std::cout << "PART 2" << std::endl;
    std::cout << "Start point: " << start.first << ", " << start.second << std::endl;
    std::cout << "End point  : " << end.first << ", " << end.second << std::endl;

    history.emplace_back(end, 0);
    visited[end] = 1;
    while (!history.empty())
    {
        auto curr_position = history.front();
        history.pop_front();

        std::vector<point> connex;
        // left
        connex.emplace_back(curr_position.p.first-1, curr_position.p.second);
        // right
        connex.emplace_back(curr_position.p.first+1, curr_position.p.second);
        // up
        connex.emplace_back(curr_position.p.first, curr_position.p.second-1);
        // down
        connex.emplace_back(curr_position.p.first, curr_position.p.second+1);
        for (auto&& p : connex)
        {
            if (p.first < 0 || p.second < 0 || p.first >= my_map[0].size() || p.second >= my_map.size())
                continue;
            if (visited[p] != 0) continue;
            if (my_map[p.second][p.first] - my_map[curr_position.p.second][curr_position.p.first] < -1)
                continue;
            if (my_map[p.second][p.first] == 'a')
            {
                std::cout << curr_position.steps + 1 << " steps to reach end point (" << p.first << ", " << p.second << ")." << std::endl;
                return 0;
            }
            visited[p] = 1;
            history.emplace_back(p, curr_position.steps + 1);
        }
    }

    return 0;
}
