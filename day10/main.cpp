#include<iostream>
#include<string>

#include "../read_file.hpp"

// struct CPU
// {
//     CPU(int _reg, std::string _instruction)
//     int reg;
//     std::string instruction;
// };

int prev_clock_cycle = 0;

int check_if_interesting(int clock_cycle, int reg)
{   
    int mult_value = 0;
    if ((clock_cycle == 20) || (clock_cycle - prev_clock_cycle == 40))
    {
        mult_value = clock_cycle * reg;
        prev_clock_cycle = clock_cycle;
    }
    
    return mult_value;
}



int part1(std::vector<std::string> commands)
{
    int result = 0;

    int clock_cycle = 0;
    int reg = 1;
    std::string instruction;
    size_t space_position;

    for (auto command : commands)
    {
        space_position = command.find(' ', 0);
        instruction = command.substr(0, space_position);

        if (instruction == "addx")
        {
            clock_cycle += 1;
            result += check_if_interesting(clock_cycle, reg);
            clock_cycle += 1;
            result += check_if_interesting(clock_cycle, reg);

            if (command[5] == '-')
                reg -= std::stoi(&command[6]);
            else
                reg += std::stoi(&command[5]);
            
        }
        else
        {
            clock_cycle += 1;
            result += check_if_interesting(clock_cycle, reg);
        }

    }

    
    prev_clock_cycle = 0;
    return result;
}



void print_crt(std::vector<std::vector<char> > crt)
{
    for (size_t i = 0; i < crt.size(); i++)
    {
        for (size_t j = 0; j < crt[i].size(); j++)
        {
            std::cout << crt[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void update_crt(std::vector<std::vector<char> > &crt, int clock_cycle, int sprite_pos, int &current_vec)
{
    if (clock_cycle - prev_clock_cycle == 40)
    {
        current_vec += 1;
        prev_clock_cycle = clock_cycle;
    }

    if ((clock_cycle - prev_clock_cycle == sprite_pos + 1) || (clock_cycle - prev_clock_cycle == sprite_pos) || (clock_cycle - prev_clock_cycle == sprite_pos - 1))
    {
        crt[current_vec][clock_cycle - prev_clock_cycle] = '#';
    }
    print_crt(crt);

}

void part2(std::vector<std::string> commands)
{
    int result = 0;

    int clock_cycle = 0;
    int sprite_pos = 1;
    std::string instruction;
    size_t space_position;
    std::vector<std::vector<char> > crt(6, std::vector<char>(40, '.'));
    crt[0][0] = '#';
    print_crt(crt);
    int current_vec = 0;

    for (auto command : commands)
    {
        space_position = command.find(' ', 0);
        instruction = command.substr(0, space_position);

        if (instruction == "addx")
        {
            clock_cycle += 1;
            update_crt(crt, clock_cycle, sprite_pos, current_vec);
            clock_cycle += 1;

            if (command[5] == '-')
                sprite_pos -= std::stoi(&command[6]);
            else
                sprite_pos += std::stoi(&command[5]);
            update_crt(crt, clock_cycle, sprite_pos, current_vec);

            
        }
        else
        {
            clock_cycle += 1;
            update_crt(crt, clock_cycle, sprite_pos, current_vec);
        }

    }

    print_crt(crt);


}




int main()
{

    std::vector<std::string> v = read_file<std::string>("input.txt");

    // std::cout << part1(v) << std::endl;

    part2(v);
    
    return 0;

}