#include <string>
using namespace std;
class File{
    public:
        virtual bool isDirectory(){}
        virtual size_t listFiles(string** result){}
        virtual string getName(){}
        virtual string getSize(){}
        virtual string blockCount(){}
};
class FileSystem;
