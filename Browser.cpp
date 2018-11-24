#include "FileSystem.cpp"
#include "err.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

FileSystem* fs;
File* cwd;
string pathCwd;
int init(){
    /*fs = new FATFileSystem(); //TODO: decidir
    if(fs){
        fs->init();
        pathCwd = "/";
        fs->fileFromPath(pathCwd, cwd);
        return OK;
    }
    return NULL_FS;*/
}

string canonPath(string path){
    /*
     * Determina o caminho absoluto canônico a partir de uma string dada.
     * O resultado será um caminho absoluto sem barras repetidas
     *
     * */
    vector<string>* stack = new vector<string>();
    string result = "";
    int start, end;
    if(path.length() < 1)
        return "";

    if(path[0] == '/'){//abs path
        path = path.substr(1, -1);
    }
    else{ //relative path -> initialize path stack with cwd
        string buffer = "";
        for(int i = 0; i < pathCwd.length(); i++){
            if(pathCwd[i] == '/'){
                if(buffer != "")
                    stack->push_back(buffer);
                buffer = "";
            }
            else{
                buffer += pathCwd[i];
            }
        }
        if(buffer != "")
            stack->push_back(buffer);
    }

    for(start = end = 0; start < path.length(); start = end){
        while(path[start] == '/')//skip /'s
            start++;
        for(end = start; end < path.length() && path[end] != '/'; end++){//find end of segment
        }
        if(end <= start)
            break;
        string segment = path.substr(start, end - start);
        if(segment == ".")
            continue;

        if(segment == ".."){
            if(!stack->empty())
                stack->pop_back();
        }
        else if (segment != "")
            stack->push_back(segment);
    }
    if(stack->empty()){
        if(result == "")
            return "/";
        return result;
    }

    for(int i = 0; i < stack->size(); i++){
        result += '/';
        result += stack->at(i);
    }
    return result;
}
/*
int cd(int argc, string* argv){
    if(argc < 1){
        string s[1] = {"/"};
        return cd(1, s);
    }
    string path = canonPath(argv[0]);
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
*/
int main(){
    pathCwd = "/home/rael";
    cout << canonPath("//////home///./rael///pasta/.././././memes/") << "\n";
    cout << canonPath("games//./memesg///") << "\n";
    cout << canonPath("games//./memesg///../..//../../../.././././//lucas/skyrim") << "\n";
}
