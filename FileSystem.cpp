#include <string>
#include "FileSystem.h"
using namespace std;
class FileSystem {
    public:
        virtual int init();
        virtual int fileFromPath(string path, File* result);
};

class FATFileSystem: public FileSystem {

}; 


class File{
    public:
        virtual bool isDirectory();
};

class FATFile: public File{

};
