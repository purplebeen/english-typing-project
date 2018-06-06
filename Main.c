#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <termios.h>
#include<unistd.h>

void print_menu();

static struct termios old, new;
void initTermios(int echo)
{
  tcgetattr(0, &old); new = old;
  new.c_lflag &= ~ICANON;
  if (echo) {
      new.c_lflag |= ECHO;
  } else {
      new.c_lflag &= ~ECHO;
  }
  tcsetattr(0, TCSANOW, &new);
}

void resetTermios(void)
{
  tcsetattr(0, TCSANOW, &old);
}

char getch_(int echo){
  char ch;  initTermios(echo);
  ch = getchar();resetTermios();
  return ch;
}

char getche(void){
  return getch_(1);
}//위의 것들은 getche를 linux환경에서 헤더없이 구현하기위해 삽입.
int tmp;

double besttype = 0;

void Update(char tmp[], char typing_storge[], int s_prosess, double s_livetype, double besttype, int s_acc, int index, bool is_long) 
{
	system("clear");
	printf("짧은 글 연습\n");
	printf("\n");
	printf("진행도: %d 현재타수: %0.f 최고타수: %0.f 정확도: %d \n\n", s_prosess, s_livetype, besttype, s_acc);
	printf("%s\n", tmp);
	if(is_long) {
		printf("\n");
	}
	for(int i = 0; i < index; i++) 
		printf("%c", typing_storge[i]);
	// printf("%s", typing_storge);
}

void Render(char tmp[], char title[], int s_prosess, double s_livetype, double besttype, int s_acc)
{
	system("clear");
	printf("%s\n", title);
	printf("\n");
	printf("진행도: %d 현재타수: %0.f 최고타수: %0.f 정확도: %d \n\n", s_prosess, s_livetype, besttype, s_acc);
	printf("%s\n", tmp);
}

void placeword(char tmp[], char title[], int s_process, int s_wrong, float s_acc)
{
	int typer;
	system("clear");
	printf("%s\n", title);
	printf("\n");
	printf("진행도 : %d%%	오타수: %d	정확도 : %.2f%%\n\n", s_process,s_wrong, s_acc);
	printf("%s\n", tmp);
}

double Livetype(int correct, time_t startTime, time_t endTime)
{
	double type =  ((correct * 60) / ((double)(endTime - startTime) /1000)); //시간에서 입력한 타자수를 곱함
	if(type > besttype)
	{
		besttype = type;
	}
	return type;
}

//짧은글 연습g
void s_sentence()
{
	char tmp[40][200] = {
		"Poetry is the mother tongue of mankind", 
		"Where there is a will there is a way.",
		"Think of the end before you begin.", 
		"Carpe Diem!",
		"boys, be ambitious!", 
		"Raise your head!",
		"Try hard, Try hard!", 
		"Ability is decided by one's own effort.",
		"Faithfulness makes all things possible.", 
		"Do to others as you would be done by.",
		"Faith without deeds is useless.", 
		"The life is only once.",
		"Think different!", 
		"The regret after not doing something is bigger than that of doing something.",
		"Try your best rather than be the best.", 
		"I determine my future all by myself.",
		"All I need to do is move forward!", 
		"I must do what I want to do.",
		"Have fun this time, because it will never come again.", 
		"My dream don't have forgotten the promise I had until now!!",
		"Time is life itself.", 
		"If  you don't walk today, you will have to run tomorrow.",
		"Why do you make efforts commonly, don't want to live commonly!", 
		"Today, which was proved to be fruitless, is the day that the dead in the past was longing for.",
		"Never put off for tommorrow what you can do today!", 
		"The real effort never betrays me.",
		"There is no Destiny.", 
		"Effort is the best way to realizing your dreams.",
		"No pain, no gain.", 
		"Opportunity seldom knocks twice.",
		"Make hay while the sun shines."
	};

	char typer, typing_storge[200];
	int s_prosess = 0, s_acc = 0; // 진행도, 타수, 최고타수, 정확도
	int index = 0;
	int correct = 0, temp; //맞은개수
	double s_livetype = 0;

	srand(time(NULL));
	int random_choice = rand() % 30;
	Render(tmp[random_choice], "짧은 글 연습", s_prosess, s_livetype, besttype, s_acc);

	time_t startTime = 0, endTime = 0;
	startTime = clock();

	while (s_prosess != 100)
	{
		typer = getche();
		if(typer == '\n')
		{
			random_choice = rand() % 30;
			index = 0;
			correct = 0;
			s_acc = 0;
			s_prosess += 20;
			Update(tmp[random_choice], typing_storge, s_prosess, s_livetype, besttype, s_acc, index, false);
		}
		else if(typer == 127 || typer == 8) {
			if(index > 0) {
				if(tmp[random_choice][index -1] == typing_storge[index -1]) {
					correct--;
				}
				index--;
				if(index == 0) {
					correct = 0;
					s_acc = 0;
				} else {
					s_acc = ((float) correct / index) * 100;
				}
				Update(tmp[random_choice], typing_storge, s_prosess, s_livetype, besttype, s_acc, index, false);
			} else {
				index = 0;
				s_acc = 0;
				correct = 0;
				Render(tmp[random_choice], "짧은 글 연습", s_prosess, s_livetype, besttype, s_acc);
				continue;
			}
		} else {
			typing_storge[index] = typer;
			if(typing_storge[index] == tmp[random_choice][index]) {
				correct++;
			}
			index++;
			endTime = clock();
			s_livetype = Livetype(correct, startTime, endTime);
			s_acc = ((float) correct / index) * 100;
			Update(tmp[random_choice], typing_storge, s_prosess, s_livetype, besttype, s_acc, index, false);
		}
	}
	print_menu();
}

