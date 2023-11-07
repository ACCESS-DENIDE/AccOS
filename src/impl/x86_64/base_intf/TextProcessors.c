#include "TextProcessors.h"

void AlignText(char* text)
{
	int cou = 0;

	do
	{
		if (text[cou] > 64 && text[cou] < 91) {
			text[cou] = text[cou] + 32;
		}
		cou++;
	} while (text[cou]!='\0');
	return;
}

int TextToInt(const char* text, int* outp, int from)
{
	if (text[from] == '-') {
		from++;
	}

	int cou = from;
	int_64 ret = 0;
	do
	{	
		ret = ret * 10;
		ret += text[cou] - 48;

		if (ret > 2147483647) {
			return -1;
		}

		if (ret < -2147483647) {
			return -1;
		}

		cou++;

	} while (text[cou] != '\0' && text[cou]>47 && text[cou]<58);

	if (from > 0) {
		if (text[from-1]=='-') {

			if (from > 1) {
				if (text[from - 2] == '*' || text[from - 2] == '/' || text[from - 2] == '^' || text[from - 2] == 'R') {
					ret = ret * -1;
				}
			}
			else {
				ret = ret * -1;
			}
			
		}
	}

	(*outp) = ret;

	return 0;
}

int Split(const char* text,char* outp, char spliter, int from)
{

	int cou = from;
	do
	{
		outp[cou-from] = text[cou];
		cou++;
	} while (text[cou]!='\0' && text[cou] != spliter);
	outp[cou-from] = '\0';
	return cou;
}

void SplitIterration(const char* text, char* outp, char spliter, int iter)
{
	int last = 0;
	for (int i = 0; i < iter+1; i++)
	{
		last= Split(text, outp, spliter, last);
		last++;

	}
}

int CompareStrings(const char* a, const char* b)
{
	int cou = 0;
	do
	{
		if (a[cou] != b[cou]) {
			return 0;
		}

		cou++;
	} while (a[cou]!='\0' && b[cou] != '\0');

	if (a[cou] != b[cou]) {
		return 0;
	}

	return 1;
}

int IntToStr(int inp, char* str)
{
	int flag = 0;
	if (inp < 0) {
		inp = inp * (-1);
		flag = 1;
	}
	
	str[19] = '\0';
	int next = inp;
	int cou = 1;
	do
	{
		str[19 - cou] = (next % 10) + 48;
		next = (next - (next % 10)) / 10;
		cou++;
	} while (next > 9);
	if (next != 0) {
		str[19 - cou] = next + 48;
	}
	else {
		cou--;
	}
	

	if (flag) {
		for (int i = 1; i <= cou+1; i++)
		{
			str[i] = str[19 - cou + i-1];
		}
		str[0] = '-';
		return cou + 1;
	}
	else {
		for (int i = 0; i <= cou; i++)
		{
			str[i] = str[19 - cou + i];
		}
		return cou;
	}

	return -1;
	
}

int Find(const char* str, char ch, int from)
{
	int cou = from;

	if (str[cou] == '\0') {
		return -1;
	}

	do
	{
		if (str[cou] == ch) {
			return cou;
		}
		cou++;
	} while (str[cou]!='\0');

	return -1;
}

void MinusCollapse(char* str)
{

	int cou = 1;

	int inter_cou = 0;
	do
	{

		if (str[cou] == '-') {
			switch (str[cou-1])
			{
			case '+':
				str[cou - 1] = '-';
				inter_cou = cou;
				do
				{
					str[inter_cou] = str[inter_cou + 1];
					inter_cou++;
				} while (str[inter_cou] != '\0');
				break;

			case '-':
				str[cou - 1] = '+';
				inter_cou = cou;
				do
				{
					str[inter_cou] = str[inter_cou + 1];
					inter_cou++;
				} while (str[inter_cou] != '\0');
				break;

			default:
				cou++;
				break;
			}
		}
		else {
			cou++;
		}
		

	} while (str[cou]!='\0');

}
