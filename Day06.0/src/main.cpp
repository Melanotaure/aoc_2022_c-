#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <stack>
#include <utility>

#define input_file_name ("inputs.txt")

const int MSG_SIZE = 4;
//const int MSG_SIZE = 14;

bool is_occurence(std::vector<char>& str);

int main()
{
    std::vector<char> slide_w;
    auto result = MSG_SIZE;

    std::ifstream filestrm(input_file_name);
    if(filestrm.is_open())
    {
        for (auto i = 0; i < MSG_SIZE; i++)
        {
            slide_w.push_back(filestrm.get());
        }

        while(is_occurence(slide_w))
        {
            slide_w.push_back(filestrm.get());
            slide_w.erase(slide_w.begin());
            result++;
        }
        filestrm.close();
    }
    else
    {
        std::cout << "Unable to open file: " << input_file_name << std::endl;
    }

    std::cout << "Result: " << result << std::endl;

    return 0;
}

bool is_occurence(std::vector<char>& str)
{
    for (auto i = 0; i < MSG_SIZE; i++)
    {
        auto c = str[i];
        for (auto j = 0; j < MSG_SIZE; j++)
        {
            if (j!=i)
            {
                if (c == str[j]) return true;
            }
        }
    }

    return false;
}