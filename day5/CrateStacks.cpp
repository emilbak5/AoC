#include "CrateStacks.h"

CrateStacks::CrateStacks()
{

}

CrateStacks::~CrateStacks()
{

}

CrateStacks::CrateStacks(std::vector<std::string> input)
{
    int i = 0;
    int start_place = 0;

    while (input[start_place] != "")
        start_place++;
    start_place -= 2;
    i = start_place;

    
    int num_of_stacks = ceil(input[0].size() / 4.0);
    for (int i = 0; i < num_of_stacks; i++)
    {
        std::stack<char> temp;
        crate_stacks.push_back(temp);
    }


    int stack_num;

    while(i >= 0)
    {
        
        for (size_t j = 0; j < input[i].size(); j++)
        {
            if (isalpha(input[i][j]))
            {
                stack_num = (0.25 * j + 0.75);
                crate_stacks[stack_num - 1].push(input[i][j]);
            }
            
        }
        i--;
    }

}


std::vector<int> CrateStacks::decode_instruction(std::string s)
{

    std::vector<int> instructions;
    for (size_t i = 0; i < s.size(); i++)
    {
        if (isdigit(s[i]))
        {
            instructions.push_back(std::stoi(&s[i]));
            if (instructions.size() != 3)
                i = s.find(' ', i);

        }
    }

    return instructions;
}




std::string CrateStacks::move_crates(std::vector<std::string> input)
{
    int start_place = 0;

    while (input[start_place] != "")
        start_place++;
    start_place ++;


    std::vector<int> instructions; // [0]: number_of_blocs, [1]: from, [2]: to.


    char block_to_be_moved;
    

    for (size_t i = start_place; i < input.size(); i++)
    {
        instructions = decode_instruction(input[i]);

        for (int j = 0; j < instructions[0]; j++)
        {
            block_to_be_moved = crate_stacks[instructions[1] - 1].top();
            crate_stacks[instructions[1] - 1].pop();

            crate_stacks[instructions[2] - 1].push(block_to_be_moved);
        }
    }


    for (size_t i = 0; i < crate_stacks.size(); i++)
    {
        std::cout << crate_stacks[i].top();
    }
    std::cout << std::endl;

    return "hej";

}


std::string CrateStacks::move_crates2(std::vector<std::string> input)
{
    int start_place = 0;

    while (input[start_place] != "")
        start_place++;
    start_place ++;


    std::vector<int> instructions; // [0]: number_of_blocs, [1]: from, [2]: to.


    char block_to_be_moved;
    

    for (size_t i = start_place; i < input.size(); i++)
    {
        instructions = decode_instruction(input[i]);

        std::vector<char> temp;

        for (int j = 0; j < instructions[0]; j++)
        {
            block_to_be_moved = crate_stacks[instructions[1] - 1].top();
            crate_stacks[instructions[1] - 1].pop();

            temp.push_back(block_to_be_moved);
        }

        for (size_t j = temp.size(); j > 0; j--)
        {
            crate_stacks[instructions[2] - 1].push(temp[j - 1]);
        }

    }


    for (size_t i = 0; i < crate_stacks.size(); i++)
    {
        std::cout << crate_stacks[i].top();
    }
    std::cout << std::endl;


}
