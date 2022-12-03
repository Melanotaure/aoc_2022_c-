#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

#define input_file_name ("inputs.txt")

using Rucksack = std::pair<std::string, std::string>;

char search_rucksack(Rucksack& sack)
{
    for(auto c : sack.first)
    {
        if(sack.second.find(c) != std::string::npos)
            return c;
    }

    return ' ';
}

char search_two_rucksacks(std::string& ref, std::string& first, std::string& second)
{
    for(auto c : ref)
    {
        if(first.find(c) != std::string::npos)
        {
            if(second.find(c) != std::string::npos)
                return c;
        }
    }

    return ' ';
}

uint32_t evaluate_point(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return ((c - 'A') + 27);
    }
    else
    {
        return ((c - 'a') + 1);
    }
}

int main()
{
    std::vector<Rucksack> rucksacks;

    std::ifstream rucksackstrm(input_file_name);
    if(rucksackstrm.is_open())
    {
        std::string compartments;

        while(rucksackstrm >> compartments)
        {
            auto comp_size = compartments.size() / 2;
            rucksacks.push_back(std::make_pair(compartments.substr(0,comp_size), compartments.substr(comp_size)));
        }
        rucksackstrm.close();
    }
    else
    {
        std::cout << "Unable to open file: " << input_file_name << std::endl;
    }

    auto score = 0;
    if(rucksacks.size() != 0)
    {
        // PART 1
        for(auto&& rucksack : rucksacks)
        {
            auto c = search_rucksack(rucksack);
            score += evaluate_point(c);
        }

        std::cout << "PART 1" << std::endl;
        std::cout << "Nb rucksacks: " << rucksacks.size() << std::endl;
        std::cout << "Score: " << score << std::endl;

        // PART 2
        score = 0;
        for (auto i = 0; i < rucksacks.size(); i+=3)
        {
            std::string rucksack_ref = rucksacks[i].first + rucksacks[i].second;
            std::string rucksack_one = rucksacks[i+1].first + rucksacks[i+1].second;
            std::string rucksack_two = rucksacks[i+2].first + rucksacks[i+2].second;
            auto c = search_two_rucksacks(rucksack_ref, rucksack_one, rucksack_two);
            score += evaluate_point(c);
        }

        std::cout << std::endl << "PART 2" << std::endl;
        std::cout << "Score: " << score << std::endl;
    }
    else
    {
        std::cout << "Error no rucksack found" << std::endl;
    }

    return 0;
}
