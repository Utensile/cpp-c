//Numeri Simpatici
#include <iostream>
#include <cmath>
using namespace std;

int main(void)
{
	int a, b, c;
	cout << "inserire 3 numeri..." << endl;
	cin >> a >> b >> c;
	if(pow(a,2)==pow(b,2)+pow(c,2))
	{
		cout << "i numeri sono simpatici perche' " << pow(a,2) << " e' uguale a " << pow(b,2) << " + " << pow (c,2) << endl;
	}
	else
	{
			if(pow(b,2)==pow(a,2)+pow(c,2))
	{
		cout << "i numeri sono simpatici perche' " << pow(b,2) << " e' uguale a " << pow(a,2) << " + " << pow (c,2) << endl;
	}
	else
	{
			if(pow(c,2)==pow(a,2)+pow(b,2))
	{
		cout << "i numeri sono simpatici perche' " << pow(c,2) << " e' uguale a " << pow(a,2) << " + " << pow (b,2) << endl;
	}
	else 
	{
		cout << "i numeri non sono simpatici";
	}
	}
	
	}
	
	return 0;
}



