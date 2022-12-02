#include<iostream>
#include<string>
#include <string_view>

#include "../read_file.hpp"


const char rock = 'A'; 
const char paper = 'B'; 
const char sissor = 'C'; 

const char loose = 'X';
const char draw = 'Y';
const char win = 'Z';

const int score_rock = 1;
const int score_paper = 2;
const int score_sissor = 3;

const int score_lost = 0;
const int score_draw = 3;
const int score_won = 6;


int calc_points(char player_gnome, char player_me)
{
    int points = 0;

    if (player_me == rock)
        points += score_rock;
    else if (player_me == paper)
        points += score_paper;
    else
        points += score_sissor;
    

    if (player_me == player_gnome)
        points += score_draw;
    else if (player_me == rock && player_gnome == sissor)
        points += score_won;
    else if (player_me == paper && player_gnome == rock)
        points += score_won;
    else if (player_me == sissor && player_gnome == paper)
        points += score_won;
    else
        points += score_lost;

    return points;
}

int convert_to_num(char a)
{
    if (a == 'A')
        return 1;
    else if (a == 'B')
        return 2;
    else
        return 3;
}



int calc_points_2(char player_gnome, char outcome)
{
    int points = 0;
    
    int player_gnome_int = convert_to_num(player_gnome);


    if (outcome == win)
    {
        points += score_won;
        int player_hand = player_gnome_int + 1;
        if (player_hand == 4)
            player_hand = 1;
        points += player_hand;
    }
    else if (outcome == loose)
    {
        points += score_lost;
        int player_hand = player_gnome_int - 1;
        if (player_hand == 0)
            player_hand = 3;
        points += player_hand;
    }
    else
    {
        points += score_draw;
        int player_hand = player_gnome_int;
        points += player_hand;
    }
        

    return points;
}



int main()
{

    char player_gnome;
    char player_me;

    std::vector<std::string> v = read_file<std::string>("input.txt");
    int points = 0;
    for (auto round : v)
    {
        points += calc_points_2(round[0], round[2]);
    }

    std::cout << points << std::endl;

    points = 0;
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i][2] == 'X')
        {
            v[i][2] = 'A';
        } 
        else if(v[i][2] == 'Y')
        {
            v[i][2] = 'B';
        }
        else
            v[i][2] = 'C';
    }

    for (auto round : v)
    {
        points += calc_points(round[0], round[2]);
    }

    std::cout << points << std::endl;
    
    return 0;

}




