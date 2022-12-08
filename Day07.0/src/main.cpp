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

struct Dir
{
    Dir(std::string name) : dir_name(name) {};
    std::string dir_name;
    std::map<std::string, uint32_t> files;
    std::vector<Dir*> dirs;
};

bool is_dir_exists(Dir* dir, std::string path);
Dir* get_dir(Dir* cdir, std::string dir_name);
uint32_t evaluate_size(Dir* dir, uint32_t& result);

int main()
{
    Dir* root = new Dir("/");
    std::stack<Dir*> current_dir;
    current_dir.push(root);

    std::ifstream filestrm(input_file_name);
    if(filestrm.is_open())
    {
        std::string cmd;

        std::string line;
        while(!filestrm.eof())
        {
            std::getline(filestrm, line);
            // Parse line
            if (line[0] == '$')
            {
                if (line[2] == 'c')
                {
                    cmd = line.substr(5, line.size()-5);
                    if (cmd == "..")
                    {
                        current_dir.pop();
                    }
                    else
                    {
                        current_dir.push(get_dir(current_dir.top(), cmd));
                    }
                }
            }
            else
            {
                std::istringstream l_strm(line);
                std::string first_cmd;
                std::string sec_cmd;
                l_strm >> first_cmd >> sec_cmd;
                if (first_cmd == "dir")
                {
                    if (!is_dir_exists(current_dir.top(), sec_cmd))
                    {
                        current_dir.top()->dirs.push_back(new Dir(sec_cmd));
                    }
                }
                else
                {
                    current_dir.top()->files.try_emplace(sec_cmd, std::stoul(first_cmd));
                }
            }
        }
    }
    else
    {
        std::cout << "Unable to open file: " << input_file_name << std::endl;
    }

    // Calculate sizes
    uint32_t result = 0;
    evaluate_size(root, result);
    std::cout << "PART 1" << std::endl;
    std::cout << "Result: " << result << std::endl;

    return 0;
}

bool is_dir_exists(Dir* dir, std::string dir_name)
{
    for (auto& d : dir->dirs)
    {
        if (dir_name == d->dir_name) return true;
    }

    return false;
}

Dir* get_dir(Dir* cdir, std::string dir_name)
{
    for (auto& d : cdir->dirs)
    {
        if (dir_name == d->dir_name)
        {
            return d;
        }
    }
    
    return cdir;
}

uint32_t evaluate_size(Dir* dir, uint32_t& result)
{
    auto size = 0;
    for (const auto& [key, value] : dir->files)
    {
        size += value;
    }

    for (auto& d : dir->dirs)
    {
        size += evaluate_size(d, result);
    }

    if (size <= 100000)
    {
        result += size;
    }

    return size;
}