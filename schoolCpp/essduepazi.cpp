#include <iostream>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
using namespace std;

int main (){
	char stringa[80];
	cout<<"inserisci una frase"<<endl;
	gets(stringa);
	for (int i = 0; i<strlen(stringa); i++){
		if (stringa[i] == ' '&&stringa[i+1]== ' '){
			for (int j = i + 1; j<strlen(stringa); j++){
				stringa [j] = stringa [j+1];
			}
		}
	}
	cout<<stringa<<endl;
	return 0;
}
