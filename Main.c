#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int tmp;

//짧은글 연습
void s_sentence()
{

}

//긴글 연습
void l_sentence()
{

}

//낱말 연습
void word()
{

}

//자리
void place()
{

}

int main()
{
	int menu;
	printf("                       영어 타자 연습              \n");
	printf("	1. 자리수 연습                    2. 낱말 연습\n");
	printf("	3. 짧은글 연습       			 4. 긴글 연습\n");
	
	scanf("%d", &menu);
	switch(menu)
	{
		case 1:
			system("clear");
			place();
		case 2:
			system("clear");
			word();
		case 3:
			system("clear");
			s_sentence();
		case 4:
			system("clear");
			l_sentence();
	}
	return 0;
}
