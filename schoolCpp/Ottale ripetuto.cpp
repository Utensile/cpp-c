//Ottale ripetuto
#include <iostream>
#include <cmath>
using namespace std;

int main(void){
	int n, c, ott, i;
	char r='s';
	cout << "inserire il numero da convertire..." << endl;
	cin >> n;
    while(r='s'){
	i=0;
	while(n>1){
		ott+=(n%8)*pow(10,i);
		i++;
		n=floor(n/8);
	}
	cout << "il numero in ottale e' " << ott << endl << "Voui continuare?(s=si, n=no)" << endl;
	cin >> r;
	if(r='s'){
		cout << "inserire il numero da convertire..." << endl;
	    cin >> n;
	}
}
	return 0;
}
