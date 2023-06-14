//27.09.2021
#include<iostream>
#include<cmath>
using namespace std;

int input(){
	int n;
	do{
	cin >>n;
	if(n<0)
	cout << "valore negativo invalido..." << endl;
	else
	return n;
	}while(n<0);
}

void Prog1(){
	int n, np, N;
	n=1;
	np=0;
	N=0;
	do{
	 np=n;
	 n=input();
	 if(n==np)
	 N++;
	}while(n!=0);
	cout << "Programma terminato, ci sono " << N << " coppie uguali" << endl;
}
void Prog2(){
	int n, np, N;
	do{
	 np=n;
	 n=input();
	 if(n%np==0)
	 N++;
	}while(n!=0);
	cout << "Programma terminato, ci sono " << N << " coppie in cui il secondo numero e' divisibile per il primo'" << endl;
}

int main(void){
	int P;
	cout << "Programma di calcolo coppie avviato, inseire tipologia del processo..." << endl << "1 = calcolo del numero di coppie di numeri consecutivi uguali" << endl << "2 = calcolo del numero di coppie in cui il secondo numero è divisore del primo (non uguali)" << endl;
	cin >> P;
	while(P!=1 && P!=2){
	if(P==1)
	 Prog1();
	if(P==2)
	 Prog2();
	if(P!=1 && P!=2)
	 cout << "Valore invalido... Re-inserire" << endl;
	 cin >> P;
}
}
