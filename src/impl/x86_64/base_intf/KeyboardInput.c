#include "KeyboardInput.h"



char CCodes[]={0,27,'1','2','3','4','5','6','7','8','9','0','-','=', 8,
9, 'q','w','e','r','t','y','u','i','o','p','[',']',13,17,
'a','s','d','f','g','h','j','k','l',';', 39 , 96 , 15 ,92
,'z','x','c','v','b','n','m',',','.','/', 14, '*', 17, ' '};

char* line;
int size=0;

char pressed_key='\0';

int_8 flag_l=0;
int_8 flag_k=0;

bool read_line=0;

bool shift_dwn=0;
bool ctrl_dwn=0;
bool alt_dwn=0;

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
                PrintNewLine();
            }
            else
            {


              
                switch (new_chr)
                {
                case 8: /*Backspace*/

                    if(size>0){
                       
                        line[size]=' ';
                        size--;
                        ShiftCursor(-1, 0);
                        PrintCharSavePos(' ');
                    }

                    break;
                
                case 9: /*Tab*/
                    GetCursor(&mem_x, &mem_y);
                    int step=mem_x % 8;

                    if(step==0){
                        step=8;
                    }
                    ShiftCursor(step, 0);

                    break;
                
                case 17: /*Ctrl*/
                    ctrl_dwn=1;
                    break;
                
                case 15: /*Shift*/
                    shift_dwn=1;
                    break;
                
                case 14: /*Alt*/
                    alt_dwn=1;
                    break;
                
                default:
                    

                    if(shift_dwn){
                        switch (new_chr)
                        {
                        case 61:
                            new_chr=43;
                            break;
                        case 48:
                            new_chr=41;
                            break;
                        case 57:
                            new_chr=40;
                            break;
                        case 54:
                            new_chr=94;
                            break;
                         case 56:
                            new_chr=42;
                            break;
                        default:
                             new_chr-=32;
                            break;
                        }
                       
                    }
                    line[size]=new_chr;
                    size++;
                    int cur_size=BlocSize(line);
                    if(!(size+1<cur_size)){

                        line=(char*)MemReal(line, size+11, 1);

                    }
                    PrintChar(new_chr);
                    break;
                }

                
            }
        }
    }
    else
    {
        pressed_key=0;
        flag_k=0;

         switch (new_chr)
                {
                case 8: /*Backspace*/
                   
                    break;
                
                case 9: /*Tab*/
                   break;
                
                case 17: /*Ctrl*/
                    ctrl_dwn=0;
                    break;
                
                case 15: /*Shift*/
                    shift_dwn=0;
                    break;
                
                case 14: /*Alt*/
                    alt_dwn=0;
                    break;
                
                default:
                
                    break;
                }
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
    Free(line);
    
    line=(char*)MemAll(10);

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
