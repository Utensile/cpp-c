//27.01.2022
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

int main(){
	FILE *input, *output;
	int c, count;
	char name[50];
	cout << "inserire nome file input: ";
	scanf("%s", name);
	input = fopen(name, "r");
	if(input == NULL){
		cout << "File input inesistente";
		return 0;
	}
	output = fopen("output.txt", "w");
	c = fgetc(input);
	while(c != EOF){
		if(c=='/n'){
			fputs(" [", output);
			fputc(count, output);
			fputs("]/n", output);
			count = 0;
		}
		else{
			count++;
			fputc(c, output);
		}
		c = fgetc(input);
	}
	
	
}
