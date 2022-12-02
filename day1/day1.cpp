#include<iostream>
#include<string>
#include<numeric>

#include "../read_file.hpp"

struct Gnome 
{
    int calories;
    int index;
};

int main()
{

    std::vector<std::string> v = read_file<std::string>("input.txt");

    std::vector<Gnome> gnomes;
    std::vector<int> temp;
    int sum = 0;

    Gnome temp_gnome;

    int index = 1;
    for (size_t i = 0; i < v.size(); i++)
    {
        if (v[i] != "")
        {
            temp.push_back(std::stoi(v[i]));
        }
        else
        {
            sum = std::accumulate(temp.begin(), temp.end(), 0);
            temp_gnome.calories = sum; 
            temp_gnome.index = index;        
            gnomes.push_back(temp_gnome);
            temp.clear();
            index++;
        }
    }

    Gnome one;
    Gnome two;
    Gnome three;

    for (Gnome gnome : gnomes)
    {
        if (gnome.calories > one.calories)
        {
            three = two;
            two = one;
            one = gnome;
        }
        else if (gnome.calories > two.calories)
        {
            three = two;
            two = gnome;
        }
        else if (gnome.calories > three.calories)
        {
            three =  gnome;
        }
    }
    std::cout << one.calories << std::endl;
    std::cout << one.calories + two.calories + three.calories << std::endl;


    return 0;

}