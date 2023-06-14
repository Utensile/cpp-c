//Briscola
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <windows.h>
using namespace std;

bool game = false;
int player;
int carte[40];
int mano[5][3];

void setcolor(unsigned short color)
{
         HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
         SetConsoleTextAttribute(hcon,color);
}
//Modulo posizione scritte
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoXY(int, int);
void gotoXY(int x, int y) 
{ 
CursorPosition.X = x; 
CursorPosition.Y = y; 
SetConsoleCursorPosition(console,CursorPosition); 
}

void imposta(int mod){
	for(int i = 0; i<40; i++)
		carte[i]=0;
	if(mod == 's')
		player = 2;
	else if(mod == 'd')
		player = 4;
	else if (mod == 'f')
		player = 5;
	for(int i=0; i<player; i++)
		for(int j=0; j<3; j++){
			do{
			mano[i][j] = rand()%40;	
			}while(carte[mano[i][j]]==1);
			carte[mano[i][j]]=1;
		}
}
void input(){
	
}
void logic(){
	
}
void display(){
	for(int i=0; i<player; i++){
		cout << endl;
		for(int j=0; j<3; j++){
			cout << mano[i][j] << "  ";
		}
	}
	game = false;
}

int main(){
	srand(time(NULL));
	char mod;
	cout << "Seleziona Modalita':";
	cin >> mod;
	imposta(mod);
	game = true;
	for(int i=0; i<player; i++){
		cout << endl;
		for(int j=0; j<3; j++){
			cout << mano[i][j] << "  ";
		}
	}
	while(game){
		input;
		logic;
		display;
		}
}

