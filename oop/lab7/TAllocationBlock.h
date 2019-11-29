#ifndef TALLOCATIONBLOCK_H
#define TALLOCATIONBLOCK_H
 
#include <cstdlib>
class TAllocationBlock {
public:
    TAllocationBlock(size_t _size,size_t _count): size(_size),count(_count)  {
        used_blocks = (char*)malloc(size*count);
        free_blocks = (void**)malloc(sizeof(void*)*count);
    
        for(size_t i=0;i<count;i++) free_blocks[i] = used_blocks + i * size;
            freecount = count;
        std::cout << "TAllocationBlock: Memory init" << std::endl;
    }


    void* allocate(int len) {

        void *result = nullptr;
    
        if(freecount > 0 && freecount >= len) {

            result = free_blocks[freecount - 1];
            freecount--;
            std::cout << "TAllocationBlock: Allocate " << (count-freecount) << " of " << count << std::endl;
        } else {
            std::cout << "TAllocationBlock: No memory exception :-)" << std::endl;
        }
    
        return result;
    }
 
    void deallocate(void *pointer) {
        std::cout << "TAllocationBlock: Deallocate block "<< std::endl;
    
        free_blocks[freecount] = pointer;
        freecount ++;
 
    }
    bool hasfree_blocks() {
        return freecount > 0;
    }
    
    virtual ~TAllocationBlock() {
    
        if(freecount<count) std::cout << "TAllocationBlock: Memory leak?" << std::endl;
            else  std::cout << "TAllocationBlock: Memory freed" << std::endl;
        delete free_blocks;
        delete used_blocks;
    }
private:
    size_t size;
    size_t count;
    
    char  *used_blocks;
    void  **free_blocks;
    
    size_t freecount;
};



#endif      /* TAllocationBlock_H */