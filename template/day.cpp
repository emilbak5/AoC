#include<iostream>
#include<string>

#include "../read_file.hpp"



int main()
{

    std::vector<float> v = read_file<float>("input.txt");

    for (int i = 1; i < v.size(); i++)
    {
        std::cout << v[i] << std::endl;
    }

    
    return 0;

}