//긴글 연습
void l_sentence()
{
	char tmp [5][2][400] = {
		{
			"When Phil Spencer went skiing three years ago, he had no idea how much his life would change as a result.\n"
			"I was a terrible skier.\n"
			"I could hardly stand up!\n"
			"says pill, now on 25.\n"
			"On Phil's first trip down the mountain he fell and crashed into a group of people standing nearby.",

			"He didn't know then, but they were snowborders.\n"
			"I heared someone shouting at me\n"
			"I looked up and there was Mika\n"
			"I've never forgotten the time I first saw him\n"
			"I was so angry. adds Mika\n"
			"But when I helped him up, he gave me a beautiful smile."
		},
		{
			"It all just disappears, doesn't it?\n"
			"Everything you are, gone in moment.\n"
			"Like breath on a mirror. Any moment now, he's coming.\n"
			"Who's coming?\n"
			"The Doctor.\n",

			"You... you are the Doctor.\n"
			"Yep. And I always will be.\n"
			"But times change, and so must I.\n"
			"Who's Amelia?\n"
			"The first face this face saw.\n"
		},
		{
			"We all change, when you think about it.\n"
			"We're all different people all through our lives.\n"
			"And that's okay, that's good.\n" 
			"You've got to keep moving.\n"
			"As long as you remember all the people that you used to be.\n",

			"I will not forget one line of this, not one day.\n"
			"I swear.\n"
			"I will always remember when the Doctor was me.\n"
			"Raggedy man. Good night.\n"
			"No no! Please don't change.\n"
		}, 
		{
			"Oh, there it is.\n"
			"The silly old universe.\n"
			"The more I save it, the more it needs saving.\n"
			"It's a treadmill.\n"
			"Yes, yes, I know. They'll get it all wrong without me.\n",

			"I suppose one more lifetime wouldn't kill anyone.\n"
			"Well, except me.\n"
			" You wait a moment, Doctor. Let's get it right.\n"
			"I've got a few things to say to you.\n"
			"Basic stuff first.\n" 
		},
		{
			"Never be cruel, never be cowardly, and never, ever eat pears!\n"
			"Remember, hate is always foolish. and love is always wise.\n"
			"Always try to be nice, but never fail to be kind.\n"
			"Oh, and you mustn't tell anyone your name.\n" 
			"No one would understand it, anyway.\n",

			"Except, ah! (collapses) Except children. Children can hear it sometimes.\n" 
			"If their hearts are in the right place, and the stars are too, children can hear your name.\n"
			"Argh! But nobody else. Nobody else, ever.\n"
			"Laugh hard. Run fast. Be kind.\n"
			"Doctor, I let you go.\n"

		}
	};
	int enter_count = 0;
	int s_process = 0, correct = 0, s_acc = 0;
	int index = 0;
	int page = 0;
	srand(time(NULL));
	int random_choice = rand() % 5;
	Render(tmp[random_choice][page], "긴글연습",s_process, 0, 0, 0);

	printf("\n");
	char typing_storage[400];

	while(s_process != 100) {
		char typer = getche();
		if(typer == 127 || typer == 8) {
			if(index > 0) {
				if(tmp[random_choice][page][index -1] == typing_storage[index -1]) {
					correct--;
				}
				if(typing_storage[index -1] == '\n') {
					enter_count--;
				}
				printf("enter_count: %d\n", enter_count);
				index--;
				if(index == 0) {
					correct = 0;
					s_acc = 0;
				} else {
					s_acc = ((float) correct / index) * 100;
				}
				Update(tmp[random_choice][page], typing_storage, s_process, 0, 0, s_acc, index, true);
			} else {
				index = 0;
				s_acc = 0;
				correct = 0;
				Render(tmp[random_choice][page], "긴글 연습", s_process, 0, 0, s_acc);
				continue;
			}
		} else  if(typer == '\n') {
			typing_storage[index] = typer;
			enter_count++;
			if(enter_count >= 5) {
				enter_count = 0;
				index = 0;
				s_acc = 0;
				correct = 0;
				if(page == 0) {
					page++;
				} else {
					random_choice = rand() % 5;
					page = 0;
				}
				Render(tmp[random_choice][page], "긴글 연습", s_process, 0, 0, s_acc);
			} else {
				if(typing_storage[index] == tmp[random_choice][page][index]) {
					correct++;
				}
				index++;
				s_acc = ((float)correct / index) * 100;
				Update(tmp[random_choice][page], typing_storage, s_process, 0, 0, s_acc, index, true);
			}
		} else {
			typing_storage[index] = typer;
			if(typing_storage[index] == tmp[random_choice][page][index]) {
				correct++;
			}
			index++;
			s_acc = ((float)correct / index) * 100;
			Update(tmp[random_choice][page], typing_storage, s_process, 0, 0, s_acc, index, true);
		}
	}

}

