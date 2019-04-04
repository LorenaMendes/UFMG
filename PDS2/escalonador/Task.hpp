#ifndef TASK_H
#define TASK_H

#include <list>
#include <vector>
#include <iostream>
#include <algorithm>

struct Task{
	int id;
	int arrival;
	int duration;
	int end;
	bool inQueue;
	Task(int,int,int);
};

struct TaskScheduler{
	int quantum; //OK
	int totalTasks; //OK
	std::list<Task*> schedulerQueue; //OK
	std::vector<Task*> tasksWaiting; //OK
	TaskScheduler(int, std::vector<Task*>); //OK
	void checkIncomingTasks(int); //OK
	void RoundRobin(); //OK
	void displayResult(std::vector<Task*>); //OK

	void showlist(std::list<Task*> g);
};			

#endif