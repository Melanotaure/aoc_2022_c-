#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <stack>
#include <utility>

#define input_file_name ("inputs.txt")

struct Inst
{
    uint32_t move;
    uint32_t start;
    uint32_t dest;
};

void init_crate_stacks(std::array<std::stack<char>, 9>&);

int main()
{
    std::array<std::stack<char>, 9> crate_stack;
    init_crate_stacks(crate_stack);
    std::vector<Inst> move_instructions;

    std::ifstream filestrm(input_file_name);
    if(filestrm.is_open())
    {
        std::string inst;
        uint32_t nb_to_move;
        uint32_t start_stack;
        uint32_t dest_stack;

        while(filestrm >> inst >> nb_to_move >> inst >> start_stack >> inst >> dest_stack)
        {
            move_instructions.push_back({nb_to_move, start_stack, dest_stack});
        }
        filestrm.close();
    }
    else
    {
        std::cout << "Unable to open file: " << input_file_name << std::endl;
    }

    if(move_instructions.size() != 0)
    {
        // PART 1
        std::cout << std::endl << "PART 1" << std::endl;
        std::cout << "Nb instructions: " << move_instructions.size() << std::endl;

        for (auto&& cur_inst : move_instructions)
        {
            for (auto i = 0; i < cur_inst.move; i++)
            {
                crate_stack[cur_inst.dest-1].push(crate_stack[cur_inst.start-1].top());
                crate_stack[cur_inst.start-1].pop();
            }
        }

        std::cout << "Final top crates: ";
        for (auto i = 0; i < crate_stack.size(); i++)
        {
            std::cout << crate_stack[i].top();
        }
        std::cout << std::endl;

        // PART 2
        //std::array<std::stack<char>, 9> crate_stack2;
        init_crate_stacks(crate_stack);
        for (auto&& cur_inst : move_instructions)
        {
            std::stack<char> crates;
            for (auto i = 0; i < cur_inst.move; i++)
            {
                crates.push(crate_stack[cur_inst.start-1].top());
                crate_stack[cur_inst.start-1].pop();
            }

            for (auto i = 0; i < cur_inst.move; i++)
            {
                crate_stack[cur_inst.dest-1].push(crates.top());
                crates.pop();
            }
        }

        std::cout << std::endl << "PART 2" << std::endl;
        std::cout << "Final top crates: ";
        for (auto i = 0; i < crate_stack.size(); i++)
        {
            std::cout << crate_stack[i].top();
        }
        std::cout << std::endl;

    }
    else
    {
        std::cout << "Error no elves pair found" << std::endl;
    }

    return 0;
}

// My distribution
void init_crate_stacks(std::array<std::stack<char>, 9>& crate_stack)
{
    // Init crates stacks
    // stack #1
    crate_stack[0].push('S');
    crate_stack[0].push('T');
    crate_stack[0].push('H');
    crate_stack[0].push('F');
    crate_stack[0].push('W');
    crate_stack[0].push('R');
    // stack 2
    crate_stack[1].push('S');
    crate_stack[1].push('G');
    crate_stack[1].push('D');
    crate_stack[1].push('Q');
    crate_stack[1].push('W');
    // stack 3
    crate_stack[2].push('B');
    crate_stack[2].push('T');
    crate_stack[2].push('W');
    // stack 4
    crate_stack[3].push('D');
    crate_stack[3].push('R');
    crate_stack[3].push('W');
    crate_stack[3].push('T');
    crate_stack[3].push('N');
    crate_stack[3].push('Q');
    crate_stack[3].push('Z');
    crate_stack[3].push('J');
    // stack 5
    crate_stack[4].push('F');
    crate_stack[4].push('B');
    crate_stack[4].push('H');
    crate_stack[4].push('G');
    crate_stack[4].push('L');
    crate_stack[4].push('V');
    crate_stack[4].push('T');
    crate_stack[4].push('Z');
    // stack 6
    crate_stack[5].push('L');
    crate_stack[5].push('P');
    crate_stack[5].push('T');
    crate_stack[5].push('C');
    crate_stack[5].push('V');
    crate_stack[5].push('B');
    crate_stack[5].push('S');
    crate_stack[5].push('G');
    // stack 7
    crate_stack[6].push('Z');
    crate_stack[6].push('B');
    crate_stack[6].push('R');
    crate_stack[6].push('T');
    crate_stack[6].push('W');
    crate_stack[6].push('G');
    crate_stack[6].push('P');
    // stack 8
    crate_stack[7].push('N');
    crate_stack[7].push('G');
    crate_stack[7].push('M');
    crate_stack[7].push('T');
    crate_stack[7].push('C');
    crate_stack[7].push('J');
    crate_stack[7].push('R');
    // stack 9
    crate_stack[8].push('L');
    crate_stack[8].push('G');
    crate_stack[8].push('B');
    crate_stack[8].push('W');
}
