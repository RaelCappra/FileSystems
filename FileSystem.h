#include <string>
using namespace std;
class File{
    public:
        virtual bool isDirectory(){}
        virtual size_t listFiles(string** result){}
        virtual string getName(){}
        virtual string getSize(){}
        virtual string blockCount(){}
        virtual int write(size_t index, size_t num_bytes, string content){}
};
class FileSystem {
    public:
        virtual size_t getBlockSize(){}
        virtual int init(){}
        virtual int fileFromPath(string path, File** result){}
        virtual bool exists(string path){}
        virtual int create(string path, size_t size, File* result){}
};
class FATFileSystem;
