#ifndef AGENDA_H
#define AGENDA_H
#include <iostream>
#include <string>
using namespace std;

typedef struct Event{
	int time;
	int day;
	int month;
	string title;
	struct Event * next;

	Event(int month, int day, int time, string title);
} Event;

typedef struct Day{
	int id;
	struct Event * event_list;

	Day(int id);
} Day;

typedef struct Month{
	int id;
	string name;
	int days;
	struct Day ** day_vector;
	struct Month * next;

	Month(int id, string name, int days);
	~Month();
} Month;

typedef struct Agenda{
	int year;
	struct Month * month_list;

	Agenda(int year);
	void InsertMonth(Month* new_month);
	void PrintAgenda();
	void InsertEvent(Event* event);
	Month* FindCurrentMonth(int m);
	void DeleteEvent(Event* event);
	Event* getEvent(int month, int day, int time);
	void ListMonthEvent(int month);
	bool IsValid(int month, int day, int hour);
	void SaveAgenda(string fileName);
	~Agenda();
} Agenda;

#endif