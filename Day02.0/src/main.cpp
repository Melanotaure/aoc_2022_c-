#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#define input_file_name ("inputs.txt")

int main()
{
    auto P1_score = 0;
    auto P2_score = 0;
    std::vector<char> P1_shape;
    std::vector<char> P2_shape;

    std::ifstream roundstrm(input_file_name);
    if(roundstrm.is_open())
    {
        char p1_current_shape;
        char p2_current_shape;
        while(roundstrm >> p1_current_shape >> p2_current_shape)
        {
            P1_shape.push_back(p1_current_shape);
            P2_shape.push_back(p2_current_shape);
        }
        roundstrm.close();
    }
    else
    {
        std::cout << "Unable to open file: " << input_file_name << std::endl;
    }

    if(P1_shape.size() != 0)
    {
        for(auto i = 0; i < P1_shape.size(); i++)
        {
            if(P1_shape[i] == 'A') // Rock
            {
                if(P2_shape[i] == 'X') // Lose
                {
                    P1_score += 6+1;
                    P2_score += 0+3; // Scissors
                }
                else if (P2_shape[i] == 'Y') // Draw
                {
                    P1_score += 3+1;
                    P2_score += 3+1;
                }
                else if(P2_shape[i] == 'Z') // Win
                {
                    P1_score += 0+1;
                    P2_score += 6+2; // Paper
                }
                
            }

            if(P1_shape[i] == 'B') // Paper
            {
                if(P2_shape[i] == 'X') // Lose
                {
                    P1_score += 6+2;
                    P2_score += 0+1; // Rock
                }
                else if (P2_shape[i] == 'Y') // Draw
                {
                    P1_score += 3+2;
                    P2_score += 3+2; // Paper
                }
                else if(P2_shape[i] == 'Z') // Win
                {
                    P1_score += 0+2;
                    P2_score += 6+3; // Scissors
                }
                
            }

            if(P1_shape[i] == 'C') // Scissors
            {
                if(P2_shape[i] == 'X') // Lose
                {
                    P1_score += 6+3;
                    P2_score += 0+2;
                }
                else if (P2_shape[i] == 'Y') // Draw
                {
                    P1_score += 3+3;
                    P2_score += 3+3;
                }
                else if(P2_shape[i] == 'Z') // Win
                {
                    P1_score += 0+3;
                    P2_score += 6+1;
                }
                
            }
        }

        std::cout << "Nb rounds: " << P1_shape.size() << std::endl;
        std::cout << "Total points:\nP1: " << P1_score << " P2: " << P2_score << std::endl;
    }
    else
    {
        std::cout << "Error no round registered" << std::endl;
    }

    return 0;
}
