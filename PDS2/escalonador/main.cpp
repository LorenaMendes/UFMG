#include <iostream>
#include <vector>
#include "Task.hpp"

using namespace std;

bool compareByArrivalTime(Task *a, Task *b){
    if(a->arrival == b->arrival) return a->id < b->id; 
    return a->arrival < b->arrival;
}

int main(){

	int quantum, tasks;
	cin >> quantum >> tasks;

	// DEFININDO UM VETOR DE TASKS
	vector<Task*> taskVector;
	int _id, _arr, _dur;
	for (int i = 0; i < tasks; ++i){
		cin >> _id >> _arr >> _dur;
		Task * task = new Task(_id,_arr,_dur);
		task->inQueue = 1;
		taskVector.push_back(task);
	}

	// CRIANDO O TASKSCHEDULER
	TaskScheduler * taskScheduler = new TaskScheduler(quantum, taskVector);
	taskScheduler->totalTasks = tasks;
	for (int i = 0; i < tasks; ++i)
		taskScheduler->schedulerQueue.push_back(taskVector[i]);
	
	// ORDENANDO POR ARRIVAL TIME E ID
	sort(taskVector.begin(), taskVector.end(), compareByArrivalTime);
	taskScheduler->displayResult(taskVector);
	
	taskScheduler->RoundRobin();

	// LIBERANDO A MEMÓRIA
	for(Task * t : taskVector) delete t;
	delete taskScheduler;
    return 0;
}