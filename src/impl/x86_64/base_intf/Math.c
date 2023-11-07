#include "Math.h"

int Floor(int a, int b)
{   
    int comp_a=a, comp_b=b;
    a=Abs(a);
    b=Abs(b);
    int ret=(a-(a % b))/b;

    if(comp_a<0){
        ret=ret*(-1);
    }


    if(comp_b<0){
        ret=ret*(-1);
    }

    return ret;
}

int Ceiling(int a, int b)
{

    int comp_a=a, comp_b=b;
    a=Abs(a);
    b=Abs(b);
   int ret=(a+(b-(a % b)))/b;

    if(comp_a<0){
        ret=ret*(-1);
    }


    if(comp_b<0){
        ret=ret*(-1);
    }

    return ret;
}

/*int Abs(int a)
{
    if(a>0){
        return a;
    }
    else{
        a=a*(-1);
        return a;
    }
}*/
