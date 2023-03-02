#include<iostream>
#include<string>

#include "../read_file.hpp"



struct Position
{
    Position(int x, int y) : x(x), y(y) {}
    int x;
    int y;
};

struct Beacon
{
    Position pos;
};

struct Sensor
{
    Sensor(Position pos, Beacon closest_beacon, int distance, std::string name) : pos(pos), closest_beacon(closest_beacon), distance(distance), name(name) {}
    Position pos;
    Beacon closest_beacon;
    int distance;
    std::string name;
};

int calc_manhatten_distance(Position const &a, Position const &b)
{
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}


std::vector<std::vector<char> > make_map(std::vector<std::string> input, std::vector<Sensor> &sensors)
{

    size_t equal; 
    int xs, ys, xb, yb;

    int largest_x = 0;
    int largest_y = 0;
    int smallest_x = 0;
    int smallest_y = 0;
    
    for (size_t i = 0; i < input.size(); i++)
    {
        equal = input[i].find('=');
        xs = std::stoi(&input[i][equal + 1]);
        equal = input[i].find('=', equal + 1);
        ys = std::stoi(&input[i][equal + 1]);

        equal = input[i].find('=', equal + 1);
        xb = std::stoi(&input[i][equal + 1]);
        equal = input[i].find('=', equal + 1);
        yb = std::stoi(&input[i][equal + 1]);

        if (xs > largest_x)
            largest_x = xs;
        else if (xb > largest_x)
            largest_x = xb;
        if (ys > largest_y)
            largest_y = ys;
        else if (yb > largest_y)
            largest_y = yb;
        
        if (xs < smallest_x)
            smallest_x = xs;
        else if (xb < smallest_x)
            smallest_x = xb;
        if (ys < smallest_y)
            smallest_y = ys;
        else if (yb < smallest_y)
            smallest_y = yb;

        int distance = calc_manhatten_distance(Position(xs, ys), Position(xb, yb));
        Beacon b = {Position(xb, yb)};
        Sensor s = {Position(xs, ys), b, distance, std::to_string(i)};
        sensors.push_back(s);
    }
    largest_x = largest_x - smallest_x;
    largest_y = largest_y - smallest_y;
    int offset_x = abs(smallest_x);
    int offset_y = abs(smallest_y); 
    // make map with size of largest x and y and smallest x and y
    std::vector<std::vector<char> > map(10 + 1, std::vector<char>(10 + 1, '.'));

    for (size_t i = 0; i < sensors.size(); i++)
    {
        sensors[i].pos.x += offset_x;
        sensors[i].pos.y += offset_y;
        sensors[i].closest_beacon.pos.x += offset_x;
        sensors[i].closest_beacon.pos.y += offset_y;
        // map[sensors[i].pos.y][sensors[i].pos.x] = sensors[i].name[0];
        // map[sensors[i].closest_beacon.pos.y][sensors[i].closest_beacon.pos.x] = 'B';
        // update the new distance in the sensor
        sensors[i].distance = calc_manhatten_distance(sensors[i].pos, sensors[i].closest_beacon.pos);
    }


    

    
    return map;
}


void draw_map(std::vector<std::vector<char> > const &map)
{
    for (size_t i = 0; i < map.size(); i++)
    {
        for (size_t j = 0; j < map[i].size(); j++)
        {
            std::cout << map[i][j];
        }
        std::cout << std::endl;
    }
}

int part1(std::vector<std::string> input)
{
    int result = 0;
    std::vector<Sensor> sensors;
    std::vector<std::vector<char> > map = make_map(input, sensors);
    // draw_map(map);

    std::string name;
    int row_to_inspect = 2'000'000;
    int current_dist;
    for (size_t i = 0; i < map[row_to_inspect].size(); i++)
    {
        bool beacon_possible = true;
        int sensor_dist;


        for (size_t j = 0; j < sensors.size(); j++)
        {
            sensor_dist = sensors[j].distance;
            current_dist = calc_manhatten_distance(Position(i, row_to_inspect), sensors[j].pos);
            name = sensors[j].name;

            if (current_dist <= sensors[j].distance)
            {
                beacon_possible = false;
                break;
            }
        }

        if (!beacon_possible && map[row_to_inspect][i] != 'B')
        {
            map[11][i] = 'X';
            result++;
        }
    }

    // draw_map(map);




    return result;
}






int main()
{

    std::vector<std::string> v = read_file<std::string>("input.txt");

    std::cout << part1(v) << std::endl;

    
    return 0;

} 