#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>

using namespace std;

//#include "red_polje.h"
#include "red_pokazivac.h"

osoba *polje;

int generator(que *Q){
	int k;
	cout << "Unesite broj cetvorki koje zelite generirati? ";
	cin >> k;
	polje = new osoba [k];
	for(int i=0; i<k; i++){
		polje[i].ai = 10 + rand()%491;
		polje[i].bi = 80 + rand()%721;
		polje[i].ci = 1 + rand()%5;
		polje[i].di = 1 + rand()%5;
	}
	cout << "Uspjesno je generirano " << k << " cetvorki!"<<endl;
	cout << "______________________________"<<endl;
	for(int i=0; i<k; i++)
		cout << i+1 << ". cetvorka: " << polje[i].ai << ", " << polje[i].bi << ", " << polje[i].ci << ", " << polje[i].di << endl;
	cout << "______________________________"<<endl;
	return k;
}


void sortiranje(que *Q){
	que *PQ = InitQ(PQ);
	que *PQ2 = InitQ(PQ2);
	osoba x;
	while(!IsEmptyQ(Q)){
		x = celoQ(Q);
		DeQueueQ(Q);
		EnQueueQ(x, PQ);
	}
	for(int i=1; i<=5; i++){
		while(!IsEmptyQ(PQ)){
			x = celoQ(PQ);
			DeQueueQ(PQ);
			if(x.ci == i) EnQueueQ(x, Q);
			else EnQueueQ(x, PQ2);
		}
		
		while(!IsEmptyQ(PQ2)){
			x = celoQ(PQ2);
			DeQueueQ(PQ2);
			EnQueueQ(x, PQ);
		}
	}
}
void ispis_cetvorki(int a, int b, int c, int d){
	cout << "Cekanje u redu nakon prethodnog: " << a << "(s)";
	cout << "Vrijeme usluzivanja: " << b << " (s)\n";
	cout << "Priroriteti klijenta: ";
	switch(c){
		case 1: cout << "1 - VIP klijent\n"; break;
		case 2: cout << "2 - Invalid\n"; break;
		case 3: cout << "3 - trudnicanica\n"; break;
		case 4: cout << "4 - Umirovljenik\n"; break;
		case 5: cout << "5 - Ostali\n"; break;
	}
	cout << "Vrsta usluge: ";
	switch(d){
		case 1: cout << "1 - Predaja/preuzimanje posiljke\n"; break;
		case 2: cout << "2 - Placanje racuna\n"; break;
		case 3: cout << "3 - Uplata lutrije\n"; break;
		case 4: cout << "4 - Western Union\n"; break;
		case 5: cout << "5 - Evotv\n"; break;
	}
}

void unos(que *Q, int brojac){
	bool trudnica, ponovi;
	cout << "Unos po 5 klijenata za svaku generiranu kombinaciju\n";
	cout << "______________________________\n";
	for(int i=0; i<brojac; i++){
		cout << i+1 << ". kombinacija\n";
		ispis_cetvorki(polje[i].ai, polje[i].bi, polje[i].ci, polje[i].di);
		cout << "______________________________\n";
		trudnica = false;
		for(int j=0; j<5; j++){
			cout << "______________________________\n";
			cout << j+1 << ". klijent\n";
			cout << "______________________________\n";
			osoba x;
			if(polje[i].ci==3){
				trudnica = true;
 				cout << "Klijent je trudnicanica te je spol zenski|Automatski je generirano!\n";
 				x.spol='Z';
 			}
			cout << "Ime: ";
			cin.ignore();
			getline(cin, x.ime);
			cout << "Prezime: ";
			getline(cin, x.prezime);
			cout << "Datum rodenja\n";
			do{
				cout << "Dan: ";
				cin >> x.dan;
				if(x.dan<1 || x.dan>31) cout << "Dan mora biti u rasponu od 1 do 31!\n";
			}while(x.dan<1 || x.dan>31);
			do{
				cout << "Mjesec: ";
				cin >> x.mj;
				if(x.mj<1 || x.mj>12) cout << "Mjesec mora biti u rasponu od 1 do 12!\n";
			}while(x.mj<1 || x.mj>12);
			do{
				ponovi = false;
				cout << "Godina: ";
				cin >> x.god;
				if(x.god<1900 || x.god>2014){
					cout << "Godina mora biti u rasponu od 1900 do 2014!\n";
					ponovi = true;
				}
				if(polje[i].ci==4 && ((2014 - x.god)<50)){
					cout << "Umirovljenici moraju biti stari barem 50 godina!\n";
					ponovi = true;
				}
			}while(ponovi);
			if(!trudnica){
				do{
					cout << "Spol (M/Z): ";
					cin >> x.spol;
					if(toupper(x.spol)!='M' && toupper(x.spol)!='Z') cout << "Spol mora biti M ili Z!\n";
				}while(toupper(x.spol)!='M' && toupper(x.spol)!='Z');
			}
			x.ai = polje[i].ai;
			x.bi = polje[i].bi;
			x.ci = polje[i].ci;
			x.di = polje[i].di;
			ispis_cetvorki(x.ai, x.bi, x.ci, x.di);
			cout << "___________________________\n";
			EnQueueQ(x, Q);
			if(x.ci<5) sortiranje(Q);
			cout << "Osoba je uspjesno dodana u red!\n\n";
		}
	}
}




