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
            value *= 811589153;
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

    for (auto x = 0; x < 10; x++)
    {
        for (auto i = 0; i < val_to_idx.size(); i++)
        {
            int64_t mov = val_to_idx[i].first;
            int64_t idx = val_to_idx[i].second;
            int64_t delta;
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
    }

    // Part 2
    std::cout << "PART 2" << std::endl;
    int64_t idx1 = ((val_to_idx[zero].second + 1000) % val_to_idx.size());
    int64_t idx2 = ((val_to_idx[zero].second + 2000) % val_to_idx.size());
    int64_t idx3 = ((val_to_idx[zero].second + 3000) % val_to_idx.size());
    int64_t result = 0;
    for (auto& p : val_to_idx)
    {
        if (p.second == idx1 || p.second == idx2 || p.second == idx3)
        {
            result += p.first;
        }
    }
    std::cout << "Result: " << result << std::endl;

    return 0;
}
