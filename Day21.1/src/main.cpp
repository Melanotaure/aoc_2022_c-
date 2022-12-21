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

struct Monkey
{
    Monkey()
    {
        operation = 0;
        monkey1 = "";
        monkey2 = "";
        value = 0;
    };
    std::string name;
    std::string monkey1;
    std::string monkey2;
    char operation;
    int64_t value;
};

std::map<std::string, Monkey*> monkeys;

int64_t make_monkey_yell(Monkey* m);

int main()
{

    std::ifstream filestrm(input_file_name);
    if(filestrm.is_open())
    {
        std::string line;
        while(!filestrm.eof())
        {
            std::getline(filestrm, line);
            Monkey* monkey = new Monkey;
            monkey->name = line.substr(0, 4);

            if (line[6] >= '0' && line[6] <= '9')
            {
                // get the value;
                std::istringstream str_line(line);
                std::string temp;
                str_line >> temp >> monkey->value;
            }
            else
            {
                // get monkeys name and operation
                std::istringstream str_line(line);
                std::string temp;

                str_line >> temp >> monkey->monkey1 >> monkey->operation >> monkey->monkey2;
            }
            monkeys.emplace(monkey->name, monkey);
        }
    }
    else
    {
        std::cout << "Unable to open file: " << input_file_name << std::endl;
    }

    // Dichotomy is king
    int64_t result = 0;
    int64_t i = 0;
    int64_t val1 = 0;
    int64_t val2 = make_monkey_yell(monkeys[monkeys["root"]->monkey2]);
    int64_t min = 0;
    int64_t max = 1000000000000000000;
    int64_t mid;

    while (min < max)
    {
        mid = (min + max) / 2;
        monkeys["humn"]->value = mid;
        val1 = make_monkey_yell(monkeys[monkeys["root"]->monkey1]);
        auto delta = (val2 - val1);
        if ( delta < 0)
        {
            min = mid;
        }
        else if (delta == 0)
        {
            result = mid;
            break;
        }
        else
        {
            max = mid;
        }
    }

    // Part 2
    std::cout << "PART 2" << std::endl;
    std::cout << "Human yells: " << result << std::endl;

    return 0;
}

int64_t make_monkey_yell(Monkey* m)
{
    int64_t result = 0;

    if (m->operation == 0)
    {
        result = m->value;
    }
    else
    {
        switch (m->operation)
        {
            case '+':
                result = (make_monkey_yell(monkeys[m->monkey1]) + make_monkey_yell(monkeys[m->monkey2]));
                break;
            case '-':
                result = (make_monkey_yell(monkeys[m->monkey1]) - make_monkey_yell(monkeys[m->monkey2]));
                break;
            case '*':
                result = (make_monkey_yell(monkeys[m->monkey1]) * make_monkey_yell(monkeys[m->monkey2]));
                break;
            case '/':
                result = (make_monkey_yell(monkeys[m->monkey1]) / make_monkey_yell(monkeys[m->monkey2]));
                break;
        }
    }

    return result;
}
