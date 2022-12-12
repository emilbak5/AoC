#include<iostream>
#include<string>


#include "OperatingSystem.h"
#include "OperatingSystem.cpp"
#include "../read_file.hpp"


long long int total_count = 0;
std::vector<int> test;


int recursion_baby(std::shared_ptr<Directory> current_dir)
{
    int temp = 0;
    int dir_total;

    current_dir->calculate_folder_size();
    dir_total = current_dir->get_directory_size();

    if (current_dir->get_name() != "/")
        current_dir->get_upper_dir()->add_to_directory_size(dir_total);


    if (current_dir->get_sub_dirs().empty())
    {
        if (dir_total < 100000)
        {
            test.push_back(dir_total);
            total_count += dir_total;
        }
        return dir_total;
    }

    else
    {
        for (auto dir : current_dir->get_sub_dirs())
        {
            dir_total += recursion_baby(dir);
        }

        if (dir_total < 100000)
        {
            test.push_back(dir_total);
            total_count += dir_total;
        }
    }

    if (dir_total > 999999999)
        int x = 5;



    return total_count;

}


// long long int total_size = 233910550;
long long int total_size = 45'349'983;

long long int TOTAL_DISK_SPACE = 70'000'000;
long long int UNUSED_NEEDED = 30'000'000;
long long int smallest_dir = INT32_MAX;

                 
int recursion_baby2(std::shared_ptr<Directory> current_dir)
{
    int temp = 0;
    int dir_total;

    current_dir->calculate_folder_size();
    dir_total = current_dir->get_directory_size();

    if (current_dir->get_name() != "/")
        current_dir->get_upper_dir()->add_to_directory_size(dir_total);


    if (current_dir->get_sub_dirs().empty())
    {
        // if (dir_total < 100000)
        // {
            test.push_back(dir_total);
            total_count += dir_total;
        // }
        return dir_total;
    }

    else
    {
        for (auto dir : current_dir->get_sub_dirs())
        {
            dir_total += recursion_baby2(dir);
        }

        // if (dir_total < 100000)
        // {
            test.push_back(dir_total);
            total_count += dir_total;
        // }
    }





    return total_count;

}



int main()
{

    std::vector<std::string> v = read_file<std::string>("input.txt");

    OperatingSystem my_os(v);


    long long int total_result = my_os.calculate_summed_size();

    total_result = recursion_baby2(my_os.get_root_dir());

    std::cout << total_result << std::endl;
    std::cout << total_count << std::endl;

    int space_we_need_to_delete = total_size - (TOTAL_DISK_SPACE - UNUSED_NEEDED);
    std::cout << *std::lower_bound(test.begin(), test.end(), space_we_need_to_delete) << std::endl;



    // long long int sum = 0;
    // std::cout << test.size() << std::endl;

    // for (auto vec : test)
    //     sum += vec;
    
    // std::cout << sum << std::endl;

    // std::cout << total_result << std::endl;


    
    return 0;

}