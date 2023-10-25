#include "MemoryManager.h"

struct AllocatedPointer
{
   void* ptr;
   int size;
   bool state;
};

char heap[HEAP_SIZE_KB*1024];
int allocated_num=0;
struct AllocatedPointer blocks[MAX_ALL_BLOCKS];

void *MemAll(int size)
{
    int best_size=(HEAP_SIZE_KB*1024)+1;
    void* ptr=NULL;
    int shift=0;
    int block_id=-1;

    for (int i = 0; i < allocated_num; i++)
    {
        if(blocks[i].state==0){
            if(best_size>blocks[i].size && blocks[i].size>=size){
                best_size=blocks[i].size;
                ptr=blocks[i].ptr;
                shift=blocks[i].size-size;
                block_id=i;
            }
        }
    }

    if(shift>0){
        blocks[allocated_num].ptr=ptr+size;
        blocks[allocated_num].size=shift;
        blocks[allocated_num].state=0;
        allocated_num++;
    }
    
    blocks[block_id].size=size;
    blocks[block_id].state=1;

   return ptr;
}

void *MemReal(void *ptr, int new_size, bool keep)
{   
    void* new_ptr=MemAll(new_size);

    if(keep){

        

        for (int i = 0; i < allocated_num; i++)
        {
        if(blocks[i].ptr==ptr){
            
            int min=new_size;

            if(blocks[i].size<new_size){
                min=blocks[i].size;
            }

            for (int g = 0; g < min; g++)
            {
                ((char*)(new_ptr))[g]=((char*)(ptr))[g];
            }
            

            break;
        }
        
        }
            

    }
    
    Free(ptr);

   return new_ptr;
}

void Free(void *ptr)
{
    struct AllocatedPointer* next=(struct AllocatedPointer*)NULL;
    struct AllocatedPointer* prev=(struct AllocatedPointer*)NULL;

    for (int i = 0; i < allocated_num; i++)
    {
        if(blocks[i].ptr==ptr){
            
            blocks[i].state=0;

            for (int g = 0; g < allocated_num; g++)
            {
                if(blocks[g].ptr==blocks[i].ptr+blocks[i].size){
                    next=&blocks[g];
                }

                if(blocks[g].ptr+blocks[g].size==blocks[i].ptr){
                    prev=&blocks[g];
                }
            }
            
            if(next!=NULL){
                if(next->state==0){
                    blocks[i].size+=next->size;


                    allocated_num--;
                    
                    bool flag=0;

                     for (int g = 0; g < allocated_num; g++)
                    {   
                        if(next->ptr==blocks[g].ptr){
                            flag=1;
                        }

                        if(flag){
                            blocks[g]=blocks[g+1];
                        }
                        else{
                            blocks[g]=blocks[g];
                        }
                    }
                }
            }

            if(prev!=NULL){
                if(prev->state==0){

                    prev->size+=blocks[i].size;

                    allocated_num--;
                    
                    bool flag=0;

                     for (int g = 0; g < allocated_num; g++)
                    {   
                        if(prev->ptr==blocks[g].ptr){
                            flag=1;
                        }

                        if(flag){
                            blocks[g]=blocks[g+1];
                        }
                        else{
                            blocks[g]=blocks[g];
                        }
                    }
                }
            }

            return;
        }
    }
    

}

void InitAll()
{
    blocks[0].ptr=heap;
    blocks[0].size=HEAP_SIZE_KB*1024;
    blocks[0].state=0;
    allocated_num=1;
}

int BlocSize(void *ptr)
{   


    for (int i = 0; i < allocated_num; i++)
    {
        if(blocks[i].ptr==ptr){
            return blocks[i].size;
        }
        
    }
            

    return -1;
}
