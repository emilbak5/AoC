#include<iostream>
#include<string>
#include <memory>
#include<algorithm>

#include "../read_file.hpp"



struct Node
{
    int shortest_distance;
    bool is_visited = false;
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
                node->start = false;
                node->shortest_distance = INT16_MAX;
                
            }
            else if (input[i][j] == 'E')
            {
                node->name = 'z';
                node->end = true;
                node->shortest_distance = 0;

                
            }
            else
            {
                node->name = input[i][j];
                node->shortest_distance = INT16_MAX;
            }

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
                if (name >= int(nodes[i][j]->name) || name == int(nodes[i][j]->name) - 1)
                    nodes[i][j]->connected_nodes.push_back(nodes[i][j-1]);
            }

            if (j + 1 < nodes[i].size())
            {
                name = int(nodes[i][j+1]->name);
                if (name >= int(nodes[i][j]->name) || name == int(nodes[i][j]->name) - 1)
                    nodes[i][j]->connected_nodes.push_back(nodes[i][j+1]);
            }

            if (i - 1 >= 0)
            {
                name = int(nodes[i-1][j]->name);
                if (name >= int(nodes[i][j]->name) || name == int(nodes[i][j]->name) - 1)
                    nodes[i][j]->connected_nodes.push_back(nodes[i-1][j]);
            }

            if (i + 1 < nodes.size())
            {
                name = int(nodes[i+1][j]->name);
                if (name >= int(nodes[i][j]->name) || name == int(nodes[i][j]->name) - 1)
                    nodes[i][j]->connected_nodes.push_back(nodes[i+1][j]);
            }


            return_nodes.push_back(nodes[i][j]);
        }
    }
    
    return return_nodes;
}


int find_smallest_dist(std::vector<std::shared_ptr<Node> > const &unvisited_nodes)
{

    int smallest_dist = INT16_MAX;
    int index = 0;
    for (size_t i = 0; i < unvisited_nodes.size(); i++)
    {
        if (unvisited_nodes[i]->shortest_distance < smallest_dist)
        {
            smallest_dist = unvisited_nodes[i]->shortest_distance;
            index = i;
        }
    }

    if (smallest_dist == INT16_MAX)
        int x = 5;
    return index;
}







int dijkstras(std::vector<std::shared_ptr<Node> > const &nodes)
{

    std::vector<int> shortest_paths;

    std::vector<std::shared_ptr<Node> > visited;
    std::vector<std::shared_ptr<Node> > unvisited = nodes;

    int index_for_smallest_dist;
    while (!unvisited.empty())
    {
        index_for_smallest_dist = find_smallest_dist(unvisited);
        std::shared_ptr<Node> current_node = unvisited[index_for_smallest_dist];

        for (auto node : unvisited[index_for_smallest_dist]->connected_nodes)
        {
            if ((unvisited[index_for_smallest_dist]->shortest_distance + 1 < node->shortest_distance) && (node->is_visited == false))
            {
                node->shortest_distance = unvisited[index_for_smallest_dist]->shortest_distance + 1;
            }
        }


        if (unvisited[index_for_smallest_dist]->name == 'a')
        {
            shortest_paths.push_back(unvisited[index_for_smallest_dist]->shortest_distance);
        }

        unvisited[index_for_smallest_dist]->is_visited = true;
        visited.push_back(unvisited[index_for_smallest_dist]);
        unvisited.erase(unvisited.begin() + index_for_smallest_dist);

    }



    return *std::min_element(shortest_paths.begin(), shortest_paths.end());



    
}



int part1(std::vector<std::string> input)
{
    std::vector<std::shared_ptr<Node> > nodes = make_nodes(input);
    int shortest_dist = dijkstras(nodes);


    return shortest_dist;

}

int part2(std::vector<std::string> input)
{
    std::vector<std::shared_ptr<Node> > nodes = make_nodes(input);
    int shortest_dist = dijkstras(nodes);


    return shortest_dist;

}


int main()
{

    std::vector<std::string> v = read_file<std::string>("input.txt");

    std::cout << part1(v) << std::endl;
    std::cout << part2(v) << std::endl;



    
    return 0;

}