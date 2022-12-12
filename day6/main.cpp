#include<iostream>
#include<string>
#include<queue>

#include "../read_file.hpp"



// void add_element(std::queue<char> &my_queue, char element)
// {
//     my_queue.push(element);

//     if (my_queue.size() > 4)
//     {
//         my_queue.pop();
//     }
// }


void add_element(std::vector<char> &myvec, char element)
{
    myvec.insert(myvec.begin(), element);

    if (myvec.size() > 14)
    {
        myvec.pop_back();
    }
}




bool check_if_same(std::vector<char> &myvec)
{
    char a, b, c, d;

    if (myvec.size() == 14)
    {
        for (size_t i = 0; i < myvec.size(); i++)
        {
            for (size_t j = 0; j < myvec.size(); j++)
            {
                if (i == j)
                    continue;
                else if (myvec[i] == myvec[j])
                {
                    return true;
                }
            }
        }
    }

    return false;

}


int main()
{

    std::vector<std::string> v = read_file<std::string>("input.txt");

    std::queue<char> queue;
    std::vector<char> vec;

    bool same = true;

    for (size_t i = 0; i < v[0].size(); i++)
    {
        add_element(vec, v[0][i]);

        same = check_if_same(vec);

        if (same == false && i > 14)
        {
            std::cout << i + 1 << std::endl;
            break;
        }

    }


    
    return 0;

}