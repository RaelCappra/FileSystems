#include "FileSystem.cpp"
FileSystem* fs;
int init(){
    fs = new FATFileSystem(); //TODO: decidir
    fs->init();
    return 0;
}

