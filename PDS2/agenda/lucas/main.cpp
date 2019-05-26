#include <iostream>
#include <fstream>
#include <string>
#include "Agenda.hpp"
using namespace std;

bool is_file_exist(const string fileName){
    ifstream infile(fileName);
    return infile.good();
}

void WriteMonths(string fileName){
	string months[12] = {"January", "February", "March", "April", "May", "June", "Jully", "August", "September", "October", "November", "December"};
	ofstream file;
	file.open(fileName);
	for (int i = 0; i < 12; ++i) file << "- " << months[i] << endl;
	file.close();
}

void ReadAgenda(string fileName, Agenda* agenda){
	Event * event;

	ifstream file;
	file.open(fileName);

	string title, day, time, month;
	char symbol;
	
	while(!file.eof()){
		file >> symbol;
		if(symbol == '-') file >> month;
		else if(symbol == '*'){
			file >> day >> time;
			getline(file, title);
			event = new Event(stoi(month), stoi(day), stoi(time), title);
			agenda->InsertEvent(event);
		}
	}
}

int main(){
	cout << "------- AGENDA -------" << endl;
	cout << "1) Create new Agenda" << endl;
	cout << "2) Open existent Agenda" << endl;

	bool flag = false;
	int choice, c_year;
	cin >> choice;
	if(choice == 1){
		cout << "For which year? ";
		cin >> c_year;
		
		string fileName = "Agenda" + to_string(c_year) + ".txt";

		if(is_file_exist(fileName)){
			cout << endl << "This agenda already exists. Do you wanna open it?" << endl;
			cout << "1) Yes" << endl;
			cout << "2) No" << endl;
			cin >> choice;
			if(choice == 2){
				cout << "Goodbye..." << endl;
				return 0;
			}
		}
		else {
			cout << "Creating a new agenda for " << c_year << "..." << endl;
  			WriteMonths(fileName);
			cout << "Agenda successfully created!" << endl;
  		}
		
	} else if(choice == 2) {
		cout << "Which year? ";
		cin >> c_year;
		
		string fileName = "Agenda" + to_string(c_year) + ".txt";
		if(!is_file_exist(fileName)){
			cout << endl << "This agenda doesn't exist. Do you wanna create it?" << endl;
			cout << "1) Yes" << endl;
			cout << "2) No" << endl;
			cin >> choice;
			if(choice == 2){
				cout << "Goodbye..." << endl;
				return 0;
			}
			else {
				cout << "Creating a new agenda for " << c_year << "..." << endl;
				WriteMonths(fileName);
				cout << "Agenda successfully created!" << endl;
			}
		} else flag = true;

	} else {
		cout << "Invalid Option.\nGoodbye..." << endl;
		return 0;
	}

	Agenda* agenda = new Agenda(c_year);
	if(flag){
		string fileName = "Agenda" + to_string(c_year) + ".txt";
		ReadAgenda(fileName, agenda);
	}
	
	do{
		cout << endl << "############ " << c_year << " ############" << endl;
		cout << "1) View all events" << endl;
		cout << "2) View events by month" << endl;
		cout << "3) Create a new event" << endl;
		cout << "4) Remove an event" << endl;
		cout << "5) Check if an event exists" << endl;
		cout << "6) Save and exit" << endl;
		cout << "##############################" << endl;

		cin >> choice;
		switch(choice){
			case 1:{
				agenda->PrintAgenda();
				break;
			}
			case 2:{
				int month;
				do{
					cout << "Which month? (tap the number) ";
					cin >> month;
					if(month < 1 || month > 12) cout << "Invalid month number" << endl;
				} while(month < 1 || month > 12);
				agenda->ListMonthEvent(month);
				break;
			}
			case 3:{
				int month, day, time;
				string title;
				cout << "Event title: ";
				cin.ignore();
				getline(cin, title);
				cout << "Which month? (tap the number) ";
				cin >> month;
				cout << "Which day? ";
				cin >> day;
				cout << "Which time? ";
				cin >> time;
				if(agenda->IsValid(month, day, time)){
					if(agenda->getEvent(month, day, time)){
						cout << "There's another event already." << endl;
						break;
					}
					Event * event = new Event(month, day, time, title);
					agenda->InsertEvent(event);
					cout << "Event successfully inserted!" << endl;
				}
				else cout << "Invalid data!" << endl;
				break;
			}
			case 4:{
				int month, day, time;
				cout << "Which month? (tap the number) ";
				cin >> month;
				cout << "Which day? ";
				cin >> day;
				cout << "Which time? ";
				cin >> time;
				if(!agenda->IsValid(month, day, time)){
					cout << "Invalid data!" << endl;
				} else {
					Event* ev = agenda->getEvent(month, day, time);
					if(ev){
						agenda->DeleteEvent(ev);
						cout << "Event successfully deleted!" << endl;
					}
					else cout << "The event you're trying to delete doesn't exist!" << endl;
				}
				break;
			}
			case 5:{
				int month, day, time;
				cout << "Which month? (tap the number) ";
				cin >> month;
				cout << "Which day? ";
				cin >> day;
				cout << "Which time? ";
				cin >> time;
				if(!agenda->IsValid(month, day, time)){
					cout << "Invalid data!" << endl;
				} else {
					Event* ev = agenda->getEvent(month, day, time);
					if(ev){
						cout << "You have an event scheduled!" << endl;
						cout << "\" " << ev->title << " \"" << endl;
					}
					else cout << "There isn't any event scheduled." << endl;
				}
				break;
			}
			case 6:{
				string fileName = "Agenda" + to_string(c_year) + ".txt";
				agenda->SaveAgenda(fileName);
				cout << "Saving agenda..." << endl;
				cout << "Successfully closed!" << endl;
				cout << "Goodbye..." << endl;

				break;
			}
			default:{
				cout << "Invalid Option.\nGoodbye..." << endl;
				return 0;
			}
		}
	} while (choice != 6);

	delete(agenda);
	return 0;
}