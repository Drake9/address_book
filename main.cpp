#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <fstream>
#include <vector>

using namespace std;

struct Adresat{
    int id = 0;
    string imie = "", nazwisko = "", adres = "", numerTelefonu = "", email = "";
};

void podzielString(string linia, char znak, vector<string> &wyrazy){

    for(int i=0, j=0, dlugosc=linia.length(); j<=dlugosc; j++){
        if(linia[j] == znak){
            wyrazy.push_back(linia.substr(i,j-i));
            i = j+1;
        }
    }
}

int wczytajDaneZPliku(vector<Adresat> &adresy){
	int nrKontaktu = 0;
	Adresat kontakt;
	string linia, temp;
	fstream plik;
	vector<string> podzielonaLinia;

    plik.open("ksiazka_adresowa_nowy_format.txt", ios::in); // wczytujemy plik
    if(plik.good()==false){
        cout << "Nie udalo sie otworzyc pliku z kontaktami. Zostanie utworzony nowy plik.";
        Sleep(3000);
        plik.open("ksiazka_adresowa_nowy_format.txt", ios::out | ios::app);
        //exit(0);
    }
    else{
        while(getline(plik,linia)){

            podzielonaLinia.clear();
            podzielString(linia, '|', podzielonaLinia);

            kontakt.id = atoi (podzielonaLinia[0].c_str());
            kontakt.imie = podzielonaLinia[1];
            kontakt.nazwisko = podzielonaLinia[2];
            kontakt.adres = podzielonaLinia[3];
            kontakt.numerTelefonu = podzielonaLinia[4];
            kontakt.email = podzielonaLinia[5];

            adresy.push_back(kontakt);
            nrKontaktu++;
        }
    }
    plik.close();
    return adresy.size();
}

int dodajKontakt(int liczbaKontaktow, vector<Adresat> &adresy){
    Adresat kontakt;
    fstream plik;
    if(liczbaKontaktow > 0)
        kontakt.id = adresy[liczbaKontaktow-1].id + 1;
    else
        kontakt.id = 1;

    system("cls");
    cin.sync();
    cout << "Podaj imie: ";           getline(cin, kontakt.imie);
    cout << "Podaj nazwisko: ";       getline(cin, kontakt.nazwisko);
    cout << "Podaj adres: ";          getline(cin, kontakt.adres);
    cout << "Podaj nr telefonu: ";    getline(cin, kontakt.numerTelefonu);
    cout << "Podaj adres e-mail: ";   getline(cin, kontakt.email);

    adresy.push_back(kontakt);

    plik.open("ksiazka_adresowa_nowy_format.txt", ios::out | ios::app);
    if(plik.good())
        plik << kontakt.id << "|" << kontakt.imie << "|" << kontakt.nazwisko << "|" << kontakt.adres << "|" << kontakt.numerTelefonu << "|" << kontakt.email << "|" << endl;
    else{
        cout << "Nie udalo sie otworzyc pliku do zapisu. Program zostanie zamkniety.";
        exit(0);
    }
    plik.close();

    return liczbaKontaktow+1;
}

void wypiszKontakt(int numerKontaktu, vector<Adresat> &adresy){
	cout << adresy[numerKontaktu].id  << endl;
	cout << adresy[numerKontaktu].imie << " ";
	cout << adresy[numerKontaktu].nazwisko << endl;
	cout << adresy[numerKontaktu].adres << endl;
	cout << adresy[numerKontaktu].numerTelefonu << endl;
	cout << adresy[numerKontaktu].email << endl << endl;
}

void wyszukajKontaktPoImieniu(int liczbaKontaktow, vector<Adresat> &adresy){
	int sprawdzono = 0;
	string imie;

	system("cls");
	cout << "Wpisz imie: ";
	cin >> imie;
	system("cls");

	for(int i=0; i<liczbaKontaktow; i++){
		if(adresy[i].imie==imie){
			wypiszKontakt(i, adresy);
		}
		else{
			sprawdzono++;
		}
	}

	if(sprawdzono==liczbaKontaktow){
		cout << "Nie znaleziono pasujacych wynikow." << endl << endl;
	}

	system("pause");
}