bool horoskop(osoba x){
	if(((x.dan>=22) && x.mj==12) || ((x.dan<=20) && x.mj==1)) return true;
	else return false;
}

void ispis_klijenta(osoba x){
	cout << "Ime: " << x.ime << endl;
	cout << "Prezime: " << x.prezime << endl;
	cout << "Datum rodenja: " << x.dan << "." << x.mj << "." << x.god << endl;
	cout << "Spol: " << x.spol << endl;
	ispis_cetvorki(x.ai, x.bi, x.ci, x.di);
	cout << "______________________________\n";
}


void ispis_red(que *Q){
	if(IsEmptyQ(Q)) return;
	osoba x = celoQ(Q);
	ispis_klijenta(x);
	DeQueueQ(Q);
	ispis_red(Q);
	EnQueueQ(x, Q);
}
void ispis_jarac(que *Q){
	cout << "\nIspis svih klijenta koji su horoskopskog znaka Jarac, mladi od 40 godina i cekaju na uplatu lutrije\n";
	cout << "______________________________\n";
	que *PQ = InitQ(Q);
	osoba x;
	bool jarac;
	while(!IsEmptyQ(Q)){
		x = celoQ(Q);
		DeQueueQ(Q);
		EnQueueQ(x, PQ);
		jarac = horoskop(x);
		if(x.di==3 && jarac && ((2014 - x.god)<40))
			ispis_klijenta(x);
	}
	
	while(!IsEmptyQ(PQ)){
		x = celoQ(PQ);
		DeQueueQ(PQ);
		EnQueueQ(x, Q);
	}
}


void povrati(que *Q){
	if(IsEmptyQ(Q)) return;
	osoba x = celoQ(Q);
	DeQueueQ(Q);
	povrati(Q);
	EnQueueQ(x, Q);
}

void rasporedi(que *Q, que *Q1, que *Q2, que *Q3, que *Q4, que *Q5, que *FQ){
	if(IsEmptyQ(Q)) return;
	osoba x = celoQ(Q);
	DeQueueQ(Q);
	if(x.ci==4) EnQueueQ(x, FQ);
	else {
		switch(x.di){
			case 1: EnQueueQ(x, Q1); break;
			case 2: EnQueueQ(x, Q2); break;
			case 3: EnQueueQ(x, Q3); break;
			case 4: EnQueueQ(x, Q4); break;
			case 5: EnQueueQ(x, Q5); break;
		}
	}
	rasporedi(Q, Q1, Q2, Q3, Q4, Q5, FQ);
}


void izlaz_trudnica(que *Q){
	if(IsEmptyQ(Q)) return;
	osoba x;
	bool pop;
	do{
		pop = false;
		x = celoQ(Q);
		if(x.ci==3 && x.di==5){
		pop = true;
		DeQueueQ(Q);
		}
		if(IsEmptyQ(Q)) break;
	}while(pop);
	if(!IsEmptyQ(Q)) DeQueueQ(Q);
	izlaz_trudnica(Q);
	if(!pop) EnQueueQ(x, Q);
}


