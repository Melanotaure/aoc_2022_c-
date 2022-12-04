#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

#define input_file_name ("inputs.txt")

int main()
{
    std::vector<std::pair<std::pair<uint32_t,uint32_t>,std::pair<uint32_t,uint32_t>>> elves_pairs;

    std::ifstream filestrm(input_file_name);
    if(filestrm.is_open())
    {
        char sep;
        uint32_t first_first;
        uint32_t first_second;
        uint32_t second_first;
        uint32_t second_second;

        while(filestrm >> first_first >> sep >> first_second >> sep >> second_first >> sep >> second_second)
        {
            elves_pairs.push_back(std::make_pair(std::make_pair(first_first, first_second), std::make_pair(second_first, second_second)));
        }
        filestrm.close();
    }
    else
    {
        std::cout << "Unable to open file: " << input_file_name << std::endl;
    }

    auto score = 0;
    if(elves_pairs.size() != 0)
    {
        // PART 1
        std::cout << std::endl << "PART 1" << std::endl;
        std::cout << "Nb elves pairs: " << elves_pairs.size() << std::endl;

        for (auto&& p : elves_pairs)
        {
            if((p.first.first >= p.second.first && p.first.second <= p.second.second) || (p.second.first >= p.first.first && p.second.second <= p.first.second))
            {
                score++;
            }
        }

        std::cout << "Nb pairs slef contained: " << score << std::endl;

        // PART 2
        score = 0;
        for (auto&& p : elves_pairs)
        {
            if (p.first.second < p.second.first || p.second.second < p.first.first)
            {
                score++;
            }
        }
        std::cout << std::endl << "PART 2" << std::endl;
        std::cout << "Nb pairs overlapping: " << (elves_pairs.size() - score) << std::endl;
    }
    else
    {
        std::cout << "Error no elves pair found" << std::endl;
    }

    return 0;
}
