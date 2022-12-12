#include<iostream>
#include<string>
#include <memory>

#include "../read_file.hpp"



struct Node
{
    int g, h, f;
    char name;
    bool start = false;
    bool end = false;
    
    std::vector<std::shared_ptr<Node> > connected_nodes;

};


std::vector<std::shared_ptr<Node> > make_nodes(std::vector<std::string> const &input)
{

    std::vector<std::vector<std::shared_ptr<Node> > >nodes;
    std::vector<std::shared_ptr<Node> > temp;

    for (size_t i = 0; i < input.size(); i++)
    {
         for (size_t j = 0; j < input[i].size(); j++)
        {
            std::shared_ptr<Node> node(new Node());
            if (input[i][j] == 'S')
            {
                node->name = 'a';
                node->start = true;
            }
            else if (input[i][j] == 'E')
            {
                node->name = 'z';
                node->end = true;
            }
            else
                node->name = input[i][j];

            temp.push_back(node);
        }
        nodes.push_back(temp);
        temp.clear();
    }

    std::vector<std::shared_ptr<Node> > return_nodes;
    
    int name;

    for (int i = 0; i < nodes.size(); i++)
    {
         for (int j = 0; j < nodes[i].size(); j++)
        {
            if (j - 1 >= 0)
            {
                name = int(nodes[i][j-1]->name);
                if (name <= int(nodes[i][j]->name) || name == int(nodes[i][j]->name) + 1)
                    nodes[i][j]->connected_nodes.push_back(nodes[i][j-1]);
            }

            if (j + 1 < nodes[i].size() - 1)
            {
                name = int(nodes[i][j+1]->name);
                if (name <= int(nodes[i][j]->name) || name == int(nodes[i][j]->name) + 1)
                    nodes[i][j]->connected_nodes.push_back(nodes[i][j+1]);
            }

            if (i - 1 >= 0)
            {
                name = int(nodes[i-1][j]->name);
                if (name <= int(nodes[i][j]->name) || name == int(nodes[i][j]->name) + 1)
                    nodes[i][j]->connected_nodes.push_back(nodes[i-1][j]);
            }

            if (i + 1 < nodes.size() - 1)
            {
                name = int(nodes[i+1][j]->name);
                if (name <= int(nodes[i][j]->name) || name == int(nodes[i][j]->name) + 1)
                    nodes[i][j]->connected_nodes.push_back(nodes[i+1][j]);
            }


            return_nodes.push_back(nodes[i][j]);
        }
    }
    
    return return_nodes;
}





int part1(std::vector<std::string> input)
{
    std::vector<std::shared_ptr<Node> > nodes = make_nodes(input);
    int x = 5;

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