//CONWAY'S GAME OF LIFE - WINDOWS
//This code was written as a 1st year undergrad..

//compile: g++ -o life life.cpp
//CMD ARGUMENTS: life.exe [frame length(ms)] [random seed]
//	    or   life.exe [frame length(ms)] -f [filename]
//	    or   life.exe [frame length(ms)] [     "     ] [pause after x frames]
/*
Before starting, set console to 196x68, font size 10
Right-click top of cmd window > Properties > Layout > Window Size
				       ... > Font > Size
Press ^C to exit a run.
*/
const int KDIMEN=66; //66 or 24   //height
const int IDIMEN=196; //40 or 80 or 196	  //width
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

//counts the live neighbors
int countAlive(int i, int k, const bool (&data)[KDIMEN][IDIMEN]);
//returns a bool for whether the cell lives or not
bool liveOrDie(int count, bool alive);
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
/*bool fileEdit();*/

int main(int argc, char** argv)
{
	bool data[KDIMEN][IDIMEN];
	bool newdata[KDIMEN][IDIMEN];
	int count=0, start=1, pauseinterval=0, ticks=0;
	bool alive;
	char inp, edit;
	unsigned int millis = 16;
	string name, out="";

	/*
	cout<<"Use file editor? ";
	edit=cin.get();
	if(edit=='y') {
		fileEdit()
		
		cin.get();
		cout<<"Continue? ";
		edit=cin.get();
		if(edit=='n')
			return 0;
	}
	//cout<<"Long Pause interval? ";
	//cin>>pauseinterval;
	*/
	
	//CMD ARGUMENTS
	if(argc >=2){
		millis = stoi(argv[1]);
		if(argc >=3){
			if(string(argv[2]) == "-f"){
				name = argv[3];
				start = 2012;
				if(argc >=5)
					pauseinterval = stoi(argv[4]);
			}else{
				start = stoi(argv[2]);
				if(argc >=4)
					pauseinterval = stoi(argv[3]);
			}
		}
	}
	srand(start);
	
	switch(start) {
	case 2012: {
		//cout<<"Filename? ";
		//cin>>name;
		ifstream fin;
		fin.open(name.c_str());
		if(fin.fail()) {
			cout<<"File opening failed";
			return -1;
		}
		//populate the array according to what is in the file
		for(int k=0; k<KDIMEN; k++) {
			for(int i=0; i<IDIMEN; i++) {
				inp=fin.get();
				if(inp==' '||inp=='\n')
					i--;
				if(inp=='0'||inp=='/')
					data[k][i]=0;
				if(inp=='X'||inp=='O'||inp=='1')
					data[k][i]=1;
			}
			//if(inp!=' '&&inp!='\n'&&inp!='/')
			//getline(fin,trash);
		}
	}
	break;

	default:
		//randomly set the starting data
		for(int k=0; k<KDIMEN; k++) {
			for(int i=0; i<IDIMEN; i++) {
				data[k][i]=rand()%2;
			}
		}
	}//end switch statement
	
	
	//**main activity loop**
	while(1) {
		//output cells to console
		out.clear();
		for(int k=0; k<KDIMEN; k++) {
			for(int i=0; i<IDIMEN; i++) {
				if(data[k][i])
					out+='X'; //cout<<'X';
				else
					out+=' '; //cout<<' ';
			}
			if(IDIMEN<80)
				out+='\n'; //cout<<endl;
		}
		cout<<out;
		gotoxy(0,1 + (start==1));

		//determine the state of each cell in next generation
		for(int k=0; k<KDIMEN; k++) {
			for(int i=0; i<IDIMEN; i++) {
				alive=data[k][i];
				count=countAlive(i,k,data);
				newdata[k][i]=liveOrDie(count, alive);
			}

		}
		//store "newdata" to "data"
		for(int k=0; k<KDIMEN; k++) {
			for(int i=0; i<IDIMEN; i++) {
				data[k][i]=newdata[k][i];
			}
		}

		Sleep(millis);
		ticks++;
		//When ticks is divisible by pauseinterval:
		//stop for 2.5 sec
		if(pauseinterval>0) {
			if(ticks/pauseinterval==1.*ticks/pauseinterval)
				Sleep(2500);
		}

		//for(int i=0; i<IDIMEN; i++) cout<<'-';
	}
	return 0;
}//end of main