void brzi_red(que *FQ, que *Qn){
	static int br=0;
	if(IsEmptyQ(Qn) || br==2) return;
	osoba x = celoQ(Qn);
	DeQueueQ(Qn);
	EnQueueQ(x, FQ);
	br++;
	brzi_red(FQ, Qn);
	br=0;
}

int main (){
	que *Q = InitQ(Q);
	que *Q1 = InitQ(Q1);
	que *Q2 = InitQ(Q2);
	que *Q3 = InitQ(Q3);
	que *Q4 = InitQ(Q4);
	que *Q5 = InitQ(Q5);
	que *FQ = InitQ(FQ);
	
	int izbor, brojac=0;
	do{
		cout << "\tIzbornik\n";
		cout << "______________________________\n";
		cout << "1. Generiranje cetvorki\n";
		cout << "2. Dodavanje klijenta poste u red\n";
		cout << "3. Odlazak trudnicanica koje su se dosle raspitati o Evotv usluzi\n";
		cout << "4. brzi salter\n";
		cout << "5. Stanje u redu\n";
		cout << "9. Izlaz\n";
		cout<<"Odabrite: \n";
		cin >> izbor;
		switch(izbor){
			case 1:
			system("cls");
				brojac = generator(Q);
				break;
			
			case 2:
			system("cls");
				if(!brojac){
					cout << "Prvo morate generirati uredene cetvorke!\n";
					break;
				}
				unos(Q, brojac);
				ispis_jarac(Q);
				break;
			
			case 3:
			system("cls");
				izlaz_trudnica(Q);
				povrati(Q);
				if(IsEmptyQ(Q)){
					cout << "Red je prazan!\n";
					break;
				}
				cout << "Stanje u redu\n";
				cout << "______________________________\n";
				ispis_red(Q);
				povrati(Q);
				break;
				
			case 4:
			system("cls");
				rasporedi(Q, Q1, Q2, Q3, Q4, Q5, FQ);
				sortiranje(Q5);
				brzi_red(FQ, Q5);
				sortiranje(Q4);
				brzi_red(FQ, Q4);
				sortiranje(Q3);
				brzi_red(FQ, Q3);
				sortiranje(Q2);
				brzi_red(FQ, Q2);
				sortiranje(Q1);
				brzi_red(FQ, Q1);
				sortiranje(FQ);
				cout << "Kreiran je brzi salter\n\n";
				cout << "______________________________\n";
				cout << "Stanje u redovima\n";
				cout << "______________________________\n";
				if(!IsEmptyQ(FQ)){
					cout << "brzi red\n";
					cout << "______________________________\n";
					ispis_red(FQ);
					cout << "______________________________\n";
				}
				if(!IsEmptyQ(Q1)){
					cout << "Prvi red - Predaja/Preuzimanje posiljke\n";
					cout << "______________________________\n";
					ispis_red(Q1);
					cout << "______________________________\n";
				}
				if(!IsEmptyQ(Q2)){
					cout << "Drugi red - Placanje racuna\n";
					cout << "______________________________\n";
					ispis_red(Q2);
					cout << "______________________________\n";
				}
				if(!IsEmptyQ(Q3)){
					cout << "Treci red - Uplata lutrije\n";
					cout << "______________________________\n";
					ispis_red(Q3);
					cout << "______________________________\n";
				}
				if(!IsEmptyQ(Q4)){
					cout << "Cetvrti red - Western Union\n";
					cout << "______________________________\n";
					ispis_red(Q4);
					cout << "______________________________\n";
				}
				if(!IsEmptyQ(Q5)){
					cout << "Peti red - Evotv\n";
					cout << "______________________________\n";
					ispis_red(Q5);
					cout << "______________________________\n";
				}
				break;
				
			case 5:
				system("cls");
				if(IsEmptyQ(Q)){
					cout << "Red je prazan!\n\n";
					break;
				}
				cout << "Stanje u redu\n";
				cout << "______________________________\n";
				ispis_red(Q);
				povrati(Q);
				break;

			case 9: cout << "Izlazak\n"; break;
			
		}
	}while(izbor!=9);
	
	system("pause");
	return 0;
}
