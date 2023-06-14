//Equazione di primo grado
#include <iostream>
#include <cmath>
using namespace std;

int main(void)
{
	int a, b;
	double x;
	cout << "inserire il coefficente di x (a)" << endl;
	cin >> a;
	cout << "Inserire il termine noto (q)" << endl;
	cin >> b;
	if(a==0 && b==0){
		cout << "l'equazione e' indeterminata " << endl;
	}
		else if(a==0){
			cout << "l'equazione e' impossibile " << endl;
		}
		else{
			cout << "l'equazione e' determinata e x = ";
			x=-b/a;
			cout << x;
		}
    return 0;
}
	
	