int countAlive(int i, int k, const bool (&data)[KDIMEN][IDIMEN])
{
//different sets of cells must be counted
//if the coordinate is on a corner or edge
	int count;

	if(i==0) {
		if(k==0) {
			count=data[k][i+1]+data[k+1][i]+data[k+1][i+1];
		}
		if(k==KDIMEN-1) {
			count=data[k][i+1]+data[k-1][i]+data[k-1][i+1];
		} else if(k!=0) {
			count=data[k+1][i]+data[k+1][i+1]+data[k][i+1]+data[k-1][i]+data[k-1][i+1];
		}

	}

	if(i==IDIMEN-1) {
		if(k==0) {
			count=data[k][i-1]+data[k+1][i-1]+data[k+1][i];
		}
		if(k==KDIMEN-1) {
			count=data[k-1][i-1]+data[k-1][i]+data[k][i-1];
		} else if(k!=0) {
			count=data[k+1][i-1]+data[k+1][i]+data[k][i-1]+data[k-1][i-1]+data[k-1][i];
		}

	}

	if(i!=0 && i!=IDIMEN-1 &&(k==0||k==KDIMEN-1)) {
		if(k==0) {
			count=data[k][i-1]+data[k][i+1]+data[k+1][i-1]+data[k+1][i]+data[k+1][i+1];
		}
		if(k==KDIMEN-1) {
			count=data[k-1][i-1]+data[k-1][i]+data[k-1][i+1]+data[k][i-1]+data[k][i+1];
		}
	}

	if(i!=0 && i!=IDIMEN-1 && k!=0 && k!=KDIMEN-1) {
		//main case for if not on corner or edge
		count=data[k-1][i-1]+data[k-1][i]+data[k-1][i+1]+data[k][i-1]+data[k][i+1]+data[k+1][i-1]+data[k+1][i]+data[k+1][i+1];

	}

	return count;
}

bool liveOrDie(int count, bool alive)
{
//RULES FOR "GAME OF LIFE"
	if(alive) {
		if(count<2 || count>3) {
			return 0;
		} else {
			return 1;
		}
	}
	if(!alive && count==3) {
		return 1;
	} else {
		return 0;
	}


}

/*
bool fileEdit()
{
	int width, blines, lines, widthc=0, linesc=0, i, j, sections, length;
	bool type, deflt;
	string name;
	ofstream fout;
	cout<<"Filename to edit? ";
	cin>>name;
	fout.open(name.c_str());
	if (fout.fail())
		return 1;

	cout<<"Enter 1 to use default size: ";
	cin>>deflt;
	if(deflt) {
		width=IDIMEN;
		lines=KDIMEN;
	} else {
		cout<<"Number of columns: ";
		cin>>width;
		cout<<"Number of lines: ";
		cin>>lines;
	}
	cout<<"Initial blank lines: ";
	cin>>blines;
	for(j=0; j<blines; j++) {
		for(i=0; i<width-1; i++) {
			fout<<'0';
		}
		fout<<'/'<<endl;
	}//initial blank lines
	linesc+=blines;

	while(linesc<lines) {
		linesc++;
		widthc=0;
		cout<<"** Line "<<linesc<<" **\n";
		cout<<"Num of sections(-1 to end): ";
		cin>>sections;
		if(sections==-1) {
			for(i=linesc; i<=lines; i++) {
				for(j=0; j<width; j++) {
					fout<<'0';
				}
				fout<<endl;
			}
			return 0;
		}
		for(i=0; i<sections; i++) { //loop for each line
			if(i==0) {
				cout<<"Line starting bit: ";
				cin>>type;
			}
			cout<<"Length of "<<type<<" section(-1 to endline): ";
			cin>>length;
			//cout<<"Type of section: ";
			//cin>>type;
			if(length==-1)
				i=sections;
			for(j=0; j<length; j++) {
				fout<<type;
				widthc++;
			}
			type=!type;
		}
		for(j=widthc; j<width; j++)//fill in unfinished line with 0's
			fout<<'0';
		fout<<endl;
	}

	return 0;
}//end of fileEdit function
*/