void wyszukajKontaktPoNazwisku(int liczbaKontaktow, vector<Adresat> &adresy){
	int sprawdzono = 0;
	string nazwisko;

	system("cls");
	cout << "Wpisz nazwisko: ";
	cin >> nazwisko;
	system("cls");

	for(int i=0; i<liczbaKontaktow; i++){
		if(adresy[i].nazwisko==nazwisko){
			wypiszKontakt(i, adresy);
		}
		else{
			sprawdzono++;
		}
	}
	if(sprawdzono==liczbaKontaktow){
		cout << "Nie znaleziono pasujacych wynikow." << endl << endl;
	}

	system("pause");
}

void wypiszWszystkieKontakty(int liczbaKontaktow, vector<Adresat> &adresy){
	system("cls");
	cout << "Liczba Kontaktow: " << liczbaKontaktow << endl << endl;
	for(int i=0; i<liczbaKontaktow; i++){
		wypiszKontakt(i, adresy);
	}
	system("pause");
}

int wyszukajKontaktPoID(int id, vector<Adresat> &adresy){
    int index = 0;
    int length = adresy.size();

    while(adresy[index].id != id && index < length){
        index++;
    }

    return index;
}

void usunAdresata(int &liczbaKontaktow, vector<Adresat> &adresy, int index, int wybraneID){
    fstream plik;

    adresy.erase(adresy.begin() + index);
    liczbaKontaktow--;

    plik.open("ksiazka_adresowa_nowy_format.txt", ios::trunc | ios::out);
    if(plik.good()==false){
        cout << "Nie udalo sie otworzyc pliku. Program zostanie zamkniety.";
        exit(0);
    }

    for(int i=0, length=adresy.size(); i<length; i++){
         plik << adresy[i].id << "|" << adresy[i].imie << "|" << adresy[i].nazwisko << "|" << adresy[i].adres << "|" << adresy[i].numerTelefonu << "|" << adresy[i].email << "|" << endl;
    }

    plik.close();
}

void przejdzDoUsuwaniaAdresata(int &liczbaKontaktow, vector<Adresat> &adresy){
    string wybraneIDJakoString = "";
    char wybor = '0';
    int wybraneID = 0;
    system("cls");
    cout << "Wpisz id adresata, ktorego chcesz usunac: ";
    getline(cin, wybraneIDJakoString);
    wybraneID = atoi(wybraneIDJakoString.c_str());
    int index = wyszukajKontaktPoID(wybraneID, adresy);

    if(index >= 0 && index < adresy.size()){
        cout << endl << "Czy na pewno chcesz usunac adresata: " << adresy[index].imie << " " << adresy[index].nazwisko << " ?" << endl << endl;
        cout << "Aby usunac wybranego adresata, nacisnij: t" << endl << endl;
        cout << "Aby powrocic do menu, nacisnij dowolny inny klawisz." << endl;

        wybor = getch();
        if(wybor == 't' || wybor == 'T'){
            usunAdresata(liczbaKontaktow, adresy, index, wybraneID);
        }
    }
    else{
        cout << "Nie znaleziono adresata o podanym id." << endl;
        Sleep(3000);
    }
}

void edytujAtrybutAdresata(int index, int wybraneID, vector<Adresat> &adresy, string &atrybut){
    fstream plik;

    system("cls");
    cout << "Podaj nowy atrybut adresata: " << endl;
    getline(cin, atrybut);

    plik.open("ksiazka_adresowa_nowy_format.txt", ios::trunc | ios::out);
    if(plik.good()==false){
        cout << "Nie udalo sie otworzyc pliku. Program zostanie zamkniety.";
        exit(0);
    }

    for(int i=0, length=adresy.size(); i<length; i++){
         plik << adresy[i].id << "|" << adresy[i].imie << "|" << adresy[i].nazwisko << "|" << adresy[i].adres << "|" << adresy[i].numerTelefonu << "|" << adresy[i].email << "|" << endl;
    }

    plik.close();
}

