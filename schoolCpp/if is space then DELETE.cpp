#include <iostream>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
using namespace std;

int main(){
	char frase[81];
	char frasews[81];
	
	gets(frase);
	
	for(int i=0; i<strlen(frase); i++){
		if(frase[i]!=' '){
		    frasews[i]=frase[i];
		    cout<<frasews[i];
		}
	}
	return 0;
}
