#include <iostream>
#include "string"
#include "vector"
#include <stdlib.h> // system("cls")
#include <fstream>
#include <sstream> // konvertieren
#include <algorithm> // find

using namespace std;

/* Zerteilt die Eingabe in seine Bestandteile */
void commandParser(string command, string &word1, string &word2){
	string substr;
	vector<string> words;
	
	//Kommando in einzelne Wörter aufteilen
	for(size_t i=0; i<command.size(); i++){
		if(command.at(i) != ' '){
			substr.insert(substr.end(), command.at(i));
		}
		if(command.at(i) == ' ' || i == command.size()-1){
			words.push_back(substr);
			substr.clear();
		}
	}
	
	//Wörter zurückgeben
	if(words.size() == 0){
		cout << "Es wurde kein Befehl eingegeben!" << endl;
	}else if(words.size() == 1){
		word1 = words.at(0);
	}else if(words.size() == 2){
		word1 = words.at(0);
		word2 = words.at(1);
	}else if(words.size() > 2){
		cout << "Der Befehl enthält zu viele Wörter!" << endl;
	}
}

/* 
 * Öffnet eine Textdatei und zeigt den Text an 
 * Gibt außerdem einen Trennstrich aus 
 */
vector<string> setLocation(string filename){
	cout << "===========================================" << endl; //Trennstrich
	
	string path = "world/";
	ifstream f;
	f.open((path + filename).c_str()); //fstream aktzepiert nur c-strings
	string line;
	
	vector<string> directions; //enthält die "Ausgänge" der letzten Position
	
	if(f.is_open()){
		//genereller Durchlauf
		while(getline(f, line)){
			//TEXT auslesen	
			if(line=="[text]"){
				while(getline(f,line)){
					if(line.at(0) != '['){
						cout << line << endl;
					}else{
						break;
					}
				}
			}
			//DIRECTIONS auslesen
			if(line=="[wege]"){
				while(getline(f,line)){
					if(line.at(0) != '['){
						directions.push_back(line);
					}else{
						break;
					}
				}
			}
			//ITEMS auslesen
			if(line=="[items]"){
				while(getline(f,line)){
					if(line.at(0) != '['){
						// Item-Array füllen
					}else{
						break;
					}
				}
			}
			
		}
		f.close();
	}else{
		cout << "FEHLER: Datei nicht gefunden." << endl;
	}
	
	return directions;
}

/* Konvertiert Char zu Int */
int toInt(char c){
	switch(c){
		case '0': return 0;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
	}
	return 0;
}

/* Konkateniert zwei einstellige Zahlen */
int append(int a, int b){
	return a*10 + b;
}

/* liefert True wenn das Element in dem Vektor enthalten ist */
bool contains(vector<string> v, string x){
	if( find(v.begin(), v.end(), x) != v.end() )
		return true;
	return false;
}

/* Ermittelt die neue Datei bei einem Positionswechsel */
void changeLocation(int direction, string &loc, vector<string> directions){
	int x=0;
	int y=0;	
	
	//location in x und y schreiben
	bool xCoord = true;
	for(size_t i=0; i<loc.length(); i++){
		if(loc.at(i) == ','){
			xCoord = false;
		}else{
			if(xCoord){
				x = append(x, toInt(loc.at(i)));
			}else{
				y = append(y, toInt(loc.at(i)));
			}
		}
	}
	
	//x und y verändern
	switch(direction){
		case 0: 
			if(contains(directions, "norden")){
				y++; 
			}else{
				cout << "In diese Richtung kannst du nicht gehen!" << endl;
			}
			break;
		case 1: 
			if(contains(directions, "osten")){
				x++; 
			}else{
				cout << "In diese Richtung kannst du nicht gehen!" << endl;
			}	
			break;
		case 2: 
			if(contains(directions, "süden")){
				y--; 
			}else{
				cout << "In diese Richtung kannst du nicht gehen!" << endl;
			}	
			break;
		case 3: 
			if(contains(directions, "westen")){
				x--; 
			}else{
				cout << "In diese Richtung kannst du nicht gehen!" << endl;
			}	
			break;
	}
	
	//int x,y zu string konvertieren
	stringstream convertX, convertY;
	convertX << x;
	convertY << y;
	
	string outX = convertX.str();
	string outY = convertY.str();
	
	//sicherstellen dass die Koordinaten zweistellig formatiert sind
	if(outX.length() == 1)
		outX = "0" + outX;
	if(outY.length() == 1)
		outY = "0" + outY;
	
	//location aktualisieren
	loc = outX + "," + outY;
}

/* Stellt die Eingabezeile bereit und ruft setLocation() auf */
int main(){
	string command;
	string word1;
	string word2;
	
	vector<string> directions; //speichert die "Ausgänge" der aktuellen Position
	string currentLocation = "00,00";
	directions = setLocation(currentLocation);

	while(command != "quit"){
		command.clear();
		cout << ">Gib ein Kommando ein:\n";
		getline(cin, command);
		cout << endl << endl << endl;

		word1.clear();
		word2.clear();
		commandParser(command, word1, word2);

		//Positionswechsel
		if(word1=="norden"){
			changeLocation(0, currentLocation, directions);
		}else if(word1=="osten"){
			changeLocation(1, currentLocation, directions);
		}else if(word1=="süden"){
			changeLocation(2, currentLocation, directions);
		}else if(word1=="westen"){
			changeLocation(3, currentLocation, directions);
		}

		directions = setLocation(currentLocation);
		
	}
	return 0;
}


