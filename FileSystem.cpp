#include <string>
#include "FileSystem.h"
#include "err.h"
using namespace std;

struct Block{
    Block* next;
    char* contents;
};
class FATFile: public File{
    public:
        FileSystem* fs;
        Block* firstBlock;
        size_t dirEntries = 0;

        bool isDirectory(){
            return true;
        }
        size_t listFiles(string **filenames){
            *filenames = new string[256];//TODO:better define dir max length (hah, as if)
            if(!isDirectory()){
                return 1;
            }
            size_t j = 0;
            Block* curBlock = firstBlock;
            for(size_t i = 0; i < dirEntries; i++){
                string name = string();
                for(; curBlock && curBlock->contents[j] != '\0'; j++){
                    if(j == fs->getBlockSize()){
                        j = 0;
                        curBlock = firstBlock->next;
                    }
                    name += curBlock->contents[j];
                }
                *filenames[i] = name;
            }
            return dirEntries;
        }
};


class FATFileSystem: public FileSystem {
    private:
        Block** table;
        string* nameTable;

        size_t tableSize = 0;
        size_t blockSize, partitionSize;
    public:
        int init(){
            return init(512*1024, 100*1024*1024);
        }
        int init(size_t blockSize, size_t partitionSize){
            this->blockSize = blockSize;
            this->partitionSize = partitionSize;
            tableSize++;
            Block* root_block = new Block();
            root_block->next = NULL;
            root_block->contents = (char*)malloc(blockSize * sizeof(char) - sizeof(Block*));
            table = (Block**)malloc(partitionSize / blockSize + blockSize);
            table[0] = root_block;
            return 0;
        }

        int fileFromPath(string path, File* result){
            FATFile* fat = new FATFile();
            if(path == "/"){
                fat->firstBlock = table[0];
                fat->fs = this;
                *result = *fat;
                return 0;
            }
            return INEX_FILE;
        }
        size_t getBlockSize(){
            return blockSize;
        }
}; 

