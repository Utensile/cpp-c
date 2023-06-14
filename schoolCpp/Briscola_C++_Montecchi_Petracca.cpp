//Briscola Montecchi-Petracca
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
using namespace std;

void setcolor(unsigned short color)
{
         HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
         SetConsoleTextAttribute(hcon,color);
}
//Modulo posizione scritte
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int mano[5][8];

void gotoXY(int, int);
void gotoXY(int x, int y) 
{ 
	CursorPosition.X = x; 
	CursorPosition.Y = y; 
	SetConsoleCursorPosition(console,CursorPosition); 
}

//funzioni di utilità

int valore(int carta){
	return carta%10+1;
}
int seme(int carta){
	return floor(carta/10);
}

int punti(int carta){
	int punti[]={11, 0, 10, 0, 0, 0, 0, 2, 3, 4};
	return punti[valore(carta)-1];
}
int potenza(int carta){
	int potenza[]={9, 0, 8, 1, 2, 3, 4, 5, 6, 7};
	return potenza[valore(carta)-1];
}

void show(int carta){
	if(carta!=-1){
		int colore[]={4, 2, 6, 9};
		setcolor(colore[seme(carta)]);
		cout << "|" << valore(carta) << "|";
		setcolor(15);
	}
	else
		cout << "|/|";
}

void write(int carta){
	if(carta!=-1){
		const char *semi[]={"Bastoni", "Coppe", "Denari", "Spade"};
		const char *valori[]={"Asso","2","Tre","4","5","6","7","Fante","Cavallo","Re"};
		cout << valori[valore(carta)-1] << " di " << semi[seme(carta)];
	}
	else
		cout << "Slot Vuoto";
}

void writeVAL( int carta){
	const char *valori[]={"Asso","2","Tre","4","5","6","7","Fante","Cavallo","Re"};
	cout << valori[valore(carta)-1];
}
//Funzioni di base

void imposta(char mod, int *carte, int player, int &briscola, int &turno, int *punti, int Nplayer, bool *Cplayers, int &Dmano){
	turno=0;
	for(int i=0; i<5; i++)
		punti[i]=0;
	for(int i = 0; i<40; i++)
		carte[i]=0;
		
	for(int i=0; i<player; i++)
		if(Nplayer==0)
			Cplayers[i]=0;
		else{
			Cplayers[i]=1;
			Nplayer--;
		}
	if(mod=='f'){
		Dmano=8;
		for(int i=0; i<player; i++)
			for(int j=0; j<Dmano; j++){
				do{
					mano[i][j] = rand()%40;	
				}while(carte[mano[i][j]]==1);
				carte[mano[i][j]]=1;	
			}
		cout << "Briscola da decidersi: - Asta in Corso - " << endl;
	}
	else{
		Dmano=3;
		briscola = rand()%40;
		for(int i=0; i<player; i++)
			for(int j=0; j<Dmano; j++){
				do{
					mano[i][j] = rand()%40;	
				}while(carte[mano[i][j]]==1 or mano[i][j]==briscola);
				carte[mano[i][j]]=1;
			}
		cout << "La Briscola e' "; show(briscola); cout << " "; write(briscola); cout << endl;
	}
}

int CarteDisp(int *carte){
	int CarteDisp = 0;
		for(int i=0; i<40; i++)
			if(carte[i]==0)
				CarteDisp++;
	return CarteDisp;
}

void Pesca(int &slot, int *carte, int &briscola){
	if(CarteDisp(carte)==1){
		slot = briscola;
		carte[briscola]=1;
	}
	else if(CarteDisp(carte)>0){
		do{
			slot = rand()%40;	
		}while(carte[slot]==1 or slot==briscola);
		carte[slot]=1;
	}
}

