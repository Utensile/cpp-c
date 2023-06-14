#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

int main(){
	char mio[80];
	char voc[5]={'a','e','i','o','u'};
	int conta[5];
	int max=0;
	int min=6;
	
	for(int i=0; i<=4; i++){
	conta[i]=0;}
	
	gets(mio);
	
	for(int i=0; i<strlen(mio); i++){
		if(mio[i]=='a')
		conta[0]++;
		
		if(mio[i]=='e')
		conta[1]++;
		
		if(mio[i]=='i')
		conta[2]++;
		
		if(mio[i]=='o')
		conta[3]++;
		
		if(mio[i]=='u')
		conta[4]++;
	}
	
	for(int i=0; i<=4; i++){
		cout<<voc[i]<<" "<<conta[i]<<" - ";
	}
	cout<<endl;
	
	for(int i=0; i<=4; i++){
		if(conta[i]>=conta[max] && conta[i]!=0)
		max=i;
		
		if(conta[i]<=conta[min] && conta[i]!=0)
		min=i;
	}
	
	cout<<"la piu' frequente e' "<<voc[max]<<endl;
	cout<<"la meno frequente e' "<<voc[min]<<endl;
	return 0;
}
