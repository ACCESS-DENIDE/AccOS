#include "print.h"

const static int NUM_COLS=80;
const static int NUM_ROWS=25;

struct ConsChar{
    char symb;
    char color;
};

struct ConsChar* buffer=(struct ConsChar*) 0xb8000;

int col=0;
int row=0;

int CurColor=COLOR_WHITE | COLOR_BLACK<<4;

void clear_row(int row_clear){
    struct ConsChar mpty;
    mpty.color=CurColor;
    mpty.symb=' ';

    for (int i = 0; i < NUM_COLS; i++)
    {
        buffer[i+NUM_COLS*row_clear]=mpty;
    }
    
    col=0;
    row=row_clear;

}



void clear_print()
{
   
    for (int i = 0; i < NUM_ROWS; i++)
    {
        clear_row(i);
    }
    col=0;
    row=0;

}

void set_color(char foreground, char background)
{
    CurColor=foreground+(background<<4);
}

char get_color()
{
    return CurColor;
}

void switch_color(char newcol)
{
    CurColor=newcol;
}

void print_chr(char ch)
{
    if(ch== '\n'){
        print_newline();
        return;
    }

    struct ConsChar mpty;
    mpty.color=CurColor;
    mpty.symb=ch;


    buffer[col+NUM_COLS*row]=mpty;

    col++;

    if(col==NUM_COLS){
       print_newline();
    }

   
}

void print_str(char *string)
{
    for (int i = 0; 1; i++)
    {
        char ch=(char)string[i];

        if(ch=='\0'){
            return;
        }

        print_chr(ch);
    }
    

}

void print_int(int inp)
{
    char to_str[20];
    to_str[19]='\0';
    int next=inp;
    int cou=1;
    do
    {
        to_str[19-cou]=(next % 10)+48;
        next=(next-(next % 10))/10;
        cou++;
    } while (next>9);
   if(next!=0){
         to_str[19 - cou] = next + 48;
    }
    else {
        cou--;
     }
    for (int i = 0; i <= cou; i++)
    {
        to_str[i]=to_str[19-cou+i];
    }
    

    print_str(to_str);
    
}

void print_newline()
{
    col=0;

    row++;

     if(row<NUM_ROWS-1){
        return;
    }
    else
    {
        for (int i = 1; i < NUM_ROWS; i++)
        {
            for (int g = 0; g < NUM_COLS; g++)
            {
                struct ConsChar MovCh=buffer[g+(NUM_COLS)*i];
                buffer[g+(NUM_COLS)*(i-1)]=MovCh;
            }
            
        }
        clear_row(NUM_ROWS-2);
        row=NUM_ROWS-2;
        
    }

}