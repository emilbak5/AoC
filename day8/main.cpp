#include<iostream>
#include<string>
#include<algorithm>


#include "../read_file.hpp"

std::vector<std::vector<int> > make_grid(std::vector<std::string> input)
{
    std::vector<int> rows;
    std::vector<std::vector<int> > grid;
    char temp;

    for (size_t i = 0; i < input.size(); i++)
    {
        rows.clear();   
        for (size_t j = 0; j < input[i].size(); j++)
        {
            temp = input[i][j];
            rows.push_back(int(temp - 48));
        }

        grid.push_back(rows);
    }

    return grid;

}


bool check_visibility(int current, std::vector<std::vector<int> > paths_to_edges)
{
    bool all_clear;

    for (auto path : paths_to_edges)
    {
        all_clear = true;
        for (auto tree : path)
        {
            if (tree >= current)
                all_clear = false;
        }
        if (all_clear == false)
            continue;
        else
            return true;
    }
    return false; 

}

std::vector<std::vector<int> > get_paths_to_edges(int pos_row, int pos_col, int row_size, int col_size, std::vector<std::vector<int> > grid)
{
    std::vector<std::vector<int> > paths_to_edges;
    std::vector<int> path_up, path_down, path_right, path_left;

    int current_tree = grid[pos_row][pos_col];

    int temp_pos;

    temp_pos = pos_row - 1;
    while (temp_pos >= 0)
    {
        path_up.push_back(grid[temp_pos][pos_col]);
        temp_pos -= 1;
    }

    temp_pos = pos_row + 1;
    while (temp_pos < row_size)
    {
        path_down.push_back(grid[temp_pos][pos_col]);
        temp_pos += 1;
    }

    temp_pos = pos_col - 1;
    while (temp_pos >= 0)
    {
        path_left.push_back(grid[pos_row][temp_pos]);
        temp_pos -= 1;
    }

    temp_pos = pos_col + 1;
    while (temp_pos < col_size)
    {
        path_right.push_back(grid[pos_row][temp_pos]);
        temp_pos += 1;
    }

    paths_to_edges = {path_up, path_down, path_right, path_left};

    return paths_to_edges;




}

// int count_visible(std::vector<std::vector<int> > grid)
// {
//     int row_size = grid.size();
//     int col_size = grid[0].size();

//     int left, right, top, bottom;

//     int visible_trees = 0;

//     for (size_t row = 0; row < grid.size(); row++)
//     {
//         for (size_t col = 0; col < grid[row].size(); col++)
//         {
//             if (row == 0 || row == row_size - 1 || col == 0 || col == col_size - 1)
//                 visible_trees += 1;
//             else
//             {
                
//                 std::vector<std::vector<int> > paths_to_edges = get_paths_to_edges(row, col, row_size, col_size, grid);

//                 bool all_clear = check_visibility(grid[row][col], paths_to_edges);

//                 if (all_clear)
//                     visible_trees += 1;
//             }
//         }
//     }

//     return visible_trees;

// }


int get_score(int current, std::vector<std::vector<int> > paths_to_edges)
{

    int scenic_score;
    int total_scenic_score = 1;

    std::vector<int> scenic_scores;

    int prev;

    for (auto path : paths_to_edges)
    {
        scenic_score = 0;
        prev = -1;

        for (size_t i = 0; i < path.size(); i++)
        {
            scenic_score += 1;

            if ((path[i] < current))// && (path[i] > prev))
            {
                prev = path[i];
            }
            else
            {
                break;
            }

        }
        total_scenic_score *= scenic_score;
        scenic_scores.push_back(scenic_score);
    }
    return total_scenic_score;  
}



int count_scenic_score(std::vector<std::vector<int> > grid)
{
    int row_size = grid.size();
    int col_size = grid[0].size();

    int left, right, top, bottom;

    int scenic_score = 0;
    std::vector<int> scenic_scores;

    int visible_trees = 0;

    for (size_t row = 0; row < grid.size(); row++)
    {
        for (size_t col = 0; col < grid[row].size(); col++)
        {
            if (row == 0 || row == row_size - 1 || col == 0 || col == col_size - 1)
                continue;

            std::vector<std::vector<int> > paths_to_edges = get_paths_to_edges(row, col, row_size, col_size, grid);

            scenic_score = get_score(grid[row][col], paths_to_edges);
            scenic_scores.push_back(scenic_score);
        }
    }

    scenic_score = *std::max_element(scenic_scores.begin(), scenic_scores.end());

    return scenic_score;

}


int main()
{

    std::vector<std::string> v = read_file<std::string>("input.txt");

    std::vector<std::vector<int> > grid = make_grid(v);

    // int visible_trees = count_visible(grid);
    // std::cout << visible_trees << std::endl;

    int scenic_score = count_scenic_score(grid);
    std::cout << scenic_score << std::endl;

    
    return 0;

}