#include <iostream>
#include <string.h>
#include <windows.h>
#include <time.h>
using namespace std;

class Persona{
	protected:
		char nome[40];
		char cognome[40];
	public:
		Persona();
		Persona(const char*, const char*);
		void setNome(const char*);
		const char* getNome();
		void setCognome(const char*);
		const char* getCognome();
};

Persona::Persona(){
	strcpy(nome, "A");
	strcpy(cognome, "B");
}

Persona::Persona(const char* a, const char* b){
	strcpy(nome, a);
	strcpy(cognome, b);
}

void Persona::setNome(const char* a){
	strcpy(nome, a);
}

const char* Persona::getNome(){
	return nome;
}

void Persona::setCognome(const char* a){
	strcpy(cognome, a);
}

const char* Persona::getCognome(){
	return cognome;
}

class Impiegato : public Persona{
	private:
		char mansione[30];
		float stipendio;
	public:
		Impiegato();
		Impiegato(const char*, float);
		void setMansione(const char*);
		const char* getMansione();
		void setStipendio(float);
		float getStipendio();
};

Impiegato::Impiegato(){
	strcpy(mansione,"disoccupato");
	stipendio = 0;
}

Impiegato::Impiegato(const char* a, float b){
	strcpy(mansione, a);
	stipendio = b;
}

void Impiegato::setMansione(const char* a){
	strcpy(mansione, a);
}

const char* Impiegato::getMansione(){
	return mansione;
}

void Impiegato::setStipendio(float a){
	stipendio=a;
}

float Impiegato::getStipendio(){
	return stipendio;
}

int main(){
	int n;
	float media;
	cout << "Quanti Impiegati si vuole creare? ";
	cin >> n;
	Impiegato imp[n];
	srand(time(NULL));
	const char* Nomi[]={"Mario", "Filippo", "Claudio", "Alessio", "Federico", "Giovanni", "Luca", "Marco", "Antonio", "Paolo"};
	const char* Cognomi[]={"Rossi", "Bianchi", "Da Vinci", "Capuleti", "Boccaccio", "Lodi"};
	const char* Mansioni[]={"Contabile", "Meccanico", "Pilota", "Cameriere", "Cuoco", "Medico", "Agricoltore", "Astronauta"};
	for(int i=0; i<n; i++){
		imp[i].setNome(Nomi[rand()%10]);
		imp[i].setCognome(Cognomi[rand()%6]);
		imp[i].setMansione(Mansioni[rand()%8]);
		imp[i].setStipendio(rand()%30000+5000);
	}
	for(int i=0; i<n; i++)
		media+=imp[i].getStipendio();
	media/=n;
	cout << endl <<"---- Persone con stipendio superiore alla media ----" << endl << endl;
	for(int i=0; i<n; i++){
		if(imp[i].getStipendio()>=media){
			cout << "Nome e Cognome: " << imp[i].getNome() << " " << imp[i].getCognome() << endl;
			cout << "Mansione: " << imp[i].getMansione() << endl;
			cout << "Stipendio: " << imp[i].getStipendio() << " euro/anno"<< endl << endl;
		}
	}
	char ans;
	cout << "Vuoi visualizzare la lista completa?(s/n) ";
	cin >> ans;
	if(ans=='s')
		for(int i=0; i<n; i++){
			cout << "Persona " << i+1 << endl;
			cout << "Nome e Cognome: " << imp[i].getNome() << " " << imp[i].getCognome() << endl;
			cout << "Mansione: " << imp[i].getMansione() << endl;
			cout << "Stipendio: " << imp[i].getStipendio() << " euro/anno"<< endl << endl;
		}
	return 0;
}
