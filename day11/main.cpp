#include<iostream>
#include<string>
#include<memory>
#include <math.h> 
#include <algorithm>
#include <limits>

#include "../read_file.hpp"







struct Monkey
{
    Monkey(long long int _name) : name(_name) {}

    long long int inspect(long long int i);

    long long int name;
    long long int test;

    long long int number_of_inspections = 0;

    std::vector<long long int> items;
    std::string operation;

    std::shared_ptr<Monkey> if_true_monkey;
    std::shared_ptr<Monkey> if_false_monkey;

};

long long int Monkey::inspect(long long int i)
{
    long long int worry_level;
    if (operation[0] == '+')
    {
        if (operation[2] == 'o')
            worry_level = items[i] + items[i];
        else
            worry_level = items[i] + std::stoi(&operation[1]);
    }
    else if (operation[0] == '*')
    {
        if (operation[2] == 'o')
            worry_level = items[i] * items[i];
        else
            worry_level = items[i] * std::stoi(&operation[1]);
    }
    return worry_level;
}


std::vector<std::shared_ptr<Monkey> > create_monkeys(std::vector<std::string> input)
{
    std::vector<std::shared_ptr<Monkey> > monkeys;
    for (auto command : input)
    {
        if (command[0] == 'M')
        {
            std::shared_ptr<Monkey> monkey(new Monkey(std::stoi(&command[7])));
            monkeys.push_back(monkey);
        }
    }

    return monkeys;
}

void add_monkey_info(std::vector<std::shared_ptr<Monkey> > &monkeys, std::vector<std::string> input)
{
    long long int current_monkey_index = -1;
    size_t comma_place;

    for (auto command : input)
    {
        if (command[0] == 'M')
            current_monkey_index += 1;
            comma_place = 18;

        if (command[2] == 'S')
        {
            std::vector<long long int> start_items;
            size_t last_comma = command.find_last_of(',');
            while(true)
            {
                long long int item = std::stoi(&command[comma_place]);
                start_items.push_back(item);

                if (comma_place - 2 == last_comma || last_comma == std::string::npos )
                    break;

                comma_place = command.find(',', comma_place + 1);
                if (command.find(',') == 1)
                    break;
                comma_place += 2;
            }
            monkeys[current_monkey_index]->items = start_items;
        }
        else if (command[2] == 'O')
            monkeys[current_monkey_index]->operation = command.substr(23);
        else if (command[2] == 'T')
            monkeys[current_monkey_index]->test = std::stoi(&command[21]);
        else if (command[7] == 't')
            monkeys[current_monkey_index]->if_true_monkey = monkeys[std::stoi(&command[29])];
        else if (command[7] == 'f')
            monkeys[current_monkey_index]->if_false_monkey = monkeys[std::stoi(&command[30])];
        
    }
}

long long int part1(std::vector<std::string> input)
{
    long long int result;
    long long int worry_level;

    std::vector<std::shared_ptr<Monkey> > monkeys = create_monkeys(input);
    add_monkey_info(monkeys, input);

    long long int rounds = 1;

    for (long long int rond = 0; rond < rounds; rond++)
    {
        for (auto monkey : monkeys)
        {
            for (long long int i = 0; i < monkey->items.size(); i++)
            {
                // inspect
                worry_level = monkey->inspect(i);
                monkey->number_of_inspections += 1;
                // chill
                // worry_level = floor((worry_level / 3.0));
                // test
                if (worry_level % monkey->test == 0)
                {
                    // monkey->if_true_monkey->items.push_back(monkey->items[i]);  
                    monkey->if_true_monkey->items.push_back(worry_level);
                    // std::cout << monkey->if_true_monkey->name << std::endl;

                }
                else
                {
                    monkey->if_false_monkey->items.push_back(worry_level);
                    // std::cout << monkey->if_false_monkey->name << std::endl;

                    // monkey->if_false_monkey->items.push_back(monkey->items[i]);
                }
            }
            monkey->items.clear();
        }
    }


    std::vector<std::vector<long long int> > worry_levels;
    for (auto monkey : monkeys)
        worry_levels.push_back(monkey->items);

    std::vector<long long int> inspections_total;
    for (auto monkey : monkeys)
        inspections_total.push_back(monkey->number_of_inspections);


    long long int index = std::distance(inspections_total.begin(),std::max_element(inspections_total.begin(), inspections_total.end()));
    long long int largest = inspections_total[index];
    inspections_total[index] = 0;
    index = std::distance(inspections_total.begin(),std::max_element(inspections_total.begin(), inspections_total.end()));
    long long int second = inspections_total[index];

    


    return largest * second;
}


long long int part2(std::vector<std::string> input)
{

    long long int result;
    long long int worry_level;
    long long int lcm = 1;
    std::vector<std::shared_ptr<Monkey> > monkeys = create_monkeys(input);
    add_monkey_info(monkeys, input);

    for (auto monkey : monkeys)
        lcm *= monkey->test;

    long long int rounds = 10000;

    for (long long int rond = 0; rond < rounds; rond++)
    {
        for (auto monkey : monkeys)
        {
            for (long long int i = 0; i < monkey->items.size(); i++)
            {
                // inspect
                worry_level = monkey->inspect(i);

                worry_level = worry_level % lcm;
                monkey->number_of_inspections += 1;
                // chill
                // worry_level = floor(float(worry_level / 3.0));
                // test
                if (worry_level % monkey->test == 0)
                {
                    // monkey->if_true_monkey->items.push_back(monkey->items[i]);  
                    monkey->if_true_monkey->items.push_back(worry_level);
                    // std::cout << monkey->if_true_monkey->name << std::endl;

                }
                else
                {
                    monkey->if_false_monkey->items.push_back(worry_level);
                    // std::cout << monkey->if_false_monkey->name << std::endl;

                    // monkey->if_false_monkey->items.push_back(monkey->items[i]);
                }
            }   
            monkey->items.clear();
        }
        // std::cout << worry_level << std::endl;
    }


    std::vector<std::vector<long long int> > worry_levels;
    for (auto monkey : monkeys)
        worry_levels.push_back(monkey->items);


    std::vector<long long int> inspections_total;
    for (auto monkey : monkeys)
        inspections_total.push_back(monkey->number_of_inspections);

    long long int index = std::distance(inspections_total.begin(),std::max_element(inspections_total.begin(), inspections_total.end()));
    long long int largest = inspections_total[index];
    inspections_total[index] = 0;
    index = std::distance(inspections_total.begin(),std::max_element(inspections_total.begin(), inspections_total.end()));
    long long int second = inspections_total[index];

    long long int test = largest * second;
    return test;
}







int main()
{

    std::vector<std::string> v = read_file<std::string>("input.txt");

    // std::cout << part1(v) << std::endl;

    std::cout << part2(v) << std::endl;

}