//MANDELBROT FRACTAL GENERATOR
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <windows.h>
/*
DEPENDENCIES: MINGW64 ON WINDOWS
make sure C:\...\MinGW\bin is on PATH
COMPILE & RUN:
Open cmd
Maximize cmd window
g++ -o mandel mandelbrot.cpp
cls
mandel.exe [board-size] [figure-size] [calculation-limit]
*/
using namespace std;
int LIM;
//recursive function
vector<double> recurse(vector<double> z, vector<double> c, int i){
	vector<double> v2(2);
	v2[0] = z[0]*z[0] - z[1]*z[1];
	v2[1] = 2*z[0]*z[1];
	v2[0] += c[0];
	v2[1] += c[1];
	if(i<LIM)
		return recurse(v2, c, i+1);
	else
		return v2;	
}

int main(int argc, char **argv){
	if(argc<4) {
		cout<<"Usage: mandel.exe [board-size] [figure-size] [calulation-limit]\n";
		cout<<"Suggested: mandel.exe 50 16 100\n";
		return 1;
	}
	
	//cmd arguments: size divisor limit
	int N = atoi(argv[1]);
	double D = atoi(argv[2]);
	LIM = atoi(argv[3]);
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
	SetConsoleTextAttribute(hStdout, 0);
	
	vector<double> z(2,0), v(2), c(2);
	bool color=0, res=0;
	for(int i=-N/2; i<N/2; i++){
		c[0]=i/D;
		for(int j=-N/2; j<N/2; j++){
			c[1]=j/D;
			v = recurse(z, c, 0);
			res = ((v[0]*v[0] + v[1]*v[1])<100);
			
			if(color!=res) SetConsoleTextAttribute(hStdout, 10-10*(color));
			cout<<res<<" ";
			color=res;
			
		}
		cout<<endl;
	}
	SetConsoleTextAttribute(hStdout,7);
}