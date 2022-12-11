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

int32_t signal_strength(int32_t cycle, int32_t value);

int main()
{
    int32_t x = 1;
    int32_t total_sig_strength = 0;
 
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
                total_sig_strength += signal_strength(cycle, x);
            }
            else
            {
                V = std::stoi(line.substr(5));
                cycle++;
                total_sig_strength += signal_strength(cycle, x);
                cycle++;
                total_sig_strength += signal_strength(cycle, x);
                x += V;
            }
        }
    }
    else
    {
        std::cout << "Unable to open file: " << input_file_name << std::endl;
    }

    // Part 1
    std::cout << "PART 1" << std::endl;
    std::cout << "Result: " << total_sig_strength << std::endl << std::endl;

    return 0;
}

int32_t signal_strength(int32_t cycle, int32_t value)
{
    auto result = 0;
    if (cycle == 20 || cycle == 60 || cycle == 100 || cycle == 140 || cycle == 180 || cycle == 220)
    {
        result = cycle * value;
    }

    return result;
}