//낱말 연습
void word()
{
	srand(time(NULL));
	char tmp[100][100]={
		"about","all","also","and" "as","at","be","because","but","by",
		"can","come","could","day","do","even","find","first","for","from",
		"get","give","go","have","he","her","here","him","his","how",
		"I","if","in","into","it","its","just","know","like","look",
		"make","man","many","me","more","my","new","no","not","now",
		"of","on","one","only","or","other","our","out","people","say",
		"see","she","so","some","take","tell","than","that","the","their",
		"them","then","there","these","they","thing","think","this","those","time",
		"to","two","up","use","very","want","way","we","well","what",
		"when","which","who","will","with","would","year","you","your","zebra"};

	int s_process=0, s_wrong=0, cnt =1;
	float s_acc=100;
	int x; 
	char typer[]={0};

	printf("\n\n");

	while(cnt!=20){
		x = rand()%100;
		placeword(tmp[x], "단어 연습",s_process,s_wrong,s_acc);
		scanf("%s", typer);

		if(strcmp(tmp[x],typer) == 0){
			s_process+=5;
			continue;
		} else {
			s_process+=5;
			s_wrong++;
		}
		cnt++;
		s_acc=100-(float)s_wrong/20*100;
	}
	system("clear");
	placeword(tmp[x], "단어 연습",s_process,s_wrong,s_acc);
}




//자수 연습
void place()
{  
	float exact =0;
	int error=-1, process=0;
	int count=0;
	int totalchallenge=0;
	char putalphabet;
	
	while(count<=20)
	{
		system("clear");
	  	printf ("자리연습 \n");
	  	printf("진행도:%d%%  오타수:%d  정확도:%.1f%% ",process,error,exact);
	  	printf("\n\n");

		char alphabet[53];
		for(int i=0; i<26;i++)
		{
			alphabet[i]=65+i;
		}
		for(int j=0; j<26;j++)
		{
			alphabet[26+j]=97+j;
		}

		char put;
		srand(time(NULL));
		totalchallenge++;
		putalphabet=alphabet[rand()%52];

		printf("%c",putalphabet);
		printf("\n");

  		put=getche();
		if(put==putalphabet) {
			count++;
   			process+=5;
     		exact=(float)count/totalchallenge*100;
		} else {
      		while(put!=putalphabet)
			{
				error++;
				totalchallenge++;
				exact=(float)count/totalchallenge*100;
				system("clear");
				printf ("자리연습 \n");
				printf("진행도:%d%%  오타수:%d  정확도:%.1f%% ",process,error,exact);
				printf("\n\n");
				printf("%c\n",putalphabet);
				put=getche();
			}
			count++;
		}
		exact=(float)count/totalchallenge*100;
 	}
	 print_menu();
}

void print_menu()
{
	int menu;
	system("clear");
	printf("	   ;>>영어 타자 연습<<		\n");
	printf("1. 자리수 연습		2. 낱말 연습\n");
	printf("3. 짧은글 연습		4. 긴글 연습\n");
	
	scanf("%d", &menu);
	getchar();
	switch(menu)
	{
		case 1:
			system("clear");
			place();
			break;
		case 2:
			system("clear");
			word();
			break;
		case 3:
			system("clear");
			s_sentence();
			break;
		case 4:
			system("clear");
			l_sentence();
			break;
	}
}

int main()
{
	print_menu();
	return 0;
}