int CPU(int cpu, int *tavolo, int pt, int br, int player, bool difficile, int Dmano, bool asta, bool *Teams){ 
	int V[Dmano], Vmin=20, Vmax=-1, min, max, win=0;
	//Assegno un valore alle carte in mano
	for(int i=0; i<Dmano; i++){
		if(mano[cpu][i]==-1)
			V[i]=100;
		else{
			V[i]=potenza(mano[cpu][i]);
			if( seme(mano[cpu][i]) == seme(br) )
				V[i]+=6;
		}
	}
	for(int i=0; i<Dmano; i++){
		if(V[i] < Vmin){
			Vmin=V[i];
			min=i;
		}
		if(V[i] > Vmax and V[i]!=100 and seme(mano[cpu][i]) != seme(br)){
			Vmax=V[i];
			max=i;
		}
	}
	for(int i=1; i<player; i++){
		if(tavolo[i]!=-1){
			if( seme(tavolo[i]) == seme(tavolo[win]) and potenza(tavolo[i]) > potenza(tavolo[win]))
				win=i;
			if( seme(tavolo[i]) != seme(tavolo[win]) and seme(tavolo[i])==seme(br))			
					win=i;
		}
	}
	
	if(!asta){
		if(difficile){
			//Decido cosa giocare
			if(tavolo[0]==-1)
				return min+1;
			else if( Teams[cpu] == Teams[win] ){
				if(Vmax!=-1 and seme(mano[cpu][max])!= seme(br))
					min=max;		
			}
			else if(pt<7){
				for(int i=0; i<Dmano; i++){
					if( seme(mano[cpu][i]) != seme(tavolo[win]) and seme(mano[cpu][i])==seme(br) and V[i]<11)
						min=i;
					if( seme(mano[cpu][i]) == seme(tavolo[win]) and potenza(mano[cpu][i]) > potenza(tavolo[win]) and seme(mano[cpu][i])!=seme(br))
						min=i;	
				}
				for(int i=0; i<Dmano; i++){
					if( seme(mano[cpu][i]) == seme(tavolo[win]) and seme(mano[cpu][i])!=seme(br) and potenza(mano[cpu][i]) > potenza(tavolo[win]) and punti(i)>punti(min) )
						min=i;
					if( seme(mano[cpu][i]) != seme(tavolo[win]) and seme(mano[cpu][i])==seme(br) and V[i]<11 )
						min=i;	
				}
			}
			else{
				for(int i=0; i<Dmano; i++){
					if( seme(mano[cpu][i]) == seme(tavolo[win]) and seme(mano[cpu][i])!=seme(br) and potenza(mano[cpu][i]) > potenza(tavolo[win]) and punti(i)>punti(min) )
						min=i;
					if( seme(mano[cpu][i]) != seme(tavolo[win]) and seme(mano[cpu][i])==seme(br) and V[i]<V[min] )
						min=i;	
				}
			}
		}
		else{
			srand(time(NULL));
			do{
				min=rand() % Dmano;
			}while(mano[cpu][min]==-1);
		}
		return min+1;
	}
	else{
		int Qsemi[4][3]; //Qsemi[seme][0->N.carte; 1->Ptot Carte; 2->Valore Seme]
		for(int i=0; i<4; i++)
			for(int j=0; j<3; j++)
				Qsemi[i][j]=0;
		for(int i=0; i<Dmano; i++){
			Qsemi[seme(mano[cpu][i])][0]++;
			Qsemi[seme(mano[cpu][i])][1]+=punti(mano[cpu][i]);
		}
		for(int i=0; i<4; i++)
			Qsemi[i][2]=Qsemi[i][0]*6+Qsemi[i][1];  //Calcolo il valore del seme i
		int max=0;int CardValue[]={0, 2, 9, 8, 7, 6, 5, 4, 3, 1};
		for(int i=1; i<4; i++)
			if(Qsemi[i][2]>=Qsemi[max][2])
				max=i;
		if(Qsemi[max][2]<30)
			return -1;
		else
			for(int i=0; i<10; i++)
				for(int j=0; j<8; j++)
					if(max*10+CardValue[i]==mano[cpu][j])
						break;
					else if(j==7 and Qsemi[max][2]>(5*i))
						if(tavolo[0]!=-1){
							if( potenza(max*10+CardValue[i])<potenza(tavolo[0]) )
								return max*10+CardValue[i];
						}
						else
							return max*10+CardValue[i];
		return -1;
	}
}

int Vincitore(int *tavolo, int turno, int briscola, int player){
	int win=0;
	for(int i=1; i<player; i++){
		if( seme(tavolo[i]) == seme(tavolo[win]) and potenza(tavolo[i]) > potenza(tavolo[win]))
			win=i;
		if( seme(tavolo[i]) != seme(tavolo[win]) and seme(tavolo[i])==seme(briscola))
			win=i;
	}
	return (turno+win)%player;
}

