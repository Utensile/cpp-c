//Ottale2
#include <iostream>
#include <cmath>
using namespace std;

int ottale(int n){
		int ott, i;
	i=0;
	while(n>=1){
		ott+=(n%8)*pow(10,i);
		i++;
		n=floor(n/8);
	}
	
	return ott;
}

int main(void){
	char r;
	r='s';
	int n;
	while(r!='n'){
		cout << "Inserire il valore da convertire in ottale..." << endl;
		cin >> n;
		n=ottale(n);
		cout << "Convertito in ottale  e' " << n << endl << endl;
		cout << "vuoi continuare? (s=si, n =no)" << endl;
		cin >> r;
	}
	return 0;
}
	