void edytujAdresata(int index, int id, vector<Adresat> &adresy){
    char wybor = '0';
    cout << endl << "Edycja adresata: " << endl << endl;
    wypiszKontakt(index, adresy);
    cout << "Wybierz, ktory atrybut chcesz zmienic." << endl << endl;
    cout << "1 - imie" << endl;
    cout << "2 - nazwisko" << endl;
    cout << "3 - adres" << endl;
    cout << "4 - numer telefonu" << endl;
    cout << "5 - email" << endl << endl;
    cout << "6 - powrot do menu" << endl;

    wybor = getch();

    switch(wybor){
        case '1':
            edytujAtrybutAdresata(index, id, adresy, adresy[index].imie);
            break;

        case '2':
            edytujAtrybutAdresata(index, id, adresy, adresy[index].nazwisko);
            break;

        case '3':
            edytujAtrybutAdresata(index, id, adresy, adresy[index].adres);
            break;

        case '4':
            edytujAtrybutAdresata(index, id, adresy, adresy[index].numerTelefonu);
            break;

        case '5':
            edytujAtrybutAdresata(index, id, adresy, adresy[index].email);
            break;

        case '6':
            ;
            break;

        default:
            ;
            break;
    }
}

void przejdzdoEdycjiAdresata(int liczbaKontaktow, vector<Adresat> &adresy){
    string wybraneIDJakoString = "";
    int wybraneID = 0;

    system("cls");
    cout << "Wpisz id adresata, ktorego chcesz edytowac: ";

    getline(cin, wybraneIDJakoString);
    wybraneID = atoi(wybraneIDJakoString.c_str());
    int index = wyszukajKontaktPoID(wybraneID, adresy);

    if(index >= 0 && index < adresy.size()){
        edytujAdresata(index, wybraneID, adresy);
    }
    else{
        cout << "Nie znaleziono adresata o podanym id." << endl;
        Sleep(3000);
    }
}

void wypiszMenu(){
	system("cls");
	cout << "KSIAZKA ADRESOWA" << endl << endl;
	cout << "1. Dodaj adresata" << endl;
	cout << "2. Wyszukaj po imieniu" << endl;
	cout << "3. Wyszukaj po nazwisku" << endl;
	cout << "4. Wyswietl wszystkich adresatow" << endl;
	cout << "5. Usun adresata" << endl;
	cout << "6. Edytuj adresata" << endl << endl;
	cout << "9. Zakoncz program." << endl << endl;
	cout << "Twoj wybor: ";
}

int main(){
    int liczbaKontaktow = 0;
    char wybor = 0;
    vector <Adresat> adresaci;

	liczbaKontaktow = wczytajDaneZPliku(adresaci);

    while(true){ // majac wczytana liste wyswietlamy menu i dzialamy
        wypiszMenu();
        wybor = getch();

        switch(wybor){
			case '1':
				liczbaKontaktow = dodajKontakt(liczbaKontaktow, adresaci);
				break;

			case '2':
				wyszukajKontaktPoImieniu(liczbaKontaktow, adresaci);
				break;

            case '3':
				wyszukajKontaktPoNazwisku(liczbaKontaktow, adresaci);
				break;

			case '4':
				wypiszWszystkieKontakty(liczbaKontaktow, adresaci);
				break;

            case '5':
				przejdzDoUsuwaniaAdresata(liczbaKontaktow, adresaci);
				break;

            case '6':
				przejdzdoEdycjiAdresata(liczbaKontaktow, adresaci);
				break;

			case '9':
				return 0;

			default:
				cout << "Nie ma takiej opcji. Wybierz jeszcze raz." << endl;
				Sleep(1500);
				break;
		}
    }
    return 0;
}
