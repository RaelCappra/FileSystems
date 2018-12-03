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
    fs = new FATFileSystem(); //TODO: decidir
    if(fs){
        fs->init();
        pathCwd = "/";
        fs->fileFromPath(pathCwd, cwd);
        return OK;
    }
    return NULL_FS;
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

int ls(int argc, string* argv){
    if(!fs)
        return NULL_FS;
    if(!cwd)
        return ERR;
    string* filenames;
    size_t len_dir = cwd->listFiles(&filenames);
    if(!filenames)
        return ERR;
    cout << "TIPO|NOME|TAMANHO|BLOCOS" << "\n";
    if(len_dir == 0){
        return 0;
    }
        
    for(int i = 0; i < len_dir; i++){
        File f;
        int error = fs->fileFromPath(filenames[i], &f);
        if(error)
            return error;
        if(f.isDirectory())
            cout << "D " << f.getName();
        else{
            cout << "A " << f.getName() << " " << f.getSize() << "B " << f.blockCount();
        }
        cout << "\n";
    }
}
int touch(int argc, string* argv){
    if(!fs)
        return NULL_FS;
    if(!cwd)
        return ERR;
    if(argc < 2)
        return ERR;
    string filename = argv[0];
    size_t size = atoi(argv[1].c_str());//TODO: Convert to int
    string content;
    if(argc < 3)
        content = string(new char[size]);
    content = argv[2];
    string path = canonPath(filename);
    if(fs->exists(path))
        return FILE_EXISTS;
    File f;
    int result = fs->create(path, size, &f);
    if(result)
        return result;
    int write_result = f.write(0, size, content);
    if(write_result)
        return write_result;
    return OK;
}

int main(){
    pathCwd = "/home/rael";
    cout << canonPath("//////home///./rael///pasta/.././././memes/") << "\n";
    cout << canonPath("games//./memesg///") << "\n";
    cout << canonPath("games//./memesg///../..//../../../.././././//lucas/skyrim") << "\n";
    cout << canonPath(".") << "\n";
    cout << canonPath("/./././") << "\n";
}
