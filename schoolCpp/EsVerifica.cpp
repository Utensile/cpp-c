#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

using namespace std;

int main ()
{

    char par1[31]; 
    char par2[31]; 
    printf("Inserisci prima parola: "); 
    gets(par1); 
    printf("Inserisci seconda parola: "); 
    gets(par2); 
    //TO DO
    bool find=false;
	for(int i=0; i<=strlen(par1)-strlen(par2); i++){ 	//scorro la stringa par1 fino a quando par 2 può esserne contenuta
		if(par1[i]==par2[0]){ 							//se trovo la prima lettera
			find=true; 									//attivo la ricerca
			for(int j=0; j<strlen(par2) and find;j++) 	//controllo se tutte le lettere successive appartengono alla par 2
				if(par1[i+j]!=par2[j])	
					find=false; 						//se non le appartengono fermo la ricerca
			if(find) 									//se trovo la parola intera
				for(int j=0; j<strlen(par2) and find;j++)//rimpiazzo ogni posizione di par1 con par 2 con "*"
					par1[i+j]='*';
			find=false; 								//continuo la ricerca
		}		
	}
	//END of "TO DO"
    puts(par1);
return 0;
}
