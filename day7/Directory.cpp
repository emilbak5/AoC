#include "Directory.h"

Directory::Directory()
{
    name = "/";
}

Directory::~Directory()
{

}


Directory::Directory(std::string _name, std::shared_ptr<Directory> _upper_dir)
{
    name = _name;
    upper_dir = _upper_dir;
}



void Directory::calculate_folder_size()
{

    for (std::shared_ptr<File> file : files)
    {
        directory_size += file->size;
    }

    if (directory_size > 99999999)
        int x = 5;

}




void Directory::add_file(std::shared_ptr<File> file_to_add)
{
    files.push_back(file_to_add);
}


void Directory::add_sub_dir(std::shared_ptr<Directory> subdir)
{
    subdirs.push_back(subdir);
}
