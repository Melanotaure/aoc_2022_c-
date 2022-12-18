#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <utility>
#include <algorithm>
#include "../Inc/RockShape.hpp"

#define input_file_name ("inputs.txt")



int main()
{
    RockChamber chamber;
    std::string jets;

    std::ifstream filestrm(input_file_name);
    if(filestrm.is_open())
    {
        while(!filestrm.eof())
        {
            std::getline(filestrm, jets);
        }
    }
    else
    {
        std::cout << "Unable to open file: " << input_file_name << std::endl;
    }
    filestrm.close();

    uint64_t count = 0;
    auto j = 0;
    RockShape* current_shape;
    while (count < 1000000000000)
    {
        auto mod = count % 5;
        switch (mod)
        {
            case 0:
                current_shape = new HBarRock();
                break;
            case 1:
                current_shape = new CrossRock();
                break;
            case 2:
                current_shape = new JayRock();
                break;
            case 3:
                current_shape = new VBarRock();
                break;
            case 4:
                current_shape = new SquareRock();
                break;
        }

        if ((count % 1000000) == 0) std::cout << count << std::endl;
        chamber.add_rock(current_shape);
        bool can_rock_move = true;
        while (can_rock_move != false)
        {
            chamber.jet_effect(jets[j]);
            can_rock_move = chamber.move_rock_down();
            j++;
            if (j >= jets.size()) j = 0;
        }
        delete current_shape;
        count++;
    }

    // Part 1
    std::cout << "PART 1" << std::endl;
    chamber.find_the_highest();
    std::cout << "Tower height: " << chamber.highest_point.second << std::endl;
    // Part 2
//    std::cout << "PART 2" << std::endl;
//    std::cout << "Result: " << max << std::endl;

    return 0;
}
