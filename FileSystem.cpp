#include <string>
#include "FileSystem.h"
using namespace std;

class FATFile: public File{
    public: bool isDirectory(){
        return true;
    }
};

class FileSystem {
    public:
        virtual int init();
        virtual int fileFromPath(string path, File* result);
};

class FATFileSystem: public FileSystem {
    public:
        int fileFromPath(string path, File* result){
            result = new FATFile();
            return 0;
        }

}; 

