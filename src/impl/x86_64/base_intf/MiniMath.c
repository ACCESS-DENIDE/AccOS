#include "MiniMath.h"
#include "print.h"

int_64 DivFlor(int a, int b)
{

    int comp_a = a, comp_b = b;
    a = Abs(a);
    b = Abs(b);
    int ret = (a - (a % b)) / b;

    if (comp_a < 0) {
        ret = ret * (-1);
    }


    if (comp_b < 0) {
        ret = ret * (-1);
    }

    return ret;
}

int_64 DivCeil(int a, int b)
{
    int comp_a = a, comp_b = b;
    a = Abs(a);
    b = Abs(b);
    int ret = (a + (b - (a % b))) / b;

    if (comp_a < 0) {
        ret = ret * (-1);
    }


    if (comp_b < 0) {
        ret = ret * (-1);
    }

    return ret;
}

int_64 IntDiv(int a, int b)
{
    if (a % b < b / 2) {
        return DivFlor(a, b);
    }
    else {
        return DivCeil(a, b);
    }
}

int_64 Pow(int a, int b)
{
    if (b < 0) {
        return -1;
    }

    if (b == 0) {
        return 1;
    }

    int ans = a;

    for (int i = 1; i < b; i++)
    {
        ans = ans * a;
    }

    return ans;
}

int_64 Root(int a, int b)
{
    for (int i = 0; i < a; i++)
    {
        if (Pow(i, b) >= a) {
            return i;
        }
    }
}

int_64 Abs(int a)
{
    if (a > 0) {
        return a;
    }
    else {
        a = a * (-1);
        return a;
    }
}

int ProcessString(char* string)
{
    int link = 0;
    int link_end = 0;
    int prior = 0;
    int prior_mem = 0;

    int cou = 0;
    char buff[40];
    int buff_cou = 0;

    int err = 0;

    MinusCollapse(string);
    do
    {
        if (Find(string, '(', 0) == -1) {
            break;
        }

        cou = 0;
        prior_mem = 0;
        prior = 0;
        do
        {
            if (string[cou] == '(') {
                prior++;
                if (prior > prior_mem) {
                    link = cou + 1;
                    prior_mem = prior;
                    buff_cou = 0;
                }
                

            }
            else if (string[cou] == ')')
            {
                if (prior == prior_mem) {
                    link_end = cou;
                }
                prior--;
                buff[buff_cou] = '\0';
                buff_cou = -1;
            }
            else {
                if (buff_cou > -1) {
                    buff[buff_cou] = string[cou];
                    buff_cou++;
                }
            }
            cou++;
        } while (string[cou]!='\0');
        

        err=SimpleProcess(buff);

        if (err <-1) {
            return err;
        }

        
        cou = 0;
        link--;
        do
        {
            cou++;
        } while (buff[cou] != '\0');

        int size = cou;

        if (size > (link_end - link + 1)) {
            int shift = size - (link_end - link + 1);

            cou = link_end;

            do
            {
                cou++;
            } while (string[cou] != '\0');

            for (int i = cou; i > link_end; i--)
            {
                string[i + shift] = string[i];
            }

        }
        else if (size < (link_end - link + 1)) {
            int shift = (link_end - link + 1) - size;

            do
            {
                cou++;
            } while (string[cou] != '\0');

            for (int i = link_end; i < cou + 1; i++)
            {
                string[i - shift] = string[i];
            }

        }


        cou = 0;

        do
        {
            string[link + cou] = buff[cou];
            cou++;
        } while (buff[cou] != '\0');


    } while (1);

    err = SimpleProcess(string);

    if (err <0) {
        return err;
    }

    return 0;
}

int SimpleProcess(char* string)
{

    MinusCollapse(string);
    int err = 0;
    int ret = -1;
    do
    {
        ret = Find(string, '^', ret + 1);

        if (ret != -1) {
            err = ProcessExp(string, ret);
            if (err < 0) {
                return err;
            }
            MinusCollapse(string);
            ret = 0;
        }
    } while (ret != -1);

    ret = -1;
    do
    {
        ret = Find(string, 'R', ret + 1);

        if (ret != -1) {
            err = ProcessExp(string, ret);
            if (err < 0) {
                return err;
            }
            MinusCollapse(string);
            ret = 0;
        }
    } while (ret != -1);

    ret = -1;
    do
    {
        ret=Find(string, '*', ret + 1);

        if (ret != -1) {
            err = ProcessExp(string, ret);
            if (err < 0) {
                return err;
            }
            MinusCollapse(string);
            ret = 0;
        }
    } while (ret!=-1);

    ret = -1;
    do
    {
        ret = Find(string, '/', ret + 1);

        if (ret != -1) {
            err=ProcessExp(string, ret);
            if (err <0) {
                return err;
            }
            MinusCollapse(string);
            ret = 0;
        }
    } while (ret != -1);

    ret = 0;
    do
    {

        ret = Find(string, '-', ret + 1);

        if (ret != -1) {
            err = ProcessExp(string, ret);
            if (err < 0) {
                return err;
            }
            MinusCollapse(string);
            ret = 0;
        }
    } while (ret != -1);

    ret = -1;
    do
    {
        ret = Find(string, '+', ret + 1);

        if (ret != -1) {
            err = ProcessExp(string, ret);
            if (err < 0) {
                return err;
            }
            MinusCollapse(string);
            ret = 0;
        }
    } while (ret != -1);

    return 0;
}

int ProcessExp(char* string, int sign)
{
    int a = 0;
    int b = 0;

    int_64 ans=0;

    int start_a=0;
    int end_b = 0;
    int err = 0;
    char operate=string[sign];

    int cou = 0;

    err = TextToInt(string, &b, sign + 1);

    if (err == -1) {
        return -2;
    }
    
    
    cou = sign + 1;

    do
    {
        cou++;
    } while (string[cou] != '\0' && string[cou] > 47 && string[cou] < 58);

    end_b = cou-1;
    cou = sign-1;
    do
    {
        cou--;
    } while (string[cou] > 47 && string[cou] < 58 && cou > -1);

    start_a = cou + 1;

    err = TextToInt(string, &a, start_a);

    if (err == -1) {
        return -2;
    }
    

    if (a < 0) {
        start_a--;
    }

    switch (operate)
    {
        case '+':
            ans = a + b;
            break;
    
        case '-':
            ans = a - b;
            break;
    
        case '*':
            ans = a * b;
            break;

        case '/':
            if (b == 0) {
                return -1;
            }
            ans = IntDiv(a, b);
            break;

        case '^':
            ans = Pow(a, b);
            break;

        case 'R':
            ans = Root(a, b);
            break;
    default:
        break;
    }


    if (ans > 2147483647) {
        return -2;
    }

    if (ans < -2147483647) {
        return -2;
    }

    char buff[10];

    int size=IntToStr(ans, buff);
    
    if (size > (end_b - start_a + 1)) {
        int shift = size-(end_b - start_a + 1);
        
        cou = end_b;

        do
        {
            cou++;
        } while (string[cou]!='\0');

        for (int i = cou; i > end_b; i--)
        {
            string[i + shift] = string[i];
        }

    }
    else if (size < (end_b - start_a + 1)) {
        int shift = (end_b - start_a + 1)-size;

        do
        {
            cou++;
        } while (string[cou] != '\0');

        for (int i = end_b; i < cou+1; i++)
        {
            string[i - shift] = string[i];
        }

    }
    

    cou = 0;

    do
    {
        string[start_a + cou] = buff[cou];
        cou++;
    } while (buff[cou] != '\0');

    return 1;
   
}

int VerifyString(char* string)
{



    return 0;
}
