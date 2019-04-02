#include "Task.hpp"

bool compareByArrivalTime(Task *a, Task *b){
    if(a->arrival == b->arrival) return a->id < b->id; 
    return a->arrival < b->arrival;
}

Task::Task(int _id, int _arr, int _dur){
	id = _id;
	arrival = _arr;
	duration = _dur;
	inQueue = false;
	end = 0;
}

TaskScheduler::TaskScheduler(int _quant, std::vector<Task*> taskVector){
	quantum = _quant;
	tasksWaiting = taskVector;
	// ORDENANDO POR ARRIVAL TIME E ID
	sort(taskVector.begin(), taskVector.end(), compareByArrivalTime);
	taskScheduler->displayResult(taskVector);
}

void TaskScheduler::displayResult(std::vector<Task*> taskVector){
	for (int i = 0; i < int(taskVector.size()); ++i){
		std::cout << "Task " << taskVector[i]->id;
		std::cout << ", Duration: [" << taskVector[i]->arrival << ", ";
		std::cout << "<<final>>" << "]\n";
	}
}

void TaskScheduler::checkIncomingTasks(int time){
	// OLHO SE TEM TAREFAS PARA ANTES DE TIME
	for (unsigned int i = 0; i < this->tasksWaiting.size(); i++)
		if (this->tasksWaiting[i]->arrival <= time)
			// SE TEM, EU COLOCO NA LISTA
			this->taskScheduler.push_back(this->tasksWaiting[i]);
}

void TaskScheduler::RoundRobin(){
	int quant = this->quantum;
	int time = 0;
	
	checkIncomingTasks();
	while(time > 0){
		
	}
}
