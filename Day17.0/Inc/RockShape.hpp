#include <string>
#include <vector>
#include <map>
#include <deque>
#include <utility>
#include <algorithm>

using Point = std::pair<int64_t, int64_t>;

struct RockShape
{
    std::vector<Point> shape;
    uint32_t height;
    uint32_t length;

    void move_rock(Point direction)
    {
        for (auto& s : shape)
        {
            s.first += direction.first;
            s.second += direction.second;
        }
    };
};

struct HBarRock : public RockShape
{
    HBarRock()
    {
        shape.emplace_back(0,0);
        shape.emplace_back(1,0);
        shape.emplace_back(2,0);
        shape.emplace_back(3,0);
        height = 1;
        length = 4;
    };

    HBarRock(Point origin)
    {
        HBarRock();
        move_rock(origin);
    };
};

struct VBarRock : public RockShape
{
    VBarRock()
    {
        shape.emplace_back(0,0);
        shape.emplace_back(0,1);
        shape.emplace_back(0,2);
        shape.emplace_back(0,3);
        height = 4;
        length = 1;
    };

    VBarRock(Point origin)
    {
        VBarRock();
        move_rock(origin);
    };
};

struct CrossRock : public RockShape
{
    CrossRock()
    {
        shape.emplace_back(1,0);
        shape.emplace_back(0,1);
        shape.emplace_back(1,1);
        shape.emplace_back(2,1);
        shape.emplace_back(1,2);
        height = 3;
        length = 3;
    };

    CrossRock(Point origin)
    {
        CrossRock();
        move_rock(origin);
    };
};

struct JayRock : public RockShape
{
    JayRock()
    {
        shape.emplace_back(0,0);
        shape.emplace_back(1,0);
        shape.emplace_back(2,0);
        shape.emplace_back(2,1);
        shape.emplace_back(2,2);
        height = 3;
        length = 3;
    };

    JayRock(Point origin)
    {
        JayRock();
        move_rock(origin);
    };
};

struct SquareRock : public RockShape
{
    SquareRock()
    {
        shape.emplace_back(0,0);
        shape.emplace_back(1,0);
        shape.emplace_back(0,1);
        shape.emplace_back(1,1);
        height = 2;
        length = 2;
    };

    SquareRock(Point origin)
    {
        SquareRock();
        move_rock(origin);
    };
};

struct RockChamber
{
    std::vector<std::vector<uint8_t>> shaft;
    RockShape* rock;
    Point highest_point;

    void add_rock(RockShape* rock);
    void jet_effect(char jet);
    bool move_rock_down();
    void erase_rock();
    void draw_rock(uint8_t movement);
    void find_the_highest();
};