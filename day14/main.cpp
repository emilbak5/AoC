#include<iostream>
#include<string>
#include<algorithm>

#include "../read_file.hpp"

const char ROCK = '#';
const char SAND = '*';
const char AIR = '.';
const char SAND_PRODUCER = '+';

const int DOWN = 0;
const int LEFT = 1;
const int RIGHT = 2;



struct Pos
{
    Pos(int _x, int _y) : x(_x), y(_y) {}

    int x;
    int y;
};

struct Rock
{
    std::vector<Pos> positions;
};


struct SandParticle
{
    Pos pos = Pos(500, 0);
};


std::vector<Pos> count_in_between(Pos a, Pos b)
{
    std::vector<Pos> positions;

    if (a.x == b.x)
    {
        int min_y = std::min(a.y, b.y);
        int max_y = std::max(a.y, b.y);

        for (int i = min_y + 1; i < max_y; i++)
        {
            positions.push_back(Pos(a.x, i));
        }
    }
    else if (a.y == b.y)
    {
        int min_x = std::min(a.x, b.x);
        int max_x = std::max(a.x, b.x);

        for (int i = min_x + 1; i < max_x; i++)
        {
            positions.push_back(Pos(i, a.y));
        }
    }

    return positions;
}



int choose_sand_path(SandParticle particle, std::vector<std::vector<char> > &map)
{
    int x = particle.pos.x;
    int y = particle.pos.y;

    if (map[y + 1][x] == AIR)
    {
        return DOWN;
    }
    else if (map[y + 1][x] != AIR)
    {
        if (map[y + 1][x - 1] == AIR)
        {
            return LEFT;
        }
        else if (map[y + 1][x + 1] == AIR)
        {
            return RIGHT;
        }
    }

    return -1;
}


std::vector<std::vector<char> >make_map(std::vector<std::string> input)
{
    int x, y;
    std::vector<int> x_values;
    std::vector<int> y_values;

    std::vector<Rock> rocks;


    for (auto command : input)
    {
        Rock rock;
        for (size_t i = 0; i < command.size(); i++)
        {
            x = std::stoi(&command[i]);
            i = command.find_first_of(',', i);
            y = std::stoi(&command[i + 1]);
            i = command.find_first_of('>', i);

            x_values.push_back(x);
            y_values.push_back(y);

            rock.positions.push_back(Pos(x, y));
            if (i > command.size())
            {
                rocks.push_back(rock);
                break;

            }
        }
    }

    // find in between positions
    for (auto &rock : rocks)
    {
        for (size_t i = 0; i < rock.positions.size() - 1; i++)
        {
            auto positions = count_in_between(rock.positions[i], rock.positions[i + 1]);
            rock.positions.insert(rock.positions.end(), positions.begin(), positions.end());
        }


    }

    // find maz value of x_values
    int max_x = *std::max_element(x_values.begin(), x_values.end());
    int max_y = *std::max_element(y_values.begin(), y_values.end());

    std::vector<std::vector<char> > map(max_y + 3, std::vector<char>(max_x + 1000, AIR));

    for (auto rock : rocks)
    {
        for (auto pos : rock.positions)
        {
            map[pos.y][pos.x] = ROCK;
        }
    }

    // make a floor of rocks at the bottom of the map
    for (size_t i = 0; i < map[0].size(); i++)
    {
        map[map.size() - 1][i] = ROCK;
    }
    map[0][500] = SAND_PRODUCER;


    return map;


}

void draw_map(std::vector<std::vector<char> > &map)
{
    for (size_t row = 0; row < map.size(); row ++)
    {
        for (size_t col = 420; col < map[row].size() - 920;  col++)
        {
            std::cout << map[row][col];
        }
        std::cout << std::endl;
    }
}


int part1(std::vector<std::string> input)
{
    std::vector<std::vector<char> > map = make_map(input);
    draw_map(map);

    std::vector<SandParticle> particles;
        

    while (true)
    {
        SandParticle particle;

        while (true)
        {
            // generate new particle
            int next_step = choose_sand_path(particle, map);
            if (next_step == -1)
            {
                particles.push_back(particle);
                break;
            }
            else if (next_step == DOWN)
            {
                map[particle.pos.y][particle.pos.x] = AIR;
                map[particle.pos.y + 1][particle.pos.x] = SAND;
                particle.pos.y += 1;
            }
            else if (next_step == LEFT)
            {
                map[particle.pos.y][particle.pos.x] = AIR;
                map[particle.pos.y + 1][particle.pos.x - 1] = SAND;
                particle.pos.x -= 1;
                particle.pos.y += 1;

            }
            else if (next_step == RIGHT)
            {
                map[particle.pos.y][particle.pos.x] = AIR;
                map[particle.pos.y + 1][particle.pos.x + 1] = SAND;
                particle.pos.x += 1;
                particle.pos.y += 1;

            }

            if (particle.pos.y == 0)
            {
                break;
            }
        }
        // draw_map(map);

        if (particle.pos.y == 0)
        {
            break;
        }
    }
    
    draw_map(map);

    int number_of_sand_particles = particles.size();




    return number_of_sand_particles;

}


int main()
{

    std::vector<std::string> v = read_file<std::string>("input.txt");

    std::cout << part1(v) << std::endl;



    
    return 0;

}