//MATRIX (MOVIE) CODE SIMULATOR
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <list>
/*
DEPENDENCIES: MINGW64 ON WINDOWS
make sure C:\MinGW\bin is on PATH
COMPILE & RUN:
open cmd
g++ -o mtx2 mtx2.cpp
cls
mtx2.exe
*/
using namespace std;

HANDLE hStdout;// = GetStdHandle(STD_OUTPUT_HANDLE); 
int mlen = 40;
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(hStdout, coord);
}
class cord{
	public:
	cord(int l, int x, int y){
		left=l;
		next.X=x;
		next.Y=y;
		//rate of blank columns
		sp=rand()%3;
	}
	bool step(int h){
		if (left<=0)
			return 0;
		left--;
		if(next.Y<h)
			next.Y++;
		else return 1;
		//SetConsoleCursorPosition(hStdout, next);
		gotoxy(next.X, next.Y);
		if(sp==0){
			//10 lime 15 white
			SetConsoleTextAttribute(hStdout, 10);
			printf("%c",32+rand()%94);
			gotoxy(next.X, next.Y-1);
			SetConsoleTextAttribute(hStdout, 2);
			printf("%c",32+rand()%94);
		}
		else printf(" ");
		//if(sp==0) Sleep(5);
		//Sleep(1);
		return 1;
	}
	int sp;
	int left;
	COORD next;
};
int main(){
	srand(0);
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo; 
	GetConsoleScreenBufferInfo(hStdout, &csbiInfo);
	int w = csbiInfo.srWindow.Right;
	int h = csbiInfo.srWindow.Bottom;
	if (mlen>h) mlen=h*2/3;
	
	list<cord> li;
	cord c(mlen/2,1,1);
	li.push_back(c);
	
	int sz;
	list<cord>::iterator it;
	while((sz=li.size())>0){	
		//step all in list, erase if no steps left
		it=li.begin();
		while(it!=li.end()){
			if(it->step(h)==0)
				li.erase(it++);
			else it++;
			//cin.get();
		}
		Sleep(20);
		 // add if list is small
		if(sz < 50+rand()%mlen){
			int y = rand()%h;
			cord cd(rand()%((mlen<h-y+1)?mlen:h-y+1)+1, rand()%w, y);
			li.push_back(cd);
		}
		
	}
}