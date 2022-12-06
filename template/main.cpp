#include<iostream>
#include<string>

#include "../read_file.hpp"



int main()
{

    std::vector<std::string> v = read_file<std::string>("input.txt");

    for (int i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << std::endl;
    }

    
    return 0;

}