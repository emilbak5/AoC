#include<iostream>
#include<string>

#include "CrateStacks.h"
#include "CrateStacks.cpp"

#include "../read_file.hpp"





int main()
{


    std::vector<std::string> v = read_file<std::string>("input.txt");

    CrateStacks my_crate_stacks(v);

    std::string test = my_crate_stacks.move_crates(v);

    CrateStacks my_crate_stacks2(v);
    std::string test2 = my_crate_stacks2.move_crates2(v);
    
    
    return 0;

}