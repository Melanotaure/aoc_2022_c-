#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


#define input_file_name ("inputs.txt")

int main()
{
    auto count = 0;
    auto calo_accu = 0;
    std::string current_calo;
    std::vector<uint32_t> calo;

    std::ifstream calostrm(input_file_name);
    if(calostrm.is_open())
    {
        while(!calostrm.eof())
        {
            std::getline(calostrm, current_calo);
            if (current_calo != "")
            {
                calo_accu += std::stoul(current_calo);
            }
            else
            {
                calo.push_back(calo_accu);
                calo_accu = 0;
            }
        }
        calostrm.close();
    }
    else
    {
        std::cout << "Unable to open file: " << input_file_name << std::endl;
    }

    if(calo.size() != 0)
    {
        std::sort(calo.begin(), calo.end(), std::greater<uint32_t>());

        std::cout << "Nb elves: " << calo.size() << std::endl;
        std::cout << "Max calories: " << calo[0] << " " << calo[1] << " " << calo[2] << std::endl << "Total: " << calo[0] + calo[1] + calo[2] << std::endl;
    }
    else
    {
        std::cout << "Error no elves" << std::endl;
    }

    return 0;
}
