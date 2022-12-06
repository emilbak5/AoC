#ifndef ELVES_H
#define ELVES_H

#pragma once

#include<vector>



class Elves
{
public:
    Elves();
    Elves(int start, int end);
    ~Elves();

    bool check_if_range_is_contained(std::vector<Elves> elfs);
    bool check_if_range_is_contained2(std::vector<Elves> elfs);

private:

int _start;
int _end;

};

#endif