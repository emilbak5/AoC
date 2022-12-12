#ifndef OPERATINGSYSTEM_H
#define OPERATINGSYSTEM_H

#pragma once

#include <vector>
#include <string>
# include <iostream>
#include <cmath>
#include <memory>
#include "Directory.h"
#include "Directory.cpp"
#include "File.h" 

class OperatingSystem
{
public:
    OperatingSystem();
    ~OperatingSystem();

    OperatingSystem(std::vector<std::string> _commands);

    void ls(size_t &i);
    void cd(std::string destination);

    std::shared_ptr<Directory> get_root_dir() { return directories[0]; }
    std::vector<std::shared_ptr<Directory> > get_dirs() { return directories; }

    int calculate_summed_size();

private:

    std::shared_ptr<Directory> current_dir;


    std::vector<std::string> commands;
    std::vector<std::shared_ptr<Directory> > directories;

};

#endif