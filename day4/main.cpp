#include<iostream>
#include<string>

#include "Elves.hpp"
#include "Elves.cpp"
#include "../read_file.hpp"



int main()
{

    std::vector<std::string> v = read_file<std::string>("input.txt");

    std::vector<std::vector<Elves> > elve_pairs;

    std::vector<Elves> temp;


    int start1, end1, start2, end2;

    size_t pos_dash1, pos_dash2, pos_comma;


    for (size_t i = 0; i < v.size(); i++)
    {
        
        start1 = std::stoi(&v[i][0]);

        pos_dash1 = v[i].find('-');
        end1 = std::stoi(&v[i][pos_dash1 + 1]);

        pos_comma = v[i].find(',');
        start2 = std::stoi(&v[i][pos_comma + 1]);

        pos_dash2 = v[i].rfind('-');
        end2 = std::stoi(&v[i][pos_dash2 + 1]);
               
        temp.push_back(Elves(start1, end1));
        temp.push_back(Elves(start2, end2));
        
        elve_pairs.push_back(temp);

        temp.clear();

    }

    int count = 0;
    for (auto elf_pair : elve_pairs)
    {
        count += elf_pair[0].check_if_range_is_contained(elf_pair);
    }

    std::cout << count << std::endl;

    count = 0;

    for (auto elf_pair : elve_pairs)
    {
        count += elf_pair[0].check_if_range_is_contained2(elf_pair);
    }


    std::cout << count << std::endl;

    
    return 0;

}