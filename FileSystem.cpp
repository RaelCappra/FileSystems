#include <string>
#include "FileSystem.h"
using namespace std;

struct Block{
    Block* next;
    char* contents;
};
class FATFile: public File{
    public:
        Block* firstBlock;
        bool isDirectory(){
            return true;
        }
};


class FATFileSystem: public FileSystem {
    private:
        Block** table;
        string* name_table;

        size_t table_size = 0;
        size_t block_size, partition_size;
    public:
        int init(){
            return init(512*1024, 100*1024*1024);
        }
        int init(size_t block_size, size_t partition_size){
            this->block_size = block_size;
            this->partition_size = partition_size;
            table_size++;
            Block* root_block = new Block();
            root_block->next = NULL;
            root_block->contents = (char*)malloc(block_size * sizeof(char) - sizeof(Block*));
            table = (Block**)malloc(partition_size * block_size);
            //table[0] = root_block;
            return 0;
        }

        int fileFromPath(string path, File* result){
            result = new FATFile();
            return 0;
        }
}; 

