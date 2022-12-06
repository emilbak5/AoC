#include "Elves.hpp"
#include<vector>

Elves::Elves()
{

}

Elves::~Elves()
{

}

Elves::Elves(int start, int end)
{
    _start = start;
    _end = end;
}

bool Elves::check_if_range_is_contained(std::vector<Elves> elfs)
{
    Elves elf1 = elfs[0];
    Elves elf2 = elfs[1];

    bool contained = false;

    if ((elf1._start >= elf2._start) &&
        (elf1._end <= elf2._end))
        {
            contained = true;
        }
    else if ((elf2._start >= elf1._start) &&
        (elf2._end <= elf1._end))
        {
            contained = true;
        }
    
    return contained;

}

bool Elves::check_if_range_is_contained2(std::vector<Elves> elfs)
{
    Elves elf1 = elfs[0];
    Elves elf2 = elfs[1];

    bool contained = false;

    if ((elf2._start <= elf1._end) && (elf2._end >= elf1._start))
    {
        contained = true;
    }

    
    return contained;

}
