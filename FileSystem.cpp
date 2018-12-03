#include <string>
#include "FileSystem.h"
using namespace std;

class FATFile: public File{
    public: bool isDirectory(){
        return true;
    }
};


class FATFileSystem: public FileSystem {
    public:
        int fileFromPath(string path, File* result){
            result = new FATFile();
            return 0;
        }

}; 

