#include <iostream>
#include <fstream>
#include <string>
#include "Agenda.hpp"
using namespace std;

int IsLeap(int year) {
	if (year % 4 != 0) return 0;
	else {
		if (year % 100 == 0) {
			if (year % 400 == 0) return 1;
			else return 0;
		} else return 1;
	}
}

Agenda::Agenda(int year) {
	this->year = year;
	this->month_list = NULL;

	Month* new_month;
	int x = IsLeap(year) ? 29 : 28;
	string months[12] = {"January", "February", "March", "April", "May", "June", "Jully", "August", "September", "October", "November", "December"};
	int days[12] = {31, x, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	for (int i = 0; i < 12; ++i){
		new_month = new Month(i+1, months[i], days[i]);
		InsertMonth(new_month);
	}
}

Day::Day(int id){
	this->id = id;
	this->event_list = NULL;
}

Month::Month(int id, string name, int days){
	this->id = id;
	this->name = name;
	this->days = days;
	this->next = NULL;
	this->day_vector = new Day*[days];
	for (int i = 0; i < days; ++i) day_vector[i] = new Day(i+1);
}

void Agenda::InsertMonth(Month* new_month){
	Month * m = month_list;
	if(!m) month_list = new_month;
	else {
		while(m->next) m = m->next;
		m->next = new_month;
	}
}

void Agenda::PrintAgenda(){
	Month* m = month_list;
	Event* ev;
	while(m){
		cout << "- " << m->name << endl;
		for (int i = 0; i < m->days; ++i){
			ev = m->day_vector[i]->event_list;
			while(ev){
				cout << "   Day: " << ev->day << "/ " << ev->time << " h - " << ev->title << endl;
				ev = ev->next;
			}
		}
		m = m->next;
	}
}

Agenda::~Agenda() {
	Month * m = month_list;
	Month * tmp = m->next;
	while (tmp){
		tmp = m->next;
		delete m;
		m = tmp;
	}
	delete m;
}

Month::~Month() {
	for (int i = 0; i < this->days; ++i){
		delete day_vector[i];
	}
	delete [] day_vector;
}

Event::Event(int month, int day, int time, string title){
	this->month = month;
	this->day = day;
	this->time = time;
	this->title = title;
	this->next = NULL;
}

void Agenda::InsertEvent(Event* new_event){
	Month* current_month = FindCurrentMonth(new_event->month);
	Event* current_event = current_month->day_vector[new_event->day-1]->event_list;
	
	if(!current_event){
		current_month->day_vector[new_event->day-1]->event_list = new_event;
		return;
	}

	if(current_event->time > new_event->time){
		current_month->day_vector[new_event->day-1]->event_list = new_event;
		new_event->next = current_event;
		return;
	}

	Event* tmp = current_event->next;
	while(tmp){
		if(tmp->time > new_event->time){
			current_event->next = new_event;
			new_event->next = tmp;
			return;
		} else {
			current_event = current_event->next;
			tmp = tmp->next;
		}
	}
	current_event->next = new_event; 
}

void Agenda::DeleteEvent(Event* event){
	Month* current_month = FindCurrentMonth(event->month);
	Event* current_event = current_month->day_vector[event->day-1]->event_list;
	Event* tmp = current_event;
	
	while(current_event->time != event->time && current_event){
		tmp = current_event;
		current_event = current_event->next;
	}

	if(current_event == tmp){
		current_month->day_vector[event->day-1]->event_list = current_event->next;
		delete(current_event);
		return;
	} else {
		tmp->next = current_event->next;
		delete(current_event);
	}
}

Month* Agenda::FindCurrentMonth(int m){
	Month* tmp = this->month_list;
	while(tmp){
		if(tmp->id == m) return tmp;
		else tmp = tmp->next;
	}
	return NULL;
}

Event* Agenda::getEvent(int month, int day, int time){
	Month* current_month = FindCurrentMonth(month);
	Event* current_event = current_month->day_vector[day-1]->event_list;
	while(current_event){
		if(current_event->time == time) return current_event;
		current_event = current_event->next;
	}
	return NULL;
}

void Agenda::ListMonthEvent(int month){
	Month* current_month = FindCurrentMonth(month);
	Event* current_event;
	for (int i = 0; i < current_month->days; ++i){
		current_event = current_month->day_vector[i]->event_list;
		while(current_event){
			cout << "   Day: " << current_event->day << "/ " << current_event->time << " h - " << current_event->title << endl;
			current_event = current_event->next;
		}
	}
}

bool Agenda::IsValid(int month, int day, int hour){
	Month* current_month = FindCurrentMonth(month);
	cout << month << endl;
	if(!current_month) return false;
	if(day < 1 || day > current_month->days) return false;
	if(hour < 0 || hour > 23) return false;
	return true;
}

void Agenda::SaveAgenda(string fileName){
	ofstream file;
	file.open(fileName);
	Month* m = this->month_list;
	Event* ev;
	while(m){
		file << "- " << m->id << endl;
		for (int i = 0; i < m->days; ++i){
			ev = m->day_vector[i]->event_list;
			while(ev){
				file << "* " << ev->day << " " << ev->time << " " << ev->title << endl;
				ev = ev->next;
			}
		}
		m = m->next;
	}
	file.close();
}