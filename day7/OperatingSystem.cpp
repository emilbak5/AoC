#include "OperatingSystem.h"

OperatingSystem::OperatingSystem()
{
    std::cout << "Booting OS" << std::endl;
    std::shared_ptr<Directory> d1(new Directory());
    directories.push_back(d1);
}

OperatingSystem::~OperatingSystem()
{

}


OperatingSystem::OperatingSystem(std::vector<std::string> _commands)
{
    commands = _commands;
    std::shared_ptr<Directory> d1(new Directory());

    directories.push_back(d1);
}


void OperatingSystem::cd(std::string destination)
{
    if (destination == "..")
    {
        if (current_dir->get_name() == "/")
        {
            current_dir = current_dir;
        }
        else
        {
            current_dir = current_dir->get_upper_dir();
        }
    }
    else if (destination == "/")
    {
        current_dir = directories[0];
    }
    else
    {
        // for (auto dir : directories)
        // {
        //     if (dir->get_name() == destination)
        //     {
        //         current_dir = dir;
        //     }
        // }
        for (auto dir : current_dir->get_sub_dirs())
        {
            if (dir->get_name() == destination)
            {
                current_dir = dir;
            }
        }
        directories.push_back(current_dir);
    }

}

void OperatingSystem::ls(size_t &i)
{
    int file_size;
    std::string name;
    char space;
    i++;

    while (commands[i][0] != '$')
    {
        if (isdigit(commands[i][0]))
        {
            file_size = std::stoi(&commands[i][0]);
            space = commands[i].find(' ');
            name = commands[i].substr(space + 1);

            std::shared_ptr<File> temp_file (new File());

            temp_file->name = name;
            temp_file->size = file_size;
            current_dir->add_file(temp_file);
        }
        else
        {
            space = commands[i].find(' ');
            name = commands[i].substr(space + 1);

            std::shared_ptr<Directory> new_dir(new Directory(name, current_dir));
            current_dir->add_sub_dir(new_dir);
        }
        
        i++;
        if (i == commands.size())
            break;
    }
}

int OperatingSystem::calculate_summed_size()
{
    int total_size = 0;

    for (size_t i = 0; i < commands.size(); i++)
    {
        std::cout << commands[i] << std::endl;
        if (commands[i][0] == '$')
        {
            if (commands[i][2] == 'c')
            {
                std::string destination = commands[i].substr(5);
                cd(destination);
            }
            else if (commands[i][2] == 'l')
            {
                ls(i);

                i--; 
            }
        }
    }


    int folder_size = 0;
    // for (auto dir : directories)
    // {
    //     dir->calculate_folder_size();
    //     folder_size = current_dir->get_directory_size();
    //     if (folder_size <= 100000)
    //         total_size += folder_size;
    // }



    return total_size;

}
