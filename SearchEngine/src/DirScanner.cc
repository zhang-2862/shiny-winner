#include "DirScanner.hh"

#include <dirent.h>
#include <iostream>

DirScanner::DirScanner() {

}

DirScanner::~DirScanner() {

}

void DirScanner::operator()(const string& dir) {
    traverse(dir);
}

vector<string>& DirScanner::files() {
    return files_;
}

void DirScanner::traverse(const string& dirname) {
    DIR* dirp = opendir(dirname.c_str());
    if (!dirp) {
        std::cerr << "Failed to open directory: " << dirname << "\n";
        return;
    }

    dirent* direntp; 
    while ((direntp = readdir(dirp)) != nullptr) {
        string d_name = direntp->d_name;
        if (d_name == "." || d_name == "..") {
            continue;
        }
        string path = dirname + "/" + direntp->d_name;
        files_.push_back(path);
    }
    closedir(dirp);
}
