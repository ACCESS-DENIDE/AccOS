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

void ClearRow(int row_clear){
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



void ClearPrint()
{
   
    for (int i = 0; i < NUM_ROWS; i++)
    {
        ClearRow(i);
    }
    col=0;
    row=0;

}

void SetPrintColor(uint_8 foreground, uint_8 background)
{
    CurColor=foreground+(background<<4);
}

void GetCursor(uint_8 *x, uint_8 *y)
{
    (*x)=col;
    (*y)=row;
}

void SetCursor(uint_8 x, uint_8 y)
{
    col=x;
    if(x>NUM_COLS-1){
        col=NUM_COLS-1;
    }

    row=y;
    if(y>NUM_ROWS-1){
        row=NUM_ROWS-1;
    }

}

char GetPrintColor()
{
    return CurColor;
}

void SwitchPrintColor(uint_8 newcol)
{
    CurColor=newcol;
}

void PrintChar(char ch)
{
    PrintCharSavePos(ch);

    col++;

    if(col==NUM_COLS){
        
        PrintNewLine();
    }

   
}

void PrintCharSavePos(char ch)
{
    if(ch== '\n'){
        PrintNewLine();
        return;
    }

    struct ConsChar mpty;
    mpty.color=CurColor;
    mpty.symb=ch;


    buffer[col+NUM_COLS*row]=mpty;

}

void PrintString(char *string)
{
    for (int i = 0; 1; i++)
    {
        char ch=(char)string[i];

        if(ch=='\0'){
            return;
        }

        PrintChar(ch);
    }
    

}

void PrintInt(int inp)
{
    int flag=0;
    if(inp<0){
        inp=inp*(-1);
        flag=1;
    }
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
    
    if(flag){
        PrintChar('-');
    }
    PrintString(to_str);
    
}

void PrintNewLine()
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
        ClearRow(NUM_ROWS-2);
        row=NUM_ROWS-2;
        
    }

}

void GetMax(uint_8 *x, uint_8 *y)
{
     (*x)=NUM_COLS;
    (*y)=NUM_ROWS;
}

void ShiftCursor(int x, int y)
{
    int vert_shift=Floor(x, NUM_COLS)+y;
    int hor_shift=x % NUM_COLS;

    row+=vert_shift;

    col+=hor_shift;

    if(row<0){
        row=0;
    }else if (row>NUM_ROWS-1)
    {
        row=NUM_ROWS-1;
    }
    

    if(col<0){
        col=NUM_COLS+col;
    }
    else if(col>NUM_COLS-1){
        col=NUM_COLS-1;
    }


    
}
