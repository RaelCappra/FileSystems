#include <string>
using namespace std;
class FileSystem {
    public:
        virtual int init();
};

class FATFileSystem: public FileSystem {

}; 
