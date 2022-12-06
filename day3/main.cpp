#include<iostream>
#include<string>
#include <ctype.h>

#include "../read_file.hpp"


// ascii a = 97
// ascii A = 65

int convert_to_value(char letter)
{
    int value;
    if (islower(letter))
    {
        value = int(letter);
        value -= 96; // ascii offset
    }
    else
    {
        value = int(letter);
        value -= 38;
    }

    if (value > 52 || value < 1)
    {
        int x = 5;
    }

    return value;
}




int main()
{

    std::vector<std::string> v = read_file<std::string>("input.txt");

/////////////////////////////////////////////////////////// part 1 ///////////////////////////////////////////////

    std::vector<std::string> compartment_1;
    std::vector<std::string> compartment_2;

    for (auto bag : v)
    {
        compartment_1.push_back(bag.substr(0, bag.size() / 2));
        compartment_2.push_back(bag.substr(bag.size() / 2, bag.size() - 1));
    }


    int count = 0;


    for (size_t i = 0; i < v.size(); i++)
    {
        for (char j : compartment_1[i])
        {
            for (char k : compartment_2[i])
            {
                if (j == k)
                { 
                    count += convert_to_value(j);
                    goto reset;
                }
            }
        }
        reset:
        int x = 5;
    }

    std::cout << count << std::endl;



    /////////////////////////////////////////////////////// part 2 //////////////////////////////////


    std::vector<std::vector<std::string> > groups;

    int j = 0;
    std::vector<std::string> temp;
    for (size_t i = 0; i < v.size(); i++)
    {
        temp.push_back(v[i]);
        j++;
        if (j == 3)
        {
            groups.push_back(temp);
            temp.clear();
            j = 0;
        }
    }


    count = 0;

    for (size_t i = 0; i < groups.size(); i++)
    {
        for (char j : groups[i][0])
        {
            for (char k : groups[i][1])
            {
                for (char l : groups[i][2])
                {
                    if (j == k && j == l)
                    { 
                        count += convert_to_value(j);
                        goto reset2;
                    }
                }
            }
        }
        reset2:
        int x = 5;
    }

    std::cout << count << std::endl;



    return 0;

}