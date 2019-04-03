#include <iostream>
#include <vector>
#include "Task.hpp"

using namespace std;

int main(){

	int quantum, tasks;
	cin >> quantum >> tasks;

	// DEFININDO UM VETOR DE TASKS
	vector<Task*> taskVector;
	int _id, _arr, _dur;
	for (int i = 0; i < tasks; ++i){
		cin >> _id >> _arr >> _dur;
		Task * task = new Task(_id,_arr,_dur);
		taskVector.push_back(task);
	}

	// CRIANDO O TASKSCHEDULER
	TaskScheduler * taskScheduler = new TaskScheduler(quantum, taskVector);
	taskScheduler->totalTasks = tasks;
	// for (int i = 0; i < tasks; ++i)
	// 	taskScheduler->schedulerQueue.push_back(taskVector[i]);
	
	taskScheduler->RoundRobin();
	taskScheduler->displayResult(taskScheduler->tasksWaiting);

	// LIBERANDO A MEMÓRIA
	for(Task * t : taskVector) delete t;
	delete taskScheduler;
    return 0;
}