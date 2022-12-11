#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include <vector>
#include <map>
#include <utility>
#include <list>

#define input_file_name ("inputs.txt")

constexpr uint32_t ROUND_MAX = 10000;

struct Monkey
{
    Monkey(char op, int32_t value, uint32_t div, uint32_t m_id1, uint32_t m_id2): operation(op), value(value), div(div), monkey_id1(m_id1), monkey_id2(m_id2) {};
    std::list<uint64_t> items;
    char operation;
    int32_t value;
    uint32_t div;
    uint32_t monkey_id1;
    uint32_t monkey_id2;
    uint64_t inspections = 0;

    void worriness()
    {
        if (!items.empty())
        {
            int32_t used_value = value;
            uint64_t current_item = items.front();
            if (value == -1) used_value = current_item;
            if (operation == '*') current_item = current_item * used_value;
            else if (operation == '+') current_item = current_item + used_value;
            items.front() = current_item;
            //inspections++;
        }
    };

    std::pair<uint64_t, int32_t> test(uint64_t w)
    {
        uint64_t ret_item = 0;
        auto m_id = 0;
        if (!items.empty())
        {
            if (w == 0)
                ret_item = items.front() / 3;
            else
                ret_item = items.front() % w;

            if (ret_item % div == 0)
            {
                m_id = monkey_id1;
            }
            else
            {
                m_id = monkey_id2;
            }
            items.pop_front();
            inspections++;
        }
        else m_id = -1;
        return std::make_pair(ret_item, m_id);
    };
};

int main()
{
    std::vector<Monkey*> monkeys;

    // Monkeys def
    monkeys.push_back(new Monkey('*', 13, 3, 2, 1));
    monkeys[0]->items.push_back(54);
    monkeys[0]->items.push_back(98);
    monkeys[0]->items.push_back(50);
    monkeys[0]->items.push_back(94);
    monkeys[0]->items.push_back(69);
    monkeys[0]->items.push_back(62);
    monkeys[0]->items.push_back(53);
    monkeys[0]->items.push_back(85);
    monkeys.push_back(new Monkey('+', 2, 13, 7, 2));
    monkeys[1]->items.push_back(71);
    monkeys[1]->items.push_back(55);
    monkeys[1]->items.push_back(82);
    monkeys.push_back(new Monkey('+', 8, 19, 4, 7));
    monkeys[2]->items.push_back(77);
    monkeys[2]->items.push_back(73);
    monkeys[2]->items.push_back(86);
    monkeys[2]->items.push_back(72);
    monkeys[2]->items.push_back(87);
    monkeys.push_back(new Monkey('+', 1, 17, 6, 5));
    monkeys[3]->items.push_back(97);
    monkeys[3]->items.push_back(91);
    monkeys.push_back(new Monkey('*', 17, 5, 6, 3));
    monkeys[4]->items.push_back(78);
    monkeys[4]->items.push_back(97);
    monkeys[4]->items.push_back(51);
    monkeys[4]->items.push_back(85);
    monkeys[4]->items.push_back(66);
    monkeys[4]->items.push_back(63);
    monkeys[4]->items.push_back(62);
    monkeys.push_back(new Monkey('+', 3, 7, 1, 0));
    monkeys[5]->items.push_back(88);
    monkeys.push_back(new Monkey('*', -1, 11, 5, 0));
    monkeys[6]->items.push_back(87);
    monkeys[6]->items.push_back(57);
    monkeys[6]->items.push_back(63);
    monkeys[6]->items.push_back(86);
    monkeys[6]->items.push_back(87);
    monkeys[6]->items.push_back(53);
    monkeys.push_back(new Monkey('+', 6, 2, 4, 3));
    monkeys[7]->items.push_back(73);
    monkeys[7]->items.push_back(59);
    monkeys[7]->items.push_back(82);
    monkeys[7]->items.push_back(65);

    uint64_t modulo = 1;
    for (auto&& m : monkeys)
    {
        modulo *= m->div;
    }

    for (auto round = 0; round < ROUND_MAX; round++)
    {
        for (auto&& m : monkeys)
        {
            auto nb_items = m->items.size();
            for (auto it = 0; it < nb_items; it++)
            {
                m->worriness();
                auto res = m->test(modulo);
                if (res.second != -1) monkeys[res.second]->items.push_back(res.first);
            }
        }
    }

    // Part 2
    std::cout << "PART 2" << std::endl;
    std::list<uint64_t> inspections;
    for (auto&& m : monkeys)
    {
        inspections.push_back(m->inspections);
    }
    inspections.sort(std::greater<uint64_t>());

    std::cout << "Inspections: ";
    for (auto&& insp : inspections)
    {
        std::cout << insp << " ";
    }
    std::cout << std::endl;

    uint64_t result = inspections.front();
    inspections.pop_front();
    result *= inspections.front();
    std::cout << "Result: " << result << std::endl;

    return 0;
}