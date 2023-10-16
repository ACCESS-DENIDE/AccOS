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


void KeyboardInit()
{
    SetDataToPort(PIC1_PORT + 1, 0xFF ^ 0x02);
}

void OnKeyEvent(uint_8 event_code)
{   
    uint_8 new_chr='\0';
    uint_8 flg=InterpritateCode(event_code, &new_chr);

    if(flg){
        pressed_key=new_chr;
        flag_k=1;
        if(pressed_key==13){
            line[size]='\0';
            flag_l=1;
            size=0;
        }
        else
        {

            line[size]=new_chr;
            size++;
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
    do
    {
        
    } while (flag_l==0);
    flag_l=0;
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
