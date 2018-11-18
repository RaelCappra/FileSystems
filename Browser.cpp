#include "FileSystem.cpp"
#include "err.h"
#include <string>
using namespace std;

FileSystem* fs;
File* cwd;
string pathCwd;
int init(){
    fs = new FATFileSystem(); //TODO: decidir
    if(fs){
        fs->init();
        pathCwd = "/";
        fs->fileFromPath(pathCwd, cwd);
        return OK;
    }
    return NULL_FS;
}

int cd(int argc, string* argv){
    if(argc < 1){
        string s[1] = {"/"};
        return cd(1, s);
    }
    string path = argv[0];
    File f;
    if(!fs)
        return NULL_FS;
    int error = fs->fileFromPath(path, &f);
    if(error)
        return error;
    if(f.isDirectory()){
        pathCwd = path;
        cwd = &f;
        return OK;
    }
    return NOT_DIR;
}
