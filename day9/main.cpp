#include<iostream>
#include<string>
#include<cmath>
#include<memory>

#include "../read_file.hpp"


struct Position
{
    Position(int _x, int _y) : row(_x), col(_y) {}

    int row;
    int col;
};


struct Knot
{  
    Knot(char _name, std::shared_ptr<Knot> _head, std::shared_ptr<Knot> _tail, Position _position) : name(_name), head(_head), tail(_tail), position(_position) {}

    char name;
    Position position;
    std::shared_ptr<Knot> head;
    std::shared_ptr<Knot> tail;
};



struct Map
{   
    Map(int _width, int _height, int _number_of_knots, Position _start_pos);

    int width, height;

    std::vector<std::shared_ptr<Knot> > knots;

    // Position start_pos = Position(width/2, height/2);
    // Position head = Position(width/2, height/2);
    // Position tail = Position(width/2, height/2);

    std::vector<std::vector<char> > grid;
    std::vector<std::vector<char> > visited_grid;

};

Map::Map(int _width, int _height, int _number_of_knots, Position _start_pos)
{
    width = _width;
    height = _height;
    
    std::shared_ptr<Knot> head(new Knot('H', std::shared_ptr<Knot>(nullptr), std::shared_ptr<Knot>(nullptr), _start_pos));

    knots.push_back(head);
    for (int i = 1; i < _number_of_knots; i++)
    {
        std::shared_ptr<Knot> temp(new Knot(char(i)+0, knots[i-1], std::shared_ptr<Knot>(nullptr), _start_pos)); 
        knots[i-1]->tail = temp; 
        knots.push_back(temp);
    }   
    
}


Map init_map(const std::vector<std::string> &input, int number_of_knots)
{   
    int current_size, width = 0, height = 0, vertical = 0, horizontal = 0, left = 0, right = 0, up = 0, down = 0;
    int largest_size = 0;
    for (size_t i = 0; i < input.size(); i++)
    {
        current_size = std::stoi(&input[i][2]);

        if (input[i][0] == 'R')
        {
            horizontal += current_size;
            if (horizontal > right)
                right = horizontal;
        }
        if (input[i][0] == 'L')
        {
            horizontal -= current_size;
            if (horizontal < left)
                left = horizontal;
        }
        if (input[i][0] == 'U')
        {
            vertical += current_size;
            if (vertical > up)
                up = vertical;
        }     
        if (input[i][0] == 'D')
        {
            vertical -= current_size;
            if (vertical < down)
                down = vertical;
        }     
    }


    width = right - left + 1;
    height = up - down + 1;

    Position start_pos = Position((width - right), (height - up));


    std::vector<std::vector<char> > grid(height, std::vector<char>(width, '*'));
    Map map(height, width, number_of_knots, start_pos);

    map.visited_grid = grid;

    map.grid = grid;

    for (size_t i = map.knots.size()-2; i > 0; i--)
    {
        map.grid[map.knots[i]->position.col][map.knots[i]->position.row] = map.knots[i]->name;
    }
    

    return map;
}



void draw_map(const Map &map)
{

    for (size_t row = 0; row < map.width; row++)
    {
        for (size_t col = 0; col < map.height; col++)
            {
                std::cout << map.grid[row][col] << ' ';
            }
        std::cout << std::endl;
    } 
    std::cout << std::endl;
}

float calc_distance(Position head, Position tail)
{
    float position = sqrt(pow(head.row - tail.row, 2) + pow(head.col - tail.col, 2));
    return position;
}


// void move_tail(Map &map, char direction)
// {
//     switch (direction)
//     {
//     case 'L':
//         if (map.head.row == map.tail.row)
//             map.tail.col -= 1;
//         else
//         {
//             map.tail.row += map.head.row - map.tail.row;
//             map.tail.col -= 1;
//         }
//         break;   
//     case 'R':
//         if (map.head.row == map.tail.row)
//             map.tail.col += 1;
//         else
//         {
//             map.tail.row += map.head.row - map.tail.row;
//             map.tail.col += 1;

//         }
//         break;   
//     case 'U':
//         if (map.head.col == map.tail.col)
//             map.tail.row -= 1;
//         else
//         {
//             map.tail.col += map.head.col - map.tail.col;
//             map.tail.row -= 1;

//         }
//         break;   
//     case 'D':
//         if (map.head.col == map.tail.col)
//             map.tail.row += 1;
//         else
//         {
//             map.tail.col += map.head.col - map.tail.col;
//             map.tail.row += 1;

//         }
//         break;        
//     }
// }


// void move_head(Map &map, char direction)
// {
//     map.grid[map.head.row][map.head.col] = '*';
//     map.grid[map.tail.row][map.tail.col] = '#';

//     map.visited_grid[map.tail.row][map.tail.col] = '#';

//     float distance;
//     switch (direction)
//         {
//         case 'L':
//             map.head.col -= 1;
//             distance = calc_distance(map.head, map.tail);
//             if (distance > 1.5)
//             {
//                 move_tail(map, direction);
//             }
//             break;   
//         case 'R':
//             map.head.col += 1;
//             distance = calc_distance(map.head, map.tail);
//             if (distance > 1.5)
//             {
//                 move_tail(map, direction);
//             }
//             break;   
//         case 'U':
//             map.head.row -= 1;
//             distance = calc_distance(map.head, map.tail);
//             if (distance > 1.5)
//             {
//                 move_tail(map, direction);
//             }
//             break;   
//         case 'D':
//             map.head.row += 1;
//             distance = calc_distance(map.head, map.tail);
//             if (distance > 1.5)
//             {
//                 move_tail(map, direction);
//             }
//             break;        
//         }
    



//     map.grid[map.start_pos.row][map.start_pos.col] = 'S';
//     map.grid[map.tail.row][map.tail.col] = 'T';
//     map.grid[map.head.row][map.head.col] = 'H';


// }

int part1(Map map, std::vector<std::string> commands)
{
    char direction;
    int number_of_movements;
    for (auto command : commands)
    {
        direction = command[0];
        number_of_movements = std::stoi(&command[2]);

        for (int i = 0; i < number_of_movements; i++)
        {
            // move_head(map, direction);
            draw_map(map);
        }

    }

    int result = 0;
    for (size_t row = 0; row < map.width; row++)
    {
        for (size_t col = 0; col < map.height; col++)
            {
                if (map.visited_grid[row][col] == '#')
                    result += 1;
            }
    }


    return result;
}




int main()
{

    std::vector<std::string> v = read_file<std::string>("input.txt");

    Map map = init_map(v, 10);
    draw_map(map);

    int result = part1(map, v);
    
    std::cout << result << std::endl;

    
    return 0;

}