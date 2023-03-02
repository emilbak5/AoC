#include<iostream>
#include<string>
#include <memory>
#include<cctype>
#include "../read_file.hpp"
#include <boost/algorithm/string/find.hpp>

#include <typeinfo>


using namespace boost;

struct LinkedVectors
{
    LinkedVectors(int _level) : level(_level) {}


    int level;
    std::vector<int> own_vec;
    std::vector<std::shared_ptr<LinkedVectors> > sub_vectors;
};




int make_vec(std::string sub_str, std::shared_ptr<LinkedVectors> &current)
{

    for (size_t i = 1; i < sub_str.size(); i++)
    {
        if (sub_str[i] == ']')
        {
            return i;
        }

        else if (sub_str[i] == '[')
        {
            std::string sub_str_new = sub_str.substr(i);
            std::shared_ptr<LinkedVectors> subvec(new LinkedVectors(current->level + 1));
            i += make_vec(sub_str_new, subvec);
            current->sub_vectors.push_back(subvec);    
        }
        else if (sub_str[i] == ',')
            continue;
        else
            current->own_vec.push_back(std::stoi(&sub_str[i]));
    }

}



bool check_order(const std::shared_ptr<LinkedVectors> left, const std::shared_ptr<LinkedVectors> right)
{

    bool corret_order = true;

    if (left->own_vec.size() > right->own_vec.size())
        return false;

    for (size_t i = 0; i < left->own_vec.size(); i++)
    {
        if (i < left->own_vec.size() && i < right->own_vec.size())
        {
            if (left->own_vec[i] > right->own_vec[i])
                return false;
            else if (left->own_vec[i] < right->own_vec[i])
                return true;
        }        

        else if (!left->own_vec.empty() && right->own_vec.empty())
            return false;
    }


    if (!left->sub_vectors.empty() && right->sub_vectors.empty())
        return false;
    

    else if (!left->sub_vectors.empty() && !right->sub_vectors.empty())
    {
        if (left->sub_vectors.size() > right->sub_vectors.size())
            return false;
        
        for (size_t i = 0; i < left->sub_vectors.size(); i++)
        {
            corret_order = check_order(left->sub_vectors[i], right->sub_vectors[i]);
            if (corret_order == false)
                break;
        }

    }



    return corret_order;
}


int part1(std::vector<std::string> const &commands)
{
    int result = 0;

    std::vector<std::shared_ptr<LinkedVectors> > vectors;

    for (size_t i = 0; i < commands.size(); i++)
    {
        if (commands[i] == "")
            continue;

        std::shared_ptr<LinkedVectors> first(new LinkedVectors(1));
        int ignore = make_vec(commands[i], first);
        vectors.push_back(first);
    }

    int pair_number = 1;
     
    for (size_t i = 0; i < vectors.size(); i += 2)
    {
        const std::shared_ptr<LinkedVectors> left = vectors[i];
        const std::shared_ptr<LinkedVectors> right = vectors[i + 1];

        bool right_order = check_order(left, right);
        if (right_order)
            result += pair_number;

        pair_number += 1;

    }





    return result;
}

int main()
{
  

    std::vector<std::string> v = read_file<std::string>("input.txt");



    std::cout << part1(v) << std::endl;

    for (size_t i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << std::endl;
    }

    
    return 0;

}