#include<iostream>
#include<string>
#include<numeric>
#include <algorithm>    // std::sort

#include "../read_file.hpp"

struct Gnome 
{
    int calories;
    int index;
};

int main()
{

    std::vector<std::string> v = read_file<std::string>("input.txt");

    std::vector<int> temp;
    std::vector<int> calories;
    int sum = 0;

    for (size_t i = 0; i < v.size(); i++)
    {
        if (v[i] != "")
        {
            temp.push_back(std::stoi(v[i]));
        }
        else
        {
            sum = std::accumulate(temp.begin(), temp.end(), 0);
            calories.push_back(sum);
            temp.clear();
        }
    }

    std::sort(calories.rbegin(), calories.rend());

    std::cout << calories[0] << std::endl;
    std::cout << calories[0] + calories[1] + calories[2] << std::endl; 


    return 0;

}