#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>

using namespace std;

int main()
{
	char par1[31];
	char par2[31];
	cout << "inserisci prima parola: " << endl;
	gets(par1);
	cout << "inserisci seconda parola: " << endl;
	gets(par2);
	
	for (int i=0; i <strlen(par1); i++) {
		if (par1[i]== par2[0]) {
			bool trovata = true;
			int cnt = i;
			for (int j=0; j < strlen(par2); j++) {
				if (par1[cnt] != par2[j]) {
					trovata = false;
				}
				cnt++;
			}
			if (trovata) {
				for (int j=0; j < strlen(par2); j++) {
					par1[i] = '*';
					i++;
				}
				i--;
			}
		}
	}
	puts(par1);
	return 0;
}
