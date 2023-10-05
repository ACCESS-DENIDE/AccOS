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

void print_newline()
{
    col=0;

    row++;

     if(row<NUM_ROWS){
        return;
    }
    else
    {
        for (int i = 1; i <NUM_ROWS; i++)
        {
            for (int g = 0; g < NUM_COLS; g++)
            {
                struct ConsChar MovCh=buffer[g+NUM_ROWS*i];
                buffer[g+NUM_ROWS*(i-1)]=MovCh;
            }
            
        }
        clear_row(NUM_ROWS-1);
        row=NUM_ROWS-1;
        
    }

}