#ifndef DIRECTORY_H
#define DIRECTORY_H

#pragma once


#include <vector>
#include <string>
#include "File.h"
#include <memory>


class Directory
{
public:
    Directory();
    ~Directory();

    Directory(std::string _name, std::shared_ptr<Directory> _upper_dir);


    void calculate_folder_size();

    void add_file(std::shared_ptr<File> file_to_add);

    std::shared_ptr<Directory> get_upper_dir(){ return upper_dir; }
    int get_directory_size() { return directory_size; }
    std::string get_name() { return name; }
    std::vector<std::shared_ptr<Directory> > get_sub_dirs() { return subdirs; }
    std::vector<std::shared_ptr<File> > get_files() { return files; }
    void set_counted() { counted = false; }
    bool get_counted() { return counted; }

    void add_to_directory_size(int num) { directory_size += num; }


    
    void add_sub_dir(std::shared_ptr<Directory> subdir);



private:

    std::shared_ptr<Directory> upper_dir;
    long long int directory_size = 0;
    std::string name;
    std::vector<std::shared_ptr<File> > files;
    std::vector<std::shared_ptr<Directory> > subdirs;
    bool counted = false;

};

#endif