int main(){
	bool game = false, difficile=true, Teams[5];
	int player, carte[40], briscola, turno, azione, round, puntiTavola, PuntiP[5], Npartite=1, Nplayer=1, Dmano, ASTA[5];
	char mod, Continue;
	double speed;
	srand(time(NULL));
	system("Color 0C");
	cout << "                                     ______________________________________________"  << endl;
	cout << "                                    {                    Briscola                  }" << endl;
	cout << "                                    {            by Utensile and Breadguy          }" << endl;
	cout << "                                    {______________________________________________}" << endl;
	setcolor(11);
	cout << "                    _______    _________   __   _________   _______   _______   __        _________ ";		gotoXY(0, 5);
	cout << "                   |   _   |  |   ___   | |  | |  _______| |  _____| |  ___  | |  |      |   ___   |";	 	gotoXY(0, 6);
	cout << "                   |  |_|  |  |  |___|  | |  | | |_______  | |       | |   | | |  |      |  |   |  |";		gotoXY(0, 7);
	cout << "                   |   _  <   |  ___   _| |  | |_______  | | |       | |   | | |  |      |  |___|  |";		gotoXY(0, 8);
	cout << "                   |  |_|  |  |  |  |  |  |  |  _______| | | |_____  | |___| | |  |____  |   ___   |";		gotoXY(0, 9);
	cout << "                   |_______|  |__|   |__| |__| |_________| |_______| |_______| |_______| |__|   |__|" 		<< endl << endl;
	setcolor(10);
	cout << "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_" << endl;
    setcolor(15);
    Sleep(1500);
	cout << "Per giocare a Briscola si utilizza un mazzo di 40 carte diviso in 4 semi, ciascuno di 10 carte."<< endl <<"Nel mazzo vi sono un totale di 120 punti," << endl <<"Ogni carta e' identificata dal suo numero e dal colore del suo seme:" << endl << endl;setcolor(4); cout << "Bastoni = rosso (1-10)" << endl;setcolor(2); cout << "Coppe = verde (11-20)" << endl;setcolor(6); cout << "Denari = giallo (21-30)" << endl; setcolor(9); cout << "Spade = blu (31-40)" << endl << endl; setcolor(15);
	cout << "Per vincere il gioco bisogna ottenere piu' punti degli avversari sapendo che:" << endl << "Il fante(8) vale 2, il cavallo(9) vale 3, il re(10) vale 4, il tre(3) vale 10 e l'asso(1) vale 11"<< endl <<"mentre il resto vale 0."<< endl <<"La partita inizia con tre carte a giocatore e si svolge a turni nei quali ognuno gioca una carta, dopo che questo "<< endl << "e' avvenuto il giocatore che prende le carte è colui che ha messo la briscola piu' alta oppure quello che ha messo"<< endl << "la carta del seme iniziale maggiore. La briscola e' determinata casualmente a inizio partita'. Per chiedere un " << endl << "suggerimento inserire 0(-1 nell'asta). Nelle 2v2 premendo 0 e' anche possibile vedere le carte del compagno'" << endl << endl; setcolor(10); cout << "Singolo    "; setcolor(15); cout <<"-->   1v1" << endl; setcolor(14); cout << "Doppio     "; setcolor(15); cout <<"-->   2v2 " << endl; setcolor(12); cout << "Cinque     "; setcolor(15); cout <<"-->   2v3 con Asta"  << endl;
	cout << "________________________________________________________________ _ _ _ _ _ _ _ _ _Storico delle partite _ _ _ _ _ _ _ _ _";
	gotoXY(64, 30);
	for(int i=0;i<10;i++){
		gotoXY(64, (33+i));
		cout << "|";
	}
	begin:
	gotoXY(0, 10);
	gotoXY(0, 33);
	cout << "Seleziona Modalita':                                 ";
	gotoXY(20, 33);
	cin >> mod;
	int scala=0;
	bool asta=false;
	for(int i=0; i<5; i++)
		if(i%2==0)
			Teams[i]=1;
		else
			Teams[i]=0;
	if(mod == 's')
		player = 2;
	else if(mod == 'd')
		player = 4;
	else if (mod == 'f'){
		player = 5;
		scala=5;
		asta=true;
		for(int i=0; i<5; i++)
			ASTA[i]=1;
	}
	else
		player = 2;
	gotoXY(0, 33);
	do{
		gotoXY(0, 33);
		cout << "Numero Giocatori:                       ";
		gotoXY(17, 33);
		cin >> Nplayer;
	}while(Nplayer<1 or Nplayer>player);	
	bool CPlayers[5];
	if(Nplayer!=player){
		gotoXY(0, 33);
		cout << "Difficolta' CPU(0/1):                       ";
		gotoXY(21, 33);
		cin >> difficile;
	} 
	gotoXY(0, 33);
	cout << "Velocita' di Gioco(1/1.5):                           ";
	gotoXY(26, 33);
	cin >> speed;
	imposta(mod, carte, player, briscola, turno, PuntiP, Nplayer, CPlayers, Dmano);
	int tavolo[player];
	for(int i=0; i<5; i++)
		tavolo[i]=-1;
	game = true;
	puntiTavola=0;
	round=0;
	start:
	while(game){
		gotoXY(0, 33);
		cout << "                                                      ";
		gotoXY(0, 33);
		cout << "Nel mazzo rimangono " << CarteDisp(carte) << " carte ";
		gotoXY(0, 35);
		if(!asta){
			if(mod!='f')
				cout << "Punti squadra 1 = " << PuntiP[0] << " | Punti squadra 2 = " << PuntiP[1] << "         "; 
			else{
				cout << "Punti -> ";
				for(int i=0; i<5; i++)
					cout << "P" << i+1 << ": " << PuntiP[i] << " - ";
			}
			gotoXY(0, 36); cout << "Carte in tavola:      Punti in tavola = " << puntiTavola <<  "               ";
			gotoXY(0, 37);
			for(int i=0; i<round; i++){
				if(tavolo[i]!=-1)
				show(tavolo[i]);
			}
			cout << "                        ";
		}	
		else{
			cout << "Ultima Carta Chiamata:                ";
			gotoXY(0, 36);
			if(tavolo[0]!=-1)
				writeVAL(tavolo[0]);
			else
				cout << "Nessuna";
			cout << "                ";
		}
		if(round==player and !asta){
			Sleep(2500/speed); //2500
			turno = Vincitore(tavolo, turno, briscola, player);
			if(mod!='f'){
				if(Teams[turno])
					PuntiP[0]+=puntiTavola;
				else
					PuntiP[1]+=puntiTavola;
			}
			else
				PuntiP[turno]+=puntiTavola;
			gotoXY(0, 43+scala);
			if(CPlayers[turno])
				cout << "/// Giocatore " << turno+1 << " ha preso questa mano! ///                            "; 
			else
				cout << "/// CPU " << turno-Nplayer+1 << " ha preso questa mano! ///                           "; 	
			Sleep(2500/speed);
			if(CarteDisp(carte)>0)
				for(int i=turno; i<player+turno; i++)
					for(int j=0; j<Dmano; j++)
						if(mano[i%player][j]==-1)
							Pesca(mano[i%player][j], carte, briscola);
			bool check=true;
			for(int i=0; i<Dmano; i++)
				if(mano[0][i]!=-1)
					check=false;
			if(check)
				game = false;
			for(int i=0; i<5; i++)
				tavolo[i]=-1;
			round = 0;
			puntiTavola=0;
			goto start;
		}
		if(CPlayers[turno]){
			cout << endl << "Mano Giocatore "<< turno+1 << ": " << endl;
			if(CPlayers[(turno-1)%player] or (turno==0 and CPlayers[player-1]) ){
				for(int i=0; i<Dmano; i++){
				cout << "                             ";
				gotoXY(0, (39+i));
				if(mano[turno][i]!=-1)
					cout << "|§| - Carta  Giocatore " << turno+1 << "               " << endl;
				else
					cout << "|/| - Slot vuoto";
				}
				if(!asta or (asta and ASTA[turno]==1)){
					gotoXY(0, 43+scala);
					cout  << "Premere 'invio' per scoprire le carte...                         ";
					gotoXY(40, 43+scala);
					getch();
 				}
			}
			for(int i=0; i<Dmano; i++){
				cout << "                             ";
				gotoXY(0, (39+i));
				show(mano[turno][i]);
				cout << " - ";
				write(mano[turno][i]);
				cout << "               ";
				cout << endl;
			}
		}
		else{
			cout << endl << "Mano CPU "<< turno-Nplayer+1 << ":              " << endl;
			for(int i=0; i<Dmano; i++){
				cout << "                             ";
				gotoXY(0, (39+i));
				if(mano[turno][i]!=-1)
					cout << "|§| - Carta  CPU " << turno-Nplayer+1 << "               " << endl;
				else
					cout << "|/| - Slot vuoto" << "               ";
			}
		}	
		gotoXY(0, 42+scala);
		cout << "                                                           ";
		gotoXY(0, 42+scala);
		if(!asta){
			if(CPlayers[turno]){
				if(Dmano!=8)
					cout << endl << "Tocca al Giocatore " << turno+1 << ", scegli la carta(1, 2, 3): ";
				else
					cout << endl << "Tocca al Giocatore " << turno+1 << ", scegli la carta(1,2.. 8): ";
				do{
					cout << "                ";
					gotoXY(47, 43+scala);
					cin >> azione;
					if(azione==0){
						gotoXY(0, 44+scala);
						cout << "|-|Suggerimento --> Gioca la carta: "; show(mano[turno][CPU(turno, tavolo, puntiTavola, briscola, player, difficile, Dmano, asta, Teams)-1]); cout << " |-|";
						if(mod=='d' and (CarteDisp(carte)==4 or CarteDisp(carte)==24)){
							gotoXY(0, 45+scala);
							cout << "|:| Carte del compagno: "; show(mano[(turno+2)%player][0]); cout << " - "; show(mano[(turno+2)%player][1]); cout << " - "; show(mano[(turno+2)%player][2]); cout << " |:|";
						}
						Sleep(2000);
						gotoXY(0, 44+scala);
						cout << "                                                                           ";
						gotoXY(0, 45+scala);
						cout << "                                                                           ";
					}
					if(azione<0 or azione>Dmano or mano[turno][azione-1]==-1 ){
						gotoXY(47, 43+scala);
						cout << "*Slot invalido*";
						Sleep(500);
						gotoXY(47, 43+scala);
					}
				}while(azione<1 or azione>Dmano or mano[turno][azione-1]==-1);
				gotoXY(0, 43+scala);
				cout << "|||Giocatore " << turno+1 << " Ha Giocato "; show(mano[turno][azione-1]); write(mano[turno][azione-1]);cout <<  " |||                                 ";
			}
			else{
				azione = CPU(turno, tavolo, puntiTavola, briscola, player, difficile, Dmano, asta, Teams);
				gotoXY(0, 43+scala);
				cout << "|||CPU " << turno-Nplayer+1 << " Ha Giocato " ; show(mano[turno][azione-1]); write(mano[turno][azione-1]);cout <<   " |||                             ";
			}
			tavolo[round] = mano[turno][azione-1];
			puntiTavola=0;
			for(int i = 0; i<=round; i++){
				puntiTavola+=punti(tavolo[i]);
			}
			mano[turno][azione-1] = -1;
			turno++;
			if(turno==player)
				turno = 0;
			round++;
			gotoXY(0, 44);
			Sleep(2000/speed);
		}
		else if(ASTA[turno]==1){
			if(CPlayers[turno]){
				do{
					redo:
					gotoXY(0, 43+scala);
					cout << "Tocca al Giocatore " << turno+1 << ", chiami una carta(1,2,..,40) o passi(0)?";
					cout << "                                                ";
					gotoXY(61, 43+scala);
					cin >> azione;
					azione--;
					if(azione==-2){
						gotoXY(0, 44+scala);
						cout << "|-|Suggerimento --> Chiama la carta: "; show(CPU(turno, tavolo, puntiTavola, briscola, player, difficile, Dmano, asta, Teams)); cout << " |-|";
						Sleep(2000);
						gotoXY(0, 44+scala);
						cout << "                                                                           ";
					}
					if(azione==-1)
						break;
					for(int i=0; i<8; i++)
						if(mano[turno][i]==azione){
							gotoXY(47, 43+scala);
							cout << "*Non puoi chiamare una tua carta*";
							Sleep(500);
							gotoXY(47, 43+scala);
							goto redo;	
						}		
					if(azione<0 or azione>39 or ( tavolo[0]!=-1 and potenza(azione)>=potenza(tavolo[0]) ) ){
						gotoXY(47, 43+scala);
						cout << "*Carta Invalida*";
						Sleep(500);
						gotoXY(47, 43+scala);
					}
				}while(azione<0 or azione>39 or ( tavolo[0]!=-1 and potenza(azione)>=potenza(tavolo[0]) ) );
				gotoXY(0, 43+scala);
				if(azione!=-1){
					cout << "|||Giocatore " << turno+1 << " Ha Chiamato "; writeVAL(azione); cout << " |||                                                             ";
				}
				else{
					cout << "|||Giocatore " << turno+1 << " Ha Passato |||                                                                                     ";
					ASTA[turno]=0;
				}
			}
			else{
				azione = CPU(turno, tavolo, puntiTavola, briscola, player, difficile, Dmano, asta, Teams);
				gotoXY(0, 43+scala);
				if(azione!=-1){
					cout << "|||CPU " << turno-Nplayer+1 << " Ha Chiamato " ; writeVAL(azione);cout <<   " |||                                                             "; 
				}
				else{
					cout << "|||CPU " << turno-Nplayer+1 << " Ha Passato |||                                                                               "; 
					ASTA[turno]=0;
				}
			}
			Sleep(2000/speed);
		}
		if(asta){
			if(ASTA[turno]==0)
				azione=-1;
			else if(azione!=-1)
				tavolo[0]=azione;
			turno++;
			if(turno==player)
				turno = 0;
			int count=0;
			for(int i=0; i<5; i++)
				if(ASTA[i]==1)
					count++;
			if(count==1 and tavolo[0]!=-1){
				briscola=tavolo[0];
				gotoXY(0, 34);
				cout << "La Briscola e' "; show(briscola); cout << " "; write(briscola); cout << "                  " << endl;
				tavolo[0]=-1;
				asta=false;
				for(int i=0; i<5; i++){
					Teams[i]=0;
					if(ASTA[i]==1){
						turno=i+1;
						Teams[i]=1;
					}
				}
				for(int i = 0; i<5; i++)
					for(int j = 0; j<Dmano; j++)
						if(mano[i][j]==briscola)
							Teams[i]=1;
				goto start;
			}
			else if(count==0){
				gotoXY(0, 43+scala);
				cout << "|/|/|/| Nessuno ha chiamato, ridistribuzione carte...|/|/|/|                     ";
				Sleep(2000/speed);
				cout << "                                                                                 ";
				gotoXY(0, 43+scala);
				gotoXY(0, 33);
				for(int i= 0; i<5; i++)
					ASTA[i]=1;
				for(int i = 0; i<40; i++)
					carte[i]=0;
				for(int i=0; i<player; i++)
					for(int j=0; j<Dmano; j++){
						do{
							mano[i][j] = rand()%40;	
						}while(carte[mano[i][j]]==1);
						carte[mano[i][j]]=1;	
					}
			}
		}
		
	}
	if(!game){
		int k[2]={0, 0};
		if(mod=='f'){
			for(int i=0; i<5; i++)
				if(Teams[i]==1)
					k[0]+=PuntiP[i];
				else
					k[1]+=PuntiP[i];
			PuntiP[0]=k[0];
			PuntiP[1]=k[1];
		}
		
				
		gotoXY(0, 43+scala);
		if(PuntiP[0]>PuntiP[1]){
			cout << "|/|/|/| La Squadra 1 (tu) HA VINTO!!! |/|/|/|          ";
			gotoXY(66, 32+Npartite);
			cout << "Partita " << Npartite; setcolor(10) ;cout << " |Esito: Vittoria Team 1|"; setcolor(8) ; cout <<" Punteggi: " << PuntiP[0] << "-" << PuntiP[1] << " |";
		}
		else if(PuntiP[0]==PuntiP[1]){
			cout << "|/|/|/| PAREGGIO (60-60) |/|/|/|                       ";
			gotoXY(66, 32+Npartite);
			cout << "Partita " << Npartite; setcolor(6) ;cout << " |    Esito: Pareggio   |"; setcolor(8) ; cout <<" Punteggi: "<< PuntiP[0] << "-" << PuntiP[1] << " |";
		}
		else if(PuntiP[0]<PuntiP[1]){
			cout << "|/|/|/| La Squadra 2 (avversari) HA VINTO!!! |/|/|/|   ";
			gotoXY(66, 32+Npartite);
			cout << "Partita " << Npartite; setcolor(12) ;cout << " |Esito: Vittoria Team 2|"; setcolor(8) ; cout <<" Punteggi: " << PuntiP[0] << "-" << PuntiP[1] << " |";
		}
		setcolor(15);
		Sleep(5000);
		for(int i = 0; i < 15; i++){
			gotoXY(0, 33+i);
			cout << "                                                           ";
		}
		gotoXY(0, 10);
		gotoXY(0, 33);
		cout << "Vuoi Giocare un'altra partita?(s/n):                      ";
		gotoXY(35, 33);
		cin >> Continue;
		if(Continue=='s'){
			Npartite++;
			goto begin;
		}
		else
			return 0;
	}
}

