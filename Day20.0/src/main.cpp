#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <algorithm>

#define input_file_name ("inputs.txt")

int main()
{
    std::vector<std::pair<int64_t, int64_t>> val_to_idx;
    int32_t zero;

    std::ifstream filestrm(input_file_name);
    if(filestrm.is_open())
    {
        int64_t value;
        uint32_t idx = 0;;
        while(filestrm >> value)
        {
            val_to_idx.emplace_back(value, idx);
            if (value == 0) zero = idx;
            idx++;
        }
    }
    else
    {
        std::cout << "Unable to open file: " << input_file_name << std::endl;
    }
    filestrm.close();

    for (auto i = 0; i < val_to_idx.size(); i++)
    {
        auto mov = val_to_idx[i].first;
        int64_t idx = val_to_idx[i].second;
        int32_t delta;
        int64_t min = 0;
        int64_t max = 0;

        idx += mov;

        if (mov == 0) continue;
        else if (idx > (int64_t)(val_to_idx.size()-1))
        {
            idx = idx % ((int64_t)val_to_idx.size()-1);
        }
        else if (idx < 0)
        {
            idx = ((int64_t)val_to_idx.size()-1) - ((-idx) % ((int64_t)val_to_idx.size()-1));
        }
        if (idx == 0) idx = (int64_t)(val_to_idx.size()-1);

        if (idx == val_to_idx[i].second) continue;
        else if (idx > val_to_idx[i].second)
        {
            min = val_to_idx[i].second;
            max = idx+1;
            delta = -1;
        }
        else if (idx < val_to_idx[i].second)
        {
            min = idx;
            max = val_to_idx[i].second;
            delta = 1;
        }

        // update indexes
        for (auto& pp : val_to_idx)
        {
            if (pp.second >= min && pp.second < max) pp.second += delta;
        }
        val_to_idx[i].second = idx;
    }
    // Part 1
    std::cout << "size: " << val_to_idx.size() << std::endl;
    std::cout << "PART 1" << std::endl;
    auto idx1 = ((val_to_idx[zero].second + 1000) % val_to_idx.size());
    auto idx2 = ((val_to_idx[zero].second + 2000) % val_to_idx.size());
    auto idx3 = ((val_to_idx[zero].second + 3000) % val_to_idx.size());
    auto result = 0;
    for (auto& p : val_to_idx)
    {
        if (p.second == idx1 || p.second == idx2 || p.second == idx3)
        {
            result += p.first;
        }
    }
    std::cout << "Result: " << result << std::endl;
    // Part 2
//    std::cout << "PART 2" << std::endl;
//    std::cout << "Result: " << max << std::endl;

    return 0;
}
