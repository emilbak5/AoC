#ifndef CRATESTACKS_H
#define CRATESTACKS_H

#pragma once

#include<vector>
#include<string>
#include<stack>
#include<ctype.h>
#include <cmath>

class CrateStacks
{
public:
    CrateStacks();
    ~CrateStacks();

    CrateStacks(std::vector<std::string> input);

    std::string move_crates(std::vector<std::string> input);
    std::string move_crates2(std::vector<std::string> input);

    std::vector<int> decode_instruction(std::string s);

private:

std::vector<std::stack<char> > crate_stacks;


};

#endif