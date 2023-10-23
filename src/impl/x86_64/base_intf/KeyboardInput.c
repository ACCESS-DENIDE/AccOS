#include "KeyboardInput.h"



char CCodes[]={0,27,'1','2','3','4','5','6','7','8','9','0','-','=', 8,
9, 'q','w','e','r','t','y','u','i','o','p','[',']',13,17,
'a','s','d','f','g','h','j','k','l',';', 39 , 96 , 15 ,92
,'z','x','c','v','b','n','m',',','.','/', 14, '*', 17, ' '};

char line[1024];
int size=0;

char pressed_key='\0';

int_8 flag_l=0;
int_8 flag_k=0;

bool read_line=0;


void KeyboardInit()
{
    SetDataToPort(PIC1_PORT + 1, 0xFF ^ 0x02);
}

void OnKeyEvent(uint_8 event_code)
{   
    uint_8 new_chr='\0';
    uint_8 flg=InterpritateCode(event_code, &new_chr);
    int mem_x=0, mem_y=0;
    int holder=0;
    if(flg){
        pressed_key=new_chr;
        flag_k=1;
        if(read_line){
             if(pressed_key==13){
                line[size]='\0';
                flag_l=1;
                size=0;
                GetCursor(&mem_x, &mem_y);
                    
                    mem_x--;

                    if(mem_x<0){
                        GetMax(&mem_x, &holder);
                        mem_x--;
                        mem_y--;
                    }

                    SetCursor(mem_x, mem_y);
                    PrintChar(' ');
                PrintNewLine();
            }
            else
            {


              
                switch (new_chr)
                {
                case 8: /*Backspace*/
                    size--;
                    line[size]='\0';
                    
                    mem_x=0;
                    mem_y=0;
                  
                    GetCursor(&mem_x, &mem_y);
                    mem_x--;
                    mem_x--;

                    switch (mem_x)
                    {
                    case -1:
                        mem_y--;
                        GetMax(&mem_x, &holder);
                        mem_x--;
                        break;
                    case -2:
                        mem_y--;
                        GetMax(&mem_x, &holder);
                        mem_x--;
                        mem_x--;
                        break;
                    
                    default:
                        break;
                    }

                    
                    SetCursor(mem_x, mem_y);
                    PrintChar(219);
                    PrintChar(' ');

                     GetCursor(&mem_x, &mem_y);
                    
                    mem_x--;

                    if(mem_x<0){
                        GetMax(&mem_x, &holder);
                        mem_x--;
                        mem_y--;
                    }

                    SetCursor(mem_x, mem_y);

                    break;
                
                case 9: /*Tab*/

                    break;
                
                case 17: /*Ctrl*/

                    break;
                
                case 15: /*Shift*/

                    break;
                
                case 14: /*Alt*/

                    break;
                
                default:
                    line[size]=new_chr;
                    size++;

                    mem_x=0;
                    mem_y=0;
                    GetCursor(&mem_x, &mem_y);
                    
                    mem_x--;

                    if(mem_x<0){
                        GetMax(&mem_x, &holder);
                        mem_x--;
                        mem_y--;
                    }

                    SetCursor(mem_x, mem_y);

                    PrintChar(new_chr);
                    PrintChar(219);
                    break;
                }

                
            }
        }
    }
    else
    {
        pressed_key=0;
        flag_k=0;
    }
}

char GetKey()
{
    return pressed_key;
}

char ReadKey()
{
    do
    {
        
    } while (flag_k==0);
    flag_k=0;
    return pressed_key;
}

char *ReadLine()
{
    PrintChar(219);
    read_line=1;
    do
    {
        
    } while (flag_l==0);
    flag_l=0;
    read_line=0;
    return &line[0];
}

uint_8 InterpritateCode(uint_8 code, char* symb)
{
    uint_8 ret=0; 
    if(code<129){
        ret=1;
    }
    else
    {
        ret=0;
        code=code-128;
    }

    (*symb)=CCodes[code];
    return ret;
    
}
