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
	std::list<Task*> schedulerQueue;
	std::vector<Task*> tasksWaiting;
	TaskScheduler(int, std::vector<Task*>); //OK
	void checkIncomingTasks(int);
	void RoundRobin();
	void displayResult(std::vector<Task*>); //OK
};

#endif